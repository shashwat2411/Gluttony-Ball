/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
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
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(30 * 32)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(30 * 18)				// �E�C���h�E�̍���
#define	SCREEN_LIMIT_UP	(0)					//	��ʏ���E���W
#define	SCREEN_LIMIT_DOWN	(30 * 18)			//	��ʉ����E���W
#define	SCREEN_LIMIT_RIGHT	(30 * 32)			//	��ʉE���E���W
#define	SCREEN_LIMIT_LEFT	(0)				//	��ʍ����E���W

#define	PI			(3.14159)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

char* GetDebugStr(void);