#pragma once

#ifndef GAME_H_

#define	GAME_H_

#include	"include_lib.h"

void	InitGame();		//	�Q�[��������
void	UninitGame();	//	�Q�[���I������
void	UpdateGame();	//	�Q�[���X�V����
void	DrawGame();		//	�Q�[���`�揈��

void SetStopBool(bool value);
bool GetStopBool();
#endif // !GAME_H_

