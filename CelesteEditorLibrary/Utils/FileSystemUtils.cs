using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using SaveFileDialog = Microsoft.Win32.SaveFileDialog;
using OpenFileDialog = Microsoft.Win32.OpenFileDialog;
using System.Text;
using BindingsKernel;
using Path = System.IO.Path;
using Microsoft.WindowsAPICodePack.Dialogs;

namespace CelesteEngineEditor
{
	/// <summary>
	/// Static class which contains extra helper functions to extend the current C# API.
	/// </summary>
	public static class FileSystemUtils
	{
		/// <summary>
		/// An enum we use to control the select mode of file picker dialogs
		/// </summary>
		public enum SelectType
		{
			kSingleSelect,
			kMultiSelect
		}

		/// <summary>
		/// Takes in a directory path and assures it's uniqueness by looking through all sibling directories and appending a counter until the name is unique.
		/// Returns a guaranteed unique path in the same parent folder.
		/// </summary>
		/// <param name="desiredDirectoryFullPath"></param>
		/// <returns></returns>
		public static string CreateUniqueDirectoryName(string desiredDirectoryFullPath)
		{
            if (string.IsNullOrWhiteSpace(desiredDirectoryFullPath))
            {
                CelDebug.Fail("Cannot input a null or whitespace string");
                return "";
            }

            string output = desiredDirectoryFullPath;
			string parentDirectoryPath = Directory.GetParent(desiredDirectoryFullPath).FullName;

			int counter = 1;
			List<string> directories = Directory.EnumerateDirectories(parentDirectoryPath).ToList();
			if (directories.Exists(x => Path.GetFullPath(x) == Path.GetFullPath(desiredDirectoryFullPath)))
			{
				while (directories.Exists(x => Path.GetFullPath(x) == Path.GetFullPath(desiredDirectoryFullPath + "_" + counter)))
				{
					// Whilst the folder contains a sub folder whose name is the directoryName + "_" + counter, we continuing incrementing
					counter++;
					CelDebug.Assert(counter < 100, "Potential infinite loop");
				}

				output += "_" + counter;
			}

			return output;
		}

		/// <summary>
		/// Takes in a file path and assures it's uniqueness by looking through all sibling files of the same type and appending a counter until the name is unique.
		/// Returns a guaranteed unique path in the same parent folder.
		/// </summary>
		/// <param name="desiredFileFullPath"></param>
		/// <returns></returns>
		public static string CreateUniqueFileName(string desiredFileFullPath)
		{
            if (string.IsNullOrWhiteSpace(desiredFileFullPath))
            {
                CelDebug.Fail("Cannot input a null or whitespace string");
                return "";
            }

			string extensionLessFileName = Path.GetFileNameWithoutExtension(desiredFileFullPath);
			string fileExtension = Path.GetExtension(desiredFileFullPath);
			string parentDirectoryPath = Directory.GetParent(desiredFileFullPath).FullName;
			string output = desiredFileFullPath;

			int counter = 1;
			List<string> files = Directory.EnumerateFiles(parentDirectoryPath, "*" + fileExtension).ToList();
			if (files.Exists(x => Path.GetFileNameWithoutExtension(x) == extensionLessFileName))
			{
				while (files.Exists(x => Path.GetFileNameWithoutExtension(x) == (extensionLessFileName + "_" + counter)))
				{
					// Whilst the folder contains a file whose name is the fileName + "_" + counter, we continuing incrementing
					counter++;
					CelDebug.Assert(counter < 100, "Potential infinite loop");
				}

                if(fileExtension.Length>0 && fileExtension.Length< output.Length)
				    output = output.Remove(output.Length - fileExtension.Length);
				output += "_" + counter + fileExtension;
			}

			CelDebug.Assert(!File.Exists(output), "Uniqueness failed");
			CelDebug.Assert(Path.GetExtension(output) == Path.GetExtension(desiredFileFullPath));
			return output;
		}

		/// <summary>
		/// Utility function for checking whether the inputted folder exists, deleting if it does and then recreating it.
		/// </summary>
		/// <param name="modelsFolder"></param>
		public static void CleanDirectory(string folderFullPath)
		{
			if (Directory.Exists(folderFullPath))
			{
				// Delete the folder and subfolders if it already exists
				Directory.Delete(folderFullPath, true);
			}

			// Recreate the folder
			Directory.CreateDirectory(folderFullPath);
		}

        /// <summary>
        /// Utility function for clearing or creating a file and all the parent directories if they do not exist.
        /// Use this function when you need a fresh version of the new file and you also need parent directories created as you are unsure of its existence.
        /// </summary>
        /// <param name="filePath"></param>
        public static void CleanFile(string filePath)
        {
            DirectoryInfo parentDirectory = Directory.GetParent(filePath);
            if (!parentDirectory.Exists)
            {
                parentDirectory.Create();
            }

            File.WriteAllText(filePath, "");
        }

