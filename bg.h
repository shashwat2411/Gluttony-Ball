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

void	InitBG();	//	�w�i������
void	UninitBG();	//	�w�i�I������
void	UpdateBG();	//	�w�i�X�V����
void	DrawBG();	//	�w�i�`�揈��

BG_SCENE GetBGScene();	//�@���݂̔w�i�V�[�����擾
//void	SetBGScene(BG_SCENE scene);	//�@�w�i�V�[�����Z�b�g
void	SetBGScene(bool value);	//�@�`���[�g���A���̃t���O���Z�b�g


#endif // !BG_H

