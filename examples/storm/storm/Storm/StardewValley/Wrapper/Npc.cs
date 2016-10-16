/*
    Copyright 2016 Inari-Whitebear

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

using System.Collections;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Storm.StardewValley.Wrapper
{
    public class Npc : Character
    {
        public Npc(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Npc()
        {
        }

        public int DirectionIndex
        {
            get { return AsDynamic._GetDirectionIndex(); }
            set { AsDynamic._SetDirectionIndex(value); }
        }

        public int LengthOfWalkingSquareX
        {
            get { return AsDynamic._GetLengthOfWalkingSquareX(); }
            set { AsDynamic._SetLengthOfWalkingSquareX(value); }
        }

        public int LengthOfWalkingSquareY
        {
            get { return AsDynamic._GetLengthOfWalkingSquareY(); }
            set { AsDynamic._SetLengthOfWalkingSquareY(value); }
        }

        public int SquarePauseAccumulation
        {
            get { return AsDynamic._GetSquarePauseAccumulation(); }
            set { AsDynamic._SetSquarePauseAccumulation(value); }
        }

        public int SquarePauseTotal
        {
            get { return AsDynamic._GetSquarePauseTotal(); }
            set { AsDynamic._SetSquarePauseTotal(value); }
        }

        public int SquarePauseOffset
        {
            get { return AsDynamic._GetSquarePauseOffset(); }
            set { AsDynamic._SetSquarePauseOffset(value); }
        }

        public Rectangle LastCrossroad
        {
            get { return AsDynamic._GetLastCrossroad(); }
            set { AsDynamic._SetLastCrossroad(value); }
        }

        public string DefaultMap
        {
            get { return AsDynamic._GetDefaultMap(); }
            set { AsDynamic._SetDefaultMap(value); }
        }

        public string LoveInterest
        {
            get { return AsDynamic._GetLoveInterest(); }
            set { AsDynamic._SetLoveInterest(value); }
        }

        public string BirthdaySeason
        {
            get { return AsDynamic._GetBirthdaySeason(); }
            set { AsDynamic._SetBirthdaySeason(value); }
        }

        public Texture2D Portrait
        {
            get { return AsDynamic._GetPortrait(); }
            set { AsDynamic._SetPortrait(value); }
        }

        public Vector2 DefaultPosition
        {
            get { return AsDynamic._GetDefaultPosition(); }
            set { AsDynamic._SetDefaultPosition(value); }
        }

        public Vector2 NextSquarePosition
        {
            get { return AsDynamic._GetNextSquarePosition(); }
            set { AsDynamic._SetNextSquarePosition(value); }
        }

        public int DefaultFacingDirection
        {
            get { return AsDynamic._GetDefaultFacingDirection(); }
            set { AsDynamic._SetDefaultFacingDirection(value); }
        }

        public int IdForClones
        {
            get { return AsDynamic._GetIdForClones(); }
            set { AsDynamic._SetIdForClones(value); }
        }

        public int ShakeTimer
        {
            get { return AsDynamic._GetShakeTimer(); }
            set { AsDynamic._SetShakeTimer(value); }
        }

        public bool IsWalkingInSquare
        {
            get { return AsDynamic._GetIsWalkingInSquare(); }
            set { AsDynamic._SetIsWalkingInSquare(value); }
        }

        public bool IsWalkingTowardPlayer
        {
            get { return AsDynamic._GetIsWalkingTowardPlayer(); }
            set { AsDynamic._SetIsWalkingTowardPlayer(value); }
        }

        public Stack CurrentDialogue
        {
            get { return AsDynamic._GetCurrentDialogue(); }
            set { AsDynamic._SetCurrentDialogue(value); }
        }

        public string TextAboveHead
        {
            get { return AsDynamic._GetTextAboveHead(); }
            set { AsDynamic._SetTextAboveHead(value); }
        }

        public int TextAboveHeadPreTimer
        {
            get { return AsDynamic._GetTextAboveHeadPreTimer(); }
            set { AsDynamic._SetTextAboveHeadPreTimer(value); }
        }

        public int TextAboveHeadTimer
        {
            get { return AsDynamic._GetTextAboveHeadTimer(); }
            set { AsDynamic._SetTextAboveHeadTimer(value); }
        }

        public int TextAboveHeadStyle
        {
            get { return AsDynamic._GetTextAboveHeadStyle(); }
            set { AsDynamic._SetTextAboveHeadStyle(value); }
        }

        public int TextAboveHeadColor
        {
            get { return AsDynamic._GetTextAboveHeadColor(); }
            set { AsDynamic._SetTextAboveHeadColor(value); }
        }

        public float TextAboveHeadAlpha
        {
            get { return AsDynamic._GetTextAboveHeadAlpha(); }
            set { AsDynamic._SetTextAboveHeadAlpha(value); }
        }

        public int Age
        {
            get { return AsDynamic._GetAge(); }
            set { AsDynamic._SetAge(value); }
        }

        public int Manners
        {
            get { return AsDynamic._GetManners(); }
            set { AsDynamic._SetManners(value); }
        }

        public int SocialAnxiety
        {
            get { return AsDynamic._GetSocialAnxiety(); }
            set { AsDynamic._SetSocialAnxiety(value); }
        }

        public int Optimism
        {
            get { return AsDynamic._GetOptimism(); }
            set { AsDynamic._SetOptimism(value); }
        }

        public int Gender
        {
            get { return AsDynamic._GetGender(); }
            set { AsDynamic._SetGender(value); }
        }

        public int Id
        {
            get { return AsDynamic._GetId(); }
            set { AsDynamic._SetId(value); }
        }

        public int HomeRegion
        {
            get { return AsDynamic._GetHomeRegion(); }
            set { AsDynamic._SetHomeRegion(value); }
        }

        public int DaysUntilBirthing
        {
            get { return AsDynamic._GetDaysUntilBirthing(); }
            set { AsDynamic._SetDaysUntilBirthing(value); }
        }

        public int DaysAfterLastBirth
        {
            get { return AsDynamic._GetDaysAfterLastBirth(); }
            set { AsDynamic._SetDaysAfterLastBirth(value); }
        }

        public int BirthdayDay
        {
            get { return AsDynamic._GetBirthdayDay(); }
            set { AsDynamic._SetBirthdayDay(value); }
        }

        public string ExtraDialogueMessageToAddThisMorning
        {
            get { return AsDynamic._GetExtraDialogueMessageToAddThisMorning(); }
            set { AsDynamic._SetExtraDialogueMessageToAddThisMorning(value); }
        }

        public GameLocation CurrentLocation
        {
            get
            {
                var tmp = AsDynamic._GetCurrentLocation();
                if (tmp == null) return null;
                return new GameLocation(Parent, tmp);
            }
            set { AsDynamic._SetCurrentLocation(value?.Underlying); }
        }

        public bool UpdatedDialogueYet
        {
            get { return AsDynamic._GetUpdatedDialogueYet(); }
            set { AsDynamic._SetUpdatedDialogueYet(value); }
        }

        public bool UniqueSpriteActive
        {
            get { return AsDynamic._GetUniqueSpriteActive(); }
            set { AsDynamic._SetUniqueSpriteActive(value); }
        }

        public bool UniquePortraitActive
        {
            get { return AsDynamic._GetUniquePortraitActive(); }
            set { AsDynamic._SetUniquePortraitActive(value); }
        }

        public bool Breather
        {
            get { return AsDynamic._GetBreather(); }
            set { AsDynamic._SetBreather(value); }
        }

        public bool HideShadow
        {
            get { return AsDynamic._GetHideShadow(); }
            set { AsDynamic._SetHideShadow(value); }
        }

        public bool HasPartnerForDance
        {
            get { return AsDynamic._GetHasPartnerForDance(); }
            set { AsDynamic._SetHasPartnerForDance(value); }
        }

        public bool ImmediateSpeak
        {
            get { return AsDynamic._GetImmediateSpeak(); }
            set { AsDynamic._SetImmediateSpeak(value); }
        }

        public bool IgnoreScheduleToday
        {
            get { return AsDynamic._GetIgnoreScheduleToday(); }
            set { AsDynamic._SetIgnoreScheduleToday(value); }
        }

        public int MoveTowardPlayerThreshold
        {
            get { return AsDynamic._GetMoveTowardPlayerThreshold(); }
            set { AsDynamic._SetMoveTowardPlayerThreshold(value); }
        }

        public float Rotation
        {
            get { return AsDynamic._GetRotation(); }
            set { AsDynamic._SetRotation(value); }
        }

        public float YOffset
        {
            get { return AsDynamic._GetYOffset(); }
            set { AsDynamic._SetYOffset(value); }
        }

        public float SwimTimer
        {
            get { return AsDynamic._GetSwimTimer(); }
            set { AsDynamic._SetSwimTimer(value); }
        }

        public float TimerSinceLastMovement
        {
            get { return AsDynamic._GetTimerSinceLastMovement(); }
            set { AsDynamic._SetTimerSinceLastMovement(value); }
        }

        public string MapBeforeEvent
        {
            get { return AsDynamic._GetMapBeforeEvent(); }
            set { AsDynamic._SetMapBeforeEvent(value); }
        }

        public Vector2 PositionBeforeEvent
        {
            get { return AsDynamic._GetPositionBeforeEvent(); }
            set { AsDynamic._SetPositionBeforeEvent(value); }
        }

        public Vector2 LastPosition
        {
            get { return AsDynamic._GetLastPosition(); }
            set { AsDynamic._SetLastPosition(value); }
        }

        public bool IsInvisible
        {
            get { return AsDynamic._GetIsInvisible(); }
            set { AsDynamic._SetIsInvisible(value); }
        }

        public bool FollowSchedule
        {
            get { return AsDynamic._GetFollowSchedule(); }
            set { AsDynamic._SetFollowSchedule(value); }
        }

        public bool Datable
        {
            get { return AsDynamic._GetDatable(); }
            set { AsDynamic._SetDatable(value); }
        }

        public bool DatingFarmer
        {
            get { return AsDynamic._GetDatingFarmer(); }
            set { AsDynamic._SetDatingFarmer(value); }
        }

        public bool HasBeenKissedToday
        {
            get { return AsDynamic._GetHasBeenKissedToday(); }
            set { AsDynamic._SetHasBeenKissedToday(value); }
        }

        public bool DoingEndOfRouteAnimation
        {
            get { return AsDynamic._GetDoingEndOfRouteAnimation(); }
            set { AsDynamic._SetDoingEndOfRouteAnimation(value); }
        }

        public bool GoingToDoEndOfRouteAnimation
        {
            get { return AsDynamic._GetGoingToDoEndOfRouteAnimation(); }
            set { AsDynamic._SetGoingToDoEndOfRouteAnimation(value); }
        }

        public int RouteEndIntro
        {
            get { return AsDynamic._GetRouteEndIntro(); }
            set { AsDynamic._SetRouteEndIntro(value); }
        }

        public int RouteEndAnimation
        {
            get { return AsDynamic._GetRouteEndAnimation(); }
            set { AsDynamic._SetRouteEndAnimation(value); }
        }

        public int RouteEndOutro
        {
            get { return AsDynamic._GetRouteEndOutro(); }
            set { AsDynamic._SetRouteEndOutro(value); }
        }

        public string EndOfRouteMessage
        {
            get { return AsDynamic._GetEndOfRouteMessage(); }
            set { AsDynamic._SetEndOfRouteMessage(value); }
        }

        public string NextEndOfRouteMessage
        {
            get { return AsDynamic._GetNextEndOfRouteMessage(); }
            set { AsDynamic._SetNextEndOfRouteMessage(value); }
        }

        public string EndOfRouteBehaviorName
        {
            get { return AsDynamic._GetEndOfRouteBehaviorName(); }
            set { AsDynamic._SetEndOfRouteBehaviorName(value); }
        }

        public Point PreviousEndPoint
        {
            get { return AsDynamic._GetPreviousEndPoint(); }
            set { AsDynamic._SetPreviousEndPoint(value); }
        }

        public int ScheduleTimeToTry
        {
            get { return AsDynamic._GetScheduleTimeToTry(); }
            set { AsDynamic._SetScheduleTimeToTry(value); }
        }

        public int SquareMovementFacingPreference
        {
            get { return AsDynamic._GetSquareMovementFacingPreference(); }
            set { AsDynamic._SetSquareMovementFacingPreference(value); }
        }

        public bool ReturningToEndPoint
        {
            get { return AsDynamic._GetReturningToEndPoint(); }
            set { AsDynamic._SetReturningToEndPoint(value); }
        }

        public bool HasSaidAfternoonDialogue
        {
            get { return AsDynamic._GetHasSaidAfternoonDialogue(); }
            set { AsDynamic._SetHasSaidAfternoonDialogue(value); }
        }

        public int Married
        {
            get { return AsDynamic._GetMarried(); }
            set { AsDynamic._SetMarried(value); }
        }

        public int DaysMarried
        {
            get { return AsDynamic._GetDaysMarried(); }
            set { AsDynamic._SetDaysMarried(value); }
        }
    }
}
