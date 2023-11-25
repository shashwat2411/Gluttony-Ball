#pragma once

#ifndef ENEMY_STICKY_BOMB_H_

#define	ENEMY_STICKY_BOMB_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	ENEMY_STICKY_BOMB_MAX	(5)

//=============================================================
//	�X�e�B�b�L�[���e�G�l�~�[�̃X�e�B�b�L�[���e�N���X
//=============================================================
class ENEMY_STICKY_BOMB : public	BASE_OF_PERFORMER
{
private:
	int	timer;	//	���e���Ă���̎��ԃJ�E���^�[

	const	int	ExpTimeOnGround = 60 * 2;	//	�n�ʂɒ��e���Ă��甚������܂ł̎���

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetTime(const	int&	new_time) { timer = new_time; }	//	���ԃZ�b�g

};

//============================================================
//	�X�e�B�b�L�[���e�G�l�~�[�̃X�e�B�b�L�[���e����v���O����
//============================================================
void	InitEnemyStickyBomb();	//	�X�e�B�b�L�[���e������
void	UninitEnemyStickyBomb();	//	�X�e�B�b�L�[���e�I������
void	UpdateEnemyStickyBomb();	//	�X�e�B�b�L�[���e�X�V����
void	DrawEnemyStickyBomb();		//	�X�e�B�b�L�[���e�`�揈��

void	SetEnemyStickyBomb(const	D3DXVECTOR2	pos);
ENEMY_STICKY_BOMB*	GetEnemyStickyBomb(void);

#endif // !ENEMY_STICKY_BOMB_H_

