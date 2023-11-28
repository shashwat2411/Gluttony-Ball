#pragma once

#ifndef EXPLOSIONTILE_H_

#include	"include_lib.h"

#define	EXPLOSIONTILE_MAX	(100)


//===========================================================
//	グラウンドクラス
//		場所固定、ギミックなし、地面
//===========================================================
class EXPLOSIONTILE : public	BASE_OF_PERFORMER
{
private:
	bool BallCollide = false;	//ボールに当たったかどうか, true:当たった, false:当たってない
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
//	地面管理プログラム
//============================================
void	InitExplosionTile();
void	UninitExplosionTile();
void	UpdateExplosionTile();
void	DrawExplosionTile();

void	SetExplosionTile(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size);
EXPLOSIONTILE*	GetExplosionTile();




#endif // !EXPLOSIONTILE_H_

