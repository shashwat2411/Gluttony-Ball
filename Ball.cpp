#include "Ball.h"
#include "player.h"
#include "ground.h"
#include "Explosion.h"
#include "StickyBomb.h"
#include "Spring.h"
#include "Enemy.h"
#include "collision.h"
#include "homingMarker.h"

unsigned	int	g_NumbersTexNum;

ENEMY* b_enemy;
GROUND* b_ground;
//==============================================================================================================================
//	ボールクラスプログラム
//==============================================================================================================================
void	BALL::Update()
{
	if (use)
	{
		counter += 1;

		if (!onWall)	pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		MovedDisSq += (pos.x - posBefForDis.x) * (pos.x - posBefForDis.x) + (pos.y - posBefForDis.y) * (pos.y - posBefForDis.y);

		if (MovedDisSq >= (ThrowDis * ThrowDis) / 10 && gravity == false && onGround == false && ability_move_ball != BOUNCE && move_type == Normal && situation == Throwing)
		{
			MovedDisSq = 0;
			gravity = true;
			situation = Free;
		}

		posBefForDis = pos;

		//======================================================================================================
		//	能力による特殊処理
		//======================================================================================================
		//	バウンド移動処理
		if (ability_move_ball == BOUNCE && situation == Throwing)
		{
			if (BounceCount > BOUNCE_COUNT && !gravity)
			{
				gravity = true;
				situation = Free;
			}
			else if (gravity)	gravity = false;
		}
		//======================================================================================================
		//	ホーミング移動処理
		else if (ability_move_ball == HOMING && situation == Throwing && HomingPos[TargetNum] != nullptr)
		{
			speed = 7.0f;
			point = *(HomingPos[TargetNum]);

			if (ArrivePoint)
			{
				if (HomingNum > 0 && HomingNum < HOMING_POS_MAX && HomingNum > TargetNum + 1)
				{
					ArrivePoint = false;
					HomingPos[TargetNum] = nullptr;
					TargetNum++;
					point = *(HomingPos[TargetNum]);
				}
				else
				{
					ArrivePoint = false;
					situation = Return;
				}
			}
		}
		//======================================================================================================


		if (gravity) { move.x *= airFrictionRate; }
		if (onGround) { move.x *= frictionRate; }
		if (onGround && fabs(move.x) < 0.01f)		situation = Stay;

		if (situation == Stay && counter % (60 * 2) == 0 && GetPlayer()->GetControl()) { counter = 0; situation = Return; }

		if (pos.y > SCREEN_HEIGHT + 100 || pos.y < -100 || pos.x > SCREEN_WIDTH + 100 || pos.x < -100) { situation = Return; }
		if (situation == Return) { SetBallReturn(); }

		if (situation == Keep && use)	situation = Return;


		Gravity();
		Move();
	}
	else if (situation != Keep && situation != ChargeThrow)	situation = Keep;
}

void	BALL::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	MoveX = true;
	MoveY = true;

	ArrivePoint = false;

	texNo = LoadTexture((char*)"data/texture/IronBall.png");				//	LoadTextureの戻り値を記録する変数
	g_NumbersTexNum = LoadTexture((char*)"data/texture/numbers.png");

	g_BallSE = LoadSound((char*)"data/SE/ballTouch_SE.wav");

	situation = Keep;
	ability_attack = NONE_ATTACK;
	ability_move_ball = NONE_BALL;
	ability_move_player = NONE_PLAYER;

	HomingNum = 0;

	animTimeMax = 13;		//	animTimerがこの値を超えると0に戻る
	animOneFlameTime = 0.2f;			//	animTimerに加算し続ける変数

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	ThrowDis = ThrowDisMin;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	frictionRate = 0.8f;
	airFrictionRate = 0.8f;
	gravityNum = 2.0f;

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x * 3 / 4, size.y * 3 / 4);				//	当たり判定のサイズ

	speed = 10.0f;
	r_speed = speed;//スピードをセット
	move = D3DXVECTOR2(1, -1);		//移動方向をセット
	D3DXVec2Normalize(&move, &move);//ベクトルの正規化
	move *= speed;					//移動距離を計算

	b_enemy = GetEnemy();
	b_ground = GetGround();
}

void	BALL::Reset()
{

}

