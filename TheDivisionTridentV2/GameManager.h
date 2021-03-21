#pragma once
#include "includes.h"

namespace TheDivisionSDK {

	namespace Snowdrop
	{
		/* Get the UserInterfaceManager */
		namespace UI {
			class UserInterfaceManager
			{
			public:
				UserInterfaceManager(const UserInterfaceManager&) = delete;

				static UserInterfaceManager* Get()
				{
					uintptr_t userInterfaceManager = (uintptr_t)(GetModuleHandle(NULL)) + 0x44FBBE8;
					if (userInterfaceManager)
					{
						std::cout << "[+] UserInterfaceManager was found" << std::endl;
						return *(UserInterfaceManager**)userInterfaceManager;
					}
					else
					{
						std::cout << "[-] did not find UserInterfaceManager" << std::endl;
						return nullptr;
					}
				}

			public:
				char pad_0000[144]; //0x0000
				class UIClass* UI; //0x0090
				char pad_0098[1000]; //0x0098
			};

			class UIClass
			{
			public:
				char pad_0000[24]; //0x0000
				class MapClass* Map; //0x0018
				char pad_0020[104]; //0x0020
			}; //Size: 0x0088

			class MapClass
			{
			public:
				char pad_0000[856]; //0x0000
				class WaypointClass* Waypoint; //0x0000
				char pad_0360[40]; //0x0360
			}; //Size: 0x0388

			class WaypointClass
			{
			public:
				char pad_0000[336]; //0x0000
				class WaypointPositionClass* WaypointPosition; //0x0150
				char pad_0158[48]; //0x0158
			}; //Size: 0x0188

			class WaypointPositionClass
			{
			public:
				char pad_0000[68]; //0x0000
				float X; //0x0044
				float Y; //0x0048
				float Z; //0x004C
				char pad_0050[76]; //0x0050
			}; //Size: 0x009C
		};

		namespace IndexModule 
		{
			class IndexModuleClass
			{
			public:
				IndexModuleClass(const IndexModuleClass&) = delete;
				static IndexModuleClass* Get()
				{
					return *(IndexModuleClass**)((uintptr_t)(GetModuleHandle(NULL)) + 0x45D2230);
				}
			public:
				char pad_0000[152]; //0x0000
				class Indexer* IndexList; //0x0098

