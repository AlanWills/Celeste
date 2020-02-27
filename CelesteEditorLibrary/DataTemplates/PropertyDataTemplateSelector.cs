using CelesteEditor.Data;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEditor.DataTemplates
{
    public class PropertyDataTemplateSelector : DataTemplateSelector
    {
        #region Properties and Fields

        private static List<PropertyDataTemplate> templates;
        /// <summary>
        /// All of the available property data templates that will allow us to customise the UI based on the type of the propery.
        /// </summary>
        private static List<PropertyDataTemplate> Templates
        {
            get
            {
                if (templates == null)
                {
                    LoadPropertyDataTemplates(Application.Current.Resources, true);
                }

                return templates;
            }
        }
        
        /// <summary>
        /// The fallback data template to use if we cannot find a matching custom template.
        /// </summary>
        public DataTemplate FallbackDataTemplate { get; set; }

        #endregion

        #region Initialization Functions
        
        /// <summary>
        /// Attempt to find all property data templates in the inputted dictionary's resources and merged dictionaries.
        /// This is a recursive function, so all property data templates will loaded from all sub dictionaries.
        /// The second flag determines whether we clear our existing cache of Templates.  Usually when you call this you want this to be true.
        /// </summary>
        /// <param name="dictionary"></param>
        public static void LoadPropertyDataTemplates(ResourceDictionary dictionary, bool clearExisting = true)
        {
            templates = templates ?? new List<PropertyDataTemplate>();
            templates = !clearExisting ? templates : new List<PropertyDataTemplate>();

            foreach (DictionaryEntry entry in dictionary)
            {
                if (entry.Value is PropertyDataTemplate)
                {
                    templates.Add(entry.Value as PropertyDataTemplate);
                }
            }

            foreach (ResourceDictionary childDictionary in dictionary.MergedDictionaries)
            {
                // Don't clear our existing templates for recursive calls
                LoadPropertyDataTemplates(childDictionary, false);
            }
        }

        #endregion

        #region Overrides

        /// <summary>
        /// Attempt to find a corresponding matching property data template for the inputted property data.
        /// If not, we use the fallback data template.
        /// </summary>
        /// <param name="item"></param>
        /// <param name="container"></param>
        /// <returns></returns>
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            ResourceDictionary dictionary = Application.Current.Resources;

            if (item is PropertyData)
            {
                PropertyData data = item as PropertyData;
                
                // First try and be specific with a match - if we find a data template exactly matching we use that
                if (Templates.Exists(x => data.Type == (x.DataType as Type)))
                {
                    return Templates.Find(x => data.Type == (x.DataType as Type));
                }
                // Otherwise we search for data templates for base types
                else if (Templates.Exists(x => (x.DataType as Type).IsAssignableFrom(data.Type)))
                {
                    return Templates.Find(x => (x.DataType as Type).IsAssignableFrom(data.Type));
                }

                // Otherwise we resort to the fallback data template
                return FallbackDataTemplate ?? base.SelectTemplate(item, container);
            }
            else
            {
                return base.SelectTemplate(item, container);
            }
        }

        #endregion
    }
}
