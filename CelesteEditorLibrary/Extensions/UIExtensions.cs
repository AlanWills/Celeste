using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using FloatParseResult = System.Tuple<bool, float>;
using IntParseResult = System.Tuple<bool, int>;
using UIntParseResult = System.Tuple<bool, uint>;
using System.Windows.Controls;
using System.Windows.Data;
using BindingsKernel;
using CelesteEditor.Views;
using CelesteEditor.Windows;
using static CelesteEditor.Windows.UtilityWindows;

namespace CelesteEditor
{
    public static class UIExtensions
    {
        /// <summary>
        /// If the input is valid number, but lies outside of allowed range we can perform two different actions.
        /// kClampToRangeAndReturnTrue will clamp the number within the desired min and max and consider this a success case.
        /// kWarnAndReturnFalse will show a warning dialog telling the user the value violated the range and consider this a failure case.
        /// </summary>
        public enum ValidationMode
        {
            kClampToRangeAndReturnTrue,
            kWarnAndReturnFalse,
        }

        /// <summary>
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="view"></param>
        /// <returns></returns>
        public static T FindFirstParent<T>(this BaseView view) where T : DependencyObject
        {
            DependencyObject parent = VisualTreeHelper.GetParent(view);
            while (!(parent is T || parent == null))
            {
                parent = VisualTreeHelper.GetParent(parent);
            }

            return parent as T;
        }

        /// <summary>
        /// Looks for a child control within the inputted by name and type
        /// </summary>
        public static T FindFirstChild<T>(this DependencyObject parent, string name) where T : FrameworkElement
        {
            // confirm parent and name are valid.
            if (parent == null || string.IsNullOrEmpty(name))
            {
                CelDebug.Fail();
                return null;
            }

            if (parent is T && (parent as T).Name == name)
            {
                return parent as T;
            }

            T result = null;

            if (parent is FrameworkElement)
            {
                (parent as FrameworkElement).ApplyTemplate();
            }

            int childrenCount = VisualTreeHelper.GetChildrenCount(parent);
            for (int i = 0; i < childrenCount; i++)
            {
                var child = VisualTreeHelper.GetChild(parent, i);
                result = FindFirstChild<T>(child, name);

                if (result != null)
                {
                    break;
                }
            }

            return result;
        }

        /// <summary>
        /// Wrapper function for closing a DesktopWindow and setting the dialog result according to the input.
        /// </summary>
        /// <param name="result"></param>
        public static void CloseWindow(this BaseView view, WindowResult result)
        {
            EditorWindow window = view.FindFirstParent<EditorWindow>();

            if (window == null)
            {
                // We must be closing the main window since our view is not attached to a DesktopView
                Application.Current.MainWindow.Close();
            }
            else
            {
                window.CloseWithResult(result);
            }
        }

        /// <summary>
        /// Checks to see that the inputted string represents a number between the inputted min and max inclusive.
        /// </summary>
        /// <param name="inputtedString"></param>
        /// <returns>Returns false and 0 if there was an error.  Otherwise returns true and the parsed float value.</returns>
        public static FloatParseResult ValidateStringValue(
            this string inputtedString, 
            float min, 
            float max, 
            ValidationMode validationMode = ValidationMode.kWarnAndReturnFalse)
        {
            CelDebug.Assert(min < max);

            float output = 0;
            bool result = float.TryParse(inputtedString, out output);

            if (result)
            {
                if (validationMode == ValidationMode.kClampToRangeAndReturnTrue)
                {
                    output = MathUtils.Clamp(output, min, max);
                }
                else
                {
                    if (output < min)
                    {
                        MessageWindow("Value must be no less than " + min.ToString());
                        result = false;
                        output = 0;
                    }
                    else if (output > max)
                    {
                        MessageWindow("Value must be no greater than " + max.ToString());
                        result = false;
                        output = 0;
                    }
                }
            }
            else
            {
                // Not even numeric
                MessageWindow("Value must be a number no less than " + min.ToString() + " and no greater than " + max.ToString() + ".");
            }

            return new FloatParseResult(result, output);
        }

        /// <summary>
        /// Checks to see that the inputted string represents a number between the inputted min and max inclusive.
        /// </summary>
        /// <param name="inputtedString"></param>
        /// <returns>Returns false and 0 if there was an error.  Otherwise returns true and the parsed int value.</returns>
        public static IntParseResult ValidateStringValue(this string inputtedString, int min, int max)
        {
            CelDebug.Assert(min < max);

            int output = 0;
            bool result = int.TryParse(inputtedString, out output);

            if (result)
            {
                if (output < min)
                {
                    MessageWindow("Value must be no less than " + min.ToString());
                    result = false;
                }
                else if (output > max)
                {
                    MessageWindow("Value must be no greater than " + max.ToString());
                    result = false;
                }
            }
            else
            {
                // Not even numeric
                MessageWindow("Value must be a whole number no less than " + min.ToString() + " and no greater than " + max.ToString() + ".");
            }

            return new IntParseResult(result, output);
        }
        
