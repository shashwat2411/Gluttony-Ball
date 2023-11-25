#pragma once

#include	"include_lib.h"

/*========================================================
	ボール、プレイヤー、エネミー、等の基礎クラス

	下記のクラスを継承して作成すること
==========================================================*/
class BASE_OF_PERFORMER
{
public:
	enum ANIMATION_TYPE
	{
		Stand_R,	Stand_L,
		Run_R,	Run_L,
		Jump_R,	Jump_L,
		ThrowPose_R,	ThrowPose_L,
		ThrowWalk_R,	ThrowWalk_L,
		ThrowBack_R,	ThrowBack_L,
		AfterThrow_R,	AfterThrow_L,
		Fall_R,	Fall_L,
		ANIMATION_TYPE_MAX
	};

	enum MOVE_TYPE
	{
		Normal,
		Point,
		Straight,
	};

	

protected:

	MOVE_TYPE	move_type;				/*	オブジェクトの移動方法
												Nomal:通常移動。posにmoveを加算し続ける。重力の影響も受ける
												Point:point座標に向かって直進する。重力の影響を受けない。
												Straight:直線移動。重力の影響を受けない。*/


	bool	use;						//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	bool	active;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	bool	animation;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	bool	gravity;					//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	bool	onGround;					//	地面に着地しているか、否
	bool	onWall;						//	壁に接しているか、否
	bool	animationOver;

	bool	MoveX;						//	オブジェクトの横移動の可不可
	bool	MoveY;						//	オブジェクトの縦移動の可不可
	bool	ArrivePoint;				//	オブジェクトのポイント移動の目的座標に着いたか、否

	bool			collisionBool;		//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	bool			OnTrigger;			//	別のオブジェクトのコリジョンに触れているかBool	false:別オブジェクトに触れてない	true:別オブジェクトに触れている
	static	bool	collisionTest;		//	DrawCollisionの描画の共通使用Bool

	int		movePointMax = 5;				//	ポイント移動で移動出来るポイントの最大値
	float	gravityNum = 1.0f;		//	重力値、move.yに加算し続ける
	const	float	fallSpeedMax = 15.0f;	//	move.yに入る最大値
	float	airFrictionRate = 0.95f;	//	浮遊中の空気抵抗
	const	float	stopSpeedMax = 0.05f;		//	スピードが数値内の場合、0とみなす
	float	frictionRate = 0.5f;	//	足場との摩擦係数

	unsigned	int	texNo;				//	LoadTextureの戻り値を記録する変数
	unsigned	int	col_TexNo;			//	DrawCollision用テクスチャ番号
	unsigned	int	befPos_TexNo;		//	DrawCollision用BefPosiテクスチャ番号

	float			animTimer;			//	アニメーションタイマー
	unsigned	int	animTimeMax;		//	animTimerがこの値を超えると0に戻る
	float			animOneFlameTime;	//	animTimerに加算し続ける変数

	unsigned	int	animFlame_W;		//	テクスチャの横分割数
	unsigned	int	animFlame_H;		//	テクスチャの縦分割数

	unsigned	int		animationNo_H;	//	テクスチャの縦のアニメーション値
	float				animationNo_W;	//	テクスチャの横のアニメーション値

	float	texSize_W;					//	テクスチャの横の表示サイズ
	float	texSize_H;					//	テクスチャの縦の表示サイズ

	float	speed;						//	オブジェクトの移動速度
	float	r_speed;					//	speedのReset値
	float	angle;						//	オブジェクトの回転角度

	D3DXVECTOR2	pos;					//	オブジェクトの現在地
	D3DXVECTOR2	pos_bef;				//	オブジェクトの前フレーム位置
	D3DXVECTOR2	actionFirstPos;			//	オブジェクトの特殊アクションの初期座標
	D3DXVECTOR2	r_pos;					//	posのReset値
	D3DXVECTOR2	StagePos;				//	ステージ全体に置ける座標
	D3DXVECTOR2	r_StagePos;				//	ステージ全体に置ける初期座標
	D3DXVECTOR2	size;					//	オブジェクトの描画範囲

	D3DXVECTOR2	move;					//	オブジェクトの移動方向、ノーマライズされたベクトルにspeedをかけた値を代入する
	D3DXVECTOR2	point;					//	オブジェクトのポイント移動の目標座標

