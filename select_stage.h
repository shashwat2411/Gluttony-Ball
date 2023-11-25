#pragma once

#ifndef SELECT_STAGE_H_

#define	SELECT_STAGE_H_

#include	"include_lib.h"

#define	BUTTON_SIZE_W	(90)
#define	BUTTON_SIZE_H	(100)

void	InitSelectStage();		//	ステージ選択初期化
void	UninitSelectStage();	//	ステージ選択終了処理
void	UpdateSelectStage();	//	ステージ選択更新処理
void	DrawSelectStage();		//	ステージ選択描画処理

const	int&	GetCurrentStageNum();

#endif // !SELECT_STAGE_H_




