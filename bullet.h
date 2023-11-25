#pragma once

#ifndef BULLET_H_

#define	BULLET_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	BULLET_MAX	(30)

//==========================================================================================
//	�o���b�g�N���X
//==========================================================================================

class BULLET : public	BASE_OF_PERFORMER
{
private:
	int	timer;	//	�o���b�g�̑��ݎ��ԃJ�E���^�[

	const	int	TimeMax = 60 * 8;	//	�o���b�g�̑��݂ł��鎞��
	const	float	TouchDis = BASE_SIZE * 3 / 4;	//	�o���b�g�ƃv���C���[�̊Ԃ̓�����������̋���

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetTime(const	int&	new_time) { timer = new_time; }	//	�o���b�g�̑��ݎ��ԃJ�E���^�[
	const	int&	GetTime(void) { return	timer; }				//	�o���b�g�̑��ݎ��Ԃ̎擾
};

//=========================================================================================
//	�o���b�g�Ǘ��v���O����
//=========================================================================================
void	InitBullet();	//	�o���b�g������
void	UninitBullet();	//	�o���b�g�I������
void	UpdateBullet();	//	�o���b�g�X�V����
void	DrawBullet();	//	�o���b�g�`�揈��

void	SetBullet(const	D3DXVECTOR2&	pos);	//	�o���b�g�̃Z�b�g
BULLET*	GetBullet();	//	�o���b�g�̎擾

#endif // !BULLET_H_

