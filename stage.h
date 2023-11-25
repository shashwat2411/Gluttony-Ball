#pragma once

#ifndef STAGE_H_

#define	STAGE_H_

#include	"include_lib.h"

#define	STAGE_MAX	(4)
#define	STAGE_HEIGHT_MAX	(18 * 2)
#define	STAGE_WIDTH_MAX	(32 * 6)

void	InitStage();	//	ステージ初期化
void	UninitStage();	//	ステージ終了処理
void	UpdateStage();	//	ステージ更新処理

void	MakeStage(const	int	stage_num);	//	ステージ作成

void	SetStageChar(const	int	stage_num, const	int	x, const	int	y, const	char	num);	//	ステージ情報セット
const	char&	GetStageChar(const	int	stage_num, const	int	x, const	int	y);				//	ステージ情報取得
#endif // !STAGE_H_

void InitializeStage();