        /// <summary>
        /// Creates an OpenFileDialog to allow the user to pick files ending in the inputted file extension.
        /// Returns a list of all of the files picked which pass the inputted validationFunction.
        /// Will return an empty list of none of the picked files are valid.
        /// </summary>
        /// <param name="fileExtension"></param>
        /// <param name="selectType"></param>
        /// <param name="validationFunction"></param>
        /// <returns></returns>
        public static Tuple<DialogResult, List<string>> PickFilesForLoading(string displayNameOfFileTypes, List<string> fileExtensions, Func<string, bool> validationFunction = null, bool multiSelect = true)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = multiSelect;

            string filter = CreateFilterString(displayNameOfFileTypes, fileExtensions);
            dialog.DefaultExt = filter;
            dialog.Filter = filter;

            bool? result = dialog.ShowDialog();
			List<string> filenames = new List<string>(dialog.FileNames);

			if (result.HasValue && result.Value && (validationFunction != null))
			{
				filenames.RemoveAll(x => !validationFunction(x));
			}

            return new Tuple<DialogResult, List<string>>((result.HasValue && result.Value) ? DialogResult.OK : DialogResult.Cancel, filenames);
        }

        /// <summary>
        /// Creates an OpenFileDialog to allow the user to pick a single file ending in the inputted file extension.
        /// If the chosen file passes the validation function we return it, otherwise we return the empty string.
        /// </summary>
        /// <param name="fileExtension"></param>
        /// <param name="selectType"></param>
        /// <param name="validationFunction"></param>
        /// <returns></returns>
        public static Tuple<DialogResult, string> PickFileForLoading(
            string displayNameOfFileTypes, 
            List<string> fileExtensions, 
            Func<string, bool> validationFunction = null, 
            string initialDirectory = "")
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;

            string filter = CreateFilterString(displayNameOfFileTypes, fileExtensions);
            dialog.DefaultExt = filter;
            dialog.Filter = filter;
            dialog.InitialDirectory = initialDirectory;

            bool? result = dialog.ShowDialog();
			string fileName = dialog.FileName;

			if (result.HasValue && result.Value && (validationFunction != null))
			{
				fileName = validationFunction(fileName) ? fileName : "";
			}

