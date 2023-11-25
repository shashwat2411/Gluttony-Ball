#pragma once

#ifndef SAVE_DATA_H_

#define	SAVE_DATA_H_

#include	"include_lib.h"

#define	SAVE_DATA_MAX	(3)
#define	SAVE_DATA_LIST_NUM	(3)

typedef	struct SAVE_DATA
{
	unsigned	int	dataNum;
	unsigned	int	life;
	unsigned	int	stageNum;
};

//==============================================================
//	セーブデータ管理プログラム
void	InitSaveData();		//	セーブデータ初期化
void	UninitSaveData();	//	セーブデータ終了処理
void	UpdateSaveData();	//	セーブデータ更新処理
void	DrawSaveData();		//	セーブデータ描画処理

void	Load(SAVE_DATA*	data);
void	Save(SAVE_DATA*	data);

SAVE_DATA*	GetSaveData();	//	セーブデータの取得

const	int&	GetSelectDataNum();

#endif // !SAVE_DATA_H_

