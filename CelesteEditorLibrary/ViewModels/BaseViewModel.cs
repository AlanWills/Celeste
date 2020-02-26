using BindingsKernel;
using System;
using System.ComponentModel;
using System.Diagnostics;

namespace CelesteEngineEditor.ViewModels
{
    /// <summary>
    /// A base class for a ViewModel which takes in an instance of a Model to then display.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class BaseViewModel<T> : Notifier where T : class
    {
        #region Properties and Fields

        protected T Model { get; private set; }

        #endregion

        public BaseViewModel(T modelInstance)
        {
            Model = modelInstance;
        }

        #region Equality Operators

        /// <summary>
        /// This ViewModel will be considered equal to a model, M, if the model instance the ViewModel represents and M are equal.
        /// </summary>
        /// <param name="viewModel"></param>
        /// <param name="model"></param>
        /// <returns></returns>
        public static bool operator ==(BaseViewModel<T> viewModel, T model)
        {
            return ((object)viewModel == model) || ((object)viewModel != null && viewModel.Model.Equals(model));
        }

        /// <summary>
        /// This ViewModel will be considered equal to a model, M, if the model instance the ViewModel represents and M are equal.
        /// </summary>
        /// <param name="model"></param>
        /// <param name="viewModel"></param>
        /// <returns></returns>
        public static bool operator ==(T model, BaseViewModel<T> viewModel)
        {
            return ((object)viewModel == model) || ((object)viewModel != null && viewModel.Model.Equals(model));
        }

        /// <summary>
        /// This ViewModel will be considered not equal to a model, M, if the model instance the ViewModel represents and M are not equal.
        /// </summary>
        /// <param name="viewModel"></param>
        /// <param name="model"></param>
        /// <returns></returns>
        public static bool operator !=(BaseViewModel<T> viewModel, T model)
        {
            return !(viewModel == model);
        }

        /// <summary>
        /// This ViewModel will be considered not equal to a model, M, if the model instance the ViewModel represents and M are not equal.
        /// </summary>
        /// <param name="model"></param>
        /// <param name="viewModel"></param>
        /// <returns></returns>
        public static bool operator !=(T model, BaseViewModel<T> viewModel)
        {
            return !(viewModel == model);
        }

        // Needed these two functions to satisfy a compiler warning, but we currently wish to not to do anything special with them

        public override bool Equals(object obj)
        {
            if (obj is T)
            {
                return this == (obj as T);
            }

            return this == obj;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        #endregion

        #region Explicit Casting

        /// <summary>
        /// An explicit operator to allow conversion to the underlying type this ViewModel is representing.
        /// </summary>
        /// <param name="viewModel"></param>
        public static explicit operator T(BaseViewModel<T> viewModel)
        {
            return viewModel.Model;
        }

        /// <summary>
        /// A function which casts the Model this ViewModel wraps to the inputted type.
        /// </summary>
        /// <typeparam name="K"></typeparam>
        /// <returns></returns>
        public K As<K>() where K : T
        {
            CelDebug.Assert(Model is K);
            return (K)Model;
        }

        #endregion
    }
}
