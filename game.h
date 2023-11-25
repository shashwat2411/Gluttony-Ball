#pragma once

#ifndef GAME_H_

#define	GAME_H_

#include	"include_lib.h"

void	InitGame();		//	ゲーム初期化
void	UninitGame();	//	ゲーム終了処理
void	UpdateGame();	//	ゲーム更新処理
void	DrawGame();		//	ゲーム描画処理

void SetStopBool(bool value);
bool GetStopBool();
#endif // !GAME_H_

