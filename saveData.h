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
//	�Z�[�u�f�[�^�Ǘ��v���O����
void	InitSaveData();		//	�Z�[�u�f�[�^������
void	UninitSaveData();	//	�Z�[�u�f�[�^�I������
void	UpdateSaveData();	//	�Z�[�u�f�[�^�X�V����
void	DrawSaveData();		//	�Z�[�u�f�[�^�`�揈��

void	Load(SAVE_DATA*	data);
void	Save(SAVE_DATA*	data);

SAVE_DATA*	GetSaveData();	//	�Z�[�u�f�[�^�̎擾

const	int&	GetSelectDataNum();

#endif // !SAVE_DATA_H_

