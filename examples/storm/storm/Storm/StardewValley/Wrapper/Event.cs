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

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Storm.StardewValley.Wrapper
{
    public class Event : StaticContextWrapper
    {
        public Event(StaticContext parent, object accessor) : base(parent)
        {
            Underlying = accessor;
        }

        public Event()
        {
        }

        public string EventCommands
        {
            get { return AsDynamic._GetEventCommands(); }
            set { AsDynamic._SetEventCommands(value); }
        }

        public int CurrentCommand
        {
            get { return AsDynamic._GetCurrentCommand(); }
            set { AsDynamic._SetCurrentCommand(value); }
        }

        public int OldPixelZoom
        {
            get { return AsDynamic._GetOldPixelZoom(); }
            set { AsDynamic._SetOldPixelZoom(value); }
        }

        public int ReadyConfirmationTimer
        {
            get { return AsDynamic._GetReadyConfirmationTimer(); }
            set { AsDynamic._SetReadyConfirmationTimer(value); }
        }

        public string MessageToScreen
        {
            get { return AsDynamic._GetMessageToScreen(); }
            set { AsDynamic._SetMessageToScreen(value); }
        }

        public string PlayerControlSequenceId
        {
            get { return AsDynamic._GetPlayerControlSequenceID(); }
            set { AsDynamic._SetPlayerControlSequenceID(value); }
        }

        public bool ShowActiveObject
        {
            get { return AsDynamic._GetShowActiveObject(); }
            set { AsDynamic._SetShowActiveObject(value); }
        }

        public bool ContinueAfterMove
        {
            get { return AsDynamic._GetContinueAfterMove(); }
            set { AsDynamic._SetContinueAfterMove(value); }
        }

        public bool SpecialEventVariable1
        {
            get { return AsDynamic._GetSpecialEventVariable1(); }
            set { AsDynamic._SetSpecialEventVariable1(value); }
        }

        public bool Forked
        {
            get { return AsDynamic._GetForked(); }
            set { AsDynamic._SetForked(value); }
        }

        public bool WasBloomDay
        {
            get { return AsDynamic._GetWasBloomDay(); }
            set { AsDynamic._SetWasBloomDay(value); }
        }

        public bool WasBloomVisible
        {
            get { return AsDynamic._GetWasBloomVisible(); }
            set { AsDynamic._SetWasBloomVisible(value); }
        }

        public bool PlayerControlSequence
        {
            get { return AsDynamic._GetPlayerControlSequence(); }
            set { AsDynamic._SetPlayerControlSequence(value); }
        }

        public bool EventSwitched
        {
            get { return AsDynamic._GetEventSwitched(); }
            set { AsDynamic._SetEventSwitched(value); }
        }

        public bool IsFestival
        {
            get { return AsDynamic._GetIsFestival(); }
            set { AsDynamic._SetIsFestival(value); }
        }

        public bool SentReadyConfirmation
        {
            get { return AsDynamic._GetSentReadyConfirmation(); }
            set { AsDynamic._SetSentReadyConfirmation(value); }
        }

        public bool AllPlayersReady
        {
            get { return AsDynamic._GetAllPlayersReady(); }
            set { AsDynamic._SetAllPlayersReady(value); }
        }

        public bool PlayerWasMounted
        {
            get { return AsDynamic._GetPlayerWasMounted(); }
            set { AsDynamic._SetPlayerWasMounted(value); }
        }

        public float TimeAccumulator
        {
            get { return AsDynamic._GetTimeAccumulator(); }
            set { AsDynamic._SetTimeAccumulator(value); }
        }

        public float ViewportXAccumulator
        {
            get { return AsDynamic._GetViewportXAccumulator(); }
            set { AsDynamic._SetViewportXAccumulator(value); }
        }

        public float ViewportYAccumulator
        {
            get { return AsDynamic._GetViewportYAccumulator(); }
            set { AsDynamic._SetViewportYAccumulator(value); }
        }

        public Vector3 ViewportTarget
        {
            get { return AsDynamic._GetViewportTarget(); }
            set { AsDynamic._SetViewportTarget(value); }
        }

        public Color PreviousAmbientLight
        {
            get { return AsDynamic._GetPreviousAmbientLight(); }
            set { AsDynamic._SetPreviousAmbientLight(value); }
        }

        public ContentManager TemporaryContent
        {
            get { return AsDynamic._GetTemporaryContent(); }
            set { AsDynamic._SetTemporaryContent(value); }
        }

        public GameLocation TemporaryLocation
        {
            get
            {
                var tmp = AsDynamic._GetTemporaryLocation();
                if (tmp == null) return null;
                return new GameLocation(Parent, tmp);
            }
            set { AsDynamic._SetTemporaryLocation(value?.Underlying); }
        }

        public Point PlayerControlTargetTile
        {
            get { return AsDynamic._GetPlayerControlTargetTile(); }
            set { AsDynamic._SetPlayerControlTargetTile(value); }
        }

        public Texture2D FestivalTexture
        {
            get { return AsDynamic._GetFestivalTexture(); }
            set { AsDynamic._SetFestivalTexture(value); }
        }

        public Npc SecretSantaRecipient
        {
            get
            {
                var tmp = AsDynamic._GetSecretSantaRecipient();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetSecretSantaRecipient(value?.Underlying); }
        }

        public Npc MySecretSanta
        {
            get
            {
                var tmp = AsDynamic._GetMySecretSanta();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetMySecretSanta(value?.Underlying); }
        }

        public bool Skippable
        {
            get { return AsDynamic._GetSkippable(); }
            set { AsDynamic._SetSkippable(value); }
        }

        public int Id
        {
            get { return AsDynamic._GetId(); }
            set { AsDynamic._SetId(value); }
        }

        public int OldShirt
        {
            get { return AsDynamic._GetOldShirt(); }
            set { AsDynamic._SetOldShirt(value); }
        }

        public Color OldPants
        {
            get { return AsDynamic._GetOldPants(); }
            set { AsDynamic._SetOldPants(value); }
        }

        public bool Skipped
        {
            get { return AsDynamic._GetSkipped(); }
            set { AsDynamic._SetSkipped(value); }
        }

        public bool WaitingForMenuClose
        {
            get { return AsDynamic._GetWaitingForMenuClose(); }
            set { AsDynamic._SetWaitingForMenuClose(value); }
        }

        public int OldTime
        {
            get { return AsDynamic._GetOldTime(); }
            set { AsDynamic._SetOldTime(value); }
        }

        public Npc FestivalHost
        {
            get
            {
                var tmp = AsDynamic._GetFestivalHost();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetFestivalHost(value?.Underlying); }
        }

        public string HostMessage
        {
            get { return AsDynamic._GetHostMessage(); }
            set { AsDynamic._SetHostMessage(value); }
        }

        public int FestivalTimer
        {
            get { return AsDynamic._GetFestivalTimer(); }
            set { AsDynamic._SetFestivalTimer(value); }
        }

        public Item TempItemStash
        {
            get
            {
                var tmp = AsDynamic._GetTempItemStash();
                if (tmp == null) return null;
                return new Item(Parent, tmp);
            }
            set { AsDynamic._SetTempItemStash(value?.Underlying); }
        }

        public int GrangeScore
        {
            get { return AsDynamic._GetGrangeScore(); }
            set { AsDynamic._SetGrangeScore(value); }
        }

        public Farmer PlayerUsingGrangeDisplay
        {
            get
            {
                var tmp = AsDynamic._GetPlayerUsingGrangeDisplay();
                if (tmp == null) return null;
                return new Farmer(Parent, tmp);
            }
            set { AsDynamic._SetPlayerUsingGrangeDisplay(value?.Underlying); }
        }

        public int PreviousFacingDirection
        {
            get { return AsDynamic._GetPreviousFacingDirection(); }
            set { AsDynamic._SetPreviousFacingDirection(value); }
        }

        public int PreviousAnswerChoice
        {
            get { return AsDynamic._GetPreviousAnswerChoice(); }
            set { AsDynamic._SetPreviousAnswerChoice(value); }
        }

        public bool StartSecretSantaAfterDialogue
        {
            get { return AsDynamic._GetStartSecretSantaAfterDialogue(); }
            set { AsDynamic._SetStartSecretSantaAfterDialogue(value); }
        }

        public bool SpecialEventVariable2
        {
            get { return AsDynamic._GetSpecialEventVariable2(); }
            set { AsDynamic._SetSpecialEventVariable2(value); }
        }
    }
}