using BindingsKernel;
using CelesteEngineEditor.Core;
using CelesteEngineEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Editors
{
    public class HierarchySceneViewModel : HierarchyEntityViewModel
    {
        #region Properties and Fields

        private Screen Screen { get; }

        /// <summary>
        /// A string that will be displayed in the UI to the user.
        /// </summary>
        public string DisplayName
        {
            get { return Screen.Name; }
        }

        #endregion

        public HierarchySceneViewModel(Screen screen) : 
            base(screen)
        {
            Screen = screen;

            CreateGameObjectViewModels();
        }

        #region Game Object Management

        private void CreateGameObjectViewModels()
        {
            foreach (GameObject gameObject in Screen.GameObjects)
            {
                if (!ChildGameObjectLookup.ContainsKey(gameObject.Name))
                {
                    HierarchyGameObjectViewModel gameObjectViewModel = gameObject is PrefabInstance ? new HierarchyPrefabInstanceViewModel(gameObject as PrefabInstance) : 
                                                                                                      new HierarchyGameObjectViewModel(gameObject);

                    ChildGameObjectLookup.Add(gameObject.Name, gameObjectViewModel);
                    ChildGameObjects.Add(gameObjectViewModel);
                }
                else
                {
                    CelDebug.Fail();
                }
            }
        }

        #endregion

        #region Virtual Functions

        protected override void OnAddGameObject(HierarchyGameObjectViewModel childGameObject)
        {
            base.OnAddGameObject(childGameObject);

            Screen.GameObjects.Add(childGameObject.Entity as GameObject);

            Project.SetDirty(Screen);
        }

        #endregion
    }
}
