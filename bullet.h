#pragma once

#ifndef BULLET_H_

#define	BULLET_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	BULLET_MAX	(30)

//==========================================================================================
//	バレットクラス
//==========================================================================================

class BULLET : public	BASE_OF_PERFORMER
{
private:
	int	timer;	//	バレットの存在時間カウンター

	const	int	TimeMax = 60 * 8;	//	バレットの存在できる時間
	const	float	TouchDis = BASE_SIZE * 3 / 4;	//	バレットとプレイヤーの間の当たった判定の距離

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetTime(const	int&	new_time) { timer = new_time; }	//	バレットの存在時間カウンター
	const	int&	GetTime(void) { return	timer; }				//	バレットの存在時間の取得
};

//=========================================================================================
//	バレット管理プログラム
//=========================================================================================
void	InitBullet();	//	バレット初期化
void	UninitBullet();	//	バレット終了処理
void	UpdateBullet();	//	バレット更新処理
void	DrawBullet();	//	バレット描画処理

void	SetBullet(const	D3DXVECTOR2&	pos);	//	バレットのセット
BULLET*	GetBullet();	//	バレットの取得

#endif // !BULLET_H_

