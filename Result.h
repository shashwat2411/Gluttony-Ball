#pragma once

#ifndef RESULT_H_

#define	RESULT_H_

#include	"include_lib.h"


void	InitResult();		//	�X�e�[�W�I��������
void	UninitResult();	//	�X�e�[�W�I���I������
void	UpdateResult();	//	�X�e�[�W�I���X�V����
void	DrawResult();		//	�X�e�[�W�I��`�揈��

void	SetClearBool(const	bool	new_Bool);
const	bool&	GetClearBool();

const	int&	GetResultSituNum();

#endif // !RESULT_H_




