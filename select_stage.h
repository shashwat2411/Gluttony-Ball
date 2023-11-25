#pragma once

#ifndef SELECT_STAGE_H_

#define	SELECT_STAGE_H_

#include	"include_lib.h"

#define	BUTTON_SIZE_W	(90)
#define	BUTTON_SIZE_H	(100)

void	InitSelectStage();		//	�X�e�[�W�I��������
void	UninitSelectStage();	//	�X�e�[�W�I���I������
void	UpdateSelectStage();	//	�X�e�[�W�I���X�V����
void	DrawSelectStage();		//	�X�e�[�W�I��`�揈��

const	int&	GetCurrentStageNum();

#endif // !SELECT_STAGE_H_




