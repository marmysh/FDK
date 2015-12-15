﻿namespace QuotesCsvExporter
{
    using System;
    using System.Windows.Forms;
    using SoftFX.Extended;

    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // Bootstrap FDK libraries
            Bootstrapper.Initialize();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new QuotesExporter());
        }
    }
}