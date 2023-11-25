#pragma once

#include "znoTouch_BaseOfPerformer.h"

#ifndef INTERLOCKARRANGEMENT_H_

#define	INTERLOCKARRANGEMENT_H_

//�����蔻��͑���u���b�N�Ɠ��l�̔���

//============================================================
//	�{�^���ɘA�����č쓮������̃N���X
//=============================================================
#define INTERLOCKARRANGEMENT_MAX (10)//�{�^���ɘA�����č쓮������̂̔z�u�����

//INTERLOCKARRANGEMENT�̌��̓{�^���̌��Ɠ���
class INTERLOCKARRANGEMENT :public	BASE_OF_PERFORMER
{
public:

	void	Update();
	void	Prepare();
	void	Reset();
	void	SetOn_Off_InterlockArrangement(const bool on_off) { On_OffSwitch = on_off; };
	void	SetInterlockArrangement(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	bool	GetOn_Off_InterlockArrangement() { return On_OffSwitch; };

private:
	bool On_OffSwitch;	//true�Ȃ�X�C�b�`���I���ɂȂ�M�~�b�N���쓮���� �{�^���̓��X�C�b�`���g����΂����OK

	unsigned int	texture1;
	unsigned int texture2;
};

//=============================================
//	�{�^���ɘA�����č쓮������̊Ǘ��v���O����
//=============================================
void	InitInterlockArrangement();		//�{�^���ƘA�����č쓮������̂�������
void	UninitInterlockArrangement();		//�{�^���ƘA�����č쓮������̏I������
void	UpdateInterlockArrangement();		//�{�^���ƘA�����č쓮������̍X�V����
void	DrawInterlockArrangement();		//�{�^���ƘA�����č쓮������̕`�揈��

void SetInterlockArrangements(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index); //�{�^���ƘA�����č쓮������̂̃Z�b�g
INTERLOCKARRANGEMENT* GetInterlockArrangement();//�{�^���ƘA�����č쓮������̂̎擾


#endif