				enum GIndexer
				{
					AimChangeAccuracyRecoveryTimeMSFinal,
					AimChangeModifierFinal,
					AimChangeSensitivityFinal,
					AimSpreadMaxFinal,
					AimSpreadMinFinal,
					AirSupplyFinal,
					AirSupplyDepletionRateFinal,
					AirSupplyRegenRateFinal,
					AirSupplyRegenTickIntervalFinal,
					AirSupplyDepletionTickIntervalFinal,
					AirSupplyDamageRateFinal,
					AirSupplyDamageIntervalFinal,
					AirSupplyEmptyDamageDelayFinal,
					FallDamageModFinal,
					FallDamageLethalHeightFinal,
					FallDamageStartHeightFinal,
					BleedingOutHealthFinal,
					BleedingOutHealthDegenRateFinal,
					BleedingOutHealthDegenTickIntervalFinal,
					BleedingOutDieQuickMultiplierFinal,
					BleedingOutReviveHealthPercentageFinal,
					ClipSizeFinal,
					CoverAimSpreadMaxFinal,
					CoverAimSpreadMinFinal,
					CoverSpreadMaxFinal,
					CoverSpreadMinFinal,
					CriticalHitChanceResilienceFinal,
					DamageDoneToSuppressedTargetModFinal,
					DamageDoneToElitesModFinal,
					DamageMultiplierArmsFinal,
					DamageMultiplierBodyFinal,
					DamageMultiplierHeadFinal,
					DamageMultiplierLegsFinal,
					DamageTakenModFinal,
					DamageTakenModBonus,
					DamageTakenFromElitesModFinal,
					NPCDamageDoneToPlayersModFinal,
					DownedDamageMaxFinal,
					DownedDamageMaxPVPFinal,
					DownedDamageModFinal,
					DownedDamageModPVPFinal,
					DownedHealthFinal,
					DownedHealthDegenRateFinal,
					DownedHealthDegenTickIntervalFinal,
					DownedInARowMaxFinal,
					DownedInARowMaxTimePeriodFinal,
					DownedDieQuickMultiplierFinal,
					DownedReviveHealthPercentageFinal,
					TalentDownedAssistSpeedModFinal,
					TalentSecondChanceHealModFinal,
					TalentSecondChanceCooldownFinal,
					FreeWeaponReloadChanceFinal,
					HealthFinal,
					HealthRegenDelayFinal,
					HealthRegenExitCombatDelayFinal,
					HealthRegenRateFinal,
					HealthRegenTickIntervalFinal,
					HealthSegmentsFinal,
					HorizontalRecoilBorderLeftFinal,
					HorizontalRecoilBorderRightFinal,
					HorizontalRecoilLeftFinal,
					HorizontalRecoilRecoveryTimeMSFinal,
					HorizontalRecoilRightFinal,
					HorizontalRecoilTimeMSFinal,
					IncomingHealingModFinal,
					OutgoingHealingModFinal,
					DarkZoneInventoryFinal,
					DefaultInventoryFinal,
					ResourceInventoryFinal,
					VanityInventoryFinal,
					BackupSpaceInventoryFinal,
					StashInventoryFinal,
					DarkZoneStashInventoryFinal,
					MailboxInventoryFinal,
					SurvivalStashInventoryFinal,
					DarkZoneInventoryFlatBonus,
					LifeOnKillFinal,
					LootChanceModFinal,
					LootedAmmoModFinal,
					LootedGoldModFinal,
					LootMagicFindFinal,
					ScavengingExtraDropChancesFinal,
					MeleeDamagePvPFinal,
					MeleeDamageFinal,
					MeleeDamageMitigationPercentageFinal,
					MovementSpeedModFinal,
					NPCVisionRangeModFinal,
					PitchRecoveryPerSecondFinal,
					PitchRecoveryPercentFinal,
					PulseCriticalHitChanceFinal,
					PulseCriticalHitDamageFinal,
					PVPDamageModifierFinal,
					RPMFinal,
					RangeLongFinal,
					RangeMaxFinal,
					RangeOptimalFinal,
					RecoilBaseFinal,
					RecoilClimbTimeMSFinal,
					RecoilIncreasePerBulletFinal,
					RecoilMaxFinal,
					RecoilMinFinal,
					RecoilRecoveryPerSecondFinal,
					RecoilRecoveryTimeMSFinal,
					RecoilResetTimeMSFinal,
					ReloadTimeMSFinal,
					EmptyClipFirstRoundReloadTimeMSFinal,
					InitialShellReloadTimeMSFinal,
					RespawnTimeMSFinal,
					RespawnMinimumTimeFinal,
					ReviveDurationMSFinal,
					ReviveFromUnconsciousDurationMSFinal,
					LootDeadBodyDurationMSFinal,
					ReviveImmunityDurationFinal,
					ReviveImmunityRangeFinal,
					ReviveServerNotifyTickIntervalMSFinal,
					SurvivalSelfReviveMedkitCostFinal,
					SurvivalUnconsciousReviveMedkitCostFinal,
					SafetyBeltCooldownFinal,
					SkillCriticalHitChanceFinal,
					SkillCriticalHitDamageModFinal,
					SkillHasteModFinal,
					SpreadIncreaseSpeedFinal,
					SpreadIncreaseTimeMSFinal,
					SpreadMaxFinal,
					SpreadMinFinal,
					SpreadMovementModFinal,
					SpreadReductionSpeedFinal,
					StaggerDamageModifierFinal,
					StaminaConsumptionRateFinal,
					StaminaConsumptionTickIntervalFinal,
					StaminaDamageTakenModFinal,
					StaminaFinal,
					StaminaRegenDelayFinal,
					StaminaRegenRateFinal,
					StaminaRegenTickIntervalFinal,
					SuppressionFinal,
					TargetOutOfCoverDamageModFinal,
					ThrowRangeModFinal,
					TimeToMaxAccuracyMSFinal,
					TimeToMinAccuracyMSFinal,
					WeaponCriticalHitChanceFinal,
					WeaponCriticalHitDamageModFinal,
					WeaponCriticalHitChanceVsOOCFinal,
					WeaponCriticalHitChanceWhileHipFiringModFinal,
					WeaponCriticalHitChanceCap,
					WeaponCriticalHitDamageFlatBonus,
					NormalizedWeaponCriticalHitDamageFlatBonus,
					WeaponDamageMultiplierHeadModBonus,
					WeaponDamageMultiplierHeadFlatBonus,
					NormalizedWeaponDamageMultiplierHeadFlatBonus,
					WeaponDrawSpeedModFinal,
					WeaponHolsterSpeedModFinal,
					WeaponRecoilKickModBonus,
					NormalizedWeaponRecoilKickModBonus,
					WeaponSwitchSpeedModFinal,
					XPModFinal,
					YawRecoveryPerSecondFinal,
					YawRecoveryPercentFinal,
					ZoneDiscoveryXPFinal,
					PhysicalDamageMinFinal,
					PhysicalDamageMaxFinal,
					PhysicalDamageVariationFinal,
					BlastDamageMinFinal,
					BlastDamageMaxFinal,
					BlastDamageVariationFinal,
					BleedDamageMinFinal,
					BleedDamageMaxFinal,
					BleedDamageVariationFinal,
					BurnDamageMinFinal,
					BurnDamageMaxFinal,
					BurnDamageVariationFinal,
					ToxinDamageMinFinal,
					ToxinDamageMaxFinal,
					ToxinDamageVariationFinal,
					ElectricDamageMinFinal,
					ElectricDamageMaxFinal,
					ElectricDamageVariationFinal,
					NeutralDamageMinFinal,
					NeutralDamageMaxFinal,
					NeutralDamageVariationFinal,
					EMPDamageMinFinal,
					EMPDamageMaxFinal,
					EMPDamageVariationFinal,
					StaminaDamageMinFinal,
					StaminaDamageMaxFinal,
					StaminaDamageVariationFinal,
					DiseaseDamageMinFinal,
					DiseaseDamageMaxFinal,
					DiseaseDamageVariationFinal,
					ColdDamageMinFinal,
					ColdDamageMaxFinal,
					ColdDamageVariationFinal,
					TestDamageScaling,
					PrimaryOffensiveCalc,
					WeaponDamageModBonus,
					WeaponTypeDamageModCalc,
					NPCArmorFinal,
					NPCArmorBypassRatioHeadFinal,
					NPCArmorBypassRatioBodyFinal,
					NPCArmorDamageModifierFinal,
					NPCArmorBypassModifierFinal,
					PhysicalDamageMitigationPercentageFinal,
					BlastDamageMitigationPercentageFinal,
					BleedDamageMitigationPercentageFinal,
					BurnDamageMitigationPercentageFinal,
					ToxinDamageMitigationPercentageFinal,
					ElectricDamageMitigationPercentageFinal,
					NeutralDamageMitigationPercentageFinal,
					EMPDamageMitigationPercentageFinal,
					StaminaDamageMitigationPercentageFinal,
					PvPArmorDamageRatioFinal,
					ArmorMitigationPercentageCalc,
					SelfSourceDamageMitigationPercentageFinal,
					FriendlySourceDamageMitigationPercentageFinal,
					NPCSourceDamageMitigationPercentageFinal,
					OpponentSourceDamageMitigationPercentageFinal,
					NullSourceDamageMitigationPercentageFinal,
					WeaponMethodDamageMitigationPercentageFinal,
					TrapMethodDamageMitigationPercentageFinal,
					SkillMethodDamageMitigationPercentageFinal,
					StatusEffectMethodDamageMitigationPercentageFinal,
					MeleeMethodDamageMitigationPercentageFinal,
					EnvironmentMethodDamageMitigationPercentageFinal,
					BleedingStatusResistancePercentageFinal,
					BlindDeafStatusResistancePercentageFinal,
					BurningStatusResistancePercentageFinal,
					ConfusedStatusResistancePercentageFinal,
					DisruptedStatusResistancePercentageFinal,
					ShockedStatusResistancePercentageFinal,
					StaggeredStatusResistancePercentageFinal,
					SuppressedStatusResistancePercentageFinal,
					AimSwayMinHorizontalFinal,
					AimSwayMaxHorizontalFinal,
					AimSwayMinVerticalFinal,
					AimSwayMaxVerticalFinal,
					AimSwaySpeedModifierFinal,
					VisualDetectionModFinal,
					VisualStealthModFinal,
					AudialDetectionModFinal,
					AudialStealthModFinal,
					DarkZoneItemsToDropFinal,
					DarkZoneItemsToDropRogueFinal,
					DarkZoneConvertXPModFinal,
					DarkZoneXPModFinal,
					DarkZoneXPLossModFinal,
					DarkZoneXPLossRogueModFinal,
					DarkZoneXPLossFinal,
					DarkZoneXPLossRogueFinal,
					ThreatPerBulletFinal,
					ThreatTotalGeneratedModFinal,
					ThreatPerBulletDamageModFinal,
					SuppressionTriggerScoreFinal,
					SuppressionDefenseModifierFinal,
					SuppressionDepletionRateFinal,
					SuppressionDurationFinal,
					SuppressionBufferScoreFinal,
					SuppressionBufferResetTimeFinal,
					StaggerGaugeFinal,
					StaggerAnimationDurationModFinal,
					ChanceOfGreenToBlueWhenCraftingFinal,
					ChanceOfBlueToPurpleWhenCraftingFinal,
					ChanceOfPurpleToOrangeWhenCraftingFinal,
					XPRepeatableEventsModFinal,
					CreditsRepeatableEventsModFinal,
					SecurityRepeatableEventsModFinal,
					PersonnelRescueMissionsModFinal,
					SupplyDropMissionsModFinal,
					XPHeadshotKillsModFinal,
					XPTacticalKillsModFinal,
					XPSpecialKillsModFinal,
					XPEliteKillsModFinal,
					XPMultiKillsModFinal,
					XPKillsModFinal,
					XPAccoladeModFinal,
					ExtractionTimeModFinal,
					CraftingCostModFinal,
					SkillXPModFinal,
					DZRewardedCredsModFinal,
					VendorCostModFinal,
					AmmoDroppedModFinal,
					CreditsDroppedModFinal,
					LootedCreditsModFinal,
					LootedDZCreditsModFinal,
					UnlockedSkillSlotsFinal,
					SecondaryWeaponAllowedBoolFinal,
					RewardedCredsModFinal,
					PerkAutoDiscoverFinal,
					LastBulletDamageModFinal,
					SkillPowerModBonus,
					TalentGunslingerFinal,
					TalentGunslingerBonusIncFinal,
					TalentGunslingerBonusIncPvPFinal,
					TalentGunslingerBonusDecFinal,
					TalentGunslingerMaxBonusFinal,
					TalentGunslingerBonusTimeDecrementFinal,
					TalentGunslingerBonusTimeDecrementIntervalFinal,
					TalentClassifiedGunslingerFinal,
					TalentClassifiedGunslingerBonusIncFinal,
					TalentClassifiedGunslingerBonusIncPvPFinal,
					TalentClassifiedGunslingerBonusDecFinal,
					TalentClassifiedGunslingerMaxBonusFinal,
					TalentClassifiedGunslingerBonusBonus,
					TalentClassifiedGunslingerBonusFinal,
					TalentClassifiedGunslingerBonusTimeDecrementFinal,
					TalentClassifiedGunslingerBonusTimeDecrementIntervalFinal,
					TalentClassifiedGunslingerTickRateFinal,
					TalentClassifiedGunslingerPvPTickRateFinal,
					TalentNomadFinal,
					TalentClassifiedNomadFinal,
					TalentClassifiedNomadDurationFinal,
					TalentClassifiedNomadDefensiveBonusFinal,
					TalentClassifiedNomadDiminishingReturnsDurationFinal,
					TalentClassifiedNomadDiminishingReturnsFinal,
					TalentClassifiedNomadChanceForNoCooldownFinal,
					TalentNomadCooldownFinal,
					TalentNomadCooldownModifierOnPvPGameStartFinal,
					TalentWardenFinal,
					TalentWardenDamageFinal,
					TalentWardenBonusIncFinal,
					TalentWardenBonusIncFromSkillProxiesFinal,
					TalentWardenBonusDecFinal,
					TalentWardenMaxBonusFinal,
					TalentClassifiedWardenFinal,
					TalentClassifiedWardenMaxBonusFinal,
					TalentClassifiedWardenChanceFinal,
					TalentClassifiedWardenBonusResetModifierFinal,
					TalentWeaponSwapReload,
					TalentSoloFinal,
					TalentRiotShieldWithSMG,
					TalentHuntersFaithFinal,
					TalentHuntersFaithBonusIncFinal,
					TalentHuntersFaithMaxBonusFinal,
					TalentHuntersFaithDurationFinal,
					TalentClassifiedHuntersFaithFinal,
					TalentClassifiedHuntersFaithMissedShotsAllowedFinal,
					TalentPredatorsMarkFinal,
					TalentPredatorBleedCounterFinal,
					TalentPredatorBleedDamageFinal,
					TalentPredatorsMarkAdditionalPvPBleedDamageModFinal,
					TalentClassifiedPredatorsMarkFinal,
					TalentGlassHalfFullFinal,
					TalentGlassHalfFullDurationFinal,
					TalentGlassHalfFullBonusFinal,
					TalentCoverShooterFinal,
					TalentCoverShooterDurationFinal,
					TalentCoverShooterMaxBonusFinal,
					TalentCoverShooterBonusIncFinal,
					TalentDevilsHeelFinal,
					TalentDevilsHeelDurationFinal,
					TalentDevilsHeelBothTalentsFinal,
					TalentFireFinal,
					TalentFireBonusIncFromHeadshotFinal,
					TalentFireBonusIncFromBodyshotFinal,
					TalentFuryFinal,
					TalentFuryBonusIncFromWeakpointFinal,
					TalentFuryBonusIncFromEquipmentFinal,
					TalentClassifiedFireCrestFinal,
					TalentClassifiedFireCrestBurnChanceFinal,
					TalentClassifiedFireCrestExplosionDamageFinal,
					TalentClassifiedFireCrestExplosionRadiusFinal,
					TalentClassifiedFireCrestExplosionCooldownFinal,
					TalentClassifiedBansheeFinal,
					TalentClassifiedBansheeBonusDamagePerManhuntStageFinal,
					TalentClassifiedBansheeInteractDurationBonusFinal,
					TalentClassifiedBansheeInteractDurationRangeFinal,
					TalentClassifiedSoloFinal,
					TalentClassifiedSoloRotationDurationFinal,
					TalentClassifiedSoloSkillDurationFinal,
					TalentClassifiedSoloAttributeRelationPercentageFinal,
					TalentClassifiedSoloAttributeRelationPenaltyFinal,
					TalentClassifiedSoloMinAttributeRelationModifierFinal,
					PrimaryDefensiveFinal,
					PrimaryOffensiveFinal,
					PrimarySupportFinal,
					OverHealFinal,
					OverHealDepletionDelayFinal,
					OverHealDepletionRateFinal,
					SignatureSkillResourceRewardModFinal,
					CombatBuff_Cooldown_Final,
					DefenceBuff_Cooldown_Final,
					GroupHeal_Cooldown_Final,
					ModSocketAttributeBonus,
					ArmorMitigationDefaultRatingFlatBonus,
					ContaminationZoneGasMaskLevelDefaultFlatBonus,
					DefaultInventoryFlatBonus,
					WeaponDamageBaseModBonus,
					WeaponDamageAssaultRifleBaseModBonus,
					WeaponDamageLMGBaseModBonus,
					WeaponDamageMarksmanRifleBaseModBonus,
					WeaponDamagePistolBaseModBonus,
					WeaponDamageShotgunBaseModBonus,
					WeaponDamageSMGBaseModBonus,
					PrimaryOffensiveFlatBonus,
					PrimaryDefensiveFlatBonus,
					PrimarySupportFlatBonus,
					PrimaryDefensiveDefaultBaseFlatBonus,
					PrimaryOffensiveDefaultBaseFlatBonus,
					PrimarySupportDefaultBaseFlatBonus,
					PrimaryDefensiveDefaultFlatBonus,
					PrimaryOffensiveDefaultFlatBonus,
					PrimarySupportDefaultFlatBonus,
					PrimaryOffensiveClassifiedFlatBonus,
					PrimaryDefensiveClassifiedFlatBonus,
					PrimarySupportClassifiedFlatBonus,
					PrimaryDefensiveClassifiedDefaultBaseFlatBonus,
					PrimaryOffensiveClassifiedDefaultBaseFlatBonus,
					PrimarySupportClassifiedDefaultBaseFlatBonus,
					AmmoIncendiaryFinal,
					AmmoIncendiaryFlatBonus,
					AmmoExplosiveFinal,
					ApplyStatusBurnPercentageFinal,
					ApplyExplosionConsumablePercentageFinal,
					ArmorRatingUI,
					ToughnessUI,
					DefaultInventoryUI,
					ContaminationProtectionUI,
					SkillPowerUI,
					WeaponDamageCompareUI,
					WeaponRPMCompareUI,
					WeaponMagazineCompareUI,
					WeaponAccuracyCompareUI,
					WeaponRangeCompareUI,
					WeaponReloadTimeCompareUI,
					WeaponStabilityCompareUI,
					MedkitStackFinal,
					SMGAmmoFinal,
					ShotgunAmmoFinal,
					MarksmanRifleAmmoFinal,
					LMGAmmoFinal,
					AssaultRifleAmmoFinal,
					Survival_TemperatureRatingFinal,
					Survival_ColdFinal,
					Survival_DiseaseFinal,
					Survival_HungerFinal,
					Survival_ThirstFinal,
					Survival_ColdAimShakeSpeedFinal,
					Survival_UIDistanceMultiplierFinal,
					Survival_ConsumableFoodCooldownFinal,
					Survival_ConsumableDrinkCooldownFinal,
					Survival_ConsumableMedicineCooldownFinal,
					Survival_ConsumableMedicineDiminishingReturn,
					Survival_ConsumableMedicineDurationMaxTime,
					Survival_ConsumableMedicineCooldownMaxTime,
					Survival_ConsumablePainkillerCooldownFinal,
					Survival_ConsumablePainkillerDiminishingReturn,
					Survival_ConsumablePainkillerDurationMaxTime,
					Survival_ConsumablePainkillerCooldownMaxTime,
					PvPDamageMultiplierArmsFinal,
					PvPDamageMultiplierBodyFinal,
					PvPDamageMultiplierHeadFinal,
					PvPDamageMultiplierLegsFinal,
					GrenadeEMPStackFinal,
					GrenadeFlashbangStackFinal,
					GrenadeHEStackFinal,
					GrenadeIncendiaryStackFinal,
					GrenadeShockStackFinal,
					GrenadeTearGasStackFinal,
					NormalizedWeaponDamageModBonus,
					Seasons_RottenToTheCore_GlobalModifiers_BleedRadius,
					Seasons_RottenToTheCore_GlobalModifiers_HeadshotBonusTimer,
					Seasons_RottenToTheCore_GlobalModifiers_HeadshotBonusCritDamage,
					Seasons_RottenToTheCore_GlobalModifiers_CurrentHeadShotDamageBonus,
					Seasons_DangerZone_GlobalModifiers_PlayerInflictEnemyDamageExtraMultiplier,
					Seasons_DangerZone_GlobalModifiers_PlayerInflictEnemyDamageRadius,
					Seasons_DangerZone_ActivityModifiers_EnemyInflictPlayerDamageExtraMultiplier,
					Seasons_DangerZone_ActivityModifiers_EnemyInflictPlayerDamageRadius,
					Seasons_DangerZone_GroupModifiers_PlayerInflictEnemyDamageNearAllyExtraMultiplier,
					Seasons_DangerZone_GroupModifiers_PlayerInflictEnemyDamageNearAllyRadius,
					Seasons_DangerZone_GroupModifiers_EnemyInflictPlayerDamageFarAllyExtraMultiplier,
					Seasons_DangerZone_GroupModifiers_EnemyInflictPlayerDamageFarAllyRadius,
					Seasons_HandleWithCare_Active,
					Seasons_StayPut_GlobalModifiers_MaxBonusDamage,
					Seasons_StayPut_GlobalModifiers_BuildUpSpeedWhileNotMoving,
					Seasons_StayPut_GlobalModifiers_DepletionSpeedWhileMoving,
					Seasons_StayPut_GlobalModifiers_RevivedGracePeriodDuration,
					Seasons_StayPut_GroupModifiers_NearAllyRadius,
					Seasons_StayPut_GroupModifiers_NearAllyDepletionSpeed,
					Seasons_StayPut_GroupModifiers_TeamKillsRequiredAmount,
					Seasons_StayPut_GroupModifiers_TeamKillsWindowTimer,
					Seasons_StayPut_GroupModifiers_TeamKillsRewardDuration,
					Seasons_HandleWithCare_GlobalModifier_UI_ExplosionTimer,
					Seasons_PrototypeBullets_Active,
					Seasons_PrototypeBullets_MatchedWeaknessMaxHealthPercentageDamage,
					Seasons_PrototypeBullets_MatchedWeaknessDamageTakenModBonus,
					Seasons_PrototypeBullets_MatchedWeaknessDamageTakenModBonusDuration,
					Seasons_PrototypeBullets_GasBulletsAOE,
					Seasons_PrototypeBullets_MagicBulletsCooldownTime,
					Seasons_Shocker_Active
				};
			};

