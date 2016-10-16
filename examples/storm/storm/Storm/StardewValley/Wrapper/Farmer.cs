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
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Storm.Collections;

namespace Storm.StardewValley.Wrapper
{
    public class Farmer : Character
    {
        public Farmer(StaticContext parent, object accessor) : base(parent, accessor)
        {
        }

        public Farmer()
        {
        }

        public WrappedProxyList<object, Item> Items
        {
            get
            {
                var tmp = AsDynamic._GetItems();
                if (tmp == null) return null;
                return new WrappedProxyList<object, Item>((IList) tmp, i => i == null ? null : new Item(Parent, i));
            }
        }

        public ProxyDictionary<string, int[]> Friendships
        {
            get
            {
                var tmp = AsDynamic._GetFriendships();
                if (tmp == null) return null;
                return new ProxyDictionary<string, int[]>(tmp);
            }
        }

        public ProxyList<string> GetMailReceived
        {
            get
            {
                var tmp = AsDynamic._GetMailReceived();
                if (tmp == null) return null;
                return new ProxyList<string>(tmp);
            }
        }

        public ProxyList<string> GetMailForTomorrow
        {
            get
            {
                var tmp = AsDynamic._GetMailForTomorrow();
                if (tmp == null) return null;
                return new ProxyList<string>(tmp);
            }
        }

        public int TileSlideThreshold
        {
            get { return AsDynamic._GetTileSlideThreshold(); }
            set { AsDynamic._SetTileSlideThreshold(value); }
        }

        public int ExperiencePoints
        {
            get { return AsDynamic._GetExperiencePoints(); }
            set { AsDynamic._SetExperiencePoints(value); }
        }

        public Item ActiveObject
        {
            get { return new Item(Parent, AsDynamic._GetActiveObject()); }
            set { AsDynamic._SetActiveObject(value?.Underlying); }
        }

        public ProxyList<int> MovementDirections
        {
            get
            {
                var tmp = AsDynamic._GetMovementDirections();
                if (tmp == null) return null;
                return new ProxyList<int>(tmp);
            }
        }

        public Tool[] ToolBox
        {
            get
            {
                var arr = AsDynamic._GetToolBox();
                return Array.ConvertAll((object[]) arr, i => new Tool(Parent, i));
            }
            set { AsDynamic._SetToolBox(Array.ConvertAll(value, i => i.Underlying)); }
        }

        public ObjectItem Cupboard
        {
            get
            {
                var tmp = AsDynamic._GetCupboard();
                if (tmp == null) return null;
                return new ObjectItem(Parent, tmp);
            }
            set { AsDynamic._SetCupboard(value?.Underlying); }
        }

        public string FarmName
        {
            get { return AsDynamic._GetFarmName(); }
            set { AsDynamic._SetFarmName(value); }
        }

