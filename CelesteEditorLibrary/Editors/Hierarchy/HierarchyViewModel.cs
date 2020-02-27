using BindingsKernel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CelesteEditor.Editors
{
    public class HierarchyViewModel : EditorViewModel
    {
        #region Properties and Fields

        private const char FIELD_DELIMITER = ',';
        private const char VECTOR_DELIMITER = '/';
        private const string MESSAGE_END_DELIMITER = "END";

        private HierarchyEntityViewModel selectedItem;
        /// <summary>
        /// A reference to the current selected item within the hierarchy.
        /// </summary>
        public HierarchyEntityViewModel SelectedItem
        {
            get { return selectedItem; }
            set
            {
                if (selectedItem != value)
                {
                    if (selectedItem != null)
                    {
                        selectedItem.IsSelected = false;
                    }

                    selectedItem = value;

                    if (selectedItem != null)
                    {
                        selectedItem.IsSelected = true;
                    }

                    Editor.OpenEditorForObject(selectedItem.Entity);

                    NotifyOnPropertyChanged(nameof(SelectedItem));
                }
            }
        }

        /// <summary>
        /// A list of scenes contained within the hierarchy.
        /// </summary>
        public ObservableCollection<HierarchySceneViewModel> Scenes { get; } = new ObservableCollection<HierarchySceneViewModel>();

        private Dictionary<string, HierarchySceneViewModel> SceneLookup { get; } = new Dictionary<string, HierarchySceneViewModel>();

        private Socket socket = new Socket(SocketType.Stream, ProtocolType.Tcp) { ReceiveTimeout = 3000 };
        private bool running; 

        #endregion

        public HierarchyViewModel(object targetObject) :
            base(targetObject)
        {
            TryConnect();
        }

        #region Editor Overrides

        protected override void OnTargetObjectChanged()
        {
            base.OnTargetObjectChanged();

            TryAddScene(TargetObject as Screen);
        }

        #endregion

        #region Scene Management

        public bool HasScene(Screen screen)
        {
            return SceneLookup.ContainsKey(screen.Name);
        }

        public void TryAddScene(Screen screen)
        {
            if (!HasScene(screen))
            {
                HierarchySceneViewModel sceneViewModel = new HierarchySceneViewModel(screen);

                SceneLookup.Add(screen.Name, sceneViewModel);
                Scenes.Add(sceneViewModel);
            }
        }

        #endregion

        #region Creation Functions

        public void CreateNewGameObject(HierarchyEntityViewModel entityViewModel)
        {
            CelDebug.AssertNotNull(entityViewModel);

            GameObject gameObject = new GameObject("New GameObject " + (entityViewModel.ChildGameObjects.Count + 1).ToString());
            HierarchyGameObjectViewModel hierarchyGameObjectViewModel = new HierarchyGameObjectViewModel(gameObject);
            entityViewModel.AddGameObjectOnUIThread(hierarchyGameObjectViewModel);

            SelectedItem = hierarchyGameObjectViewModel;
        }

        #endregion

        #region Data Synchronization

        private void TryConnect()
        {
            if (!socket.Connected)
            {
                SocketAsyncEventArgs eventArgs = new SocketAsyncEventArgs();
                eventArgs.RemoteEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 13000);
                eventArgs.Completed += (o, e) => { TryConnect(); };
                socket.ConnectAsync(eventArgs);
            }
            else
            {
                running = true;
                ThreadPool.QueueUserWorkItem((object obj) => ListenForData());
            }
        }

        private void ListenForData()
        {
            bool messageComplete;
            StringBuilder builder = new StringBuilder(256);

            while (running)
            {
                messageComplete = false;
                builder.Clear();

                do
                {
                    byte[] bytes = new byte[256];
                    try
                    {
                        int read = socket.Receive(bytes);
                        string translated = Encoding.ASCII.GetString(bytes, 0, read);

                        messageComplete = translated.EndsWith(MESSAGE_END_DELIMITER);

                        // Translate data bytes to a ASCII string.
                        builder.Append(translated);
                    }
                    catch (SocketException socketException)
                    {
                        if (socketException.SocketErrorCode == SocketError.TimedOut)
                        {
                            socket.Disconnect(true);
                            running = false;

                            Scenes.ClearOnUIThread();
                            SceneLookup.Clear();

                            TryConnect();

                            return;
                        }
                    }
                }
                while (!messageComplete);

                string content = builder.ToString();
                builder.Clear();

                int startDelimiter = content.IndexOf("[[");
                HashSet<string> sceneNames = new HashSet<string>();

                while (startDelimiter > -1)
                {
                    int endDelimiter = content.IndexOf("]]", startDelimiter);

                    HierarchySceneViewModel viewModel = ParseSceneData(content.Substring(startDelimiter + 2, endDelimiter - startDelimiter - 2));
                    sceneNames.Add(viewModel.DisplayName);

                    // Separator line between scenes
                    builder.AppendLine();

                    startDelimiter = content.IndexOf("[[", endDelimiter);
                    endDelimiter = content.IndexOf("]]", endDelimiter + 2);
                }

                // Remove all the old scenes that are no longer present in the running game
                for (int i = Scenes.Count - 1; i >= 0; --i)
                {
                    if (!sceneNames.Contains(Scenes[i].DisplayName))
                    {
                        SceneLookup.Remove(Scenes[i].DisplayName);
                        Scenes.RemoveAtOnUIThread(i);
                    }
                }
            }
        }

        #endregion

        #region Data Parsing

        private HierarchySceneViewModel ParseSceneData(string sceneData)
        {
            int currentIndex = 0;
            int nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

            string sceneName = sceneData.Substring(currentIndex, nextIndex - currentIndex);
            bool scenePresent = SceneLookup.ContainsKey(sceneName);

            HierarchySceneViewModel sceneViewModel = scenePresent ? SceneLookup[sceneName] : new HierarchySceneViewModel(new Screen(sceneName));

            currentIndex = nextIndex + 1;
            nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

            HashSet<string> childNames = new HashSet<string>();

            int children;
            if (int.TryParse(sceneData.Substring(currentIndex, nextIndex - currentIndex), out children))
            {
                for (int i = 0; i < children; ++i)
                {
                    currentIndex = nextIndex + 1;
                    nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                    HierarchyGameObjectViewModel childGameObject = ParseGameObject(sceneData, sceneViewModel, ref currentIndex, ref nextIndex);
                    childNames.Add(childGameObject.DisplayName);
                }
            }
            else
            {
                Debug.Fail("Failed to convert child count.");
            }

            if (!scenePresent)
            {
                Scenes.AddOnUIThread(sceneViewModel);
                SceneLookup.Add(sceneName, sceneViewModel);
            }

            // Remove all the old game objects that are no longer present in the scene
            for (int i = sceneViewModel.ChildGameObjects.Count - 1; i >= 0; --i)
            {
                if (!childNames.Contains(sceneViewModel.ChildGameObjects[i].DisplayName))
                {
                    SceneLookup.Remove(sceneViewModel.ChildGameObjects[i].DisplayName);
                    sceneViewModel.RemoveGameObjectOnUIThread(sceneViewModel.ChildGameObjects[i]);
                }
            }

            return sceneViewModel;
        }

        private HierarchyGameObjectViewModel ParseGameObject(string sceneData, HierarchyEntityViewModel parent, ref int currentIndex, ref int nextIndex)
        {
            string gameObjectName = sceneData.Substring(currentIndex, nextIndex - currentIndex);
            bool gameObjectPresent = parent.HasChildGameObject(gameObjectName);

            HierarchyGameObjectViewModel gameObjectViewModel = gameObjectPresent ? parent.FindChildGameObject(gameObjectName) : new HierarchyGameObjectViewModel(new GameObject(gameObjectName));

            // Local Translation
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                Vector3 localTranslation = new Vector3();
                if (TryParseVector3(sceneData.Substring(currentIndex, nextIndex - currentIndex), ref localTranslation))
                {
                    gameObjectViewModel.Translation = localTranslation;
                }
            }

            // Local Rotation
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                if (float.TryParse(sceneData.Substring(currentIndex, nextIndex - currentIndex), out float localRotation))
                {
                    gameObjectViewModel.Rotation = localRotation;
                }
            }

            // Local Scale
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                Vector3 localScale = new Vector3();
                if (TryParseVector3(sceneData.Substring(currentIndex, nextIndex - currentIndex), ref localScale))
                {
                    gameObjectViewModel.Scale = localScale;
                }
            }

            // World Translation
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                Vector3 worldTranslation = new Vector3();
                if (TryParseVector3(sceneData.Substring(currentIndex, nextIndex - currentIndex), ref worldTranslation))
                {
                    gameObjectViewModel.WorldTranslation = worldTranslation;
                }
            }

            // World Rotation
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                if (float.TryParse(sceneData.Substring(currentIndex, nextIndex - currentIndex), out float worldRotation))
                {
                    gameObjectViewModel.WorldRotation = worldRotation;
                }
            }

            // World Scale
            {
                currentIndex = nextIndex + 1;
                nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                Vector3 worldScale = new Vector3();
                if (TryParseVector3(sceneData.Substring(currentIndex, nextIndex - currentIndex), ref worldScale))
                {
                    gameObjectViewModel.WorldScale = worldScale;
                }
            }

            HashSet<string> childNames = new HashSet<string>();

            currentIndex = nextIndex + 1;
            nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

            int children;
            if (int.TryParse(sceneData.Substring(currentIndex, nextIndex - currentIndex), out children))
            {
                for (int i = 0; i < children; ++i)
                {
                    currentIndex = nextIndex + 1;
                    nextIndex = sceneData.IndexOf(FIELD_DELIMITER, currentIndex);

                    HierarchyGameObjectViewModel childGameObject = ParseGameObject(sceneData, gameObjectViewModel, ref currentIndex, ref nextIndex);
                    childNames.Add(childGameObject.DisplayName);
                }
            }
            else
            {
                Debug.Fail("Failed to convert child count.");
            }

            if (!gameObjectPresent)
            {
                parent.AddGameObjectOnUIThread(gameObjectViewModel);
            }

            // Remove all the old game objects that are no longer present in the parent
            for (int i = gameObjectViewModel.ChildGameObjects.Count - 1; i >= 0; --i)
            {
                if (!childNames.Contains(gameObjectViewModel.ChildGameObjects[i].DisplayName))
                {
                    gameObjectViewModel.RemoveGameObjectOnUIThread(gameObjectViewModel.ChildGameObjects[i]);
                }
            }

            return gameObjectViewModel;
        }

        private bool TryParseVector3(string vector3, ref Vector3 vector)
        {
            string[] numbers = vector3.Split(VECTOR_DELIMITER);
            if (numbers.Length != 3)
            {
                CelDebug.Fail("3 numeric entries do not exist in vector string.");
                return false;
            }

            if (float.TryParse(numbers[0], out float x))
            {
                vector.X = x;
            }
            else
            {
                CelDebug.Fail("Failed to parse X component of vector.");
                return false;
            }

            if (float.TryParse(numbers[1], out float y))
            {
                vector.Y = y;
            }
            else
            {
                CelDebug.Fail("Failed to parse Y component of vector.");
                return false;
            }

            if (float.TryParse(numbers[2], out float z))
            {
                vector.Z = z;
            }
            else
            {
                CelDebug.Fail("Failed to parse Z component of vector.");
                return false;
            }

            return true;
        }

        #endregion
    }
}
