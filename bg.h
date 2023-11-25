#pragma once

#ifndef BG_H_

#define	BG_H_

#include	"include_lib.h"

enum BG_SCENE
{
	BG_TITLE,
	BG_SELECT_DATA,
	BG_SELECT_STAGE,
	BG_TUTORIAL1,
	BG_TUTORIAL2,
	BG_STAGE1,
	BG_STAGE2,
	BG_STAGE3,
	BG_RESULT,
};

void	InitBG();	//	背景初期化
void	UninitBG();	//	背景終了処理
void	UpdateBG();	//	背景更新処理
void	DrawBG();	//	背景描画処理

BG_SCENE GetBGScene();	//　現在の背景シーンを取得
//void	SetBGScene(BG_SCENE scene);	//　背景シーンをセット
void	SetBGScene(bool value);	//　チュートリアルのフラグをセット


#endif // !BG_H

