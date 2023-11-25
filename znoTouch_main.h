/*==============================================================================

   共通ヘッダー [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#include	"znoTouch_renderer.h"
#include	"znoTouch_sprite.h"
#include	"znoTouch_sound.h"
#include	"znoTouch_texture.h"
#include	"znoTouch_input.h"

#include	"znoTouch_BaseOfPerformer.h"

#include	"include_lib.h"


#pragma warning(pop)



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(30 * 32)				// ウインドウの幅
#define SCREEN_HEIGHT	(30 * 18)				// ウインドウの高さ
#define	SCREEN_LIMIT_UP	(0)					//	画面上限界座標
#define	SCREEN_LIMIT_DOWN	(30 * 18)			//	画面下限界座標
#define	SCREEN_LIMIT_RIGHT	(30 * 32)			//	画面右限界座標
#define	SCREEN_LIMIT_LEFT	(0)				//	画面左限界座標

#define	PI			(3.14159)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

char* GetDebugStr(void);