void	BALL::SetBallReturn()
{
	move_type = Point;
	point = GetPlayer()->GetPosi();
	gravity = false;
	onGround = false;
	collisionBool = false;
	speed = 20.0f;


	if (ArrivePoint)
	{
		GetPlayer()->SetStockBall(true);
		use = false;
		ArrivePoint = false;
		collisionBool = true;
		situation = Keep;
		ThrowDis = ThrowDisMin;
		speed = r_speed;
		
		if (ability_move_ball == BALL::HOMING)
		{
			ResetHomingMaker();
			HomingNum = 0;

			for (int i = 0; i < HOMING_POS_MAX; i++)
			{
				HomingPos[i] = nullptr;
			}
		}
	}

}

void BALL::SetBallPoint(D3DXVECTOR2 new_point)
{
	move_type = Point;
	point = new_point;
	gravity = false;
	onGround = false;
	speed = 3.0f;
	situation = Throwing;

	if (ArrivePoint)
	{
		ArrivePoint = false;
		//move_type = Normal;
		//speed = r_speed;
	}

}

void BALL::SetBall(D3DXVECTOR2 pos, D3DXVECTOR2	way)
{
	use = true;		//使用フラグをtrueに
	SetPosi(pos);	//座標をセット
	posBefForDis = pos;
	MovedDisSq = 0;
	TargetNum = 0;

	UsedSEBool = false;
	ArrivePoint = false;
	gravity = false;			//重力を無効化
	D3DXVec2Normalize(&move, &way);//ベクトルの正規化
	move *= speed;
	onGround = false;
	MoveX = true;
	MoveY = true;
	BounceCount = 0;
	move_type = Normal;

}

void	BALL::SetTarget(ENEMY*	new_Enemy, BUTTON*	new_Button)		//	ホーミングでロックしたエネミーの追加
{
	if (HomingNum > 0)
	{
		if (new_Enemy != nullptr)
		{
			if (HomingPos[0] == &(new_Enemy->GetPosi()))	return;
		}
		if (new_Button != nullptr)
		{
			if (HomingPos[0] == &(new_Button->GetPosi()))	return;
		}
	}

	if (HomingNum <= HOMING_POS_MAX)
	{
		if (new_Enemy != nullptr)
		{
			for (int i = 0; i < HomingNum; i++)
			{
				if (HomingPos[i] == &(new_Enemy->GetPosi()))
				{
					/*for (int j = i; j > 0; j--)
					{
						HomingPos[j] = HomingPos[j - 1];
					}
					HomingPos[0] = &(new_Enemy->GetPosi());*/

					return;
				}
			}

			SetHomingMarker(new_Enemy, nullptr);
			HomingPos[HomingNum] = &(new_Enemy->GetPosi());
			HomingNum++;
		}
		if (new_Button != nullptr)
		{
			for (int i = 0; i < HomingNum; i++)
			{
				if (HomingPos[i] == &(new_Button->GetPosi()))
				{
					/*for (int j = i; j > 0; j--)
					{
						HomingPos[j] = HomingPos[j - 1];
					}
					HomingPos[0] = &(new_Button->GetPosi());*/

					return;
				}
			}

			SetHomingMarker(nullptr, new_Button);
			HomingPos[HomingNum] = &(new_Button->GetPosi());
			HomingNum++;
		}
	}
}


//==============================================================================================================================
//	ボール管理プログラム
//==============================================================================================================================
BALL	ball;

/*==================================
	ボール初期化
====================================*/
void	InitBall()
{
	ball.Init();
	ball.Prepare();
}

/*==================================
	ボール終了処理
====================================*/
void	UninitBall()
{
	ball.Uninit();
}

/*==================================
	ボール更新処理
====================================*/
void	UpdateBall()
{
	ball.Update();
}

/*==================================
	ボール描画処理
====================================*/
void	DrawBall()
{
	ball.Draw();

	if (ball.GetHomingNum() > 0 && ball.GetAbilityMoveBall() == BALL::HOMING)
	{
		D3DXVECTOR2**	g_TargetPos = ball.GetTargetEnemy();
		for (int i = 0; i < ball.GetHomingNum(); i++)
		{
			if (g_TargetPos[i] != nullptr)
			{
				// テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_NumbersTexNum));

				//	ポリゴン配置
				DrawSpriteColorRotate((*g_TargetPos[i]).x + BASE_SIZE, (*g_TargetPos[i]).y + BASE_SIZE, BASE_SIZE / 2, BASE_SIZE, 0.0f,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), i, 1.0f / 10, 1.0f, 0.0f);
			}
		}
	}
}

/*==================================
	ボール取得
====================================*/
BALL*	GetBall()
{
	return	&ball;
}


