			class Indexer
			{
			public:
				class IndexInfo* Indices[629]; //0x0000
			};
			class IndexInfo
			{
			public:
				IndexInfo(const IndexInfo&) = delete;
				static IndexInfo& Get()
				{
					return s_Instance;
				};

			public:
				char pad_0000[8]; //0x0000
				int32_t Type; //0x0008
				char pad_000C[68]; //0x000C
				int32_t Index; //0x0050
				char pad_0054[4]; //0x0054
				char* Name; //0x0058
				char pad_0060[4]; //0x0060
				int32_t Flag; //0x0064
				char pad_0068[80]; //0x0068
				char* Dictionary; //0x00B8
				char pad_00C0[8]; //0x00C0
				char* Category; //0x00C8
				char pad_00D0[152]; //0x00D0

			public:
				bool GetAttribute(int index, uint32_t& Index);

			private:
				IndexInfo() { };

				static IndexInfo s_Instance;
			};
		};

		/* Get the GameManager aka RRClient */
		class GameManager
		{
		public:
			GameManager(const GameManager&) = delete;

			static GameManager* Get()
			{
				uintptr_t gameManager = (uintptr_t)(GetModuleHandle(NULL)) + 0x468EB28;
				if (gameManager)
				{
					std::cout << "[+] GameManager was found" << std::endl;
					return (GameManager*)gameManager;
				}
				else
				{
					std::cout << "[-] did not find GameManager" << std::endl;
					return nullptr;
				}
			}

