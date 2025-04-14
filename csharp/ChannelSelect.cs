/*
 * @file ChannelSelect.cs
 * @brief Contains the ChannelSelect class, which is used to control relay channels on a Waveshare 8-Channel Relay HAT.
 * @date 2025-02-26
 * @author Simon Cahill (s.cahill@procyon-systems.de)
 */

using System;

namespace ChannelSelect {

    using System.Runtime.InteropServices;

    /// <summary>
    /// The Channel enum represents the 8 relay channels on a Waveshare 8-Channel Relay HAT.
    /// </summary>
    /// <remarks>
    /// The following GPIO pins are used to control the relay channels:
    /// - 5
    /// - 6
    /// - 13
    /// - 16
    /// - 19
    /// - 20
    /// - 21
    /// - 26
    /// </remarks>
    public enum Channel: int {
        /// <summary>
        /// The first relay channel.
        /// </summary>
        Channel1 = 5,
        /// <summary>
        /// The second relay channel.
        /// </summary>
        Channel2 = 6,
        /// <summary>
        /// The third relay channel.
        /// </summary>
        Channel3 = 13,
        /// <summary>
        /// The fourth relay channel.
        /// </summary>
        Channel4 = 16,
        /// <summary>
        /// The fifth relay channel.
        /// </summary>
        Channel5 = 19,
        /// <summary>
        /// The sixth relay channel.
        /// </summary>
        Channel6 = 20,
        /// <summary>
        /// The seventh relay channel.
        /// </summary>
        Channel7 = 21,
        /// <summary>
        /// The eighth relay channel.
        /// </summary>
        Channel8 = 26
    }

    /// <summary>
    /// The ChannelSelect provides a high-level API for controlling the relay channels on a Waveshare 8-Channel Relay hat.
    /// This class utilises the wave8channelselect C++ library to control the relay channels.
    /// </summary>
    /// <remarks>
    /// The wave8channelselect library is a C++ library that provides a high-level API for controlling the relay channels on a Waveshare 8-Channel Relay HAT.
    /// It is located in the cpp directory of this repository and is built using the CMake build system.
    /// When this project is built, it will automatically configure and compile the wave8channelselect library, before importing it into the C# project.
    /// </remarks>
    public static partial class ChannelSelect {

        #region DllImports
        [LibraryImport("libwave8channelselect.so")]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(System.Runtime.CompilerServices.CallConvCdecl) })]
        private static partial int getChannelState(int channel);

        [LibraryImport("libwave8channelselect.so")]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(System.Runtime.CompilerServices.CallConvCdecl) })]
        private static partial int setChannelState(int channel, [MarshalAs(UnmanagedType.Bool)] bool state);

        [LibraryImport("libwave8channelselect.so")]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(System.Runtime.CompilerServices.CallConvCdecl) })]
        private static partial IntPtr getLastError();
        #endregion

        /// <summary>
        /// Gets the last error message from the C++ library.
        /// </summary>
        /// <returns></returns>
        public static string? GetChannelStateError() {
            IntPtr errorPtr = getLastError();
            if (errorPtr == IntPtr.Zero) { return null; }
            
            return Marshal.PtrToStringAnsi(errorPtr);
        }

        /// <summary>
        /// Gets the state of all relay channels.
        /// </summary>
        /// <returns>
        /// A dictionary containing the state of each relay channel.
        /// The key is the channel number, and the value is true if the channel is on, false if it is off.
        /// </returns>
        public static Dictionary<Channel, bool> GetChannelStates() {
            var channelStates = new Dictionary<Channel, bool>();
            foreach (Channel channel in Enum.GetValues(typeof(Channel))) {
                channelStates[channel] = GetChannelState(channel);
            }
            return channelStates;
        }

        /// <summary>
        /// Gets the state of a specific relay channel.
        /// </summary>
        /// <param name="channel">The relay channel to get the state of.</param>
        public static bool GetChannelState(Channel channel) {
            var result = getChannelState((int)channel);
            if (result == -1) {
                throw new InvalidOperationException($"Failed to get channel state: {GetChannelStateError()}");
            }

            return result == 1;
        }

        /// <summary>
        /// Sets the state of a specific relay channel.
        /// </summary>
        /// <param name="channel">The relay channel to set the state of.</param>
        /// <param name="state">True to turn the relay channel on, false to turn it off.</param>
        /// <remarks>
        /// This method will turn the relay channel on or off, depending on the value of the state parameter.
        /// If the state is true, the relay channel will be turned on.
        /// If the state is false, the relay channel will be turned off.
        /// </remarks>
        public static void SetChannelState(Channel channel, bool state) {
            var result = setChannelState((int)channel, state);
            if (result == -1) {
                throw new InvalidOperationException($"Failed to set channel state: {GetChannelStateError()}");
            }
        }

    }

}
