﻿using System;

namespace StardewModdingAPI.Events
{
    /// <summary>
    /// 
    /// </summary>
    public static class GraphicsEvents
    {
        /// <summary>
        /// Occurs when the form (game) is resized.
        /// </summary>
        public static event EventHandler Resize = delegate { };

        /// <summary>
        /// Occurs before anything is drawn.
        /// </summary>
        public static event EventHandler OnPreRenderEvent = delegate { };

        /// <summary>
        /// Occurs before the GUI is drawn.
        /// </summary>
        public static event EventHandler OnPreRenderGuiEvent = delegate { };

        /// <summary>
        /// Occurs after the GUI is drawn.
        /// </summary>
        public static event EventHandler OnPostRenderGuiEvent = delegate { };

        /// <summary>
        /// Occurs before the HUD is drawn.
        /// </summary>
        public static event EventHandler OnPreRenderHudEvent = delegate { };

        /// <summary>
        /// Occurs after the HUD is drawn.
        /// </summary>
        public static event EventHandler OnPostRenderHudEvent = delegate { };

        /// <summary>
        /// Occurs after everything is drawn.
        /// </summary>
        public static event EventHandler OnPostRenderEvent = delegate { };

        /// <summary>
        /// Occurs before the GUI is drawn. Does not check for conditional statements.
        /// </summary>
        public static event EventHandler OnPreRenderGuiEventNoCheck = delegate { };

        /// <summary>
        /// Occurs after the GUI is drawn. Does not check for conditional statements.
        /// </summary>
        public static event EventHandler OnPostRenderGuiEventNoCheck = delegate { };

        /// <summary>
        /// Occurs before the HUD is drawn. Does not check for conditional statements.
        /// </summary>
        public static event EventHandler OnPreRenderHudEventNoCheck = delegate { };

        /// <summary>
        /// Occurs after the HUD is drawn. Does not check for conditional statements.
        /// </summary>
        public static event EventHandler OnPostRenderHudEventNoCheck = delegate { };

        /// <summary>
        /// Draws when SGame.Debug is true. F3 toggles this.
        /// Game1.spriteBatch.Begin() is pre-called.
        /// Do not make end or begin calls to the spritebatch.
        /// If you are only trying to add debug information, use SGame.DebugMessageQueue in your Update loop.
        /// </summary>
        public static event EventHandler DrawDebug = delegate { };

        internal static void InvokeDrawDebug(object sender, EventArgs e)
        {
            DrawDebug.Invoke(sender, e);
        }

        internal static void InvokeOnPreRenderEvent(object sender, EventArgs e)
        {
            OnPreRenderEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPreRenderGuiEvent(object sender, EventArgs e)
        {
            OnPreRenderGuiEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPostRenderGuiEvent(object sender, EventArgs e)
        {
            OnPostRenderGuiEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPreRenderHudEvent(object sender, EventArgs e)
        {
            OnPreRenderHudEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPostRenderHudEvent(object sender, EventArgs e)
        {
            OnPostRenderHudEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPostRenderEvent(object sender, EventArgs e)
        {
            OnPostRenderEvent.Invoke(sender, e);
        }

        internal static void InvokeOnPreRenderGuiEventNoCheck(object sender, EventArgs e)
        {
            OnPreRenderGuiEventNoCheck.Invoke(sender, e);
        }

        internal static void InvokeOnPostRenderGuiEventNoCheck(object sender, EventArgs e)
        {
            OnPostRenderGuiEventNoCheck.Invoke(sender, e);
        }

        internal static void InvokeOnPreRenderHudEventNoCheck(object sender, EventArgs e)
        {
            OnPreRenderHudEventNoCheck.Invoke(sender, e);
        }

        internal static void InvokeOnPostRenderHudEventNoCheck(object sender, EventArgs e)
        {
            OnPostRenderHudEventNoCheck.Invoke(sender, e);
        }

        internal static void InvokeResize(object sender, EventArgs e)
        {
            Resize.Invoke(sender, e);
        }

        #region To Remove

        [Obsolete("Use the other Pre/Post render events instead.")]
        public static event EventHandler DrawTick = delegate { };

        [Obsolete("Use the other Pre/Post render events instead. All of them will automatically be drawn into the render target if needed.")]
        public static event EventHandler DrawInRenderTargetTick = delegate { };

        [Obsolete("Should not be used.")]
        public static void InvokeDrawTick()
        {
            try
            {
                DrawTick.Invoke(null, EventArgs.Empty);
            }
            catch (Exception ex)
            {
                Log.AsyncR("An exception occured in a Mod's DrawTick: " + ex);
            }
        }

        [Obsolete("Should not be used.")]
        public static void InvokeDrawInRenderTargetTick()
        {
            DrawInRenderTargetTick.Invoke(null, EventArgs.Empty);
        }

        #endregion
    }
}