#pragma once

#ifndef SPRITE_H_

#define	SPRITE_H_

//===================================
//
//�X�v���C�g�`�揈��
//===================================

#include	"znoTouch_main.h"
#include	"znoTouch_renderer.h"

//===================================
//�}�N����`
//===================================

//===================================
//�O���[�o���ϐ�
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================
			//static	float	PaternNo = 0;	// �ŏ��Ɉ�񂾂��O������A���̌�̓O���[�o���ϐ��Ɠ����Œl���ۑ������
			//float			uv_w = 0.5f;	// �L�����N�^�[�̉��T�C�Y(UV���W�\��)
			//float			uv_h = 0.5f;	// �L�����N�^�[�̏c�T�C�Y(UV���W�\��)
			//int				NumPatern = 2;	// �L�����N�^�[�̉��̖���

void DrawSpriteColorRotate(float posx, float posy, int size_w, int size_h, float kakudo, D3DXCOLOR col,
	float	PaternNo, float	uv_w, float uv_h, int NumPatern);
void	InitSprite();
void	UninitSprite();

#endif // !SPRITE_H_