            return new Tuple<DialogResult, string>((result.HasValue && result.Value) ? DialogResult.OK : DialogResult.Cancel, fileName);
        }

        /// <summary>
        /// Creates a SaveFileDialog to allow the user to pick a file location for saving ending in the inputted file extension.
        /// Returns the chosen file if it passes the validationFunction and is a valid OS path or an empty string if not.
        /// </summary>
        /// <param name="fileExtension"></param>
        /// <param name="validationFunction"></param>
        /// <returns></returns>
        public static Tuple<DialogResult, string> PickFileForSaving(
            string displayNameOfFileTypes, 
            List<string> fileExtensions, 
            Func<string, bool> validationFunction = null, 
            string suggestedFileName = "")
        {
            SaveFileDialog dialog = new SaveFileDialog();

            string filter = CreateFilterString(displayNameOfFileTypes, fileExtensions);
            dialog.DefaultExt = filter;
            dialog.FileName = suggestedFileName;
            dialog.Filter = filter;

			bool? result = dialog.ShowDialog();
			string fileName = dialog.FileName;

            if (result.HasValue && result.Value && (validationFunction != null))
            {
                fileName = IsValidOSPath(fileName) && validationFunction(fileName) ? fileName : "";
            }

            return new Tuple<DialogResult, string>((result.HasValue && result.Value) ? DialogResult.OK : DialogResult.Cancel, fileName);
        }

        /// <summary>
        /// Creates a dialog to allow the user to pick a directory.
        /// Returns the dialog result and (chosen directory if it passes the validationFunction and is a valid OS path) or (an empty string if not).
        /// </summary>
        /// <param name="validationFunction"></param>
        /// <returns></returns>
        public static Tuple<CommonFileDialogResult, string> PickDirectory(
            Func<string, bool> validationFunction = null,
            string initialDirectory = "")
        {
            using (CommonOpenFileDialog dialog = new CommonOpenFileDialog())
            {
                string path = "";
                dialog.InitialDirectory = initialDirectory;
                dialog.IsFolderPicker = true;
                CommonFileDialogResult result = dialog.ShowDialog();

                if (result == CommonFileDialogResult.Ok)
                {
                    path = IsValidOSPath(dialog.FileName) ? dialog.FileName : "";
                    path = (validationFunction == null || validationFunction.Invoke(dialog.FileName)) ? path : "";
                }

                return new Tuple<CommonFileDialogResult, string>(result, path);
            }
        }

        /// <summary>
        /// Generates the correct filter string for a file picker using the inputted file extensions.
        /// The display name of file types is the user friendly display name that will be presented.
        /// </summary>
        /// <param name="displayNameOfFileTypes"></param>
        /// <param name="fileExtensions"></param>
        /// <returns></returns>
        public static string CreateFilterString(string displayNameOfFileTypes, List<string> fileExtensions)
        {
            if (fileExtensions == null ||
                fileExtensions.Count == 0)
            {
                // If we have not provided any file extensions, don't create a filter string
                return "";
            }

            StringBuilder filter = new StringBuilder(displayNameOfFileTypes + " (");
            CelDebug.AssertNotNull(fileExtensions);

            if (fileExtensions != null)
            {
                for (int i = 0, n = fileExtensions.Count; i < n; ++i)
                {
                    filter.Append("*" + fileExtensions[i]);

                    if (i < (n - 1))
                    {
                        filter.Append(";");
                    }
                }
            }
            filter.Append(")|");

            foreach (string fileExtension in fileExtensions)
            {
                filter.Append("*" + fileExtension + ";");
            }

            return filter.ToString();
        }

		/// <summary>
		/// A function which attempts to access a file to determine if it is in use by another process.
		/// Returns true if the file is currently in use and false otherwise (including if it doesn't exist).
		/// </summary>
		/// <param name="fullFilePath"></param>
		/// <returns></returns>
		public static bool IsFileLocked(string fullFilePath)
		{
			if (!File.Exists(fullFilePath))
			{
				return false;
			}

			FileStream stream = null;

			try
			{
				stream = File.Open(fullFilePath, FileMode.Open, FileAccess.Read, FileShare.None);
			}
			catch
			{
				// The file is unavailable because it is:
				// still being written to
				// or being processed by another thread
				// or does not exist (has already been processed)
				return true;
			}
			finally
			{
				stream?.Close();
			}

			// File is not locked
			return false;
		}

		/// <summary>
		/// Copies a file from one place to another without throwing exceptions.
		/// </summary>
		/// <returns>
		/// true if the file was copied
		/// </returns>
		public static bool CopyFileNoThrow(string sourceFileName, string destFileName, bool overwrite)
		{
            try
            {
                File.Copy(sourceFileName, destFileName, overwrite);
            }
            catch { return false; }

			// Ensure the file now exists
			return File.Exists(destFileName);
		}

		/// <summary>
		/// Deletes a file without throwing exceptions.
		/// </summary>
		/// <returns>
		/// true if the file was deleted
		/// </returns>
		public static bool DeleteFileNoThrow(string fileName)
		{
            try
            {
                File.Delete(fileName);
            }
            catch { return false; }

			// Ensure the file doesn't exist
			return !File.Exists(fileName);
		}

        /// <summary>
        /// Deletes a file without throwing exceptions.
        /// </summary>
        /// <returns>
        /// true if the file was deleted
        /// </returns>
        public static bool DeleteFileNoThrow(this FileInfo fileInfo)
        {
            if (fileInfo == null)
            {
                CelDebug.Fail();
                return false;
            }

            try
            {
                fileInfo.Delete();
                fileInfo.Refresh();
            }
            catch { return false; }

            // Ensure the file doesn't exist
            return !fileInfo.Exists;
        }

        /// <summary>
        /// Takes an inputted filesystem path (directory or file) and returns whether it is valid for windows.
        /// This means it must be less than 260 characters and the directory name must be less than 248 characters.
        /// Does not do checks on the existence of the file.
        /// </summary>
        /// <param name="inputPath"></param>
        /// <returns></returns>
        public static bool IsValidOSPath(string inputPath)
		{
			try
			{
				// This will throw exceptions if the path is bad
				Path.GetFullPath(inputPath);
				return true;
			}
			catch
			{
				return false;
			}
		}

        /// <summary>
        /// Returns the inputted full path without the extension.
        /// E.g. Parent/File.txt -> Parent/File
        /// If the input is null or the empty string, this function will return the empty string.
        /// If the input is a directory/filepath without extension, it will return the input string
        /// E.g. Parent/File -> Parent/File
        /// </summary>
        /// <param name="inputtedFilePath"></param>
        /// <returns></returns>
        public static string GetFilePathWithoutExtension(string inputtedFilePath)
        {
            if (string.IsNullOrEmpty(inputtedFilePath))
            {
                return "";
            }

            string fileExtension = Path.GetExtension(inputtedFilePath);
            return inputtedFilePath.Substring(0, inputtedFilePath.Length - fileExtension.Length);
        }
	}
}
