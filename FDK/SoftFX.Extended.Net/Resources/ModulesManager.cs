﻿namespace SoftFX.Extended.Resources
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Reflection;
    using System.Threading;

    class ModulesManager
    {
        public ModulesManager(ModulesProvider provider)
        {
            if (provider == null)
                throw new ArgumentNullException(nameof(provider));

            this.provider = provider;

            Modules = provider.Modules.ToDictionary(k => k.Name);
        }

        public void Extract()
        {
            TraceUtils.WriteLine("ModuleManager.Extract");

            AssemblyDirectory = Library.Path;

            if (string.IsNullOrEmpty(AssemblyDirectory) || (DirectoryExists(AssemblyDirectory) && Directory.GetFiles(AssemblyDirectory).Length > 0))
                return;

            var mutexName = string.Format(@"Global\{0}-{1}", Id, Library.Id);
            var mutex = new Mutex(false, mutexName);
            mutex.WaitOne();

            try
            {
                CreateDirectory(AssemblyDirectory);
                Modules["AnyCPU_zip"].Extract(AssemblyDirectory);
                if (!Environment.Is64BitProcess)
                {
                    Modules["x32_zip"].Extract(AssemblyDirectory);
                }
                else
                {
                    Modules["x64_zip"].Extract(AssemblyDirectory);
                }
            }
            finally
            {
                mutex.ReleaseMutex();
                mutex.Dispose();
            }
        }

        public void ExtractUnderlyingFiles(string location)
        {
            CreateDirectory(location);
            var x86Path = Path.Combine(location, "x86");
            var x64Path = Path.Combine(location, "x64");
            CreateDirectory(x86Path);
            CreateDirectory(x64Path);

            Modules["AnyCPU_zip"].Extract(x86Path);
            Modules["AnyCPU_zip"].Extract(x64Path);
            Modules["x32_zip"].Extract(x86Path);
            Modules["x64_zip"].Extract(x64Path);
        }

        static bool DirectoryExists(string path)
        {
            var info = new DirectoryInfo(path);
            return info.Exists;
        }

        public Assembly LoadAssembly(string assemblyName)
        {
            Assembly assembly = null;

            try
            {
                if (assemblyName.EndsWith(".resources"))
                    assemblyName = assemblyName.Substring(0, assemblyName.LastIndexOf('.'));
                assembly = Assembly.LoadFile(Path.Combine(AssemblyDirectory, assemblyName + ".dll"));
            }
            catch(Exception ex)
            {
                TraceUtils.WriteLine("Error loading: '{0}' with exception: {1}", assemblyName, ex);
            }

            return assembly;
        }

        static void CreateDirectory(string path)
        {
            TraceUtils.WriteLine("Create directory: '{0}'", path);
            var items = path.Split(Path.DirectorySeparatorChar);
            path = items[0] + Path.DirectorySeparatorChar;
            var count = items.Length;
            for (var index = 1; index < count; ++index)
            {
                var item = items[index];
                path = Path.Combine(path, item);
                if (!Directory.Exists(path))
                    Directory.CreateDirectory(path);
            }
        }

        #region Members

        readonly Dictionary<string, StaticPropertyInfoModuleSource> Modules;
        readonly ModulesProvider provider;
        private string AssemblyDirectory;

        #endregion

        #region Constants

        const string Id = "{41C5D963-25E6-4BC2-B814-B686408B5ABD}";
        const string Info = ".info";

        #endregion
    }
}
