#pragma once

#include	<Windows.h>
#include	"xaudio2.h"		//XAudio�𗘗p�������Ƃ��ɃC���N���[�h


bool	InitSound(HWND	hWnd);	//	�T�E���h������
void	UninitSound(void);		//	�T�E���h�I��

int		LoadSound(char*	pFilename);		//	�f�[�^�̃��[�h
void	PlaySound(int index, int loopCount);	//	�f�[�^�̍Đ�	�t���O0�ň��A-1�Ń��[�v�Đ�
void	StopSound(int	index);			//	�f�[�^�̍Đ���~


void	StopSoundAll(void);						//	�S�Ă̍Đ����~
void	SetVolume(int	index, float	vol);	//	�{�����[���̕ύX


//	�T�E���h�ǉ�
//	1	�R���g���[���[�Ɠ����^�C�~���O�ŏ��������I���������s��
//	2	�^�C�g���Ȃǂ̃V�[���̏������Ńf�[�^���[�h���Đ��J�n�iBGM�j
//		�I�������ōĐ���~�iBGM�j
//	3	�e�E�����Ȃǂ��������Ń��[�h���Ă����B
//		�Đ����͂��ꂼ��̃^�C�~���O�ōs�����A���[�v���Ƃɖ���Đ�����Ȃ��悤��
//		���ӂ��K�v�B
//		���l�Ƀ��[�h���������̈��݂̂ɂȂ�悤���ӁB
//