			D3DXVECTOR2 GetScreenSize() 
			{
				return D3DXVECTOR2(ScreenHeight, ScreenWidth);
			};

		public:
			class RClientClass* RClient; //0x0000
			char pad_0008[2848]; //0x0008
			D3DXMATRIX ViewMatrix; //0x0B28
			char pad_0B68[536]; //0x0B68
			float ScreenHeight; //0x0D80
			float ScreenWidth; //0x0D84
		}; //Size: 0x0D88

		/* Get the RClient */
		class RClientClass
		{
		public:
			RClientClass(const RClientClass&) = delete;

			static RClientClass* Get()
			{
				auto RClient = TheDivisionSDK::Snowdrop::GameManager::Get()->RClient;
				if (RClient)
				{
					std::cout << "[+] RClient was found" << std::endl;
					return RClient;
				}
				else
				{
					std::cout << "[-] did not find RClient" << std::endl;
					return nullptr;
				}
			}

		public:
			char pad_0000[288]; //0x0000
			class ClientClass* Client; //0x0120
			char pad_0128[168]; //0x0128
		};

		/* Get the Client */
		class ClientClass
		{
		public:
			ClientClass(const ClientClass&) = delete;

			static ClientClass* Get()
			{
				auto Client = TheDivisionSDK::Snowdrop::GameManager::Get()->RClient->Client;
				if (Client)
				{
					std::cout << "[+] Client was found" << std::endl;
					return Client;
				}
				else
				{
					std::cout << "[-] did not find Client" << std::endl;
					return nullptr;
				}
			}

