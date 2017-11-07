#include <vector>

#include "Debug.h"
#include "FileMan.h"
#include "LoadSaveData.h"
#include "LoadSaveTacticalStatusType.h"
#include "Overhead.h"


void ExtractTacticalStatusTypeFromFile(HWFILE const f, bool stracLinuxFormat)
{
	UINT32 dataSize = stracLinuxFormat ? TACTICAL_STATUS_TYPE_SIZE_STRAC_LINUX : TACTICAL_STATUS_TYPE_SIZE;
	std::vector<BYTE> data(dataSize);
	FileRead(f, data.data(), dataSize);

	TacticalStatusType* const s = &gTacticalStatus;
	const BYTE* d = data.data();
	EXTR_U32(d, s->uiFlags)
	FOR_EACH(TacticalTeamType, t, s->Team)
	{
		EXTR_U8(d, t->bFirstID)
		EXTR_U8(d, t->bLastID)
		EXTR_SKIP(d, 2)
		EXTR_U32(d, t->RadarColor)
		EXTR_I8(d, t->bSide)
		EXTR_I8(d, t->bMenInSector)
		EXTR_SOLDIER(d, t->last_merc_to_radio)
		EXTR_SKIP(d, 1)
		EXTR_I8(d, t->bAwareOfOpposition)
		EXTR_I8(d, t->bHuman)
		EXTR_SKIP(d, 2)
	}
	EXTR_U8(d, s->ubCurrentTeam)
	EXTR_SKIP(d, 1)
	EXTR_I16(d, s->sSlideTarget)
	EXTR_SKIP(d, 4)
	EXTR_U32(d, s->uiTimeSinceMercAIStart)
	EXTR_I8(d, s->fPanicFlags)
	EXTR_SKIP(d, 5)
	EXTR_U8(d, s->ubSpottersCalledForBy)
	EXTR_SOLDIER(d, s->the_chosen_one)
	EXTR_U32(d, s->uiTimeOfLastInput)
	EXTR_U32(d, s->uiTimeSinceDemoOn)
	EXTR_SKIP(d, 7)
	EXTR_BOOLA(d, s->fCivGroupHostile, lengthof(s->fCivGroupHostile))
	EXTR_U8(d, s->ubLastBattleSectorX)
	EXTR_U8(d, s->ubLastBattleSectorY)
	EXTR_BOOL(d, s->fLastBattleWon)
	EXTR_SKIP(d, 2)
	EXTR_BOOL(d, s->fVirginSector)
	EXTR_BOOL(d, s->fEnemyInSector)
	EXTR_BOOL(d, s->fInterruptOccurred)
	EXTR_I8(d, s->bRealtimeSpeed)
	EXTR_SKIP(d, 2)
	EXTR_SOLDIER(d, s->enemy_sighting_on_their_turn_enemy)
	EXTR_SKIP(d, 1)
	EXTR_BOOL(d, s->fEnemySightingOnTheirTurn)
	EXTR_BOOL(d, s->fAutoBandageMode)
	EXTR_U8(d, s->ubAttackBusyCount)
	EXTR_SKIP(d, 1)
	EXTR_U8(d, s->ubEngagedInConvFromActionMercID)
	EXTR_SKIP(d, 1)
	EXTR_U16(d, s->usTactialTurnLimitCounter)
	EXTR_BOOL(d, s->fInTopMessage)
	EXTR_U8(d, s->ubTopMessageType)
	if(stracLinuxFormat)
	{
		EXTR_SKIP(d, 82);
	}
	else
	{
		EXTR_SKIP(d, 40);
	}
	EXTR_U16(d, s->usTactialTurnLimitMax)
	if(stracLinuxFormat)
	{
		EXTR_SKIP(d, 2);
	}
	EXTR_U32(d, s->uiTactialTurnLimitClock)
	EXTR_BOOL(d, s->fTactialTurnLimitStartedBeep)
	EXTR_I8(d, s->bBoxingState)
	EXTR_I8(d, s->bConsNumTurnsNotSeen)
	EXTR_U8(d, s->ubArmyGuysKilled)
	EXTR_I16A(d, s->sPanicTriggerGridNo, lengthof(s->sPanicTriggerGridNo))
	EXTR_I8A(d, s->bPanicTriggerIsAlarm, lengthof(s->bPanicTriggerIsAlarm))
	EXTR_U8A(d, s->ubPanicTolerance, lengthof(s->ubPanicTolerance))
	EXTR_BOOL(d, s->fAtLeastOneGuyOnMultiSelect)
	EXTR_SKIP(d, 2)
	EXTR_BOOL(d, s->fKilledEnemyOnAttack)
	EXTR_SOLDIER(d, s->enemy_killed_on_attack)
	EXTR_I8(d, s->bEnemyKilledOnAttackLevel)
	EXTR_U16(d, s->ubEnemyKilledOnAttackLocation)
	EXTR_BOOL(d, s->fItemsSeenOnAttack)
	EXTR_SOLDIER(d, s->items_seen_on_attack_soldier)
	EXTR_SKIP(d, 2)
	EXTR_U16(d, s->usItemsSeenOnAttackGridNo)
	EXTR_BOOL(d, s->fLockItemLocators)
	EXTR_U8(d, s->ubLastQuoteSaid)
	EXTR_U8(d, s->ubLastQuoteProfileNUm)
	EXTR_BOOL(d, s->fCantGetThrough)
	EXTR_I16(d, s->sCantGetThroughGridNo)
	EXTR_I16(d, s->sCantGetThroughSoldierGridNo)
	EXTR_SOLDIER(d, s->cant_get_through)
	EXTR_BOOL(d, s->fDidGameJustStart)
	EXTR_SKIP(d, 1)
	EXTR_U8(d, s->ubLastRequesterTargetID)
	EXTR_SKIP(d, 1)
	EXTR_U8(d, s->ubNumCrowsPossible)
	EXTR_SKIP(d, 4)
	EXTR_BOOL(d, s->fUnLockUIAfterHiddenInterrupt)
	EXTR_I8A(d, s->bNumFoughtInBattle, lengthof(s->bNumFoughtInBattle))
	EXTR_SKIP(d, 1)
	EXTR_U32(d, s->uiDecayBloodLastUpdate)
	EXTR_U32(d, s->uiTimeSinceLastInTactical)
	EXTR_BOOL(d, s->fHasAGameBeenStarted)
	EXTR_I8(d, s->bConsNumTurnsWeHaventSeenButEnemyDoes)
	EXTR_BOOL(d, s->fSomeoneHit)
	EXTR_SKIP(d, 1)
	EXTR_U32(d, s->uiTimeSinceLastOpplistDecay)
	EXTR_I8(d, s->bMercArrivingQuoteBeingUsed)
	EXTR_SOLDIER(d, s->enemy_killed_on_attack_killer)
	EXTR_BOOL(d, s->fCountingDownForGuideDescription)
	EXTR_I8(d, s->bGuideDescriptionCountDown)
	EXTR_U8(d, s->ubGuideDescriptionToUse)
	EXTR_I8(d, s->bGuideDescriptionSectorX)
	EXTR_I8(d, s->bGuideDescriptionSectorY)
	EXTR_I8(d, s->fEnemyFlags)
	EXTR_BOOL(d, s->fAutoBandagePending)
	EXTR_BOOL(d, s->fHasEnteredCombatModeSinceEntering)
	EXTR_BOOL(d, s->fDontAddNewCrows)
	EXTR_SKIP(d, 1)
	EXTR_U16(d, s->sCreatureTenseQuoteDelay)
	EXTR_SKIP(d, 2)
	EXTR_U32(d, s->uiCreatureTenseQuoteLastUpdate)
	Assert(d == (data.data() + dataSize));
}