        /// <summary>
        /// Checks to see that the inputted string represents a number between the inputted min and max inclusive.
        /// </summary>
        /// <param name="inputtedString"></param>
        /// <returns>Returns false and 0 if there was an error.  Otherwise returns true and the parsed uint value.</returns>
        public static UIntParseResult ValidateStringValue(
            this string inputtedString, 
            uint min, 
            uint max,
            ValidationMode validationMode = ValidationMode.kWarnAndReturnFalse)
        {
            CelDebug.Assert(min < max);

            uint output = 0;
            bool result = uint.TryParse(inputtedString, out output);

            if (result)
            {
                if (validationMode == ValidationMode.kClampToRangeAndReturnTrue)
                {
                    output = MathUtils.Clamp(output, min, max);
                }
                else
                {
                    if (output < min)
                    {
                        MessageWindow("Value must be no less than " + min.ToString());
                        result = false;
                        output = 0;
                    }
                    else if (output > max)
                    {
                        MessageWindow("Value must be no greater than " + max.ToString());
                        result = false;
                        output = 0;
                    }
                }
            }
            else
            {
                // Not even numeric
                MessageWindow("Value must be a whole number no less than " + min.ToString() + " and no greater than " + max.ToString() + ".");
            }

            return new UIntParseResult(result, output);
        }

        /// <summary>
        /// Clears the collection on the UI thread of the application.
        /// Use this function if you wish to clear a collection bound to UI (such as ObservableCollection), but are on a different thread.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name=""></param>
        /// <param name="item"></param>
        public static void ClearOnUIThread<T>(this ICollection<T> collection)
        {
            Action clearMethod = collection.Clear;
            Application.Current.Dispatcher.BeginInvoke(clearMethod);
        }

        /// <summary>
        /// Adds the inputted item on the UI thread of the application.
        /// Use this function if you wish to add an item to a collection bound to UI (such as ObservableCollection), but are on a different thread.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name=""></param>
        /// <param name="item"></param>
        public static void AddOnUIThread<T>(this ICollection<T> collection, T item)
        {
            Action<T> addMethod = collection.Add;
            Application.Current.Dispatcher.BeginInvoke(addMethod, item);
        }

        /// <summary>
        /// Removes the inputted item on the UI thread of the application.
        /// Use this function if you wish to remove an item to a collection bound to UI (such as ObservableCollection), but are on a different thread.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name=""></param>
        /// <param name="item"></param>
        public static void RemoveOnUIThread<T>(this ICollection<T> collection, T item)
        {
            Func<T, bool> removeMethod = collection.Remove;
            Application.Current.Dispatcher.BeginInvoke(removeMethod, item);
        }

        /// <summary>
        /// Removes the item at the inputted index on the UI thread of the application.
        /// Use this function if you wish to remove an item to a collection bound to UI (such as ObservableCollection), but are on a different thread.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name=""></param>
        /// <param name="item"></param>
        public static void RemoveAtOnUIThread<T>(this IList<T> collection, int index)
        {
            Action<int> removeAtMethod = collection.RemoveAt;
            Application.Current.Dispatcher.BeginInvoke(removeAtMethod, index);
        }

        /// <summary>
        /// Literally the worst.
        /// Combo boxes do not update display names of items, even when changed in the backend.
        /// The only way we can force an update is by changing the selected index.
        /// However, if we do that, we will change the values in the ViewModel which will cause other items to be nulled.
        /// So we subscribe to the on changed event, change the index and swallow the event to force the UI to update without changing the backend.
        /// </summary>
        /// <param name="comboBox"></param>
        public static void RefreshComboBoxText(this ComboBox comboBox)
        {
            // Unbind any data so properties are not set when this occurs
            BindingExpression source = comboBox.GetBindingExpression(ComboBox.SelectedItemProperty);
            BindingOperations.ClearBinding(comboBox, ComboBox.SelectedItemProperty);

            comboBox.SelectionChanged += Handle_SelectionChanged;
            int currentIndex = comboBox.SelectedIndex;
            comboBox.SelectedIndex = -1;
            comboBox.Items.Refresh();
            comboBox.SelectedIndex = currentIndex;
            comboBox.SelectionChanged -= Handle_SelectionChanged;

            if (source != null)
            {
                // Readd binding if it exists
                comboBox.SetBinding(ComboBox.SelectedItemProperty, source.ResolvedSourcePropertyName);
            }
        }

        private static void Handle_SelectionChanged(object sender, SelectionChangedEventArgs e) { e.Handled = true; }
    }
}