		public:
			char pad_0000[40]; //0x0000
			class WorldClass* World; //0x0028
			char pad_0030[88]; //0x0030
		};

		/* Get the World */
		class WorldClass
		{
		public:
			WorldClass(const WorldClass&) = delete;

			static WorldClass* Get()
			{
				auto World = TheDivisionSDK::Snowdrop::GameManager::Get()->RClient->Client->World;
				if (World)
				{
					std::cout << "[+] World was found" << std::endl;
					return World;
				}
				else
				{
					std::cout << "[-] did not find World" << std::endl;
					return nullptr;
				}
			}

		public:
			char pad_0000[120]; //0x0000
			class LootListClass* LootList; //0x0078
			char pad_0080[592]; //0x0080
			class CameraListClass* CameraList; //0x02D0
			char pad_02D8[360]; //0x02D8
			class EntityListClass* EntityList; //0x0440
			int32_t NumberOfEntities; //0x0448
			int32_t MaxNumberOfEntities; //0x044C
		};

		/* Get the Loot */
		namespace Loot 
		{
			/* Get the LootList */
			class LootListClass
			{
			public:
				char pad_0000[24]; //0x0000
				class LootClass* LootArray[1]; //0x0018
				int32_t LootCounter; //0x0020
			};
		};

		/* Get the Camera */
		namespace Camera 
		{
			class CameraListClass
			{
			public:
				char pad_0000[24]; //0x0000
				class CameraManagerClass* CameraManager; //0x0018
			};