	D3DXVECTOR2	collisionLocalPos;		//	オブジェクトから見た当たり判定の中心座標
	D3DXVECTOR2	collisionSize;			//	当たり判定のサイズ

	D3DXCOLOR	color;					//	色

public:

	void	Init();						//	オブジェクトの初期化
	void	Uninit();					//	オブジェクトの終了処理
	virtual	void	Update() = 0;		//	継承先で使用する更新処理
	void	Draw();						//	オブジェクトの描画処理
	void	DrawCollision();			//	当たり判定位置、サイズ確認描画

	void	Animation();				//	オブジェクトのアニメーション

	//==============================================================================
	void	Move();						//	オブジェクトの移動操作
	void	Gravity();					//	オブジェクトの重力操作
	//==============================================================================

	virtual	void	Prepare() = 0;		//	オブジェクトの情報をセットする
	virtual	void	Reset() = 0;		//	オブジェクトの初期情報をセットする

	void	SetUse(const	bool&	new_use) { use = new_use; }		//	オブジェクト使用セット
	const	bool&	GetUse(void) { return	use; }					//	オブジェクト使用取得

	void	SetActive(const	bool&	new_active) { active = new_active; }	//	移動の可不可のセット
	const	bool&	GetActive(void) { return	active; }					//	移動の可不可の取得

	void	SetAnimation(const	bool&	new_use) { animation = new_use; }		//	オブジェクトアニメーションセット
	const	bool&	GetAnimation(void) { return	animation; }					//	オブジェクトアニメーション取得

	void	SetMoveType(const	MOVE_TYPE&	new_type) { move_type = new_type; }	//	移動タイプセット
	const	MOVE_TYPE&	GetMoveType(void) { return	move_type; }				//	移動タイプ取得

	void	SetTexNo(const	int&	new_TexNo) { texNo = new_TexNo; }	//	テクスチャ番号セット
	const	int&	GetTexNo(void) { return	texNo; }					//	テクスチャ番号取得

	void	SetPosi(const	D3DXVECTOR2&	new_Pos) { pos = new_Pos; }	//	座標セット
	D3DXVECTOR2&	GetPosi(void) { return	pos; }				//	座標取得

	void	SetBefPosi(const	D3DXVECTOR2&	new_BefPos) { pos_bef = new_BefPos; }	//	前座標のセット
	const	D3DXVECTOR2&	GetBefPosi(void) { return	pos_bef; }						//	前座標の取得

	void	SetRPos(const	D3DXVECTOR2&	new_RPos) { r_pos = new_RPos; }	//	オブジェクトの初期座標のセット
	const	D3DXVECTOR2&	GetRPos(void) { return	r_pos; }				//	オブジェクトの初期座標の取得

	void	SetStagePos(const	D3DXVECTOR2&	new_StPos) { StagePos = new_StPos; }	//	ステージ全体に置ける座標のセット
	const	D3DXVECTOR2&	GetStagePos(void) { return	StagePos; }						//	ステージ全体に置ける座標の取得

	void	SetRStagePos(const	D3DXVECTOR2&	new_RStPos) { r_StagePos = new_RStPos; }	//	ステージ全体に置ける座標のセット
	const	D3DXVECTOR2&	GetRStagePos(void) { return	r_StagePos; }						//	ステージ全体に置ける座標の取得

	void	SetAngle(const	float	new_Angle) { angle = new_Angle; }	//	回転角度セット
	const	float&	GetAngle(void) { return	angle; }					//	回転角度取得

	void	SetAnimTimer(const	float&	new_value) { animTimer = new_value; }	//	回転角度セット
	const	float&	GetAnimTimer(void) { return	animTimer; }					//	回転角度取得

	void	SetTexSizeWidth(const	float&	new_texSize) { texSize_W = new_texSize; }	//	テクスチャの横表示サイズのセット
	const	float&	GetTexSizeWidth(void) { return	texSize_W; }						//	テクスチャの横表示サイズの取得

	void	SetTexSizeHeight(const	float&	new_texSize) { texSize_H = new_texSize; }	//	テクスチャの縦表示サイズのセット
	const	float&	GetTexSizeHeight(void) { return	texSize_H; }						//	テクスチャの縦表示サイズの取得