        public string FavoriteThing
        {
            get { return AsDynamic._GetFavoriteThing(); }
            set { AsDynamic._SetFavoriteThing(value); }
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

        public long UniqueMultiplayerId
        {
            get { return AsDynamic._GetUniqueMultiplayerID(); }
            set { AsDynamic._SetUniqueMultiplayerID(value); }
        }

        public string TmpLocationName
        {
            get { return AsDynamic._GetTmpLocationName(); }
            set { AsDynamic._SetTmpLocationName(value); }
        }

        public string PreviousLocationName
        {
            get { return AsDynamic._GetPreviousLocationName(); }
            set { AsDynamic._SetPreviousLocationName(value); }
        }

        public bool CatPerson
        {
            get { return AsDynamic._GetCatPerson(); }
            set { AsDynamic._SetCatPerson(value); }
        }

        public Item MostRecentlyGrabbedItem
        {
            get
            {
                var tmp = AsDynamic._GetMostRecentlyGrabbedItem();
                if (tmp == null) return null;
                return new Item(Parent, tmp);
            }
            set { AsDynamic._SetMostRecentlyGrabbedItem(value?.Underlying); }
        }

        public Item ItemToEat
        {
            get
            {
                var tmp = AsDynamic._GetItemToEat();
                if (tmp == null) return null;
                return new Item(Parent, tmp);
            }
            set { AsDynamic._SetItemToEat(value?.Underlying); }
        }

        public int ToolPower
        {
            get { return AsDynamic._GetToolPower(); }
            set { AsDynamic._SetToolPower(value); }
        }

        public int ToolHold
        {
            get { return AsDynamic._GetToolHold(); }
            set { AsDynamic._SetToolHold(value); }
        }

        public Vector2 MostRecentBed
        {
            get { return AsDynamic._GetMostRecentBed(); }
            set { AsDynamic._SetMostRecentBed(value); }
        }

        public int Shirt
        {
            get { return AsDynamic._GetShirt(); }
            set { AsDynamic._SetShirt(value); }
        }

        public int Hair
        {
            get { return AsDynamic._GetHair(); }
            set { AsDynamic._SetHair(value); }
        }

        public int Skin
        {
            get { return AsDynamic._GetSkin(); }
            set { AsDynamic._SetSkin(value); }
        }

        public int Accessory
        {
            get { return AsDynamic._GetAccessory(); }
            set { AsDynamic._SetAccessory(value); }
        }

        public int FacialHair
        {
            get { return AsDynamic._GetFacialHair(); }
            set { AsDynamic._SetFacialHair(value); }
        }

        public int CurrentEyes
        {
            get { return AsDynamic._GetCurrentEyes(); }
            set { AsDynamic._SetCurrentEyes(value); }
        }

        public int BlinkTimer
        {
            get { return AsDynamic._GetBlinkTimer(); }
            set { AsDynamic._SetBlinkTimer(value); }
        }

        public int FestivalScore
        {
            get { return AsDynamic._GetFestivalScore(); }
            set { AsDynamic._SetFestivalScore(value); }
        }

        public float TemporarySpeedBuff
        {
            get { return AsDynamic._GetTemporarySpeedBuff(); }
            set { AsDynamic._SetTemporarySpeedBuff(value); }
        }

        public Color HairstyleColor
        {
            get { return AsDynamic._GetHairstyleColor(); }
            set { AsDynamic._SetHairstyleColor(value); }
        }

        public Color PantsColor
        {
            get { return AsDynamic._GetPantsColor(); }
            set { AsDynamic._SetPantsColor(value); }
        }

        public Color NewEyeColor
        {
            get { return AsDynamic._GetNewEyeColor(); }
            set { AsDynamic._SetNewEyeColor(value); }
        }

        public Npc DancePartner
        {
            get
            {
                var tmp = AsDynamic._GetDancePartner();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetDancePartner(value?.Underlying); }
        }

        public bool RidingMineElevator
        {
            get { return AsDynamic._GetRidingMineElevator(); }
            set { AsDynamic._SetRidingMineElevator(value); }
        }

        public bool MineMovementDirectionWasUp
        {
            get { return AsDynamic._GetMineMovementDirectionWasUp(); }
            set { AsDynamic._SetMineMovementDirectionWasUp(value); }
        }

        public bool CameFromDungeon
        {
            get { return AsDynamic._GetCameFromDungeon(); }
            set { AsDynamic._SetCameFromDungeon(value); }
        }

        public bool ReadyConfirmation
        {
            get { return AsDynamic._GetReadyConfirmation(); }
            set { AsDynamic._SetReadyConfirmation(value); }
        }

        public bool Exhausted
        {
            get { return AsDynamic._GetExhausted(); }
            set { AsDynamic._SetExhausted(value); }
        }

        public int DeepestMineLevel
        {
            get { return AsDynamic._GetDeepestMineLevel(); }
            set { AsDynamic._SetDeepestMineLevel(value); }
        }

        public int CurrentToolIndex
        {
            get { return AsDynamic._GetCurrentToolIndex(); }
            set { AsDynamic._SetCurrentToolIndex(value); }
        }

        public int WoodPieces
        {
            get { return AsDynamic._GetWoodPieces(); }
            set { AsDynamic._SetWoodPieces(value); }
        }

        public int StonePieces
        {
            get { return AsDynamic._GetStonePieces(); }
            set { AsDynamic._SetStonePieces(value); }
        }

        public int CopperPieces
        {
            get { return AsDynamic._GetCopperPieces(); }
            set { AsDynamic._SetCopperPieces(value); }
        }

        public int IronPieces
        {
            get { return AsDynamic._GetIronPieces(); }
            set { AsDynamic._SetIronPieces(value); }
        }

        public int CoalPieces
        {
            get { return AsDynamic._GetCoalPieces(); }
            set { AsDynamic._SetCoalPieces(value); }
        }

        public int GoldPieces
        {
            get { return AsDynamic._GetGoldPieces(); }
            set { AsDynamic._SetGoldPieces(value); }
        }

        public int IridiumPieces
        {
            get { return AsDynamic._GetIridiumPieces(); }
            set { AsDynamic._SetIridiumPieces(value); }
        }

        public int QuartzPieces
        {
            get { return AsDynamic._GetQuartzPieces(); }
            set { AsDynamic._SetQuartzPieces(value); }
        }

        public int CaveChoice
        {
            get { return AsDynamic._GetCaveChoice(); }
            set { AsDynamic._SetCaveChoice(value); }
        }

        public int Feed
        {
            get { return AsDynamic._GetFeed(); }
            set { AsDynamic._SetFeed(value); }
        }

        public int FarmingLevel
        {
            get { return AsDynamic._GetFarmingLevel(); }
            set { AsDynamic._SetFarmingLevel(value); }
        }

        public int MiningLevel
        {
            get { return AsDynamic._GetMiningLevel(); }
            set { AsDynamic._SetMiningLevel(value); }
        }

        public int CombatLevel
        {
            get { return AsDynamic._GetCombatLevel(); }
            set { AsDynamic._SetCombatLevel(value); }
        }

        public int ForagingLevel
        {
            get { return AsDynamic._GetForagingLevel(); }
            set { AsDynamic._SetForagingLevel(value); }
        }

        public int FishingLevel
        {
            get { return AsDynamic._GetFishingLevel(); }
            set { AsDynamic._SetFishingLevel(value); }
        }

        public int LuckLevel
        {
            get { return AsDynamic._GetLuckLevel(); }
            set { AsDynamic._SetLuckLevel(value); }
        }

        public int NewSkillPointsToSpend
        {
            get { return AsDynamic._GetNewSkillPointsToSpend(); }
            set { AsDynamic._SetNewSkillPointsToSpend(value); }
        }

        public int AddedFarmingLevel
        {
            get { return AsDynamic._GetAddedFarmingLevel(); }
            set { AsDynamic._SetAddedFarmingLevel(value); }
        }

        public int AddedMiningLevel
        {
            get { return AsDynamic._GetAddedMiningLevel(); }
            set { AsDynamic._SetAddedMiningLevel(value); }
        }

        public int AddedCombatLevel
        {
            get { return AsDynamic._GetAddedCombatLevel(); }
            set { AsDynamic._SetAddedCombatLevel(value); }
        }

        public int AddedForagingLevel
        {
            get { return AsDynamic._GetAddedForagingLevel(); }
            set { AsDynamic._SetAddedForagingLevel(value); }
        }

        public int AddedFishingLevel
        {
            get { return AsDynamic._GetAddedFishingLevel(); }
            set { AsDynamic._SetAddedFishingLevel(value); }
        }

        public int AddedLuckLevel
        {
            get { return AsDynamic._GetAddedLuckLevel(); }
            set { AsDynamic._SetAddedLuckLevel(value); }
        }

        public int MaxStamina
        {
            get { return AsDynamic._GetMaxStamina(); }
            set { AsDynamic._SetMaxStamina(value); }
        }

        public int MaxItems
        {
            get { return AsDynamic._GetMaxItems(); }
            set { AsDynamic._SetMaxItems(value); }
        }

        public float Stamina
        {
            get { return AsDynamic._GetStamina(); }
            set { AsDynamic._SetStamina(value); }
        }

        public int Resilience
        {
            get { return AsDynamic._GetResilience(); }
            set { AsDynamic._SetResilience(value); }
        }

        public int Attack
        {
            get { return AsDynamic._GetAttack(); }
            set { AsDynamic._SetAttack(value); }
        }

        public int Immunity
        {
            get { return AsDynamic._GetImmunity(); }
            set { AsDynamic._SetImmunity(value); }
        }

        public float AttackIncreaseModifier
        {
            get { return AsDynamic._GetAttackIncreaseModifier(); }
            set { AsDynamic._SetAttackIncreaseModifier(value); }
        }

        public float KnockbackModifier
        {
            get { return AsDynamic._GetKnockbackModifier(); }
            set { AsDynamic._SetKnockbackModifier(value); }
        }

        public float WeaponSpeedModifier
        {
            get { return AsDynamic._GetWeaponSpeedModifier(); }
            set { AsDynamic._SetWeaponSpeedModifier(value); }
        }

        public float CritChanceModifier
        {
            get { return AsDynamic._GetCritChanceModifier(); }
            set { AsDynamic._SetCritChanceModifier(value); }
        }

        public float CritPowerModifier
        {
            get { return AsDynamic._GetCritPowerModifier(); }
            set { AsDynamic._SetCritPowerModifier(value); }
        }

        public float WeaponPrecisionModifier
        {
            get { return AsDynamic._GetWeaponPrecisionModifier(); }
            set { AsDynamic._SetWeaponPrecisionModifier(value); }
        }

        public int Money
        {
            get { return AsDynamic._GetMoney(); }
            set { AsDynamic._SetMoney(value); }
        }

        public int ClubCoins
        {
            get { return AsDynamic._GetClubCoins(); }
            set { AsDynamic._SetClubCoins(value); }
        }

        public uint TotalMoneyEarned
        {
            get { return AsDynamic._GetTotalMoneyEarned(); }
            set { AsDynamic._SetTotalMoneyEarned(value); }
        }

        public uint MillisecondsPlayed
        {
            get { return AsDynamic._GetMillisecondsPlayed(); }
            set { AsDynamic._SetMillisecondsPlayed(value); }
        }

        public Tool ToolBeingUpgraded
        {
            get
            {
                var tmp = AsDynamic._GetToolBeingUpgraded();
                if (tmp == null) return null;
                return new Tool(Parent, tmp);
            }
            set { AsDynamic._SetToolBeingUpgraded(value?.Underlying); }
        }

        public int DaysLeftForToolUpgrade
        {
            get { return AsDynamic._GetDaysLeftForToolUpgrade(); }
            set { AsDynamic._SetDaysLeftForToolUpgrade(value); }
        }

        public float TimeOfLastPositionPacket
        {
            get { return AsDynamic._GetTimeOfLastPositionPacket(); }
            set { AsDynamic._SetTimeOfLastPositionPacket(value); }
        }

        public int NumUpdatesSinceLastDraw
        {
            get { return AsDynamic._GetNumUpdatesSinceLastDraw(); }
            set { AsDynamic._SetNumUpdatesSinceLastDraw(value); }
        }

        public int HouseUpgradeLevel
        {
            get { return AsDynamic._GetHouseUpgradeLevel(); }
            set { AsDynamic._SetHouseUpgradeLevel(value); }
        }

        public int DaysUntilHouseUpgrade
        {
            get { return AsDynamic._GetDaysUntilHouseUpgrade(); }
            set { AsDynamic._SetDaysUntilHouseUpgrade(value); }
        }

        public int CoopUpgradeLevel
        {
            get { return AsDynamic._GetCoopUpgradeLevel(); }
            set { AsDynamic._SetCoopUpgradeLevel(value); }
        }

        public int BarnUpgradeLevel
        {
            get { return AsDynamic._GetBarnUpgradeLevel(); }
            set { AsDynamic._SetBarnUpgradeLevel(value); }
        }

        public bool HasGreenhouse
        {
            get { return AsDynamic._GetHasGreenhouse(); }
            set { AsDynamic._SetHasGreenhouse(value); }
        }

        public bool HasRustyKey
        {
            get { return AsDynamic._GetHasRustyKey(); }
            set { AsDynamic._SetHasRustyKey(value); }
        }

        public bool HasSkullKey
        {
            get { return AsDynamic._GetHasSkullKey(); }
            set { AsDynamic._SetHasSkullKey(value); }
        }

        public bool HasUnlockedSkullDoor
        {
            get { return AsDynamic._GetHasUnlockedSkullDoor(); }
            set { AsDynamic._SetHasUnlockedSkullDoor(value); }
        }

        public int MagneticRadius
        {
            get { return AsDynamic._GetMagneticRadius(); }
            set { AsDynamic._SetMagneticRadius(value); }
        }

        public int TemporaryInvincibilityTimer
        {
            get { return AsDynamic._GetTemporaryInvincibilityTimer(); }
            set { AsDynamic._SetTemporaryInvincibilityTimer(value); }
        }

        public float Rotation
        {
            get { return AsDynamic._GetRotation(); }
            set { AsDynamic._SetRotation(value); }
        }

        public int CraftingTime
        {
            get { return AsDynamic._GetCraftingTime(); }
            set { AsDynamic._SetCraftingTime(value); }
        }

        public int RaftPuddleCounter
        {
            get { return AsDynamic._GetRaftPuddleCounter(); }
            set { AsDynamic._SetRaftPuddleCounter(value); }
        }

        public int RaftBobCounter
        {
            get { return AsDynamic._GetRaftBobCounter(); }
            set { AsDynamic._SetRaftBobCounter(value); }
        }

        public int Health
        {
            get { return AsDynamic._GetHealth(); }
            set { AsDynamic._SetHealth(value); }
        }

        public int MaxHealth
        {
            get { return AsDynamic._GetMaxHealth(); }
            set { AsDynamic._SetMaxHealth(value); }
        }

        public int TimesReachedMineBottom
        {
            get { return AsDynamic._GetTimesReachedMineBottom(); }
            set { AsDynamic._SetTimesReachedMineBottom(value); }
        }

        public Vector2 Jitter
        {
            get { return AsDynamic._GetJitter(); }
            set { AsDynamic._SetJitter(value); }
        }

        public Vector2 LastPosition
        {
            get { return AsDynamic._GetLastPosition(); }
            set { AsDynamic._SetLastPosition(value); }
        }

        public Vector2 LastGrabTile
        {
            get { return AsDynamic._GetLastGrabTile(); }
            set { AsDynamic._SetLastGrabTile(value); }
        }

        public float JitterStrength
        {
            get { return AsDynamic._GetJitterStrength(); }
            set { AsDynamic._SetJitterStrength(value); }
        }

        public float XOffset
        {
            get { return AsDynamic._GetXOffset(); }
            set { AsDynamic._SetXOffset(value); }
        }

        public bool IsMale
        {
            get { return AsDynamic._GetIsMale(); }
            set { AsDynamic._SetIsMale(value); }
        }

        public bool CanMove
        {
            get { return AsDynamic._GetCanMove(); }
            set { AsDynamic._SetCanMove(value); }
        }

        public bool Running
        {
            get { return AsDynamic._GetRunning(); }
            set { AsDynamic._SetRunning(value); }
        }

        public bool UsingTool
        {
            get { return AsDynamic._GetUsingTool(); }
            set { AsDynamic._SetUsingTool(value); }
        }

        public bool ForceTimePass
        {
            get { return AsDynamic._GetForceTimePass(); }
            set { AsDynamic._SetForceTimePass(value); }
        }

        public bool IsRafting
        {
            get { return AsDynamic._GetIsRafting(); }
            set { AsDynamic._SetIsRafting(value); }
        }

        public bool UsingSlingshot
        {
            get { return AsDynamic._GetUsingSlingshot(); }
            set { AsDynamic._SetUsingSlingshot(value); }
        }

        public bool BathingClothes
        {
            get { return AsDynamic._GetBathingClothes(); }
            set { AsDynamic._SetBathingClothes(value); }
        }

        public bool CanOnlyWalk
        {
            get { return AsDynamic._GetCanOnlyWalk(); }
            set { AsDynamic._SetCanOnlyWalk(value); }
        }

        public bool TemporarilyInvincible
        {
            get { return AsDynamic._GetTemporarilyInvincible(); }
            set { AsDynamic._SetTemporarilyInvincible(value); }
        }

        public bool HasBusTicket
        {
            get { return AsDynamic._GetHasBusTicket(); }
            set { AsDynamic._SetHasBusTicket(value); }
        }

        public bool StardewHero
        {
            get { return AsDynamic._GetStardewHero(); }
            set { AsDynamic._SetStardewHero(value); }
        }

        public bool HasClubCard
        {
            get { return AsDynamic._GetHasClubCard(); }
            set { AsDynamic._SetHasClubCard(value); }
        }

        public bool HasSpecialCharm
        {
            get { return AsDynamic._GetHasSpecialCharm(); }
            set { AsDynamic._SetHasSpecialCharm(value); }
        }

        public bool CanReleaseTool
        {
            get { return AsDynamic._GetCanReleaseTool(); }
            set { AsDynamic._SetCanReleaseTool(value); }
        }

        public bool IsCrafting
        {
            get { return AsDynamic._GetIsCrafting(); }
            set { AsDynamic._SetIsCrafting(value); }
        }

        public Rectangle TemporaryImpassableTile
        {
            get { return AsDynamic._GetTemporaryImpassableTile(); }
            set { AsDynamic._SetTemporaryImpassableTile(value); }
        }

        public bool CanUnderstandDwarves
        {
            get { return AsDynamic._GetCanUnderstandDwarves(); }
            set { AsDynamic._SetCanUnderstandDwarves(value); }
        }

        public Vector2 PositionBeforeEvent
        {
            get { return AsDynamic._GetPositionBeforeEvent(); }
            set { AsDynamic._SetPositionBeforeEvent(value); }
        }

        public Vector2 RemotePosition
        {
            get { return AsDynamic._GetRemotePosition(); }
            set { AsDynamic._SetRemotePosition(value); }
        }

        public int OrientationBeforeEvent
        {
            get { return AsDynamic._GetOrientationBeforeEvent(); }
            set { AsDynamic._SetOrientationBeforeEvent(value); }
        }

        public int SwimTimer
        {
            get { return AsDynamic._GetSwimTimer(); }
            set { AsDynamic._SetSwimTimer(value); }
        }

        public int TimerSinceLastMovement
        {
            get { return AsDynamic._GetTimerSinceLastMovement(); }
            set { AsDynamic._SetTimerSinceLastMovement(value); }
        }

        public int NoMovementPause
        {
            get { return AsDynamic._GetNoMovementPause(); }
            set { AsDynamic._SetNoMovementPause(value); }
        }

        public int FreezePause
        {
            get { return AsDynamic._GetFreezePause(); }
            set { AsDynamic._SetFreezePause(value); }
        }

        public float YOffset
        {
            get { return AsDynamic._GetYOffset(); }
            set { AsDynamic._SetYOffset(value); }
        }

        public string Spouse
        {
            get { return AsDynamic._GetSpouse(); }
            set { AsDynamic._SetSpouse(value); }
        }

        public string DateStringForSaveGame
        {
            get { return AsDynamic._GetDateStringForSaveGame(); }
            set { AsDynamic._SetDateStringForSaveGame(value); }
        }

        public int OverallsColor
        {
            get { return AsDynamic._GetOverallsColor(); }
            set { AsDynamic._SetOverallsColor(value); }
        }

        public int ShirtColor
        {
            get { return AsDynamic._GetShirtColor(); }
            set { AsDynamic._SetShirtColor(value); }
        }

        public int SkinColor
        {
            get { return AsDynamic._GetSkinColor(); }
            set { AsDynamic._SetSkinColor(value); }
        }

        public int HairColor
        {
            get { return AsDynamic._GetHairColor(); }
            set { AsDynamic._SetHairColor(value); }
        }

        public int EyeColor
        {
            get { return AsDynamic._GetEyeColor(); }
            set { AsDynamic._SetEyeColor(value); }
        }

        public Vector2 ArmOffset
        {
            get { return AsDynamic._GetArmOffset(); }
            set { AsDynamic._SetArmOffset(value); }
        }

        public string Bobber
        {
            get { return AsDynamic._GetBobber(); }
            set { AsDynamic._SetBobber(value); }
        }

        public ContentManager FarmerTextureManager
        {
            get { return AsDynamic._GetFarmerTextureManager(); }
            set { AsDynamic._SetFarmerTextureManager(value); }
        }

        public int SaveTime
        {
            get { return AsDynamic._GetSaveTime(); }
            set { AsDynamic._SetSaveTime(value); }
        }

        public int DaysMarried
        {
            get { return AsDynamic._GetDaysMarried(); }
            set { AsDynamic._SetDaysMarried(value); }
        }

        public int ToolPitchAccumulator
        {
            get { return AsDynamic._GetToolPitchAccumulator(); }
            set { AsDynamic._SetToolPitchAccumulator(value); }
        }

        public int CharacterCollisionTimer
        {
            get { return AsDynamic._GetCharactercollisionTimer(); }
            set { AsDynamic._SetCharactercollisionTimer(value); }
        }

        public Npc CollisionNpc
        {
            get
            {
                var tmp = AsDynamic._GetCollisionNPC();
                if (tmp == null) return null;
                return new Npc(Parent, tmp);
            }
            set { AsDynamic._SetCollisionNPC(value?.Underlying); }
        }

        public float MovementMultiplier
        {
            get { return AsDynamic._GetMovementMultiplier(); }
            set { AsDynamic._SetMovementMultiplier(value); }
        }

        public int AddedSpeed
        {
            get { return AsDynamic._GetAddedSpeed(); }
            set { AsDynamic._SetAddedSpeed(value); }
        }

        public ProxyDictionary<int, int[]> FishCaught
        {
            get
            {
                var tmp = AsDynamic._GetFishCaught();
                if (tmp == null) return null;
                return new ProxyDictionary<int, int[]>(tmp);
            }
        }

        public void SetToolInToolBox(int idx, Tool t)
        {
            AsDynamic._GetToolBox()[idx] = t?.Underlying;
        }

        public void SetItem(int idx, Item item)
        {
            var set = item?.Underlying;
            AsDynamic._GetItems()[idx] = set;
        }
    }
}