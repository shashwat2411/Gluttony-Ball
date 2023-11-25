#pragma once

#include "znoTouch_BaseOfPerformer.h"

#ifndef BUTTON_H_

#define	BUTTON_H_


//============================================================
//	�{�^���u���b�N�N���X
//=============================================================
#define BUTTON_MAX (10) //�{�^���u���b�N�̔z�u�����

class BUTTON :public	BASE_OF_PERFORMER
{
	private:
		unsigned	int	g_ButtonSE;

		bool	SwitchAble;

		bool	BallCollide = false;	//�{�[���ɓ����������ǂ���, true:��������, false:�������ĂȂ�
		bool	On_OffSwitch;	//true�Ȃ�X�C�b�`���I���ɂȂ�M�~�b�N���쓮����

		bool	SaveAble;

	public:
		void	Update();
		void	Prepare();
		void	Reset();

		void	SetOn_OffSwitch(const bool on_off) { On_OffSwitch = on_off;	PlaySound(g_ButtonSE, 0); };
		bool	GetOn_OffSwitch() { return On_OffSwitch; };
		void	SetButton(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off);

		void	SetSaveAble(const	bool	new_bool) { SaveAble = new_bool; }
		const	bool&	GetSaveAble(void) { return	SaveAble; }

	private:

};

//=============================================
//	�{�^���Ǘ��v���O����
//=============================================
void	InitButton();		//�{�^���u���b�N������
void	UninitButton();		//�{�^���u���b�N�I������
void	UpdateButton();		//�{�^���u���b�N�X�V����
void	DrawButton();		//�{�^���u���b�N�`�揈��

void	SetButtons(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off, int index);	//	�{�^���̃Z�b�g
//void SetButtons(const D3DXVECTOR2& pos, const D3DXVECTOR2& size); //�{�^���u���b�N�̃Z�b�g
BUTTON* GetButton();//�{�^���u���b�N�擾


#endif