void InjectTacticalStatusTypeIntoFile(HWFILE const f)
{
	BYTE data[316];
	BYTE*                     d = data;
	TacticalStatusType* const s = &gTacticalStatus;
	INJ_U32(d, s->uiFlags)
	FOR_EACH(TacticalTeamType const, t, s->Team)
	{
		INJ_U8(d, t->bFirstID)
		INJ_U8(d, t->bLastID)
		INJ_SKIP(d, 2)
		INJ_U32(d, t->RadarColor)
		INJ_I8(d, t->bSide)
		INJ_I8(d, t->bMenInSector)
		INJ_SOLDIER(d, t->last_merc_to_radio)
		INJ_SKIP(d, 1)
		INJ_I8(d, t->bAwareOfOpposition)
		INJ_I8(d, t->bHuman)
		INJ_SKIP(d, 2)
	}
	INJ_U8(d, s->ubCurrentTeam)
	INJ_SKIP(d, 1)
	INJ_I16(d, s->sSlideTarget)
	INJ_SKIP(d, 4)
	INJ_U32(d, s->uiTimeSinceMercAIStart)
	INJ_I8(d, s->fPanicFlags)
	INJ_SKIP(d, 5)
	INJ_U8(d, s->ubSpottersCalledForBy)
	INJ_SOLDIER(d, s->the_chosen_one)
	INJ_U32(d, s->uiTimeOfLastInput)
	INJ_U32(d, s->uiTimeSinceDemoOn)
	INJ_SKIP(d, 7)
	INJ_BOOLA(d, s->fCivGroupHostile, lengthof(s->fCivGroupHostile))
	INJ_U8(d, s->ubLastBattleSectorX)
	INJ_U8(d, s->ubLastBattleSectorY)
	INJ_BOOL(d, s->fLastBattleWon)
	INJ_SKIP(d, 2)
	INJ_BOOL(d, s->fVirginSector)
	INJ_BOOL(d, s->fEnemyInSector)
	INJ_BOOL(d, s->fInterruptOccurred)
	INJ_I8(d, s->bRealtimeSpeed)
	INJ_SKIP(d, 2)
	INJ_SOLDIER(d, s->enemy_sighting_on_their_turn_enemy)
	INJ_SKIP(d, 1)
	INJ_BOOL(d, s->fEnemySightingOnTheirTurn)
	INJ_BOOL(d, s->fAutoBandageMode)
	INJ_U8(d, s->ubAttackBusyCount)
	INJ_SKIP(d, 1)
	INJ_U8(d, s->ubEngagedInConvFromActionMercID)
	INJ_SKIP(d, 1)
	INJ_U16(d, s->usTactialTurnLimitCounter)
	INJ_BOOL(d, s->fInTopMessage)
	INJ_U8(d, s->ubTopMessageType)
	INJ_SKIP(d, 40)
	INJ_U16(d, s->usTactialTurnLimitMax)
	INJ_U32(d, s->uiTactialTurnLimitClock)
	INJ_BOOL(d, s->fTactialTurnLimitStartedBeep)
	INJ_I8(d, s->bBoxingState)
	INJ_I8(d, s->bConsNumTurnsNotSeen)
	INJ_U8(d, s->ubArmyGuysKilled)
	INJ_I16A(d, s->sPanicTriggerGridNo, lengthof(s->sPanicTriggerGridNo))
	INJ_I8A(d, s->bPanicTriggerIsAlarm, lengthof(s->bPanicTriggerIsAlarm))
	INJ_U8A(d, s->ubPanicTolerance, lengthof(s->ubPanicTolerance))
	INJ_BOOL(d, s->fAtLeastOneGuyOnMultiSelect)
	INJ_SKIP(d, 2)
	INJ_BOOL(d, s->fKilledEnemyOnAttack)
	INJ_SOLDIER(d, s->enemy_killed_on_attack)
	INJ_I8(d, s->bEnemyKilledOnAttackLevel)
	INJ_U16(d, s->ubEnemyKilledOnAttackLocation)
	INJ_BOOL(d, s->fItemsSeenOnAttack)
	INJ_SOLDIER(d, s->items_seen_on_attack_soldier)
	INJ_SKIP(d, 2)
	INJ_U16(d, s->usItemsSeenOnAttackGridNo)
	INJ_BOOL(d, s->fLockItemLocators)
	INJ_U8(d, s->ubLastQuoteSaid)
	INJ_U8(d, s->ubLastQuoteProfileNUm)
	INJ_BOOL(d, s->fCantGetThrough)
	INJ_I16(d, s->sCantGetThroughGridNo)
	INJ_I16(d, s->sCantGetThroughSoldierGridNo)
	INJ_SOLDIER(d, s->cant_get_through)
	INJ_BOOL(d, s->fDidGameJustStart)
	INJ_SKIP(d, 1)
	INJ_U8(d, s->ubLastRequesterTargetID)
	INJ_SKIP(d, 1)
	INJ_U8(d, s->ubNumCrowsPossible)
	INJ_SKIP(d, 4)
	INJ_BOOL(d, s->fUnLockUIAfterHiddenInterrupt)
	INJ_I8A(d, s->bNumFoughtInBattle, lengthof(s->bNumFoughtInBattle))
	INJ_SKIP(d, 1)
	INJ_U32(d, s->uiDecayBloodLastUpdate)
	INJ_U32(d, s->uiTimeSinceLastInTactical)
	INJ_BOOL(d, s->fHasAGameBeenStarted)
	INJ_I8(d, s->bConsNumTurnsWeHaventSeenButEnemyDoes)
	INJ_BOOL(d, s->fSomeoneHit)
	INJ_SKIP(d, 1)
	INJ_U32(d, s->uiTimeSinceLastOpplistDecay)
	INJ_I8(d, s->bMercArrivingQuoteBeingUsed)
	INJ_SOLDIER(d, s->enemy_killed_on_attack_killer)
	INJ_BOOL(d, s->fCountingDownForGuideDescription)
	INJ_I8(d, s->bGuideDescriptionCountDown)
	INJ_U8(d, s->ubGuideDescriptionToUse)
	INJ_I8(d, s->bGuideDescriptionSectorX)
	INJ_I8(d, s->bGuideDescriptionSectorY)
	INJ_I8(d, s->fEnemyFlags)
	INJ_BOOL(d, s->fAutoBandagePending)
	INJ_BOOL(d, s->fHasEnteredCombatModeSinceEntering)
	INJ_BOOL(d, s->fDontAddNewCrows)
	INJ_SKIP(d, 1)
	INJ_U16(d, s->sCreatureTenseQuoteDelay)
	INJ_SKIP(d, 2)
	INJ_U32(d, s->uiCreatureTenseQuoteLastUpdate)
	Assert(d == endof(data));

	FileWrite(f, data, sizeof(data));
}
