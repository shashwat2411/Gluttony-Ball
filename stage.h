#pragma once

#ifndef STAGE_H_

#define	STAGE_H_

#include	"include_lib.h"

#define	STAGE_MAX	(4)
#define	STAGE_HEIGHT_MAX	(18 * 2)
#define	STAGE_WIDTH_MAX	(32 * 6)

void	InitStage();	//	�X�e�[�W������
void	UninitStage();	//	�X�e�[�W�I������
void	UpdateStage();	//	�X�e�[�W�X�V����

void	MakeStage(const	int	stage_num);	//	�X�e�[�W�쐬

void	SetStageChar(const	int	stage_num, const	int	x, const	int	y, const	char	num);	//	�X�e�[�W���Z�b�g
const	char&	GetStageChar(const	int	stage_num, const	int	x, const	int	y);				//	�X�e�[�W���擾
#endif // !STAGE_H_

void InitializeStage();