			/* Get the CameraList */
			class CameraManagerClass
			{
			public:
				char pad_0000[176]; //0x0000
				class CameraClass* Camera; //0x00B0
				char pad_00B8[24]; //0x00B8
			};

			/* Get the CameraClass */
			class CameraClass
			{
			public:
				char pad_0000[120]; //0x0000
				class AgentCameraClass* AgentCamera; //0x0078
			};

			/* Get the AgentCameraClass */
			class AgentCameraClass
			{
			public:
				char pad_0000[192]; //0x0000
				float Yaw; //0x00C0
				float Pitch; //0x00C4
			};
		};

		/* Get the Entity */
		namespace Entity 
		{
			class EntityListClass
			{
			public:
				class EntityClass* EntityArray[27]; //0x0000
			};

			class EntityClass
			{
			public:
				char pad_0000[40]; //0x0000
				class EntityInfoClass* EntityInfo; //0x0028
				char pad_0030[16]; //0x0030
				D3DXMATRIX TransformMatrix; //0x0040
				D3DXVECTOR3 Position; //0x0080
				float Yaw; //0x008C
				char pad_0090[256]; //0x0090
				class DeadZoneInfoClass* DeadZoneInfo; //0x0190
				char pad_0198[40]; //0x0198
				bool IsDead; //0x01C0
				char pad_01C1[15]; //0x01C1
				class PositionDataClass* PositionData; //0x01D0
				char EntityType[8]; //0x01D8
				char pad_01E0[372]; //0x01E0
				bool IsGadget; //0x0354
				char pad_0355[27]; //0x0355
				char Name[12]; //0x0370
				char pad_037C[40]; //0x037C
				int32_t Type0; //0x03A4
				char pad_03A8[12]; //0x03A8
				int32_t Type1; //0x03B4
				char pad_03B8[24]; //0x03B8
				int32_t Level; //0x03D0
				int32_t DarkZoneLevel; //0x03D4
				char pad_03D8[12]; //0x03D8
				int32_t UndergroundLevel; //0x03E4
				char pad_03E8[8]; //0x03E8
				int32_t PvPLevel; //0x03F0
				char pad_03F4[12]; //0x03F4
				bool IsHuman; //0x0400
				char pad_0401[40]; //0x0401
				char GloballyUniqueIdentifier[37]; //0x0429
				char pad_044E[218]; //0x044E
				class AttributeClass* Attribute; //0x0528
				char pad_0530[168]; //0x0530
				class HealthClass* Health; //0x05D8
				char pad_05E0[80]; //0x05E0
				class CrosshairClass* Crosshair; //0x0630
				char pad_0638[204]; //0x0638
				D3DXVECTOR3 AimingPosition; //0x0704
				D3DXVECTOR3 AimingPosition1; //0x0710
				char pad_071C[24]; //0x071C
				int32_t SelectedWeaponIndex; //0x0734
				char pad_0738[16]; //0x0738
				bool IsFriendly; //0x0748
				char pad_0749[3]; //0x0749
				bool IsRunning; //0x074C
				char pad_074D[3]; //0x074D
				bool IsShooting; //0x0750
				char pad_0751[11]; //0x0751
				bool IsRogue; //0x075C
				char pad_075D[3]; //0x075D
				bool IsAiming; //0x0760
				char pad_0761[2]; //0x0761
				bool IsFriendlyNPC; //0x0763
				char pad_0764[19]; //0x0764
				bool IsNotHuman; //0x0777
				char pad_0778[184]; //0x0778
				int32_t PlayerType; //0x0830
			};

