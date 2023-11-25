#pragma once

#ifndef SCENE_H_

#define	SCENE_H_

#include	"include_lib.h"

//===========================================================
//	シーンenum	(macro.hに定義してある)
//===========================================================

void	InitScene(SCENE SceneNo);	//	シーン初期化
void	UninitScene();	//	シーン終了処理
void	UpdateScene();	//	シーン更新処理
void	DrawScene();	//	シーン描画処理

void	SetScene(const	SCENE	new_Scene);	//	シーン変数のセット
const	SCENE& GetScene();
void	CheckScene();

#endif // !SCENE_H_

