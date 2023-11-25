#pragma once

#ifndef SPRITE_H_

#define	SPRITE_H_

//===================================
//
//スプライト描画処理
//===================================

#include	"znoTouch_main.h"
#include	"znoTouch_renderer.h"

//===================================
//マクロ定義
//===================================

//===================================
//グローバル変数
//===================================

//===================================
//プロトタイプ宣言
//===================================
			//static	float	PaternNo = 0;	// 最初に一回だけ０が入る、その後はグローバル変数と同じで値が保存される
			//float			uv_w = 0.5f;	// キャラクターの横サイズ(UV座標表現)
			//float			uv_h = 0.5f;	// キャラクターの縦サイズ(UV座標表現)
			//int				NumPatern = 2;	// キャラクターの横の枚数

void DrawSpriteColorRotate(float posx, float posy, int size_w, int size_h, float kakudo, D3DXCOLOR col,
	float	PaternNo, float	uv_w, float uv_h, int NumPatern);
void	InitSprite();
void	UninitSprite();

#endif // !SPRITE_H_
