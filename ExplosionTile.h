#pragma once

#ifndef EXPLOSIONTILE_H_

#include	"include_lib.h"

#define	EXPLOSIONTILE_MAX	(100)


//===========================================================
//	�O���E���h�N���X
//		�ꏊ�Œ�A�M�~�b�N�Ȃ��A�n��
//===========================================================
class EXPLOSIONTILE : public	BASE_OF_PERFORMER
{
private:
	bool BallCollide = false;	//�{�[���ɓ����������ǂ���, true:��������, false:�������ĂȂ�
public:

	void	Update();

	void	Prepare();
	void	Reset();

	void SetBallCollide(const bool col)
	{
		BallCollide = col;
	}
	const bool GetBallCollide()
	{
		return BallCollide;
	}


};



//============================================
//	�n�ʊǗ��v���O����
//============================================
void	InitExplosionTile();
void	UninitExplosionTile();
void	UpdateExplosionTile();
void	DrawExplosionTile();

void	SetExplosionTile(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size);
EXPLOSIONTILE*	GetExplosionTile();




#endif // !EXPLOSIONTILE_H_

