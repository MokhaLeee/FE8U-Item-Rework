#include "prep-item.h"



#define TH_PREP_ITEM gUnknown_02013498
extern struct TextHandle gUnknown_02013498[];






void PrepScreenItemUseScreen_OnUpdateSMS (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_OnInit (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_InitDisplay (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_OnIdle (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_AreUSureBoxInit (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_AreUSureBoxLoop (struct Proc_PrepItemUse*);
extern const struct ProcCmd gProc_StatScreenItemStatBoosterEffect[];
void NewFadeIn (ProcPtr);
void NewFadeOut (ProcPtr);
int FadeOutExists (void);
int FadeInExists(void);
void WaitForFade (ProcPtr);
void StartFadeInBlackMedium (void);
void StartPrepScreenPromotion (struct Proc_PrepItemUse*);
static const uint32_t PrepScreenItemUseScreen_Promo_09CC9C = 0x809CC9C+1;
static const uint32_t PrepScreenItemUseScreen_Promo_09CC60 = 0x809CC60+1;
static const uint32_t PrepScreenItemUseScreen_Promo_002A6C = 0x8002A6C+1;
static const uint32_t PrepScreenItemUseScreen_OnEnd = 0x809C940+1;
void DrawSpecialUiChar(u16* out, int color, int chr);

// const struct ProcCmd gProc_StatScreenItemJunaFruitEffect[]; // 0x8A191C4
static const uint32_t gProc_StatScreenItemJunaFruitEffect = 0x8A191C4;
// static void PrepScreenItemUseScreen_HandleItemEffect (struct Proc_PrepItemUse*);
static const uint32_t PrepScreenItemUseScreen_HandleItemEffect = 0x809CB39;










// 8A19064
const struct ProcCmd _gProc_PrepScreenItemUseScreen[] = {
	
	PROC_NAME ("E_PREP_ITEM_USE"),
	PROC_YIELD,

// Label 0: init	
PROC_LABEL(0),	
	PROC_CALL (PrepScreenItemUseScreen_OnInit),
	PROC_CALL (PrepScreenItemUseScreen_InitDisplay),
	PROC_CALL_ARG (NewFadeIn, 0x10),
	PROC_WHILE (FadeInExists),

// Label 1: main Loop
PROC_LABEL(1),	
	PROC_REPEAT (PrepScreenItemUseScreen_OnIdle),


// Label 2: "are you sure" text
PROC_LABEL(2),	
	PROC_CALL (PrepScreenItemUseScreen_AreUSureBoxInit),
	PROC_REPEAT (PrepScreenItemUseScreen_AreUSureBoxLoop),
	PROC_GOTO(1),	// Back to main loop

	
// Label 3: handle item effect
PROC_LABEL(3),
	PROC_CALL ((void*)PrepScreenItemUseScreen_HandleItemEffect),
	PROC_START_CHILD_BLOCKING (gProc_StatScreenItemStatBoosterEffect),
	PROC_GOTO(1),	// Back to main loop


// Label 4:  juna fruit
PROC_LABEL(4),
	PROC_START_CHILD_BLOCKING ((void*)gProc_StatScreenItemJunaFruitEffect),
	PROC_GOTO(1),	// Back to main loop


// Label 5:  promote
PROC_LABEL(5),
	PROC_CALL_ARG (NewFadeOut, 0x10),
	PROC_WHILE (FadeOutExists),
	PROC_CALL (StartFadeInBlackMedium),
	PROC_REPEAT (WaitForFade),
	PROC_CALL (StartPrepScreenPromotion),
	PROC_SLEEP(8),
	PROC_CALL ((void*)PrepScreenItemUseScreen_Promo_09CC9C),
	PROC_SLEEP (8),
	PROC_CALL ((void*)PrepScreenItemUseScreen_Promo_09CC60),
	PROC_CALL (PrepScreenItemUseScreen_InitDisplay),
	PROC_CALL_ARG (NewFadeIn, 8),
	PROC_WHILE (FadeInExists),
	PROC_WHILE ((void*)PrepScreenItemUseScreen_Promo_002A6C),
	PROC_GOTO(1),	// Back to main loop
	

// Label 6:  fade out into end
PROC_LABEL(6),
	PROC_CALL_ARG (NewFadeOut, 0x10),
	PROC_WHILE (FadeOutExists),
	
// Label 7:  end
PROC_LABEL(7),
	PROC_CALL ((void*)PrepScreenItemUseScreen_OnEnd),
	PROC_END,

};






// Start prep-item-use proc
void StartPrepScreenItemUseScreen (struct Unit* unit, ProcPtr parent) {
	
	struct Proc_PrepItemUse* child = 
		(struct Proc_PrepItemUse*)
		Proc_StartBlocking(_gProc_PrepScreenItemUseScreen, parent);
	
	child->unit = unit;
	
}







// ====================================================
// -------------- Inside Proc Funcs -------------------
// ====================================================

// 0x809C4E4
void PrepScreenItemUseScreen_InitDisplay (struct Proc_PrepItemUse* proc) {
	
	// Common defs
	extern const struct FaceVramEntry gFaceConfig_8205C70[];
	extern u16 gBgConfig_8A181E8[];
	void SetupFaceGfxData(const struct FaceVramEntry*);
	void RestartScreenMenuScrollingBg();
	void NewFace2(int, int, int, int, int);
	static void (*PrepScreenItemUseScreen_Init_DrawSomeGfx1)(int, int) = (const void*) 0x8098C3D;
	static void (*PrepScreenItemUseScreen_Init_DrawSomeGfx2)(int, int) = (const void*) 0x8098C8D;
	extern u8 gGenericBuffer[0x200];
	int StartSmallBrownNameBoxes(int, int, int, int, int, ProcPtr);
	static void (*MaybeConfigSmallBrownNameBox)(int, int, int, int) = (const void*) 0x80ADBFD;
	extern const struct ProcCmd gProc_8A20B4C[];
	void ResetPrepScreenHandCursor(struct Proc_PrepItemUse*);
	static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
	void Get6CDifferedLoop6C(void*, ProcPtr);
	void SetColorEffectsFirstTarget(int bg0, int bg1, int bg2, int bg3, int obj);
	static struct Proc* (*_StartHelpPromptSprite)(int x, int y, int palid, ProcPtr) = (const void*) 0x80894e1;
	static void (*PrepScreenItemUseScreen_Init_HandsFunc) (int, int, int, int) = (const void*) 0x80AD51D;
	void SMS_RegisterUsage(int);
	
	
	// Datas
	#define Gfx_PrepItemUseScreen gUnknown_08A1BAB8
	#define Tsa_PrepItemUseScreen gUnknown_08A1BAE4
	extern const u8 gUnknown_08A1BAB8[];
	extern const u8 gUnknown_08A1BAE4[];
	
	
	// Some funcs that maybe work on later
	void DrawPrepScreenItemUseStatLabels(struct Unit*);
	void DrawPrepScreenItemUseStatBars(struct Unit*, int);
	void DrawPrepScreenItemUseStatValues(struct Unit*);
	void DrawPrepScreenItemUseItemUseDesc(struct Unit*, uint32_t);
	static void (*DrawPrepScreenItemUseItems)(void*, struct TextHandle*, struct Unit*, int) = (const void*) 0x809B74C+1;
	
	
	// begin
	char* str;
	int tmp;
	
	gLCDControlBuffer.dispcnt.mode = 0;
	
	SetupBackgrounds(gBgConfig_8A181E8);
	SetupFaceGfxData(gFaceConfig_8205C70);
	
	proc->item34 = 0xFF;
	
	BG_Fill(BG_GetMapBuffer(0), 0);
	BG_Fill(BG_GetMapBuffer(1), 0);
	BG_Fill(BG_GetMapBuffer(2), 0);
	
	
	gLCDControlBuffer.bg0cnt.priority = 1;
	gLCDControlBuffer.bg1cnt.priority = 2;
	gLCDControlBuffer.bg2cnt.priority = 0;
	gLCDControlBuffer.bg3cnt.priority = 3;
	
	Font_InitForUIDefault();
	ResetIconGraphics_();
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	SetupMapSpritesPalettes();
	
	BG_SetPosition(0, 0,0);
	BG_SetPosition(1, 0,0);
	BG_SetPosition(2, 0,0);
	
	LoadDialogueBoxGfx(BG_CHAR_ADDR(5), -1);
	LoadIconPalettes(4);
	RestartScreenMenuScrollingBg();
	
	for (int i = 0; i < 5; i++)
		Text_Allocate( &TH_PREP_ITEM[15+i], 7);
	
	
	for (int i = 0; i < 8; i++)
		Text_Init( &TH_PREP_ITEM[i], 3);
	
	Text_Init( &TH_PREP_ITEM[8], 8);
	Text_Init( &TH_PREP_ITEM[25], 15);
	Text_Init( &TH_PREP_ITEM[26], 15);
	Text_Init( &TH_PREP_ITEM[27], 14);
	Text_Init( &TH_PREP_ITEM[28], 8);
	Text_Init( &TH_PREP_ITEM[29], 15);
	
	DrawPrepScreenItemUseStatLabels(proc->unit);
	DrawPrepScreenItemUseStatValues(proc->unit);
	DrawPrepScreenItemUseStatBars(proc->unit,0);
		
	NewFace2(0, GetUnitPortraitId(proc->unit), 0x40, -4, 0x203);
	PrepScreenItemUseScreen_Init_DrawSomeGfx1( 0x6000, 5);
	PrepScreenItemUseScreen_Init_DrawSomeGfx2( 0x800, 10);
	
	CopyDataWithPossibleUncomp(
		Gfx_PrepItemUseScreen, 
		(void*) (BG_VRAM + 0x440)
	);
	
	CopyDataWithPossibleUncomp(
		Tsa_PrepItemUseScreen,
		gGenericBuffer
	);
	
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	BG_EnableSyncByMask(0b111);
	
	// (int objNode, int tileOffset, int palIndex, int oam2base, int oam0base, ProcPtr parent);
	StartSmallBrownNameBoxes(0xD, 0xE00, 0xF, 0xC00, 0, proc);
	MaybeConfigSmallBrownNameBox(0, -0x28, -1, 1);
	
	str = GetStringFromIndex( proc->unit->pCharacterData->nameTextId );
	
	DrawTextInline(
		0, gBG0TilemapBuffer, 
		TEXT_COLOR_NORMAL, 
		(0x30 - GetStringTextWidth(str))/2,
		6, str
	);
	
	// sub_80AC9C0
	Proc_Start(gProc_8A20B4C, proc);
	
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 1);
	Get6CDifferedLoop6C(PrepScreenItemUseScreen_OnUpdateSMS, proc);
	
	
	gLCDControlBuffer.dispcnt.win0_on = 1;
	gLCDControlBuffer.dispcnt.win1_on = 0;
	gLCDControlBuffer.dispcnt.objWin_on = 0;
	
	gLCDControlBuffer.win0_top = 0x5E;
	gLCDControlBuffer.win0_bottom = 0x92;
	gLCDControlBuffer.win0_left = 0x68;
	gLCDControlBuffer.win0_right = 0xF0;
	
	gLCDControlBuffer.wincnt.win0_enableBg0 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg1 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg2 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg3 = 1;
	gLCDControlBuffer.wincnt.win0_enableObj = 1;
	gLCDControlBuffer.wincnt.win0_enableBlend = 1;
	
	gLCDControlBuffer.wincnt.wout_enableBg0 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg1 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg2 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg3 = 1;
	gLCDControlBuffer.wincnt.wout_enableObj = 1;
	gLCDControlBuffer.wincnt.wout_enableBlend = 0;
	
	
	
	SetSpecialColorEffectsParameters(3,0,0,8);
	SetColorEffectsFirstTarget(0,0,0,1,0);
	NewGreenTextColorManager((ProcPtr)proc);
	
	_StartHelpPromptSprite(0xC0, 0x90, 9, proc);
	DrawPrepScreenItemUseItemUseDesc(proc->unit, proc->item30);
	DrawPrepScreenItemUseItems(
		TILEMAP_LOCATED(gBG0TilemapBuffer, 2, 9),
		&TH_PREP_ITEM[15],
		proc->unit, 1
	);
	
	tmp = (proc->item30 & 0b111) << 4;
	PrepScreenItemUseScreen_Init_HandsFunc(tmp+0x10, tmp+0x48, 0xB, 0x800);
	

	SMS_RegisterUsage(GetUnitSMSId(proc->unit));
	SMS_FlushIndirect();
	
	
	#undef Gfx_PrepItemUseScreen
	#undef Tsa_PrepItemUseScreen
}




void DrawPrepScreenItemUseStatLabels(struct Unit* unit) {
	
	char* str;
	
	for( int i = 0; i < 8; i++ )
		Text_Clear( &TH_PREP_ITEM[i] );
	
	DrawTextInline(
		&TH_PREP_ITEM[0],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 3),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4E9 ) // HP
	);
	
	
	if ( 0 == UnitHasMagicRank(unit) )
		DrawTextInline(
			&TH_PREP_ITEM[1],
			TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 5),
			TEXT_COLOR_GOLD,
			0, 0, GetStringFromIndex( 0x4FE ) // Str
		);
	else
		DrawTextInline(
			&TH_PREP_ITEM[1],
			TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 5),
			TEXT_COLOR_GOLD,
			0, 0, GetStringFromIndex( 0x4FF ) // Mag
		);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[2],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 7),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EC ) // Skill
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[3],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 9),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4ED ) // Spd
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[4],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 3),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EE ) // Luck
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[5],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 5),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EF ) // Def
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[6],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 7),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4F0 ) // Res
	);
	
	DrawTextInline(
		&TH_PREP_ITEM[7],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 9),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4F7 ) // Con
	);
	
	str = GetStringFromIndex( unit->pClassData->nameTextId );
	
	DrawTextInline(
		&TH_PREP_ITEM[8],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 21, 1),
		TEXT_COLOR_NORMAL,
		GetStringTextCenteredPos(0x40, str), 
		0, 
		str // unit class
	);
	
	
	DrawSpecialUiChar( TILEMAP_LOCATED(gBG2TilemapBuffer, 17, 1), 3, 0x24);
	DrawSpecialUiChar( TILEMAP_LOCATED(gBG2TilemapBuffer, 18, 1), 3, 0x25);
	
}




#undef TH_PREP_ITEM // $02013498