	void	SetSize(const	D3DXVECTOR2&	new_Size) { size = new_Size; }	//	サイズセット
	const	D3DXVECTOR2&	GetSize(void) { return	size; }					//	サイズ取得

	void	SetMove(const	D3DXVECTOR2&	new_Move) { move = new_Move; }	//	移動ベクトルセット
	const	D3DXVECTOR2&	GetMove(void) { return	move; }					//	移動ベクトル取得

	void	SetSpeed(const	float&	new_Speed) { speed = new_Speed; }		//	移動スピードセット
	const	float&	GetSpeed(void) { return	speed; }						//	移動スピード取得

	void	SetRSpeed(const	float&	new_Speed) { r_speed = new_Speed; }		//	移動スピードセット
	const	float&	GetRSpeed(void) { return	r_speed; }						//	移動スピード取得

	void	SetFrictionRate(const	float&	newValue) { frictionRate = newValue; }		//	移動スピードセット
	const	float&	GetFrictionRate(void) { return	frictionRate; }						//	移動スピード取得

	void	SetCollisionPos(const	D3DXVECTOR2&	new_CollisionPos) { collisionLocalPos = new_CollisionPos; }	//	当たり判定座標セット
	const	D3DXVECTOR2&	GetCollisionPos(void) { return	collisionLocalPos; }								//	当たり判定座標取得

	void	SetCollisionSize(const	D3DXVECTOR2&	new_CollisionSize) { collisionSize = new_CollisionSize; }	//	当たり判定サイズセット
	const	D3DXVECTOR2&	GetCollisionSize(void) { return	collisionSize; }									//	当たり判定座標取得

	void	SetPoint(const	D3DXVECTOR2&	new_Point) { point = new_Point; }	//	ポイント移動座標セット
	const	D3DXVECTOR2&	GetPoint(void) { return	point; }					//	ポイント移動座標取得

	void	SetColor(const	D3DXCOLOR&	new_Color) { color = new_Color; }	//	色セット
	const	D3DXCOLOR	GetColor(void) { return	color; }					//	色取得

	void	SetGravity(bool	new_Gravity) { gravity = new_Gravity; }		//	重力ブールセット
	const	bool&	GetGravity(void) { return	gravity; }				//	重力ブール取得

	void	SetMoveX(bool	new_MoveX) { MoveX = new_MoveX; }	//	横移動セット
	const	bool&	GetMoveX(void) { return	MoveX; }			//	横移動取得

	void	SetMoveY(bool	new_MoveY) { MoveY = new_MoveY; }	//	縦移動セット
	const	bool&	GetMoveY(void) { return	MoveY; }			//	縦移動取得

	void	SetOnGround(bool	new_OnGround) { onGround = new_OnGround; }	//	着地しているかBoolのセット
	const	bool&	GetOnGround(void) { return	onGround; }					//	着地しているかBoolの取得

	void	SetOnWall(bool	new_onWall) { onWall = new_onWall; }	//	壁に接しているかBoolのセット
	const	bool&	GetOnWall(void) { return	onWall; }			//	壁に接しているかBoolの取得

	void	SetArrivePoint(const	bool&	new_Arrive) {	ArrivePoint = new_Arrive; }	//	ポイントに到着しているかBoolのセット
	const	bool&	GetArrivePoint(void) { return	ArrivePoint; }						//	ポイントに到着しているかBoolの取得

	void	SetCollisionBool(bool	new_col) { collisionBool = new_col; }	//	当たり判定使用セット
	const	bool&	GetCollisionBool(void) { return	collisionBool; }		//	当たり判定取得

	void	SetOnTrigger(bool	new_bool) { OnTrigger = new_bool; }	//	別コリジョンに触れているかBoolのセット
	bool*	GetOnTrigger(void) { return	&OnTrigger; }				//	別コリジョンに触れているかBoolの取得

	void	SetAnimationOver(bool	new_col) { animationOver = new_col; }	//	アニメーション終了セット
	const	bool&	GetAnimationOver(void) { return	animationOver; }		//	アニメーション終了の有無取得

	static	void	SetCollitionTest(const	bool&	Switch) { collisionTest = Switch; }		//	DrawCollisionの使用Bool切り替え
};






