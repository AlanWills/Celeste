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
    public class HierarchyGameObjectViewModel : HierarchyEntityViewModel
    {
        #region Properties and Fields

        private GameObject GameObject { get; }

        /// <summary>
        /// A string that will be displayed in the UI to the user.
        /// </summary>
        public string DisplayName
        {
            get { return GameObject.Name; }
        }

        #region Transform Information

        public Vector3 Translation
        {
            get { return GameObject.Translation; }
            set { GameObject.Translation = value; }
        }

        public float Rotation
        {
            get { return GameObject.Rotation; }
            set { GameObject.Rotation = value; }
        }

        public Vector3 Scale
        {
            get { return GameObject.Scale; }
            set { GameObject.Scale = value; }
        }

        public Vector3 WorldTranslation
        {
            get { return GameObject.WorldTranslation; }
            set { GameObject.WorldTranslation = value; }
        }

        public float WorldRotation
        {
            get { return GameObject.WorldRotation; }
            set { GameObject.WorldRotation = value; }
        }

        public Vector3 WorldScale
        {
            get { return GameObject.WorldScale; }
            set { GameObject.WorldScale = value; }
        }

        #endregion

        #endregion

        public HierarchyGameObjectViewModel(GameObject gameObject) : 
            base(gameObject)
        {
            GameObject = gameObject;

            CreateChildGameObjectViewModels();
        }

        #region Game Object Management

        private void CreateChildGameObjectViewModels()
        {
            foreach (GameObject gameObject in GameObject.ChildGameObjects)
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

            GameObject.ChildGameObjects.Add(childGameObject.Entity as GameObject);

            Project.SetDirty(GameObject);
        }

        #endregion
    }
}
