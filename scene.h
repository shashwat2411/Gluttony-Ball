#pragma once

#ifndef SCENE_H_

#define	SCENE_H_

#include	"include_lib.h"

//===========================================================
//	�V�[��enum	(macro.h�ɒ�`���Ă���)
//===========================================================

void	InitScene(SCENE SceneNo);	//	�V�[��������
void	UninitScene();	//	�V�[���I������
void	UpdateScene();	//	�V�[���X�V����
void	DrawScene();	//	�V�[���`�揈��

void	SetScene(const	SCENE	new_Scene);	//	�V�[���ϐ��̃Z�b�g
const	SCENE& GetScene();
void	CheckScene();

#endif // !SCENE_H_

