#pragma once

#ifndef PLAYER_H_

#define	PLAYER_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	TRACE_POS_MAX	(5)

class PLAYER :public	BASE_OF_PERFORMER
{
public:
	enum SE_TYPE
	{
		None,
		Run,
		Jump,
		Throw,
		SE_TYPE_MAX
	};

private:
	const	float	acceleration = 0.1f;		//	プレイヤーの加速値

	const	float	JumpSpeed_min = -11;		//	プレイヤーの最小のジャンプスピード
	const	float	JumpAcceleration = 0.55f;	//	プレイヤーのジャンプ加速値

	const	float	QuickBallWayDis = 1.0f / 3;		//	クイック投げの投球方向の判定範囲
	const	float	ThrowJudgeNum = 0.5f;			//	右スティック、X軸の投げる値の範囲

	const	float	HomingLockAngle = 60.0f;			//	ホーミング能力でロック出来る角度範囲

	unsigned	int	TexNums[ANIMATION_TYPE_MAX];	//	プレイヤーの各アクションのテクスチャ番号を格納する配列
	unsigned	int	SENums[SE_TYPE_MAX];		//

	bool	stockBall;		//	ボールを持っている時、true
	bool	stick;	//プレーヤーの操作の有無

	unsigned	int	ChargeTimer;	//	右スティックの入力時間
	const	int	ChargeTimeMax = 60 / 2;	//	クイック投げからチャージ投げに切り替わる時間

	bool	control;	//	プレイヤーのコントロールの可不可

	int		StayTimeBefTrace;	//	追従開始前の待機状態をカウントする変数
	const	int	StayTimeBefTraceMax = 60 / 2;	//	追従開始前の待機状態の時間

	int		way_x = 1;			//	右：1	左：-1

	bool following;	//追従能力で追従している時、true
	int FollowCount = 0;	//追従能力の座標カウント

	int	timer;
	const	int	MakeShineTimeMax = 60 / 6;	//	キラキラが発生する時間間隔

	SE_TYPE	typeSE;
	bool	OneTimeSE;

	int	TraceNum;
	D3DXVECTOR2	TracePos[TRACE_POS_MAX + 1];	//	追従能力で通る座標配列

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	CorrectScreen();

	void	SetStockBall(bool	new_stock) { stockBall = new_stock; }	//	ボール保持セット
	const	bool& GetStockBall(void) { return	stockBall; }			//	ボール保持取得

	void	SetStick(bool	new_stock) { stick = new_stock; }	//	ボール保持セット
	const	bool& GetStick(void) { return	stick; }			//	ボール保持取得

	void	SetControl(bool	new_value) { control = new_value; }	//	ボール保持セット
	const	bool& GetControl(void) { return	control; }			//	ボール保持取得

	void	SetWayX(const	int	way) { way_x = way; }
	const	int&	GetWayX() { return	way_x; }

	void	SetTraceNum(const	int	new_num) { TraceNum = new_num; }
	const	int&	GetTraceNum() { return	TraceNum; }

	void	SetSeType(const	SE_TYPE	new_type) { typeSE = new_type; }
	const	SE_TYPE&	GetSeType() { return	typeSE; }

	void	SetTracePos(const	D3DXVECTOR2	new_pos) { if (TraceNum < TRACE_POS_MAX) {
		TracePos[TraceNum] = new_pos;
		TraceNum++;
	} }
	D3DXVECTOR2*	GetTracePos() { return	TracePos; }
};


//=============================================
//	プレイヤー管理プログラム
//=============================================
void	InitPlayer();			//	プレイヤー初期化
void	UninitPlayer();			//	プレイヤー終了処理
void	UpdatePlayer();			//	プレイヤー更新処理
void	DrawPlayer();			//	プレイヤー描画処理

PLAYER* GetPlayer();	//	プレイヤー取得
bool GetPlayerUse();
#endif // !PLAYER_H_