			class AttributeClass
			{
			public:
				struct Info
				{
					char pad_0000[4]; //0x0000
					float value; //0x0004
					char pad_0008[56]; //0x0008
				};
			public:

				Info* GetInfoByIndex(unsigned int index)
				{
					if (!m_AttributeComponent || !m_AttributeComponent->info)
						return nullptr;

					return &m_AttributeComponent->info[index];
				}

				Info* GetFireRate()
				{
					uint32_t index = 0;
					IndexModule::IndexInfo::Get().GetAttribute(IndexModule::IndexModuleClass::RPMFinal, index);
					return GetInfoByIndex(index);
				}

			private:
				char unknown[0x28];

				struct AttributeComponent
				{
					char unknown[0x78];
					Info* info;
				} *m_AttributeComponent;
			};

			class EntityInfoClass
			{
			public:
				char pad_0000[136]; //0x0000
			}; //Size: 0x0088

			class DeadZoneInfoClass
			{
			public:
				char pad_0000[136]; //0x0000
			}; //Size: 0x0088

			class PositionDataClass
			{
			public:
				char pad_0000[544]; //0x0000
				class PlayerCoordinateClass* PlayerCoordinate; //0x0220
				char pad_0228[4664]; //0x0228
				class BoneMatrixClass* BoneMatrix; //0x1460
				int32_t MaxBones; //0x1468
			}; //Size: 0x146C

