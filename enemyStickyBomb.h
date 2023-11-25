#pragma once

#ifndef ENEMY_STICKY_BOMB_H_

#define	ENEMY_STICKY_BOMB_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	ENEMY_STICKY_BOMB_MAX	(5)

//=============================================================
//	スティッキー爆弾エネミーのスティッキー爆弾クラス
//=============================================================
class ENEMY_STICKY_BOMB : public	BASE_OF_PERFORMER
{
private:
	int	timer;	//	着弾してからの時間カウンター

	const	int	ExpTimeOnGround = 60 * 2;	//	地面に着弾してから爆発するまでの時間

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetTime(const	int&	new_time) { timer = new_time; }	//	時間セット

};

//============================================================
//	スティッキー爆弾エネミーのスティッキー爆弾制御プログラム
//============================================================
void	InitEnemyStickyBomb();	//	スティッキー爆弾初期化
void	UninitEnemyStickyBomb();	//	スティッキー爆弾終了処理
void	UpdateEnemyStickyBomb();	//	スティッキー爆弾更新処理
void	DrawEnemyStickyBomb();		//	スティッキー爆弾描画処理

void	SetEnemyStickyBomb(const	D3DXVECTOR2	pos);
ENEMY_STICKY_BOMB*	GetEnemyStickyBomb(void);

#endif // !ENEMY_STICKY_BOMB_H_

