#ifndef __FINANCES_H
#define __FINANCES_H

void GameInitFinances();
void EnterFinances();
void ExitFinances();
void HandleFinances();
void RenderFinances();

#define	FINANCES_DATA_FILE					"Temp/finances.dat"

enum
{
	ACCRUED_INTEREST,
	ANONYMOUS_DEPOSIT,
	TRANSACTION_FEE,
	HIRED_MERC,
	BOBBYR_PURCHASE,
	PAY_SPECK_FOR_MERC,
	MEDICAL_DEPOSIT,
	IMP_PROFILE,
	PURCHASED_INSURANCE,
	REDUCED_INSURANCE,
	EXTENDED_INSURANCE,
	CANCELLED_INSURANCE,
	INSURANCE_PAYOUT,
	EXTENDED_CONTRACT_BY_1_DAY,
	EXTENDED_CONTRACT_BY_1_WEEK,
	EXTENDED_CONTRACT_BY_2_WEEKS,
	DEPOSIT_FROM_GOLD_MINE,
	DEPOSIT_FROM_SILVER_MINE,
	PURCHASED_FLOWERS,
	FULL_MEDICAL_REFUND,
	PARTIAL_MEDICAL_REFUND,
	NO_MEDICAL_REFUND,
	PAYMENT_TO_NPC,
	TRANSFER_FUNDS_TO_MERC,
	TRANSFER_FUNDS_FROM_MERC,
	TRAIN_TOWN_MILITIA,
	PURCHASED_ITEM_FROM_DEALER,
	MERC_DEPOSITED_MONEY_TO_PLAYER_ACCOUNT,

};

void AddTransactionToPlayersBook(UINT8 ubCode, UINT8 ubSecondCode, UINT32 uiDate, INT32 iAmount);
INT32 GetProjectedTotalDailyIncome( void );

void SPrintMoney(wchar_t* Str, INT32 Amount);

#endif