			class BoneMatrixClass
			{
			public:
				D3DXMATRIX Lowerbody; //0x0000
				D3DXMATRIX Centerbody; //0x0040
				D3DXMATRIX Midbody; //0x0080
				D3DXMATRIX Upperbody; //0x00C0
				D3DXMATRIX Neck; //0x0100
				D3DXMATRIX Head; //0x0140
				D3DXMATRIX bone6; //0x0180
				D3DXMATRIX LeftShoulder; //0x01C0
				D3DXMATRIX bone8; //0x0200
				D3DXMATRIX bone9; //0x0240
				D3DXMATRIX bone10; //0x0280
				D3DXMATRIX LeftHand; //0x02C0
				D3DXMATRIX bone12; //0x0300
				D3DXMATRIX bone13; //0x0340
				D3DXMATRIX bone14; //0x0380
				D3DXMATRIX bone15; //0x03C0
				D3DXMATRIX bone16; //0x0400
				D3DXMATRIX bone17;
				D3DXMATRIX bone18;
				D3DXMATRIX bone19;
				D3DXMATRIX bone20; //0x0280
				D3DXMATRIX bone21; //0x02C0
				D3DXMATRIX bone22; //0x0300
				D3DXMATRIX bone23; //0x0340
				D3DXMATRIX bone24; //0x0380
				D3DXMATRIX bone25; //0x03C0
				D3DXMATRIX bone26; //0x0400
				D3DXMATRIX bone27;
				D3DXMATRIX bone28;
				D3DXMATRIX bone29;
				D3DXMATRIX bone30; //0x0280
				D3DXMATRIX bone31; //0x02C0
				D3DXMATRIX bone32; //0x0300
				D3DXMATRIX bone33; //0x0340
				D3DXMATRIX bone34; //0x0380
				D3DXMATRIX bone35; //0x03C0
				D3DXMATRIX bone36; //0x0400
				D3DXMATRIX RightShoulder;
				D3DXMATRIX bone38;
				D3DXMATRIX bone39;
				D3DXMATRIX bone40; //0x0280
				D3DXMATRIX RightHand; //0x02C0
				D3DXMATRIX bone42; //0x0300
				D3DXMATRIX bone43; //0x0340
				D3DXMATRIX bone44; //0x0380
				D3DXMATRIX bone45; //0x03C0
				D3DXMATRIX bone46; //0x0400
				D3DXMATRIX bone47;
				D3DXMATRIX bone48;
				D3DXMATRIX bone49;
				D3DXMATRIX bone50; //0x0280
				D3DXMATRIX bone51; //0x02C0
				D3DXMATRIX bone52; //0x0300
				D3DXMATRIX bone53; //0x0340
				D3DXMATRIX bone54; //0x0380
				D3DXMATRIX bone55; //0x03C0
				D3DXMATRIX bone56; //0x0400
				D3DXMATRIX bone57;
				D3DXMATRIX bone58;
				D3DXMATRIX bone59;
				D3DXMATRIX bone60; //0x0280
				D3DXMATRIX bone61; //0x02C0
				D3DXMATRIX bone62; //0x0300
				D3DXMATRIX bone63; //0x0340
				D3DXMATRIX bone64; //0x0380
				D3DXMATRIX bone65; //0x03C0
				D3DXMATRIX bone66; //0x0400
				D3DXMATRIX bone67;
				D3DXMATRIX bone68;
				D3DXMATRIX bone69;
				D3DXMATRIX bone70; //0x0280
				D3DXMATRIX bone71; //0x02C0
				D3DXMATRIX bone72; //0x0300
				D3DXMATRIX bone73; //0x0340
				D3DXMATRIX RightMidLeg; //0x0380
				D3DXMATRIX bone75; //0x03C0
				D3DXMATRIX LeftLowerLeg; //0x0400LeftLowerLeg
				D3DXMATRIX bone77;
				D3DXMATRIX bone78;
				D3DXMATRIX RightUpperLeg;
				D3DXMATRIX bone80; //0x0280
				D3DXMATRIX bone81; //0x02C0
				D3DXMATRIX LeftMidLeg; //0x0300
				D3DXMATRIX bone83; //0x0340
				D3DXMATRIX RightLowerLeg; //0x0380
				D3DXMATRIX bone85; //0x03C0
				D3DXMATRIX bone86; //0x0400
				D3DXMATRIX LeftUpperLeg;
				D3DXMATRIX bone88;
				D3DXMATRIX bone89;
				D3DXMATRIX bone90; //0x0280
				D3DXMATRIX bone91; //0x02C0
				D3DXMATRIX bone92; //0x0300
				D3DXMATRIX bone93; //0x0340
				D3DXMATRIX bone94; //0x0380
				D3DXMATRIX bone95; //0x03C0
			}; //Size: 0x0440

			class PlayerCoordinateClass
			{
			public:
				char pad_0000[632]; //0x0000
				class LocalPlayerCoordinateClass* LocalPlayerCoordinate; //0x0278
			}; //Size: 0x0280

			class LocalPlayerCoordinateClass
			{
			public:
				char pad_0000[112]; //0x0000
				float PositionX; //0x0070
				float PositionY; //0x0074
				float PositionZ; //0x0078
			}; //Size: 0x007C

			class CrosshairClass
			{
			public:
				char pad_0000[13128]; //0x0000
				float Pitch; //0x3348
				char pad_334C[32]; //0x334C
				float Yaw; //0x336C
				char pad_3370[2612]; //0x3370
			};

			class HealthClass
			{
			public:
				char pad_0000[168]; //0x0000
				int32_t CurrentHealth; //0x00A8
				int32_t MaxHealth; //0x00AC
			};

		};
	};
};