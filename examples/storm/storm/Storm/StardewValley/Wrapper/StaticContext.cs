/*
    Copyright 2016 Cody R. (Demmonic), Inari-Whitebear

    Storm is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Storm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Storm.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Storm.Collections;
using xTile.Display;
using Rectangle = xTile.Dimensions.Rectangle;

namespace Storm.StardewValley.Wrapper
{
    [WrappedAccessor(SimpleName = "StaticContext")]
    public class StaticContext : Wrapper
    {
        public StaticContext(object accessor)
        {
            Underlying = accessor;
        }

        public StaticContext()
        {
        }

        public GameWindow Window => AsDynamic.Window;

        public Rectangle Viewport => AsDynamic._GetViewport();

        /// <summary>
        ///     The Farmer Cast<StaticContextAccessor>() for this game
        /// </summary>
        /// <value>The Player property gets the value of the Farmer field Farmer</value>
        public Farmer Player
        {
            get
            {
                var farmer = AsDynamic._GetPlayer();
                return farmer == null ? null : new Farmer(this, farmer);
            }
        }

        /// <summary>
        ///     The current location of the player in the world
        /// </summary>
        /// <value>The CurrentLocation property gets the value of the GameLocation field CurrentLocation</value>
        public GameLocation CurrentLocation
        {
            get
            {
                var tmp = AsDynamic._GetCurrentLocation();
                return tmp == null ? null : new GameLocation(this, AsDynamic._GetCurrentLocation());
            }
        }

        public bool IsActive => AsDynamic.IsActive;

        public WrappedProxyList<object, GameLocation> Locations
        {
            get
            {
                var locations = AsDynamic._GetLocations();
                if (locations == null) return null;
                return new WrappedProxyList<object, GameLocation>((IList) locations, c => new GameLocation(this, c));
            }
            set { AsDynamic._SetLocations(value.Real); }
        }

        public int PixelZoom
        {
            get { return AsDynamic._GetPixelZoom(); }
            set { AsDynamic._SetPixelZoom(value); }
        }

        public int TileSize
        {
            get { return AsDynamic._GetTileSize(); }
            set { AsDynamic._SetTileSize(value); }
        }

        public string Version
        {
            get { return AsDynamic._GetVersion(); }
            set { AsDynamic._SetVersion(value); }
        }

        public GraphicsDeviceManager Graphics
        {
            get { return AsDynamic._GetGraphics(); }
            set { AsDynamic._SetGraphics(value); }
        }

        public ContentManager Content
        {
            get { return AsDynamic._GetContent(); }
            set { AsDynamic._SetContent(value); }
        }

        public ContentManager TemporaryContent
        {
            get { return AsDynamic._GetTemporaryContent(); }
            set { AsDynamic._SetTemporaryContent(value); }
        }

        public SpriteBatch SpriteBatch
        {
            get { return AsDynamic._GetSpriteBatch(); }
            set { AsDynamic._SetSpriteBatch(value); }
        }

        public GamePadState OldPadState
        {
            get { return AsDynamic._GetOldPadState(); }
            set { AsDynamic._SetOldPadState(value); }
        }

        public float ThumbStickSensitivity
        {
            get { return AsDynamic._GetThumbStickSensitivity(); }
            set { AsDynamic._SetThumbStickSensitivity(value); }
        }

        public float RunThreshold
        {
            get { return AsDynamic._GetRunThreshold(); }
            set { AsDynamic._SetRunThreshold(value); }
        }

        public KeyboardState OldKbState
        {
            get { return AsDynamic._GetOldKBState(); }
            set { AsDynamic._SetOldKBState(value); }
        }

        public MouseState OldMouseState
        {
            get { return AsDynamic._GetOldMouseState(); }
            set { AsDynamic._SetOldMouseState(value); }
        }

        public GameLocation LocationAfterWarp
        {
            get
            {
                var tmp = AsDynamic._GetLocationAfterWarp();
                if (tmp == null) return null;
                return new GameLocation(this, tmp);
            }
            set { AsDynamic._SetLocationAfterWarp(value?.Underlying); }
        }

        public IDisplayDevice MapDisplayDevice
        {
            get { return AsDynamic._GetMapDisplayDevice(); }
            set { AsDynamic._SetMapDisplayDevice(value); }
        }

        public Farmer ServerHost
        {
            get
            {
                var tmp = AsDynamic._GetServerHost();
                if (tmp == null) return null;
                return new Farmer(this, tmp);
            }
            set { AsDynamic._SetServerHost(value?.Underlying); }
        }

        public Texture2D ObjectSpriteSheet
        {
            get { return AsDynamic._GetObjectSpriteSheet(); }
            set { AsDynamic._SetObjectSpriteSheet(value); }
        }

        public Texture2D ToolSpriteSheet
        {
            get { return AsDynamic._GetToolSpriteSheet(); }
            set { AsDynamic._SetToolSpriteSheet(value); }
        }

        public Texture2D CropSpriteSheet
        {
            get { return AsDynamic._GetCropSpriteSheet(); }
            set { AsDynamic._SetCropSpriteSheet(value); }
        }

        public Texture2D MailboxTexture
        {
            get { return AsDynamic._GetMailboxTexture(); }
            set { AsDynamic._SetMailboxTexture(value); }
        }

        public Texture2D EmoteSpriteSheet
        {
            get { return AsDynamic._GetEmoteSpriteSheet(); }
            set { AsDynamic._SetEmoteSpriteSheet(value); }
        }

        public Texture2D DebrisSpriteSheet
        {
            get { return AsDynamic._GetDebrisSpriteSheet(); }
            set { AsDynamic._SetDebrisSpriteSheet(value); }
        }

        public Texture2D ToolIconBox
        {
            get { return AsDynamic._GetToolIconBox(); }
            set { AsDynamic._SetToolIconBox(value); }
        }

        public Texture2D RainTexture
        {
            get { return AsDynamic._GetRainTexture(); }
            set { AsDynamic._SetRainTexture(value); }
        }

        public Texture2D BigCraftableSpriteSheet
        {
            get { return AsDynamic._GetBigCraftableSpriteSheet(); }
            set { AsDynamic._SetBigCraftableSpriteSheet(value); }
        }

        public Texture2D SwordSwipe
        {
            get { return AsDynamic._GetSwordSwipe(); }
            set { AsDynamic._SetSwordSwipe(value); }
        }

        public Texture2D SwordSwipeDark
        {
            get { return AsDynamic._GetSwordSwipeDark(); }
            set { AsDynamic._SetSwordSwipeDark(value); }
        }

        public Texture2D BuffsIcons
        {
            get { return AsDynamic._GetBuffsIcons(); }
            set { AsDynamic._SetBuffsIcons(value); }
        }

        public BuffsDisplay BuffsDisplay
        {
            get
            {
                var tmp = AsDynamic._GetBuffsDisplay();
                if (tmp == null) return null;
                return new BuffsDisplay(this, tmp);
            }
        }

        public Texture2D Daybg
        {
            get { return AsDynamic._GetDaybg(); }
            set { AsDynamic._SetDaybg(value); }
        }

        public Texture2D Nightbg
        {
            get { return AsDynamic._GetNightbg(); }
            set { AsDynamic._SetNightbg(value); }
        }

        public Texture2D LogoScreenTexture
        {
            get { return AsDynamic._GetLogoScreenTexture(); }
            set { AsDynamic._SetLogoScreenTexture(value); }
        }

        public Texture2D TvStationTexture
        {
            get { return AsDynamic._GetTvStationTexture(); }
            set { AsDynamic._SetTvStationTexture(value); }
        }

        public Texture2D Cloud
        {
            get { return AsDynamic._GetCloud(); }
            set { AsDynamic._SetCloud(value); }
        }

        public Texture2D MenuTexture
        {
            get { return AsDynamic._GetMenuTexture(); }
            set { AsDynamic._SetMenuTexture(value); }
        }

        public Texture2D Lantern
        {
            get { return AsDynamic._GetLantern(); }
            set { AsDynamic._SetLantern(value); }
        }

        public Texture2D WindowLight
        {
            get { return AsDynamic._GetWindowLight(); }
            set { AsDynamic._SetWindowLight(value); }
        }

        public Texture2D SconceLight
        {
            get { return AsDynamic._GetSconceLight(); }
            set { AsDynamic._SetSconceLight(value); }
        }

        public Texture2D CauldronLight
        {
            get { return AsDynamic._GetCauldronLight(); }
            set { AsDynamic._SetCauldronLight(value); }
        }

        public Texture2D ShadowTexture
        {
            get { return AsDynamic._GetShadowTexture(); }
            set { AsDynamic._SetShadowTexture(value); }
        }

        public Texture2D MouseCursors
        {
            get { return AsDynamic._GetMouseCursors(); }
            set { AsDynamic._SetMouseCursors(value); }
        }

        public Texture2D IndoorWindowLight
        {
            get { return AsDynamic._GetIndoorWindowLight(); }
            set { AsDynamic._SetIndoorWindowLight(value); }
        }

        public Texture2D Animations
        {
            get { return AsDynamic._GetAnimations(); }
            set { AsDynamic._SetAnimations(value); }
        }

        public Texture2D TitleScreenBg
        {
            get { return AsDynamic._GetTitleScreenBG(); }
            set { AsDynamic._SetTitleScreenBG(value); }
        }

        public Texture2D Logo
        {
            get { return AsDynamic._GetLogo(); }
            set { AsDynamic._SetLogo(value); }
        }

        public RenderTarget2D Lightmap
        {
            get { return AsDynamic._GetLightmap(); }
            set { AsDynamic._SetLightmap(value); }
        }

        public Texture2D FadeToBlackRect
        {
            get { return AsDynamic._GetFadeToBlackRect(); }
            set { AsDynamic._SetFadeToBlackRect(value); }
        }

        public Texture2D StaminaRect
        {
            get { return AsDynamic._GetStaminaRect(); }
            set { AsDynamic._SetStaminaRect(value); }
        }

        public Texture2D CurrentCoopTexture
        {
            get { return AsDynamic._GetCurrentCoopTexture(); }
            set { AsDynamic._SetCurrentCoopTexture(value); }
        }

        public Texture2D CurrentBarnTexture
        {
            get { return AsDynamic._GetCurrentBarnTexture(); }
            set { AsDynamic._SetCurrentBarnTexture(value); }
        }

        public Texture2D CurrentHouseTexture
        {
            get { return AsDynamic._GetCurrentHouseTexture(); }
            set { AsDynamic._SetCurrentHouseTexture(value); }
        }

        public Texture2D GreenhouseTexture
        {
            get { return AsDynamic._GetGreenhouseTexture(); }
            set { AsDynamic._SetGreenhouseTexture(value); }
        }

        public Texture2D LittleEffect
        {
            get { return AsDynamic._GetLittleEffect(); }
            set { AsDynamic._SetLittleEffect(value); }
        }

        public SpriteFont DialogueFont
        {
            get { return AsDynamic._GetDialogueFont(); }
            set { AsDynamic._SetDialogueFont(value); }
        }

        public SpriteFont SmallFont
        {
            get { return AsDynamic._GetSmallFont(); }
            set { AsDynamic._SetSmallFont(value); }
        }

        public SpriteFont BorderFont
        {
            get { return AsDynamic._GetBorderFont(); }
            set { AsDynamic._SetBorderFont(value); }
        }

        public SpriteFont TinyFont
        {
            get { return AsDynamic._GetTinyFont(); }
            set { AsDynamic._SetTinyFont(value); }
        }

        public SpriteFont TinyFontBorder
        {
            get { return AsDynamic._GetTinyFontBorder(); }
            set { AsDynamic._SetTinyFontBorder(value); }
        }

        public SpriteFont SmoothFont
        {
            get { return AsDynamic._GetSmoothFont(); }
            set { AsDynamic._SetSmoothFont(value); }
        }

        public float FadeToBlackAlpha
        {
            get { return AsDynamic._GetFadeToBlackAlpha(); }
            set { AsDynamic._SetFadeToBlackAlpha(value); }
        }

        public float PickToolInterval
        {
            get { return AsDynamic._GetPickToolInterval(); }
            set { AsDynamic._SetPickToolInterval(value); }
        }

        public float ScreenGlowAlpha
        {
            get { return AsDynamic._GetScreenGlowAlpha(); }
            set { AsDynamic._SetScreenGlowAlpha(value); }
        }

        public float FlashAlpha
        {
            get { return AsDynamic._GetFlashAlpha(); }
            set { AsDynamic._SetFlashAlpha(value); }
        }

        public float StarCropShimmerPause
        {
            get { return AsDynamic._GetStarCropShimmerPause(); }
            set { AsDynamic._SetStarCropShimmerPause(value); }
        }

        public float NoteBlockTimer
        {
            get { return AsDynamic._GetNoteBlockTimer(); }
            set { AsDynamic._SetNoteBlockTimer(value); }
        }

        public float GlobalFadeSpeed
        {
            get { return AsDynamic._GetGlobalFadeSpeed(); }
            set { AsDynamic._SetGlobalFadeSpeed(value); }
        }

        public bool FadeToBlack
        {
            get { return AsDynamic._GetFadeToBlack(); }
            set { AsDynamic._SetFadeToBlack(value); }
        }

        public bool FadeIn
        {
            get { return AsDynamic._GetFadeIn(); }
            set { AsDynamic._SetFadeIn(value); }
        }

        public bool DialogueUp
        {
            get { return AsDynamic._GetDialogueUp(); }
            set { AsDynamic._SetDialogueUp(value); }
        }

        public bool DialogueTyping
        {
            get { return AsDynamic._GetDialogueTyping(); }
            set { AsDynamic._SetDialogueTyping(value); }
        }

        public bool PickingTool
        {
            get { return AsDynamic._GetPickingTool(); }
            set { AsDynamic._SetPickingTool(value); }
        }

        public bool IsQuestion
        {
            get { return AsDynamic._GetIsQuestion(); }
            set { AsDynamic._SetIsQuestion(value); }
        }

        public bool NonWarpFade
        {
            get { return AsDynamic._GetNonWarpFade(); }
            set { AsDynamic._SetNonWarpFade(value); }
        }

        public bool ParticleRaining
        {
            get { return AsDynamic._GetParticleRaining(); }
            set { AsDynamic._SetParticleRaining(value); }
        }

        public bool NewDay
        {
            get { return AsDynamic._GetNewDay(); }
            set { AsDynamic._SetNewDay(value); }
        }

        public bool InMine
        {
            get { return AsDynamic._GetInMine(); }
            set { AsDynamic._SetInMine(value); }
        }

        public bool IsEating
        {
            get { return AsDynamic._GetIsEating(); }
            set { AsDynamic._SetIsEating(value); }
        }

        public bool MenuUp
        {
            get { return AsDynamic._GetMenuUp(); }
            set { AsDynamic._SetMenuUp(value); }
        }

        public bool EventUp
        {
            get { return AsDynamic._GetEventUp(); }
            set { AsDynamic._SetEventUp(value); }
        }

        public bool ViewportFreeze
        {
            get { return AsDynamic._GetViewportFreeze(); }
            set { AsDynamic._SetViewportFreeze(value); }
        }

        public bool EventOver
        {
            get { return AsDynamic._GetEventOver(); }
            set { AsDynamic._SetEventOver(value); }
        }

        public bool NameSelectUp
        {
            get { return AsDynamic._GetNameSelectUp(); }
            set { AsDynamic._SetNameSelectUp(value); }
        }

        public bool ScreenGlow
        {
            get { return AsDynamic._GetScreenGlow(); }
            set { AsDynamic._SetScreenGlow(value); }
        }

        public bool ScreenGlowHold
        {
            get { return AsDynamic._GetScreenGlowHold(); }
            set { AsDynamic._SetScreenGlowHold(value); }
        }

        public bool ScreenGlowUp
        {
            get { return AsDynamic._GetScreenGlowUp(); }
            set { AsDynamic._SetScreenGlowUp(value); }
        }

        public bool ProgressBar
        {
            get { return AsDynamic._GetProgressBar(); }
            set { AsDynamic._SetProgressBar(value); }
        }

        public bool IsRaining
        {
            get { return AsDynamic._GetIsRaining(); }
            set { AsDynamic._SetIsRaining(value); }
        }

        public bool IsSnowing
        {
            get { return AsDynamic._GetIsSnowing(); }
            set { AsDynamic._SetIsSnowing(value); }
        }

        public bool KillScreen
        {
            get { return AsDynamic._GetKillScreen(); }
            set { AsDynamic._SetKillScreen(value); }
        }

        public bool CoopDwellerBorn
        {
            get { return AsDynamic._GetCoopDwellerBorn(); }
            set { AsDynamic._SetCoopDwellerBorn(value); }
        }

        public bool MessagePause
        {
            get { return AsDynamic._GetMessagePause(); }
            set { AsDynamic._SetMessagePause(value); }
        }

        public bool IsDebrisWeather
        {
            get { return AsDynamic._GetIsDebrisWeather(); }
            set { AsDynamic._SetIsDebrisWeather(value); }
        }

        public bool BoardingBus
        {
            get { return AsDynamic._GetBoardingBus(); }
            set { AsDynamic._SetBoardingBus(value); }
        }

        public bool ListeningForKeyControlDefinitions
        {
            get { return AsDynamic._GetListeningForKeyControlDefinitions(); }
            set { AsDynamic._SetListeningForKeyControlDefinitions(value); }
        }

        public bool WeddingToday
        {
            get { return AsDynamic._GetWeddingToday(); }
            set { AsDynamic._SetWeddingToday(value); }
        }

        public bool ExitToTitle
        {
            get { return AsDynamic._GetExitToTitle(); }
            set { AsDynamic._SetExitToTitle(value); }
        }

        public bool DebugMode
        {
            get { return AsDynamic._GetDebugMode(); }
            set { AsDynamic._SetDebugMode(value); }
        }

        public bool IsLightning
        {
            get { return AsDynamic._GetIsLightning(); }
            set { AsDynamic._SetIsLightning(value); }
        }

        public bool DisplayHud
        {
            get { return AsDynamic._GetDisplayHUD(); }
            set { AsDynamic._SetDisplayHUD(value); }
        }

        public bool DisplayFarmer
        {
            get { return AsDynamic._GetDisplayFarmer(); }
            set { AsDynamic._SetDisplayFarmer(value); }
        }

        public bool ShowKeyHelp
        {
            get { return AsDynamic._GetShowKeyHelp(); }
            set { AsDynamic._SetShowKeyHelp(value); }
        }

        public bool InputMode
        {
            get { return AsDynamic._GetInputMode(); }
            set { AsDynamic._SetInputMode(value); }
        }

        public bool ShippingTax
        {
            get { return AsDynamic._GetShippingTax(); }
            set { AsDynamic._SetShippingTax(value); }
        }

        public bool DialogueButtonShrinking
        {
            get { return AsDynamic._GetDialogueButtonShrinking(); }
            set { AsDynamic._SetDialogueButtonShrinking(value); }
        }

        public bool JukeboxPlaying
        {
            get { return AsDynamic._GetJukeboxPlaying(); }
            set { AsDynamic._SetJukeboxPlaying(value); }
        }

        public bool DrawLighting
        {
            get { return AsDynamic._GetDrawLighting(); }
            set { AsDynamic._SetDrawLighting(value); }
        }

        public bool BloomDay
        {
            get { return AsDynamic._GetBloomDay(); }
            set { AsDynamic._SetBloomDay(value); }
        }

        public bool Quit
        {
            get { return AsDynamic._GetQuit(); }
            set { AsDynamic._SetQuit(value); }
        }

        public bool IsChatting
        {
            get { return AsDynamic._GetIsChatting(); }
            set { AsDynamic._SetIsChatting(value); }
        }

        public bool GlobalFade
        {
            get { return AsDynamic._GetGlobalFade(); }
            set { AsDynamic._SetGlobalFade(value); }
        }

        public bool DrawGrid
        {
            get { return AsDynamic._GetDrawGrid(); }
            set { AsDynamic._SetDrawGrid(value); }
        }

        public bool FreezeControls
        {
            get { return AsDynamic._GetFreezeControls(); }
            set { AsDynamic._SetFreezeControls(value); }
        }

        public bool SaveOnNewDay
        {
            get { return AsDynamic._GetSaveOnNewDay(); }
            set { AsDynamic._SetSaveOnNewDay(value); }
        }

        public bool PanMode
        {
            get { return AsDynamic._GetPanMode(); }
            set { AsDynamic._SetPanMode(value); }
        }

        public bool ShowingEndOfNightStuff
        {
            get { return AsDynamic._GetShowingEndOfNightStuff(); }
            set { AsDynamic._SetShowingEndOfNightStuff(value); }
        }

        public bool WasRainingYesterday
        {
            get { return AsDynamic._GetWasRainingYesterday(); }
            set { AsDynamic._SetWasRainingYesterday(value); }
        }

        public bool HasLoadedGame
        {
            get { return AsDynamic._GetHasLoadedGame(); }
            set { AsDynamic._SetHasLoadedGame(value); }
        }

        public bool IsActionAtCurrentCursorTile
        {
            get { return AsDynamic._GetIsActionAtCurrentCursorTile(); }
            set { AsDynamic._SetIsActionAtCurrentCursorTile(value); }
        }

        public bool IsInspectionAtCurrentCursorTile
        {
            get { return AsDynamic._GetIsInspectionAtCurrentCursorTile(); }
            set { AsDynamic._SetIsInspectionAtCurrentCursorTile(value); }
        }

        public bool Paused
        {
            get { return AsDynamic._GetPaused(); }
            set { AsDynamic._SetPaused(value); }
        }

        public bool LastCursorMotionWasMouse
        {
            get { return AsDynamic._GetLastCursorMotionWasMouse(); }
            set { AsDynamic._SetLastCursorMotionWasMouse(value); }
        }

        public string CurrentSeason
        {
            get { return AsDynamic._GetCurrentSeason(); }
            set { AsDynamic._SetCurrentSeason(value); }
        }

        public string DebugOutput
        {
            get { return AsDynamic._GetDebugOutput(); }
            set { AsDynamic._SetDebugOutput(value); }
        }

        public string NextMusicTrack
        {
            get { return AsDynamic._GetNextMusicTrack(); }
            set { AsDynamic._SetNextMusicTrack(value); }
        }

        public string SelectedItemsType
        {
            get { return AsDynamic._GetSelectedItemsType(); }
            set { AsDynamic._SetSelectedItemsType(value); }
        }

        public string NameSelectType
        {
            get { return AsDynamic._GetNameSelectType(); }
            set { AsDynamic._SetNameSelectType(value); }
        }

        public string MessageAfterPause
        {
            get { return AsDynamic._GetMessageAfterPause(); }
            set { AsDynamic._SetMessageAfterPause(value); }
        }

        public string Fertilizer
        {
            get { return AsDynamic._GetFertilizer(); }
            set { AsDynamic._SetFertilizer(value); }
        }

        public string SamBandName
        {
            get { return AsDynamic._GetSamBandName(); }
            set { AsDynamic._SetSamBandName(value); }
        }

        public string ElliottBookName
        {
            get { return AsDynamic._GetElliottBookName(); }
            set { AsDynamic._SetElliottBookName(value); }
        }

        public string SlotResult
        {
            get { return AsDynamic._GetSlotResult(); }
            set { AsDynamic._SetSlotResult(value); }
        }

        public string KeyHelpString
        {
            get { return AsDynamic._GetKeyHelpString(); }
            set { AsDynamic._SetKeyHelpString(value); }
        }

        public string DebugInput
        {
            get { return AsDynamic._GetDebugInput(); }
            set { AsDynamic._SetDebugInput(value); }
        }

        public string LoadingMessage
        {
            get { return AsDynamic._GetLoadingMessage(); }
            set { AsDynamic._SetLoadingMessage(value); }
        }

        public string ErrorMessage
        {
            get { return AsDynamic._GetErrorMessage(); }
            set { AsDynamic._SetErrorMessage(value); }
        }

        public int XLocationAfterWarp
        {
            get { return AsDynamic._GetXLocationAfterWarp(); }
            set { AsDynamic._SetXLocationAfterWarp(value); }
        }

        public int YLocationAfterWarp
        {
            get { return AsDynamic._GetYLocationAfterWarp(); }
            set { AsDynamic._SetYLocationAfterWarp(value); }
        }

        public int GameTimeInterval
        {
            get { return AsDynamic._GetGameTimeInterval(); }
            set { AsDynamic._SetGameTimeInterval(value); }
        }

        public int CurrentQuestionChoice
        {
            get { return AsDynamic._GetCurrentQuestionChoice(); }
            set { AsDynamic._SetCurrentQuestionChoice(value); }
        }

        public int CurrentDialogueCharacterIndex
        {
            get { return AsDynamic._GetCurrentDialogueCharacterIndex(); }
            set { AsDynamic._SetCurrentDialogueCharacterIndex(value); }
        }

        public int DialogueTypingInterval
        {
            get { return AsDynamic._GetDialogueTypingInterval(); }
            set { AsDynamic._SetDialogueTypingInterval(value); }
        }

        public int DayOfMonth
        {
            get { return AsDynamic._GetDayOfMonth(); }
            set { AsDynamic._SetDayOfMonth(value); }
        }

        public int Year
        {
            get { return AsDynamic._GetYear(); }
            set { AsDynamic._SetYear(value); }
        }

        public int TimeOfDay
        {
            get { return AsDynamic._GetTimeOfDay(); }
            set { AsDynamic._SetTimeOfDay(value); }
        }

        public int NumberOfSelectedItems
        {
            get { return AsDynamic._GetNumberOfSelectedItems(); }
            set { AsDynamic._SetNumberOfSelectedItems(value); }
        }

        public int PriceOfSelectedItem
        {
            get { return AsDynamic._GetPriceOfSelectedItem(); }
            set { AsDynamic._SetPriceOfSelectedItem(value); }
        }

        public int CurrentWallpaper
        {
            get { return AsDynamic._GetCurrentWallpaper(); }
            set { AsDynamic._SetCurrentWallpaper(value); }
        }

        public int FarmerWallpaper
        {
            get { return AsDynamic._GetFarmerWallpaper(); }
            set { AsDynamic._SetFarmerWallpaper(value); }
        }

        public int WallpaperPrice
        {
            get { return AsDynamic._GetWallpaperPrice(); }
            set { AsDynamic._SetWallpaperPrice(value); }
        }

        public int CurrentFloor
        {
            get { return AsDynamic._GetCurrentFloor(); }
            set { AsDynamic._SetCurrentFloor(value); }
        }

        public int FarmerFloor
        {
            get { return AsDynamic._GetFarmerFloor(); }
            set { AsDynamic._SetFarmerFloor(value); }
        }

        public int FloorPrice
        {
            get { return AsDynamic._GetFloorPrice(); }
            set { AsDynamic._SetFloorPrice(value); }
        }

        public int DialogueWidth
        {
            get { return AsDynamic._GetDialogueWidth(); }
            set { AsDynamic._SetDialogueWidth(value); }
        }

        public int CountdownToWedding
        {
            get { return AsDynamic._GetCountdownToWedding(); }
            set { AsDynamic._SetCountdownToWedding(value); }
        }

        public int MenuChoice
        {
            get { return AsDynamic._GetMenuChoice(); }
            set { AsDynamic._SetMenuChoice(value); }
        }

        public int TvStation
        {
            get { return AsDynamic._GetTvStation(); }
            set { AsDynamic._SetTvStation(value); }
        }

        public int CurrentBillboard
        {
            get { return AsDynamic._GetCurrentBillboard(); }
            set { AsDynamic._SetCurrentBillboard(value); }
        }

        public int FacingDirectionAfterWarp
        {
            get { return AsDynamic._GetFacingDirectionAfterWarp(); }
            set { AsDynamic._SetFacingDirectionAfterWarp(value); }
        }

        public int TmpTimeOfDay
        {
            get { return AsDynamic._GetTmpTimeOfDay(); }
            set { AsDynamic._SetTmpTimeOfDay(value); }
        }

        public int PercentageToWinStardewHero
        {
            get { return AsDynamic._GetPercentageToWinStardewHero(); }
            set { AsDynamic._SetPercentageToWinStardewHero(value); }
        }

        public int MouseClickPolling
        {
            get { return AsDynamic._GetMouseClickPolling(); }
            set { AsDynamic._SetMouseClickPolling(value); }
        }

        public int WeatherIcon
        {
            get { return AsDynamic._GetWeatherIcon(); }
            set { AsDynamic._SetWeatherIcon(value); }
        }

        public int HitShakeTimer
        {
            get { return AsDynamic._GetHitShakeTimer(); }
            set { AsDynamic._SetHitShakeTimer(value); }
        }

        public int StaminaShakeTimer
        {
            get { return AsDynamic._GetStaminaShakeTimer(); }
            set { AsDynamic._SetStaminaShakeTimer(value); }
        }

        public int PauseThenDoFunctionTimer
        {
            get { return AsDynamic._GetPauseThenDoFunctionTimer(); }
            set { AsDynamic._SetPauseThenDoFunctionTimer(value); }
        }

        public int WeatherForTomorrow
        {
            get { return AsDynamic._GetWeatherForTomorrow(); }
            set { AsDynamic._SetWeatherForTomorrow(value); }
        }

        public int CurrentSongIndex
        {
            get { return AsDynamic._GetCurrentSongIndex(); }
            set { AsDynamic._SetCurrentSongIndex(value); }
        }

        public int CursorTileHintCheckTimer
        {
            get { return AsDynamic._GetCursorTileHintCheckTimer(); }
            set { AsDynamic._SetCursorTileHintCheckTimer(value); }
        }

        public int TimerUntilMouseFade
        {
            get { return AsDynamic._GetTimerUntilMouseFade(); }
            set { AsDynamic._SetTimerUntilMouseFade(value); }
        }

        public int MinecartHighScore
        {
            get { return AsDynamic._GetMinecartHighScore(); }
            set { AsDynamic._SetMinecartHighScore(value); }
        }

        public Color MorningColor
        {
            get { return AsDynamic._GetMorningColor(); }
            set { AsDynamic._SetMorningColor(value); }
        }

        public Color EveningColor
        {
            get { return AsDynamic._GetEveningColor(); }
            set { AsDynamic._SetEveningColor(value); }
        }

        public Color UnselectedOptionColor
        {
            get { return AsDynamic._GetUnselectedOptionColor(); }
            set { AsDynamic._SetUnselectedOptionColor(value); }
        }

        public Color ScreenGlowColor
        {
            get { return AsDynamic._GetScreenGlowColor(); }
            set { AsDynamic._SetScreenGlowColor(value); }
        }

        public Npc CurrentSpeaker
        {
            get
            {
                var tmp = AsDynamic._GetCurrentSpeaker();
                if (tmp == null) return null;
                return new Npc(this, tmp);
            }
            set { AsDynamic._SetCurrentSpeaker(value.Underlying); }
        }

        public Random Random
        {
            get { return AsDynamic._GetRandom(); }
            set { AsDynamic._SetRandom(value); }
        }

        public Random RecentMultiplayerRandom
        {
            get { return AsDynamic._GetRecentMultiplayerRandom(); }
            set { AsDynamic._SetRecentMultiplayerRandom(value); }
        }

        public float MusicPlayerVolume
        {
            get { return AsDynamic._GetMusicPlayerVolume(); }
            set { AsDynamic._SetMusicPlayerVolume(value); }
        }

        public float PauseAccumulator
        {
            get { return AsDynamic._GetPauseAccumulator(); }
            set { AsDynamic._SetPauseAccumulator(value); }
        }

        public float PauseTime
        {
            get { return AsDynamic._GetPauseTime(); }
            set { AsDynamic._SetPauseTime(value); }
        }

        public float UpPolling
        {
            get { return AsDynamic._GetUpPolling(); }
            set { AsDynamic._SetUpPolling(value); }
        }

        public float DownPolling
        {
            get { return AsDynamic._GetDownPolling(); }
            set { AsDynamic._SetDownPolling(value); }
        }

        public float RightPolling
        {
            get { return AsDynamic._GetRightPolling(); }
            set { AsDynamic._SetRightPolling(value); }
        }

        public float LeftPolling
        {
            get { return AsDynamic._GetLeftPolling(); }
            set { AsDynamic._SetLeftPolling(value); }
        }

        public float DebrisSoundInterval
        {
            get { return AsDynamic._GetDebrisSoundInterval(); }
            set { AsDynamic._SetDebrisSoundInterval(value); }
        }

        public float ToolHold
        {
            get { return AsDynamic._GetToolHold(); }
            set { AsDynamic._SetToolHold(value); }
        }

        public float WindGust
        {
            get { return AsDynamic._GetWindGust(); }
            set { AsDynamic._SetWindGust(value); }
        }

        public float DialogueButtonScale
        {
            get { return AsDynamic._GetDialogueButtonScale(); }
            set { AsDynamic._SetDialogueButtonScale(value); }
        }

        public float CreditsTimer
        {
            get { return AsDynamic._GetCreditsTimer(); }
            set { AsDynamic._SetCreditsTimer(value); }
        }

        public float GlobalOutdoorLighting
        {
            get { return AsDynamic._GetGlobalOutdoorLighting(); }
            set { AsDynamic._SetGlobalOutdoorLighting(value); }
        }

        public PlayerIndex PlayerOneIndex
        {
            get { return AsDynamic._GetPlayerOneIndex(); }
            set { AsDynamic._SetPlayerOneIndex(value); }
        }

        public Vector2 Shiny
        {
            get { return AsDynamic._GetShiny(); }
            set { AsDynamic._SetShiny(value); }
        }

        public Vector2 PreviousViewportPosition
        {
            get { return AsDynamic._GetPreviousViewportPosition(); }
            set { AsDynamic._SetPreviousViewportPosition(value); }
        }

        public Vector2 CurrentCursorTile
        {
            get { return AsDynamic._GetCurrentCursorTile(); }
            set { AsDynamic._SetCurrentCursorTile(value); }
        }

        public Vector2 LastCursorTile
        {
            get { return AsDynamic._GetLastCursorTile(); }
            set { AsDynamic._SetLastCursorTile(value); }
        }

        public double ChanceToRainTomorrow
        {
            get { return AsDynamic._GetChanceToRainTomorrow(); }
            set { AsDynamic._SetChanceToRainTomorrow(value); }
        }

        public double DailyLuck
        {
            get { return AsDynamic._GetDailyLuck(); }
            set { AsDynamic._SetDailyLuck(value); }
        }

        public byte GameMode
        {
            get { return AsDynamic._GetGameMode(); }
            set { AsDynamic._SetGameMode(value); }
        }

        public byte MultiplayerMode
        {
            get { return AsDynamic._GetMultiplayerMode(); }
            set { AsDynamic._SetMultiplayerMode(value); }
        }

        public ulong UniqueIdForThisGame
        {
            get { return AsDynamic._GetUniqueIDForThisGame(); }
            set { AsDynamic._SetUniqueIDForThisGame(value); }
        }

        public int CropsOfTheWeek
        {
            get { return AsDynamic._GetCropsOfTheWeek(); }
            set { AsDynamic._SetCropsOfTheWeek(value); }
        }

        public Color AmbientLight
        {
            get { return AsDynamic._GetAmbientLight(); }
            set { AsDynamic._SetAmbientLight(value); }
        }

        public Color OutdoorLight
        {
            get { return AsDynamic._GetOutdoorLight(); }
            set { AsDynamic._SetOutdoorLight(value); }
        }

        public Color TextColor
        {
            get { return AsDynamic._GetTextColor(); }
            set { AsDynamic._SetTextColor(value); }
        }

        public Color TextShadowColor
        {
            get { return AsDynamic._GetTextShadowColor(); }
            set { AsDynamic._SetTextShadowColor(value); }
        }

        public ClickableMenu ActiveClickableMenu
        {
            get
            {
                var tmp = AsDynamic._GetActiveClickableMenu();
                if (tmp == null) return null;
                return new ClickableMenu(this, tmp);
            }
            set { AsDynamic._SetActiveClickableMenu(value?.Underlying); }
        }

        public int FramesThisSecond
        {
            get { return AsDynamic._GetFramesThisSecond(); }
            set { AsDynamic._SetFramesThisSecond(value); }
        }

        public int SecondCounter
        {
            get { return AsDynamic._GetSecondCounter(); }
            set { AsDynamic._SetSecondCounter(value); }
        }

        public int Currentfps
        {
            get { return AsDynamic._GetCurrentfps(); }
            set { AsDynamic._SetCurrentfps(value); }
        }

        public ObjectItem DishOfTheDay
        {
            get
            {
                var tmp = AsDynamic._GetDishOfTheDay();
                if (tmp == null) return null;
                return new ObjectItem(this, tmp);
            }
            set { AsDynamic._SetDishOfTheDay(value?.Underlying); }
        }

        public GameTime CurrentGameTime
        {
            get { return AsDynamic._GetCurrentGameTime(); }
            set { AsDynamic._SetCurrentGameTime(value); }
        }

        public Stack EndOfNightMenus
        {
            get { return AsDynamic._GetEndOfNightMenus(); }
            set { AsDynamic._SetEndOfNightMenus(value); }
        }

        public Point LastMousePositionBeforeFade
        {
            get { return AsDynamic._GetLastMousePositionBeforeFade(); }
            set { AsDynamic._SetLastMousePositionBeforeFade(value); }
        }

        public Point ViewportCenter
        {
            get { return AsDynamic._GetViewportCenter(); }
            set { AsDynamic._SetViewportCenter(value); }
        }

        public Vector2 ViewportTarget
        {
            get { return AsDynamic._GetViewportTarget(); }
            set { AsDynamic._SetViewportTarget(value); }
        }

        public float ViewportSpeed
        {
            get { return AsDynamic._GetViewportSpeed(); }
            set { AsDynamic._SetViewportSpeed(value); }
        }

        public int ViewportHold
        {
            get { return AsDynamic._GetViewportHold(); }
            set { AsDynamic._SetViewportHold(value); }
        }

        public int ThumbstickPollingTimer
        {
            get { return AsDynamic._GetThumbstickPollingTimer(); }
            set { AsDynamic._SetThumbstickPollingTimer(value); }
        }

        public bool ToggleFullScreen
        {
            get { return AsDynamic._GetToggleFullScreen(); }
            set { AsDynamic._SetToggleFullScreen(value); }
        }

        public bool IsFullscreen
        {
            get { return AsDynamic._GetIsFullscreen(); }
            set { AsDynamic._SetIsFullscreen(value); }
        }

        public bool SetToWindowedMode
        {
            get { return AsDynamic._GetSetToWindowedMode(); }
            set { AsDynamic._SetSetToWindowedMode(value); }
        }

        public bool SetToFullscreen
        {
            get { return AsDynamic._GetSetToFullscreen(); }
            set { AsDynamic._SetSetToFullscreen(value); }
        }

        public string WhereIsTodaysFest
        {
            get { return AsDynamic._GetWhereIsTodaysFest(); }
            set { AsDynamic._SetWhereIsTodaysFest(value); }
        }

        public bool FarmerShouldPassOut
        {
            get { return AsDynamic._GetFarmerShouldPassOut(); }
            set { AsDynamic._SetFarmerShouldPassOut(value); }
        }

        public Vector2 CurrentViewportTarget
        {
            get { return AsDynamic._GetCurrentViewportTarget(); }
            set { AsDynamic._SetCurrentViewportTarget(value); }
        }

        public Vector2 ViewportPositionLerp
        {
            get { return AsDynamic._GetViewportPositionLerp(); }
            set { AsDynamic._SetViewportPositionLerp(value); }
        }

        public float ScreenGlowRate
        {
            get { return AsDynamic._GetScreenGlowRate(); }
            set { AsDynamic._SetScreenGlowRate(value); }
        }

        public float ScreenGlowMax
        {
            get { return AsDynamic._GetScreenGlowMax(); }
            set { AsDynamic._SetScreenGlowMax(value); }
        }

        public bool HaltAfterCheck
        {
            get { return AsDynamic._GetHaltAfterCheck(); }
            set { AsDynamic._SetHaltAfterCheck(value); }
        }

        public string PanModeString
        {
            get { return AsDynamic._GetPanModeString(); }
            set { AsDynamic._SetPanModeString(value); }
        }

        public bool PanFacingDirectionWait
        {
            get { return AsDynamic._GetPanFacingDirectionWait(); }
            set { AsDynamic._SetPanFacingDirectionWait(value); }
        }

        public int ThumbstickMotionMargin
        {
            get { return AsDynamic._GetThumbstickMotionMargin(); }
            set { AsDynamic._SetThumbstickMotionMargin(value); }
        }

        public int TriggerPolling
        {
            get { return AsDynamic._GetTriggerPolling(); }
            set { AsDynamic._SetTriggerPolling(value); }
        }

        public int RightClickPolling
        {
            get { return AsDynamic._GetRightClickPolling(); }
            set { AsDynamic._SetRightClickPolling(value); }
        }

        public Matrix ScaleMatrix
        {
            get { return AsDynamic._GetScaleMatrix(); }
            set { AsDynamic._SetScaleMatrix(value); }
        }

        public Color BgColor
        {
            get { return AsDynamic._GetBgColor(); }
            set { AsDynamic._SetBgColor(value); }
        }

        public int MouseCursor
        {
            get { return AsDynamic._GetMouseCursor(); }
            set { AsDynamic._SetMouseCursor(value); }
        }

        public float MouseCursorTransparency
        {
            get { return AsDynamic._GetMouseCursorTransparency(); }
            set { AsDynamic._SetMouseCursorTransparency(value); }
        }

        public IDictionary ObjectInformation => AsDynamic._GetObjectInformation();

        public Npc ObjectDialoguePortraitPerson
        {
            get
            {
                var tmp = AsDynamic._GetObjectDialoguePortraitPerson();
                if (tmp == null) return null;
                return new Npc(this, tmp);
            }
            set { AsDynamic._SetObjectDialoguePortraitPerson(value.Underlying); }
        }

        public ChatBox ChatBox
        {
            get
            {
                foreach (var menu in AsDynamic._GetOnScreenMenus())
                {
                    /*if (menu is ChatBoxAccessor)
                    {
                        return new ChatBox(this, (ChatBoxAccessor)menu);
                    }*/
                }
                return null;
            }
        }

        public WrappedProxyList<object, ClickableMenu> OnScreenMenus
        {
            get
            {
                var tmp = AsDynamic._GetOnScreenMenus();
                if (tmp == null) return null;
                return new WrappedProxyList<object, ClickableMenu>((IList) tmp, i => new ClickableMenu(this, i));
            }
        }

        public void AddHudMessage(HudMessage value)
        {
            AsDynamic._AddHUDMessage(value?.Underlying);
        }

        public Texture2D LoadResource(string path)
        {
            var fs = new FileStream(path, FileMode.Open);
            var tex = Texture2D.FromStream(Graphics.GraphicsDevice, fs);
            fs.Close();
            return tex;
        }

        public bool IsFestivalDay(int day, string season)
        {
            var key = day + season;
            var map = TemporaryContent?.Load<Dictionary<string, string>>(@"Data\Festivals\FestivalDates");
            return map != null && map.ContainsKey(key);
        }
    }
}