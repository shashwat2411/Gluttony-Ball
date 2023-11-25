#pragma once

#ifndef RESULT_H_

#define	RESULT_H_

#include	"include_lib.h"


void	InitResult();		//	ステージ選択初期化
void	UninitResult();	//	ステージ選択終了処理
void	UpdateResult();	//	ステージ選択更新処理
void	DrawResult();		//	ステージ選択描画処理

void	SetClearBool(const	bool	new_Bool);
const	bool&	GetClearBool();

const	int&	GetResultSituNum();

#endif // !RESULT_H_




