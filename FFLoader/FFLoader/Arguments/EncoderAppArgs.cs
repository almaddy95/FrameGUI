﻿using System.Globalization;

namespace FFLoader.Arguments
{
    internal class EncoderAppArgs
    {
        /// <summary>
        /// Writes the encoder application to the metadata of the output video.
        /// </summary>
        /// <returns>The writing application in a string format.</returns>
        internal static string EncoderApp()
        {
            return string.Format(@" -metadata:g encoding_tool=""FrameGUI v1.0""", CultureInfo.InvariantCulture);
        }
    }
}
