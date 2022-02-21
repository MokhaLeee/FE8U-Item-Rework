#pragma once

// ====================================================

// C-Lib version: FE-CLib-Decompatible
// https://github.com/boviex/FE-CLib-Decompatible.git

#include "gbafe.h"

// ====================================================




struct Proc_PrepItemUse
{
	/* 00 */ PROC_HEADER;
	/* 2C */ struct Unit* unit;
	
	/* 30 */ uint32_t item_slot :3;
	/* 30 */ uint32_t item_unk30 :29;
	
	/* 34 */ uint32_t item34;
	/* 38 */ uint32_t item38_rText;
};