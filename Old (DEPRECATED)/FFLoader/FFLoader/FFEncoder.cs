﻿using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using FFLoader.Helpers;

namespace FFLoader
{
    internal class FFEncoder
    {
        /// <summary>
        /// The timer for the encoding process.
        /// </summary>
        internal static Stopwatch Timer = new Stopwatch();

        /// <summary>
        /// Attmpts to start the process and will catch FFLoader exceptions if they occur.
        /// </summary>
        /// <param name="log">Instace of StreamWriter logger.</param>
        /// <param name="process">Instance of the process.</param>
        /// <param name="sb">Instace of the AviSynth+ error StringBuilder.</param>
        /// <param name="ffloader">Instance of FFLoader.</param>
        internal static void TryStartProcess(StreamWriter log, Process process, StringBuilder sb, FFLoaderBase ffloader)
        {
            try
            {
                FFHelper.FFMpegPathNullOrMissing(ffloader.FFMpegPath);
                FFHelper.InputFileNullOrMissing(ffloader.InputVideoPath);
                FFHelper.OutputPathNullOrMissing(ffloader.OutputVideoPath);

                if (!string.IsNullOrEmpty(ffloader.AvisynthScriptPath))
                {
                    FFHelper.AvsScriptFileNullOrMissing(ffloader.AvisynthScriptPath);
                }

                process.Start();
                Timer.Restart();

                string line = new string('=', 100);

                //Create and write log file.
                log.WriteLine(line);
                log.WriteLine($"FFMpeg logs generated by FFLoader on {DateTime.Now}");
                log.WriteLine($"FFMpeg Command: ffmpeg.exe {ffloader.FFMpegCommand}");
                log.WriteLine(line + Environment.NewLine);

                process.BeginErrorReadLine();
                process.WaitForExit();
                Timer.Stop();

                FileInfo file = new FileInfo(ffloader.OutputVideoPath);

                if (!string.IsNullOrEmpty(sb.ToString()))
                {
                    ffloader.CatchAvsError(sb.ToString(), out AviSynthErrorHandler handler);
                    ffloader.UpdateAvsError(handler);
                    ProcessWorker.Cancelled = true;
                }
                else if (FFHelper.OutputFileNotCreated(ffloader.OutputVideoPath) || file.Length < 10000)
                {
                    ffloader.CatchFFMpegError("An unknown error occured with FFMpeg.", out FFMpegErrorHandler handler);
                    ffloader.UpdateFFMpegError(handler);
                    ProcessWorker.Cancelled = true;
                }

                log.WriteLine();
                log.WriteLine(line);
                log.WriteLine("End of logs.");
                log.WriteLine(line);
                log.Close();
                line = null;
            }
            catch (FFLoaderException e)
            {
                ffloader.CatchException(e.Source + ": " + e.Message, out FFExceptionHandler handler);
                ffloader.UpdateException(handler);
            }
            finally
            {
                try
                {
                    log = null;
                    ffloader.CloseProcess();
                }
                catch (FFLoaderException e)
                {
                    ffloader.CatchException(e.Source + ": " + e.Message, out FFExceptionHandler handler);
                    ffloader.UpdateException(handler);
                }
            }
        }
    }
}