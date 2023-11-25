#pragma once

#include "znoTouch_BaseOfPerformer.h"
#include	"collision.h"

//============================================================
//	プレイヤークラス
//		キー移動、重力、ジャンプ
//=============================================================
#define	ENEMY_MAX	(10)

class ENEMY : public	BASE_OF_PERFORMER
{
public:
	enum ENEMY_TYPE
	{
		Bound,		//	バウンドエネミー
		Homing,		//	ホーミングエネミー
		Explosion,	//	爆発エネミー
		Sticky,		//	スティッキー爆弾エネミー
		Trace,		//	追従エネミー
		Spring,		//	バネエネミー

		enemy_type_max
	};

	enum ENEMY_ANIMATION
	{
		bound_stand_R,
		bound_move_R,
		bound_stand_L,
		bound_move_L,
		homing,
		explosion,
		sticky,
		trace,
		spring_R,
		spring_L,

		enemy_anim_max
	};

private:
	ENEMY_TYPE	enemy_type;		//	エネミーの種類
	ENEMY_ANIMATION	animation_type;
	unsigned	int	TexNums[enemy_anim_max];	//	エネミーの各タイプのテクスチャ番号
	unsigned	int	TraceMarkNum;				//	追従エネミーの追従マーカーのテクスチャ番号
	unsigned	int	g_EnemyBoundSE;
	unsigned	int	g_EnemySpringSE;

	bool	BallCollide = false;	//ボールに当たったかどうか, true:当たった, false:当たってない
	bool	DrawTraceBool;


	int	timer;		//	各エネミーで使うタイマー変数

	int	boundCount;	//	バウンドエネミーのバウンドした回数カウント
	const	int	boundMax = 3;	//	バウンドエネミーのバウンドする最大回数

	const	int	HomingShootTime = 60 * 5;	//	ホーミングエネミーのバレット発射間隔時間

	const	int	UseStickyBombTime = 60 * 5;	//	スティッキー爆弾を出す時間間隔

	const	int	BoundStayTime = 60 * 3;	//	バウンドエネミーの待機時間（3秒）

	const	int	TraceSearchDis = BASE_SIZE * 20;	//	追従エネミーの追従する範囲距離

	const	float	ExpAcceleration = 2.0f;	//	爆発エネミーの移動加速度、move.xに加算し続ける
	const	float	ExpDis = BASE_SIZE * 2.0f;	//	爆発エネミーが爆発するプレイヤーとの距離

	const	float	FlyingMoveX = BASE_SIZE * 7;	//	スティッキー爆弾エネミーの横軸に動く範囲

public:
	
	void	Update();

	void	Prepare();
	void	Reset();

	void	DrawTraceMark();	//	追従エネミーの追従場所を示すマーカーを描画する処理

	void	SetEnemy(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	ENEMY_TYPE&	EnemyType);

	void SetBallCollide(const bool col) { BallCollide = col; }
	const bool GetBallCollide() { return BallCollide; }

	void	SetEnemyType(const	ENEMY_TYPE	new_type) { enemy_type = new_type; }	//	エネミータイプのセット
	const	ENEMY_TYPE&	GetEnemyTyep(void) { return	enemy_type; }					//	エネミータイプの取得
	
	void	SetBoundCount(const	int	new_Count) {
		boundCount = new_Count;	if (boundCount <= boundMax)	PlaySound(g_EnemyBoundSE, 0);
	}	//	バウンド回数のセット
	const	int&	GetBoundCount(void) { return	boundCount; }			//	バウンド回数の取得

	void	PlaySpringSE() { PlaySound(g_EnemySpringSE, 0); }

	void	SetTime(const	int	new_Time) { timer = new_Time; }		//	タイマーのセット
	const	int&	GetTime(void) { return	timer; }				//	タイマーの取得

	void	SetBoundStand(const	COLLISION_WAY&	way);
};


//=============================================
//	プレイヤー管理プログラム
//=============================================
void	InitEnemy();		//	ボール初期化
void	UninitEnemy();	//	ボール終了処理
void	UpdateEnemy();	//	ボール更新処理
void	DrawEnemy();		//	ボール描画処理

void	SetEnemys(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	ENEMY::ENEMY_TYPE&	EnemyType);	//	エネミーのセット

ENEMY*	GetEnemy();		//	ボール取得

