#pragma once

#include "Enemy.h"
#include "Button.h"


#define BOUNCE_COUNT (2)
#define	HOMING_POS_MAX (10)
#define FOCUS_MAX (100)
//============================================================
//	プレイヤークラス
//		キー移動、重力、ジャンプ
//=============================================================
class BALL : public	BASE_OF_PERFORMER
{
public:
	enum BALL_SITU
	{
		Keep,
		Throwing,
		ChargeThrow,
		Free,
		Stay,
		Return,
	};
	//	攻撃系能力
	enum ABILITY_ATTACK
	{
		NONE_ATTACK,
		EXPLOSION,
		STICKY,
	};

	//	軌道系能力
	enum ABILITY_MOVE_BALL
	{
		NONE_BALL,
		BOUNCE,
		HOMING,
	};

	//	移動系能力
	enum ABILITY_MOVE_PLAYER
	{
		NONE_PLAYER,
		SPRING,
		TRACE,
	};

private:
	BALL_SITU	situation;	//	ボールの状態。Keep:プレイヤーがボールを所持している。
							//				  Throwing:プレイヤーが投げて、移動している。
							//				  ChargeThrow:チャージ投げ、チャージ中
							//				  Stay:ボールが既定の動作を完了し、待機状態に入る。
							//				  Return:ボールが既定の動作を完了し、プレイヤーの元に戻る。


	ABILITY_ATTACK	ability_attack;
	ABILITY_MOVE_BALL	ability_move_ball;
	ABILITY_MOVE_PLAYER	ability_move_player;

	D3DXVECTOR2*	HomingPos[HOMING_POS_MAX];

	unsigned	int	g_BallSE;

	bool	UsedAttackBool;	//	攻撃系能力を使用したかBool
	bool	UsedSpringBool;	//	バネを設置したかBool
	bool	UsedSEBool;		//	ボールSEを流したかBool

	int		HomingNum;		//	ホーミングでロックした敵の数
	int		TargetNum;		//	ホーミングで狙っている敵の番号

	int		BounceCount;	//バウンスした数

	float	MovedDisSq;	//	ボールが飛んだ総距離

	float	ThrowDis;	//	ボールが出現した位置から重力が働かない距離。
	const	float	ThrowDisMin = BASE_SIZE * 3;
	const	float	ThrowDisMax = BASE_SIZE * 8;

	D3DXVECTOR2	posBefForDis;	//	ボールが飛んだ総距離を計算するための座標

public:
	int counter = 0;
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetBallReturn();
	void	SetBallPoint(D3DXVECTOR2 new_point);

	void	SetBall(D3DXVECTOR2 pos, D3DXVECTOR2	way);

	void	PlayBallSE(const	bool	new_bool) {
		if (new_bool && !UsedSEBool) { PlaySound(g_BallSE, 0); }
		UsedSEBool = new_bool; }

	void	SetAbilityAttack(const	ABILITY_ATTACK	new_attack) { ability_attack = new_attack; }	//	攻撃系能力のセット
	const	ABILITY_ATTACK&	GetAbilityAttack(void) { return	ability_attack; }						//	攻撃系能力の取得

	void	SetAbilityMoveBall(const	ABILITY_MOVE_BALL	new_ball) { ability_move_ball = new_ball; }	//	軌道系能力のセット
	const	ABILITY_MOVE_BALL&	GetAbilityMoveBall(void) { return	ability_move_ball; }				//	軌道系能力の取得

	void	SetAbilityMovePlayer(const	ABILITY_MOVE_PLAYER	new_player) { ability_move_player = new_player; }	//	移動系能力のセット
	const	ABILITY_MOVE_PLAYER&	GetAbilityMovePlayer(void) { return	ability_move_player; }					//	移動系能力の取得

	void	SetUsedAttackBool(const	bool	new_bool) { UsedAttackBool = new_bool; }	//	攻撃系能力を使用したかBoolのセット
	const	bool&	GetUsedAttackBool(void) { return	UsedAttackBool; }				//	攻撃系能力を使用したかBoolの取得

	void	SetUsedSpringBool(const	bool	new_bool) { UsedSpringBool = new_bool; }	//	バネを設置したかBoolのセット
	const	bool&	GetUsedSpringBool(void) { return	UsedSpringBool; }				//	バネを設置したかBoolの取得

	void	SetUsedSEBool(const	bool	new_bool) { UsedSEBool = new_bool; }
	const	bool&	GetUsedSEBool() { return	UsedSEBool; }

	void	ThrowDisRateUp(const	float	rate) { ThrowDis = (ThrowDisMax - ThrowDisMin) * rate + ThrowDisMin; }
	void	SetThrowDis(const	float&	new_dis) { ThrowDis = new_dis; }	//	投げる距離セット
	const	float&	GetThrowDis(void) { return	ThrowDis; }					//	投げる距離取得

	void	SetSituation(const	BALL_SITU&	new_Situ) { situation = new_Situ; }	//	ボール状態セット
	const	BALL_SITU&	GetSituation(void) { return	situation; }				//	ボール状態取得

	float	GetMoveDistance() { return sqrt((pos.x - actionFirstPos.x) * (pos.x - actionFirstPos.x) + (pos.y - actionFirstPos.y) * (pos.y - actionFirstPos.y)); };

	void SetBounceCount(const int& newCount) { BounceCount = newCount; }
	const int& GetBounceCount() { return BounceCount; }
	//void AddBounceCount(int add) { BounceCount += add; }

	void	SetHomingNum(const	int	new_Num) {	HomingNum = new_Num; }
	const	int&	GetHomingNum(void) { return	HomingNum; }

	void	SetTarget(ENEMY*	new_Enemy, BUTTON*	new_Button);		//	ホーミングでロックしたエネミーの追加
	D3DXVECTOR2**	GetTargetEnemy(void) { return	HomingPos; }
};


//=============================================
//	プレイヤー管理プログラム
//=============================================
void	InitBall();		//	ボール初期化
void	UninitBall();	//	ボール終了処理
void	UpdateBall();	//	ボール更新処理
void	DrawBall();		//	ボール描画処理

BALL*	GetBall();		//	ボール取得

//void UpdateAbilityBounce(bool onWall);
//void UpdateAbilityHoming();
//void UpdateAbilityExplode();
//void UpdateAbilitySticky(bool onWall, ENEMY* follow);
//void UpdateAbilityFollow();
//void UpdateAbilitySpring();