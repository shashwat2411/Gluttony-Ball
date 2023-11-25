
#include	"collision.h"

#include	"player.h"
#include	"ball.h"
#include	"Enemy.h"
#include	"ground.h"
#include	"Spring.h"
#include	"StickyBomb.h"
#include	"Explosion.h"
#include	"bullet.h"
#include	"enemyStickyBomb.h"
#include	"Waiver.h"
#include	"Button.h"
#include	"InterlockArrangement.h"
#include	"knife.h"
#include	"StageGimmick.h"
#include	"effect.h"
#include	"oneWayBlock.h"

//==============================================================
//	オブジェクト変数
//==============================================================
PLAYER*	c_player;
BALL*	c_ball;
ENEMY*	c_enemy;
GROUND*	c_ground;
SPRING* c_spring;
EXPLOSION*	c_explosion;
BULLET*	c_bullet;
ENEMY_STICKY_BOMB*	c_enemy_sticky_bomb;
WAIVER*	c_waiver;
BUTTON* c_button;
INTERLOCKARRANGEMENT* c_inter;
KNIFE*	c_knife;
STAGEGIMMICK* c_stageGimmick;
ONE_WAY_BLOCK*	c_oneWayBlock;

bool AllCollisionBool;

//==============================================================
//	コリジョン検索
//==============================================================
void	InitCollision()
{
	c_player = GetPlayer();	//	プレイヤー情報の取得
	c_ball = GetBall();		//	ボール情報の取得
	c_enemy = GetEnemy();	//	エネミー情報の取得
	c_ground = GetGround();	//	グラウンド情報の取得

	c_spring = GetSpring();
	c_button = GetButton(); //ボタン情報の取得
	c_inter = GetInterlockArrangement(); //ボタンに連動して作動するもの情報の取得
	c_knife = GetKnife();
	c_stageGimmick = GetStageGimmick();

	c_explosion = GetExplosion();	//	爆発情報の取得
	c_bullet = GetBullet();	//	バレット情報の取得
	c_enemy_sticky_bomb = GetEnemyStickyBomb();	//	スティッキー爆弾情報の取得

	c_waiver = GetWaiver();	//	放棄アビリティの取得

	c_oneWayBlock = GetOneWayBlock();

	AllCollisionBool = true;
}
void	UpdateCollision()
{
	if (AllCollisionBool == true)
	{
		//PLAYER & BALL
		Collision_Player_VS_Ground();	//	PLAYER VS GROUND
		Collision_Ball_VS_Ground();	//	BALL VS GROUND

		//EXPLOSION
		Collision_Explosion();	//	PLAYER, ENEMY

		//WAIVER
		Collision_Waiver();	//	PLAYER, GROUND

		//BUTTON
		Collision_Button();	//  PLAYER, BALL

		//DOOR
		Collision_InterlockArrangement();	//	PLAYER, BALL

		//SPRING
		Collision_Spring();	//PLAYER

		//STAGE GIMMICK
		Collision_StageGimmick();	//	PLAYER, ENEMY, BALL

		//ENEMY
		Collision_Enemy_VS_Ground();	//	ENEMY VS GROUND
		Collision_Enemy_VS_Ball();	//	ENEMY VS BALL
		Collision_Enemy_VS_Player();	//	ENEMY VS PLAYER

		Collision_EnemyKnife();	//	PLAYER, GROUND, BALL

		Collision_EnemyBullet();	//	GROUND, BALL

		Collision_EnemySticky();	//	GROUND
	}
}




//PLAYER & BALL
void	Collision_Player_VS_Ground()	//	プレイヤーvsグラウンドの当たり判定チェッカー
{
	if (c_player->GetUse() && c_player->GetCollisionBool())
	{
		bool	OnGround = false;
		bool	OnWall = false;
		for (GROUND* g_ground = c_ground; g_ground < c_ground + GROUND_MAX; g_ground++)
		{
			if (g_ground->GetUse() && g_ground->GetCollisionBool())
			{
				//=============================================
				//	追従能力で引っかかった時の処理
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && !c_player->GetArrivePoint() && c_player->GetActive())
				{
					if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						c_player->SetArrivePoint(true);
					}
				}

				//	足場の上コリジョンとの当たり判定
				if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
				{
					OnGround = true;
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - c_player->GetSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
				}
				//	足場の下コリジョンとの当たり判定
				if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
				{
					c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
				}
				//	足場の右コリジョンとの当たり判定
				if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
				{
					OnWall = true;
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
				}
				//	足場の左コリジョンとの当たり判定
				if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
				{
					OnWall = true;
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
				}

				//	足場の全体コリジョンによる誤作動修正
				if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()) && !OnGround && !OnWall)
				{
					if (fabs(c_player->GetMove().x) > fabs(c_player->GetMove().y))
					{
						//	足場より左にいる場合
						if (c_player->GetPosi().x - g_ground->GetPosi().x < 0 && c_player->GetMove().x > 0)
						{
							OnWall = true;
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
						}
						//	足場より右にいる場合
						else if (c_player->GetPosi().x - g_ground->GetPosi().x > 0 && c_player->GetMove().x < 0)
						{
							OnWall = true;
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
						}
					}
					if (fabs(c_player->GetMove().x) < fabs(c_player->GetMove().y))
					{
						//	足場より下にいる場合
						if (c_player->GetPosi().y - g_ground->GetPosi().y > 0)
						{
							c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
						}
						//	足場より上にいる場合
						else if (c_player->GetPosi().y - g_ground->GetPosi().y < 0)
						{
							OnGround = true;
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - c_player->GetSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
						}
					}
				}
			}
		}

		//==========================================================================
		//	プレイヤーvsOneWayBlock
		for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
		{
			if (c_oneWayBlock[i].GetUse() && c_oneWayBlock[i].GetCollisionBool())
			{
				if (c_oneWayBlock[i].GetWay() == ONE_WAY_BLOCK::WAY::UP)
				{
					if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}

					if (c_oneWayBlock[i].GetCollisionBool())
					{
						if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
							c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
						{
							OnGround = true;
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_oneWayBlock[i].GetPosi().y - c_oneWayBlock[i].GetSize().y / 2 - c_player->GetSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));

							//c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
						
							//=============================================
							//	追従能力で引っかかった時の処理
							if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && !c_player->GetArrivePoint() && c_player->GetActive())
							{
								c_player->SetArrivePoint(true);
							}
						}
					}
				}
				else if (c_oneWayBlock[i].GetWay() == ONE_WAY_BLOCK::WAY::DOWN)
				{
					if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}

					if (c_oneWayBlock[i].GetCollisionBool())
					{
						if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
							c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
						{
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_oneWayBlock[i].GetPosi().y + c_oneWayBlock[i].GetSize().y / 2 + c_player->GetSize().y / 2));
							c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));

							//=============================================
							//	追従能力で引っかかった時の処理
							if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && !c_player->GetArrivePoint() && c_player->GetActive())
							{
								c_player->SetArrivePoint(true);
							}
						}
					}
				}
				else if (c_oneWayBlock[i].GetWay() == ONE_WAY_BLOCK::WAY::RIGHT)
				{
					if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}

					if (c_oneWayBlock[i].GetCollisionBool())
					{
						if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
							c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
						{
							OnWall = true;
							c_player->SetPosi(D3DXVECTOR2(c_oneWayBlock[i].GetPosi().x + c_oneWayBlock[i].GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));

							//=============================================
							//	追従能力で引っかかった時の処理
							if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && !c_player->GetArrivePoint() && c_player->GetActive())
							{
								c_player->SetArrivePoint(true);
							}
						}
					}
				}
				else if (c_oneWayBlock[i].GetWay() == ONE_WAY_BLOCK::WAY::LEFT)
				{
					if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}
					if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
					{
						c_oneWayBlock[i].SetCollisionBool(false);
					}

					if (c_oneWayBlock[i].GetCollisionBool())
					{
						if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
							c_player->GetCollisionSize(), c_oneWayBlock[i].GetPosi() + c_oneWayBlock[i].GetCollisionPos(), c_oneWayBlock[i].GetCollisionSize()))
						{
							OnWall = true;
							c_player->SetPosi(D3DXVECTOR2(c_oneWayBlock[i].GetPosi().x - c_oneWayBlock[i].GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));

							//=============================================
							//	追従能力で引っかかった時の処理
							if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && !c_player->GetArrivePoint() && c_player->GetActive())
							{
								c_player->SetArrivePoint(true);
							}
						}
					}
				}
			}
		}


		c_player->SetOnWall(OnWall);
		c_player->SetOnGround(OnGround);
	}
}
void	Collision_Ball_VS_Ground()	//	ボールvsグラウンドの当たり判定チェッカー
{
	if (c_ball->GetUse() && c_ball->GetCollisionBool())
	{
		bool	OnGround = false;
		bool	OnWall = false;
		bool	AttackBool = false;
		bool	SpringBool = false;
		bool	SEBool = false;

		if (c_ball->GetAbilityMoveBall() == BALL::BOUNCE && c_ball->GetBounceCount() <= BOUNCE_COUNT)
		{
			switch (CheckTouchGround(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi()
				+ c_ball->GetCollisionPos(), c_ball->GetCollisionSize()))
			{
			case	Up:	c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, -fabs(c_ball->GetMove().y)));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_ball->GetCollisionSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_ball->GetCollisionSize().y / 2 - BASE_SIZE / 2));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
					c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y));

				break;
			case	Down:	c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetCollisionSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetCollisionSize().y / 2 + BASE_SIZE / 2));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
					c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_player->GetSize().y));

				break;
			case	Right:	c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x - c_ball->GetCollisionSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 90.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x - c_ball->GetCollisionSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

				break;
			case	Left:	c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x + c_ball->GetCollisionSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 270.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x + c_ball->GetCollisionSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

				break;
			default:
				break;
			}
		}
		else
		{
			//======================================================================================================
			//	ボールと足場との当たり判定チェック及び、通常物理演算処理
			for (GROUND* g_ground = c_ground; g_ground < c_ground + GROUND_MAX; g_ground++)
			{
				if (g_ground->GetUse() && g_ground->GetCollisionBool())
				{
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnGround = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
						c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
						c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));


						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
							c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_player->GetSize().y));

					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnWall = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));

						c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 90.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnWall = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));

						c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 270.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						if (fabs(c_ball->GetMove().x) < fabs(c_ball->GetMove().y))
						{
							//	足場より下にいる場合
							if (c_ball->GetPosi().y - g_ground->GetPosi().y > 0)
							{
								/*AttackBool = true;
								SpringBool = true;*/

								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));


								//========================================================================
								//	スティッキー爆弾能力の使用処理
								/*if (c_ball->GetAbilityAttack() == BALL::STICKY)
								{
									if (!c_ball->GetUsedAttackBool() && AttackBool)
									{
										SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);
									}
								}*/
								//========================================================================
								//	バネ能力の使用処理
								/*if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
								{
									if (!c_ball->GetUsedSpringBool() && SpringBool)
									{
										SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2));
									}
								}*/
								//========================================================================
							}
							//	足場より上にいる場合
							else if (c_ball->GetPosi().y - g_ground->GetPosi().y < 0)
							{
								OnGround = true;
								/*AttackBool = true;
								SpringBool = true;*/

								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
								c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

								//========================================================================
								//	スティッキー爆弾能力の使用処理
								/*if (c_ball->GetAbilityAttack() == BALL::STICKY)
								{
									if (!c_ball->GetUsedAttackBool() && AttackBool)
									{
										SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);
									}
								}*/
								//========================================================================
								//	バネ能力の使用処理
								/*if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
								{
									if (!c_ball->GetUsedSpringBool() && SpringBool)
									{
										SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2));
									}
								}*/
								//========================================================================
							}
						}
					}
				}
			}
		}

		if (c_ball->GetAbilityMoveBall() == BALL::BOUNCE && c_ball->GetBounceCount() < BOUNCE_COUNT)
		{
			switch (CheckTouchStageGimmick(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi()
				+ c_ball->GetCollisionPos(), c_ball->GetCollisionSize()))
			{
			case	Up:	c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, -fabs(c_ball->GetMove().y)));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_ball->GetCollisionSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_ball->GetCollisionSize().y / 2 - BASE_SIZE / 2));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
					c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y));

				break;
			case	Down:	c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetCollisionSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetCollisionSize().y / 2 + BASE_SIZE / 2));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
					c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_player->GetSize().y));

				break;
			case	Right:	c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x - c_ball->GetCollisionSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 90.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x - c_ball->GetCollisionSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

				break;
			case	Left:	c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
				c_ball->SetBounceCount(c_ball->GetBounceCount() + 1);	AttackBool = true;	SpringBool = true;	SEBool = true;

				//	スティッキー爆弾
				if (c_ball->GetAbilityAttack() == BALL::STICKY && !c_ball->GetUsedAttackBool() && AttackBool)
					SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x + c_ball->GetCollisionSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 270.0f);

				//	バネ設置
				if (c_ball->GetAbilityMovePlayer() == BALL::SPRING && !c_ball->GetUsedSpringBool() && SpringBool)
					SetSpring(D3DXVECTOR2(c_ball->GetPosi().x + c_ball->GetCollisionSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y));

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

				break;
			default:
				break;
			}
		}
		else
		{
			//======================================================================================================
			//	ボールと足場との当たり判定チェック及び、通常物理演算処理
			for (STAGEGIMMICK* g_stageGimmick = c_stageGimmick; g_stageGimmick < c_stageGimmick + STAGEGIMMICK_MAX; g_stageGimmick++)
			{
				if (g_stageGimmick->GetUse() && g_stageGimmick->GetCollisionBool())
				{
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
					{
						OnGround = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
						c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - BASE_SIZE / 2));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
					{
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
						c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));


						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + BASE_SIZE / 2));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)
							c_player->SetTracePos(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y + c_player->GetSize().y));

					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
					{
						OnWall = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));

						c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 90.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + BASE_SIZE / 2, c_ball->GetPosi().y));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
					{
						OnWall = true;
						AttackBool = true;
						SpringBool = true;
						SEBool = true;

						c_ball->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));

						c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));

						//========================================================================
						//	スティッキー爆弾能力の使用処理
						if (c_ball->GetAbilityAttack() == BALL::STICKY)
						{
							if (!c_ball->GetUsedAttackBool() && AttackBool)
							{
								SetStickyBomb(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y), nullptr, 270.0f);
							}
						}
						//========================================================================
						//	バネ能力の使用処理
						if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
						{
							if (!c_ball->GetUsedSpringBool() && SpringBool)
							{
								SetSpring(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - BASE_SIZE / 2, c_ball->GetPosi().y));
							}
						}
						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
						//========================================================================
						//	追従能力
						if (c_ball->GetAbilityMovePlayer() == BALL::TRACE)	c_player->SetTracePos(c_ball->GetPosi());

					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
					{
						if (fabs(c_ball->GetMove().x) < fabs(c_ball->GetMove().y))
						{
							//	足場より下にいる場合
							if (c_ball->GetPosi().y - g_stageGimmick->GetPosi().y > 0)
							{
								/*AttackBool = true;
								SpringBool = true;*/

								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));


								//========================================================================
								//	スティッキー爆弾能力の使用処理
								/*if (c_ball->GetAbilityAttack() == BALL::STICKY)
								{
									if (!c_ball->GetUsedAttackBool() && AttackBool)
									{
										SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2), nullptr, 180.0f);
									}
								}*/
								//========================================================================
								//	バネ能力の使用処理
								/*if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
								{
									if (!c_ball->GetUsedSpringBool() && SpringBool)
									{
										SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + BASE_SIZE / 2));
									}
								}*/
								//========================================================================
							}
							//	足場より上にいる場合
							else if (c_ball->GetPosi().y - g_stageGimmick->GetPosi().y < 0)
							{
								OnGround = true;
								/*AttackBool = true;
								SpringBool = true;*/

								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
								c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

								//========================================================================
								//	スティッキー爆弾能力の使用処理
								/*if (c_ball->GetAbilityAttack() == BALL::STICKY)
								{
									if (!c_ball->GetUsedAttackBool() && AttackBool)
									{
										SetStickyBomb(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2), nullptr, 0.0f);
									}
								}*/
								//========================================================================
								//	バネ能力の使用処理
								/*if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
								{
									if (!c_ball->GetUsedSpringBool() && SpringBool)
									{
										SetSpring(D3DXVECTOR2(c_ball->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - BASE_SIZE / 2));
									}
								}*/
								//========================================================================
							}
						}
					}
				}
			}
		}

		for (INTERLOCKARRANGEMENT* g_inter = c_inter; g_inter < c_inter + BUTTON_MAX; g_inter++)
		{
			if (g_inter->GetUse() && g_inter->GetCollisionBool())
			{
				bool onoff = g_inter->GetOn_Off_InterlockArrangement();

				if (!onoff) //まだ作動していない場合は壁としての当たり判定有り
				{
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnGround = true;
						SEBool = true;
						//c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, 0));
						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_inter->GetPosi().y - g_inter->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
						c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));
						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_inter->GetPosi().y + g_inter->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
						//c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));

						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnWall = true;
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
						c_ball->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_ball->GetCollisionSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_ball->GetCollisionSize().x / 2, c_ball->GetBefPosi().y));

						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnWall = true;
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
						c_ball->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_ball->GetCollisionSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_ball->GetCollisionSize().x / 2, c_ball->GetBefPosi().y));

						//========================================================================
						//	ホーミング能力の強制帰還処理
						if (c_ball->GetAbilityMoveBall() == BALL::HOMING && c_ball->GetHomingNum() > 0)
						{
							c_ball->SetArrivePoint(true);
							c_ball->SetHomingNum(0);
						}
					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						if (fabs(c_ball->GetMove().x) > fabs(c_ball->GetMove().y))
						{
							//	足場より左にいる場合
							//if (c_ball->GetPosi().x - g_ground->GetPosi().x < 0 && c_ball->GetMove().x > 0)
							//{
							//	OnWall = true;
							//	c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
							//	c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetPosi().y));
							//	c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
							//}
							////	足場より右にいる場合
							//else if (c_ball->GetPosi().x - g_ground->GetPosi().x > 0 && c_ball->GetMove().x < 0)
							//{
							//	OnWall = true;
							//	c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
							//	c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetPosi().y));
							//	c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
							//}
						}
						if (fabs(c_ball->GetMove().x) < fabs(c_ball->GetMove().y))
						{
							//	足場より下にいる場合
							if (c_ball->GetPosi().y - g_inter->GetPosi().y > 0)
							{
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, 0));
								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_inter->GetPosi().y + g_inter->GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
								c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));
							}
							//	足場より上にいる場合
							else if (c_ball->GetPosi().y - g_inter->GetPosi().y < 0)
							{
								OnGround = true;
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, 0));
								c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, g_inter->GetPosi().y - g_inter->GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
							}
						}
					}
				}
			}
		}

		if (c_ball->GetAbilityAttack() != BALL::NONE_ATTACK)
		{
			//=============================================================================================================
			//	爆発能力の足場に置ける使用処理
			if (c_ball->GetAbilityAttack() == BALL::EXPLOSION && !c_ball->GetUsedAttackBool() && AttackBool)
				SetExplosion(c_ball->GetPosi(), D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE * 5), EXPLOSION::PLAYER);
			//=============================================================================================================

			c_ball->SetUsedAttackBool(AttackBool);
		}

		//=================================================================================================
		//	バネを使用したかBoolのセット、ここで同じ場所に連続でバネを設置するのを防ぐ
		if (c_ball->GetAbilityMovePlayer() == BALL::SPRING)
		{
			c_ball->SetUsedSpringBool(SpringBool);
		}
		//=================================================================================================

		//=================================================================================================
		//	ボールSE処理
		c_ball->PlayBallSE(SEBool);
		//=================================================================================================

		c_ball->SetOnGround(OnGround);
		c_ball->SetOnWall(OnWall);
	}
}

//EXPLOSION
void	Collision_Explosion()	//	Player, Enemy
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//PLAYER
		if (c_explosion[i].GetUse() && c_explosion[i].GetSource() == EXPLOSION::ENEMY && c_player->GetUse())
		{
			if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), c_explosion[i].GetPosi() + c_explosion[i].GetCollisionPos(), c_explosion[i].GetCollisionSize()))
			{
				c_player->SetUse(false);
			}
		}

		//ENEMY
		if (c_explosion[i].GetUse() && c_explosion[i].GetSource() == EXPLOSION::PLAYER && c_explosion[i].GetCollisionBool())
		{
			for (int enemy_num = 0; enemy_num < ENEMY_MAX; enemy_num++)
			{
				if (c_enemy[enemy_num].GetUse() && c_enemy[enemy_num].GetCollisionBool())
				{
					if (GetCollision(c_enemy[enemy_num].GetPosi() + c_enemy[enemy_num].GetCollisionPos(),
						c_enemy[enemy_num].GetBefPosi() + c_enemy[enemy_num].GetCollisionPos(), c_enemy[enemy_num].GetCollisionSize(),
						c_explosion[i].GetPosi() + c_explosion[i].GetCollisionPos(), c_explosion[i].GetCollisionSize()))
					{
						c_enemy[enemy_num].SetUse(false);
					}
				}
			}
		}
	}
}

//WAIVER
void	Collision_Waiver()	//	Player, Ground
{
	bool	OnGround;
	bool	OnWall;
	for (WAIVER* g_waiver = c_waiver; g_waiver < c_waiver + WAIVER_MAX; g_waiver++)
	{
		//PLAYER
		if (c_player->GetUse() && c_player->GetCollisionBool() && g_waiver->GetUse() && g_waiver->GetCollisionBool())
		{
			if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetCollisionSize()))
			{
				if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetCollisionSize()))
				{
					if (c_ball->GetAbilityAttack() == BALL::NONE_ATTACK)
					{
						c_ball->SetAbilityAttack(g_waiver->GetAbilityType_AT());
						g_waiver->SetUse(false);
					}
					if (c_ball->GetAbilityMoveBall() == BALL::NONE_BALL)
					{
						c_ball->SetAbilityMoveBall(g_waiver->GetAbilityType_MB());
						g_waiver->SetUse(false);
					}
					if (c_ball->GetAbilityMovePlayer() == BALL::NONE_PLAYER)
					{
						c_ball->SetAbilityMovePlayer(g_waiver->GetAbilityType_MP());
						g_waiver->SetUse(false);
					}
				}
			}
		}

		
		//GROUND
		if (g_waiver->GetUse() && g_waiver->GetCollisionBool())
		{
			OnGround = false;
			OnWall = false;
			for (GROUND* g_ground = c_ground; g_ground < c_ground + GROUND_MAX; g_ground++)
			{
				if (g_ground->GetUse() && g_ground->GetCollisionBool())
				{
					//	バネエネミーの瞬間の当たり判定処理
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetBefPosi() + g_waiver->GetCollisionPos(),
						g_waiver->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnGround = true;
						g_waiver->SetPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - g_waiver->GetCollisionSize().y / 2));
						g_waiver->SetBefPosi(D3DXVECTOR2(g_waiver->GetBefPosi().x, g_waiver->GetPosi().y - g_waiver->GetSize().y / 3));
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetBefPosi() + g_waiver->GetCollisionPos(),
						g_waiver->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						g_waiver->SetMove(D3DXVECTOR2(g_waiver->GetMove().x, 0));
						g_waiver->SetPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + g_waiver->GetCollisionSize().y / 2));
						g_waiver->SetBefPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_waiver->GetPosi().y + g_waiver->GetSize().y / 3));
					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetBefPosi() + g_waiver->GetCollisionPos(),
						g_waiver->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnWall = true;
						g_waiver->SetMove(D3DXVECTOR2(0, g_waiver->GetMove().y));
						g_waiver->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_waiver->GetCollisionSize().x / 2, g_waiver->GetPosi().y));
						g_waiver->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_waiver->GetSize().x / 2, g_waiver->GetBefPosi().y));
					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetBefPosi() + g_waiver->GetCollisionPos(),
						g_waiver->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
					{
						OnWall = true;
						g_waiver->SetMove(D3DXVECTOR2(0, g_waiver->GetMove().y));
						g_waiver->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_waiver->GetCollisionSize().x / 2, g_waiver->GetPosi().y));
						g_waiver->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_waiver->GetSize().x / 2, g_waiver->GetBefPosi().y));
					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(g_waiver->GetPosi() + g_waiver->GetCollisionPos(), g_waiver->GetBefPosi() + g_waiver->GetCollisionPos(),
						g_waiver->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()) && !OnGround && !OnWall)
					{
						if (fabs(g_waiver->GetMove().x) > fabs(g_waiver->GetMove().y))
						{
							//	足場より左にいる場合
							if (g_waiver->GetPosi().x - g_ground->GetPosi().x < 0 && g_waiver->GetMove().x > 0)
							{
								OnWall = true;
								g_waiver->SetMove(D3DXVECTOR2(0, g_waiver->GetMove().y));
								g_waiver->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_waiver->GetSize().x / 2, g_waiver->GetPosi().y));
								g_waiver->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_waiver->GetSize().x / 2, g_waiver->GetBefPosi().y));
							}
							//	足場より右にいる場合
							else if (g_waiver->GetPosi().x - g_ground->GetPosi().x > 0 && g_waiver->GetMove().x < 0)
							{
								OnWall = true;
								g_waiver->SetMove(D3DXVECTOR2(0, g_waiver->GetMove().y));
								g_waiver->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_waiver->GetSize().x / 2, g_waiver->GetPosi().y));
								g_waiver->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_waiver->GetSize().x / 2, g_waiver->GetBefPosi().y));
							}
						}
						if (fabs(g_waiver->GetMove().x) < fabs(g_waiver->GetMove().y))
						{
							//	足場より下にいる場合
							if (g_waiver->GetPosi().y - g_ground->GetPosi().y > 0)
							{
								//g_waiver->SetMove(D3DXVECTOR2(g_waiver->GetMove().x, 0));
								g_waiver->SetPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + g_waiver->GetCollisionSize().y / 2));
								g_waiver->SetBefPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_waiver->GetPosi().y + g_waiver->GetSize().y / 3));
							}
							//	足場より上にいる場合
							else if (g_waiver->GetPosi().y - g_ground->GetPosi().y < 0)
							{
								OnGround = true;
								g_waiver->SetPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - g_waiver->GetSize().y / 2));
								g_waiver->SetBefPosi(D3DXVECTOR2(g_waiver->GetPosi().x, g_waiver->GetPosi().y - g_waiver->GetSize().y / 3));
							}
						}
					}
				}

				g_waiver->SetOnWall(OnWall);
				g_waiver->SetOnGround(OnGround);
			}
		}
	}
}

//STAGE GIMMICK
void	Collision_StageGimmick()	//	PLAYER, ENEMY, BALL
{
	bool PlayerOnGround = c_player->GetOnGround();
	bool EnemyOnGround;

	bool PlayerOnWall = c_player->GetOnWall();
	bool EnemyOnWall;

	//=========================================================================
	//	プレイヤーとの当たり判定
	if (c_player->GetUse() && c_player->GetCollisionBool())
	{
		for (STAGEGIMMICK* g_stageGimmick = c_stageGimmick; g_stageGimmick < c_stageGimmick + STAGEGIMMICK_MAX; g_stageGimmick++)
		{
			if (g_stageGimmick->GetUse() && g_stageGimmick->GetCollisionBool())
			{
				//	足場の上コリジョンとの当たり判定
				if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
				{
					PlayerOnGround = true;
					g_stageGimmick->SetOnPlayer(true);
					g_stageGimmick->SetPlayerHit(true);
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - c_player->GetSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
				}
				else
				{
					g_stageGimmick->SetOnPlayer(false);
				}
				//	足場の下コリジョンとの当たり判定
				if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
				{
					g_stageGimmick->SetPlayerHit(true);
					c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
				}
				//	足場の右コリジョンとの当たり判定
				if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
				{
					PlayerOnWall = true;
					g_stageGimmick->SetPlayerHit(true);
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
				}
				//	足場の左コリジョンとの当たり判定
				if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
				{
					PlayerOnWall = true;
					g_stageGimmick->SetPlayerHit(true);
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
				}

				//	足場の全体コリジョンによる誤作動修正
				if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()) && !PlayerOnGround && !PlayerOnWall)
				{
					if (fabs(c_player->GetMove().x) > fabs(c_player->GetMove().y))
					{
						//	足場より左にいる場合
						if (c_player->GetPosi().x - g_stageGimmick->GetPosi().x < 0 && c_player->GetMove().x > 0)
						{
							PlayerOnWall = true;
							g_stageGimmick->SetPlayerHit(true);
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
						}
						//	足場より右にいる場合
						else if (c_player->GetPosi().x - g_stageGimmick->GetPosi().x > 0 && c_player->GetMove().x < 0)
						{
							PlayerOnWall = true;
							g_stageGimmick->SetPlayerHit(true);
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetBefPosi().y));
						}
					}
					if (fabs(c_player->GetMove().x) < fabs(c_player->GetMove().y))
					{
						//	足場より下にいる場合
						if (c_player->GetPosi().y - g_stageGimmick->GetPosi().y > 0)
						{
							g_stageGimmick->SetPlayerHit(true);
							c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
						}
						//	足場より上にいる場合
						else if (c_player->GetPosi().y - g_stageGimmick->GetPosi().y < 0)
						{
							PlayerOnGround = true;
							g_stageGimmick->SetPlayerHit(true);
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - c_player->GetSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
						}
					}
				}
			}
		}

		c_player->SetOnWall(PlayerOnWall);
		c_player->SetOnGround(PlayerOnGround);
	}

	//=========================================================================
	//	エネミーとの当たり判定
	for (ENEMY* g_enemy = c_enemy; g_enemy < c_enemy + ENEMY_MAX; g_enemy++)
	{
		EnemyOnGround = g_enemy->GetOnGround();
		EnemyOnWall = g_enemy->GetOnWall();
		if (g_enemy->GetUse() && g_enemy->GetCollisionBool())
		{
			if (g_enemy->GetEnemyTyep() == ENEMY::Bound)
			{
				switch (CheckTouchStageGimmick(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi()
					+ g_enemy->GetCollisionPos(), g_enemy->GetCollisionSize()))
				{
				case	Up:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, -fabs(g_enemy->GetMove().y)));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Up);
					break;
				case	Down:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, fabs(g_enemy->GetMove().y)));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Down);
					break;
				case	Right:	g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Right);
					break;
				case	Left:	g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Left);
					break;
				default:
					break;
				}
			}
			else if (g_enemy->GetEnemyTyep() == ENEMY::Spring)	//	バネエネミーの処理
			{
				switch (CheckTouchStageGimmick(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi()
					+ g_enemy->GetCollisionPos(), g_enemy->GetCollisionSize()))
				{
				case	Up:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, -g_enemy->GetRSpeed()));
					g_enemy->SetAnimation(true);	g_enemy->PlaySpringSE();
					break;
				case	Down:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
					break;
				case	Right:	g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					break;
				case	Left:	g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					break;
				default:
					break;
				}
			}
			else if (g_enemy->GetEnemyTyep() != ENEMY::Sticky)
			{
				EnemyOnGround = false;
				EnemyOnWall = false;

				for (STAGEGIMMICK* g_stageGimmick = c_stageGimmick; g_stageGimmick < c_stageGimmick + STAGEGIMMICK_MAX; g_stageGimmick++)
				{
					if (g_stageGimmick->GetUse() && g_stageGimmick->GetCollisionBool())
					{
						//	バネエネミーの瞬間の当たり判定処理
						//	足場の上コリジョンとの当たり判定
						if (GetCollisionUp(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
						{
							EnemyOnGround = true;
							g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - g_enemy->GetSize().y / 2));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetBefPosi().x, g_enemy->GetPosi().y - g_enemy->GetSize().y / 3));
						}
						//	足場の下コリジョンとの当たり判定
						if (GetCollisionDown(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
						{
							g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
							g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + g_enemy->GetCollisionSize().y / 2));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y + g_enemy->GetSize().y / 3));
						}
						//	足場の右コリジョンとの当たり判定
						if (GetCollisionRight(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
						{
							EnemyOnWall = true;
							g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
							g_enemy->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
						}
						//	足場の左コリジョンとの当たり判定
						if (GetCollisionLeft(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()))
						{
							EnemyOnWall = true;
							g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
							g_enemy->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
						}

						//	足場の全体コリジョンによる誤作動修正
						if (GetCollision(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_stageGimmick->GetPosi() + g_stageGimmick->GetCollisionPos(), g_stageGimmick->GetCollisionSize()) && !EnemyOnGround && !EnemyOnWall)
						{
							if (fabs(g_enemy->GetMove().x) > fabs(g_enemy->GetMove().y))
							{
								//	足場より左にいる場合
								if (g_enemy->GetPosi().x - g_stageGimmick->GetPosi().x < 0 && g_enemy->GetMove().x > 0)
								{
									EnemyOnWall = true;
									g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
									g_enemy->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x - g_stageGimmick->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
								}
								//	足場より右にいる場合
								else if (g_enemy->GetPosi().x - g_stageGimmick->GetPosi().x > 0 && g_enemy->GetMove().x < 0)
								{
									EnemyOnWall = true;
									g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
									g_enemy->SetPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_stageGimmick->GetPosi().x + g_stageGimmick->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
								}
							}
							if (fabs(g_enemy->GetMove().x) < fabs(g_enemy->GetMove().y))
							{
								//	足場より下にいる場合
								if (g_enemy->GetPosi().y - g_stageGimmick->GetPosi().y > 0)
								{
									g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
									g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_stageGimmick->GetPosi().y + g_stageGimmick->GetSize().y / 2 + g_enemy->GetCollisionSize().y / 2));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y + g_enemy->GetSize().y / 3));
								}
								//	足場より上にいる場合
								else if (g_enemy->GetPosi().y - g_stageGimmick->GetPosi().y < 0)
								{
									EnemyOnGround = true;
									g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_stageGimmick->GetPosi().y - g_stageGimmick->GetSize().y / 2 - g_enemy->GetSize().y / 2));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y - g_enemy->GetSize().y / 3));
								}
							}
						}
					}
				}
			}

			g_enemy->SetOnWall(EnemyOnWall);
			g_enemy->SetOnGround(EnemyOnGround);
		}

	}
}

//OneWayBlock
void	Collision_OneWayBlock()	//	PLAYER, ENEMY, BALL
{

}

//BUTTON
void	Collision_Button()	//	PLAYER, BALL
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		//PLAYER
		if (c_player->GetUse() && c_player->GetCollisionBool())
		{
			bool	OnGround = c_player->GetOnGround();
			bool	OnWall = c_player->GetOnWall();

			//プレーヤー
			if (c_button[i].GetUse() && c_button[i].GetCollisionBool())
			{
				//	足場の上コリジョンとの当たり判定
				if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
				{
					OnGround = true;
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_button[i].GetPosi().y - c_button[i].GetSize().y / 2 - c_player->GetSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
				}
				//	足場の下コリジョンとの当たり判定
				if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
				{
					c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
					c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_button[i].GetPosi().y + c_button[i].GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
					c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
				}
				//	足場の右コリジョンとの当たり判定
				if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
				{
					OnWall = true;
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
				}
				//	足場の左コリジョンとの当たり判定
				if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
				{
					OnWall = true;
					c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
					c_player->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetPosi().y));
					c_player->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
				}

				//	足場の全体コリジョンによる誤作動修正
				if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
					c_player->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()) && !OnGround && !OnWall)
				{
					if (fabs(c_player->GetMove().x) > fabs(c_player->GetMove().y))
					{
						//	足場より左にいる場合
						if (c_player->GetPosi().x - c_button[i].GetPosi().x < 0 && c_player->GetMove().x > 0)
						{
							OnWall = true;
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
						}
						//	足場より右にいる場合
						else if (c_player->GetPosi().x - c_button[i].GetPosi().x > 0 && c_player->GetMove().x < 0)
						{
							OnWall = true;
							c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
							c_player->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetPosi().y));
							c_player->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
						}
					}
					if (fabs(c_player->GetMove().x) < fabs(c_player->GetMove().y))
					{
						//	足場より下にいる場合
						if (c_player->GetPosi().y - c_button[i].GetPosi().y > 0)
						{
							c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_button[i].GetPosi().y + c_button[i].GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
						}
						//	足場より上にいる場合
						else if (c_player->GetPosi().y - c_button[i].GetPosi().y < 0)
						{
							OnGround = true;
							c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, c_button[i].GetPosi().y - c_button[i].GetSize().y / 2 - c_player->GetSize().y / 2));
							c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
						}
					}
				}
			}
			c_player->SetOnGround(OnGround);
			c_player->SetOnWall(OnWall);
		}

		//BALL
		if (c_ball->GetUse() && c_ball->GetCollisionBool())
		{
			bool	OnGround = c_ball->GetOnGround();
			bool	OnWall = c_ball->GetOnWall();
			bool	SEBool = c_ball->GetUsedSEBool();

			INTERLOCKARRANGEMENT* g_inter = GetInterlockArrangement();

			if (c_button[i].GetUse() && c_button[i].GetCollisionBool())
			{
				if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
					c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
				{
					c_button[i].SetCollisionBool(false);
					c_button[i].SetOn_OffSwitch(!(c_button[i].GetOn_OffSwitch()));
					g_inter[i].SetOn_Off_InterlockArrangement(c_button[i].GetOn_OffSwitch());	//対応する扉を作動させる
				}

				if (c_ball->GetAbilityMoveBall() != BALL::HOMING)
				{
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
					{
						OnGround = true;
						SEBool = true;
						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_button[i].GetPosi().y - c_button[i].GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
						c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
					{
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));
						c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_button[i].GetPosi().y + c_button[i].GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
					{
						OnWall = true;
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
						c_ball->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x + c_button[i].GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
					{
						OnWall = true;
						SEBool = true;
						c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
						c_ball->SetPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetPosi().y));
						c_ball->SetBefPosi(D3DXVECTOR2(c_button[i].GetPosi().x - c_button[i].GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
						c_ball->GetCollisionSize(), c_button[i].GetPosi() + c_button[i].GetCollisionPos(), c_button[i].GetCollisionSize()))
					{
						if (fabs(c_ball->GetMove().x) > fabs(c_ball->GetMove().y))
						{
							//	足場より左にいる場合
							//if (c_ball->GetPosi().x - g_ground->GetPosi().x < 0 && c_ball->GetMove().x > 0)
							//{
							//	OnWall = true;
							//	c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));
							//	c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetPosi().y));
							//	c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
							//}
							////	足場より右にいる場合
							//else if (c_ball->GetPosi().x - g_ground->GetPosi().x > 0 && c_ball->GetMove().x < 0)
							//{
							//	OnWall = true;
							//	c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));
							//	c_ball->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetPosi().y));
							//	c_ball->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + c_ball->GetSize().x / 2, c_ball->GetBefPosi().y));
							//}
						}
						if (fabs(c_ball->GetMove().x) < fabs(c_ball->GetMove().y))
						{
							//	足場より下にいる場合
							//if (c_ball->GetPosi().y - c_button[i].GetPosi().y > 0)
							//{
							//	if (c_ball->GetAbilityMoveBall() != BALL::HOMING)
							//	{
							//		c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));
							//		c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_button[i].GetPosi().y + c_button[i].GetSize().y / 2 + c_ball->GetCollisionSize().y / 2));
							//	}

							//	c_button[i].SetCollisionBool(false);
							//	c_button[i].SetOn_OffSwitch(!(c_button[i].GetOn_OffSwitch()));
							//	g_inter[i].SetOn_Off_InterlockArrangement(c_button[i].GetOn_OffSwitch());	//対応する扉を作動させる
							//}
							////	足場より上にいる場合
							//else if (c_ball->GetPosi().y - c_button[i].GetPosi().y < 0)
							//{
							//	if (c_ball->GetAbilityMoveBall() != BALL::HOMING)
							//	{
							//		OnGround = true;
							//		c_ball->SetPosi(D3DXVECTOR2(c_ball->GetPosi().x, c_button[i].GetPosi().y - c_button[i].GetSize().y / 2 - c_ball->GetCollisionSize().y / 2));
							//		c_ball->SetBefPosi(D3DXVECTOR2(c_ball->GetBefPosi().x, c_ball->GetPosi().y - c_ball->GetSize().y / 3));
							//	}

							//	c_button[i].SetCollisionBool(false);
							//	c_button[i].SetOn_OffSwitch(!(c_button[i].GetOn_OffSwitch()));
							//	g_inter[i].SetOn_Off_InterlockArrangement(c_button[i].GetOn_OffSwitch());	//対応する扉を作動させる
							//}
						}
					}
				}
			}

			//=================================================================================================
			//	ボールSE処理
			c_ball->PlayBallSE(SEBool);
			//=================================================================================================

			c_ball->SetOnGround(OnGround);
			c_ball->SetOnWall(OnWall);
		}

	}
}

//DOOR
void	Collision_InterlockArrangement()	//	PLAYER
{
	for (INTERLOCKARRANGEMENT* g_inter = c_inter; g_inter < c_inter + BUTTON_MAX; g_inter++)
	{
		//PLAYER
		{
			bool	OnGround = c_player->GetOnGround();
			bool	OnWall = c_player->GetOnWall();


			bool onoff = g_inter->GetOn_Off_InterlockArrangement();
			if (!onoff)
			{
				if (g_inter->GetUse() && c_player->GetUse() && g_inter->GetCollisionBool() && c_player->GetCollisionBool())
				{
					//	足場の上コリジョンとの当たり判定
					if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnGround = true;
						c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_inter->GetPosi().y - g_inter->GetSize().y / 2 - c_player->GetSize().y / 2));
						c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
					}
					//	足場の下コリジョンとの当たり判定
					if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
						c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_inter->GetPosi().y + g_inter->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
						c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
					}
					//	足場の右コリジョンとの当たり判定
					if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnWall = true;
						c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
						c_player->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
						c_player->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
					}
					//	足場の左コリジョンとの当たり判定
					if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()))
					{
						OnWall = true;
						c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
						c_player->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
						c_player->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
					}

					//	足場の全体コリジョンによる誤作動修正
					if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
						c_player->GetCollisionSize(), g_inter->GetPosi() + g_inter->GetCollisionPos(), g_inter->GetCollisionSize()) && !OnGround && !OnWall)
					{
						if (fabs(c_player->GetMove().x) > fabs(c_player->GetMove().y))
						{
							//	足場より左にいる場合
							if (c_player->GetPosi().x - g_inter->GetPosi().x < 0 && c_player->GetMove().x > 0)
							{
								OnWall = true;
								c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
								c_player->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetPosi().y));
								c_player->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x - g_inter->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
							}
							//	足場より右にいる場合
							else if (c_player->GetPosi().x - g_inter->GetPosi().x > 0 && c_player->GetMove().x < 0)
							{
								OnWall = true;
								c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
								c_player->SetPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetPosi().y));
								c_player->SetBefPosi(D3DXVECTOR2(g_inter->GetPosi().x + g_inter->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
							}
						}
						if (fabs(c_player->GetMove().x) < fabs(c_player->GetMove().y))
						{
							//	足場より下にいる場合
							if (c_player->GetPosi().y - g_inter->GetPosi().y > 0)
							{
								c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
								c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_inter->GetPosi().y + g_inter->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
								c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
							}
							//	足場より上にいる場合
							else if (c_player->GetPosi().y - g_inter->GetPosi().y < 0)
							{
								OnGround = true;
								c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_inter->GetPosi().y - g_inter->GetSize().y / 2 - c_player->GetSize().y / 2));
								c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
							}
						}
					}
				}
			}
			c_player->SetOnGround(OnGround);
			c_player->SetOnWall(OnWall);
		}
	}
}

//SPRING
void	Collision_Spring()	//	PLAYER
{
	bool	OnWall = false;
	for (SPRING* g_spring = c_spring; g_spring < c_spring + SPRING_MAX; g_spring++)
	{
		if (g_spring->GetUse() && c_player->GetUse() && g_spring->GetCollisionBool() && c_player->GetCollisionBool())
		{
			//	足場の上コリジョンとの当たり判定
			if (GetCollisionUp(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), g_spring->GetPosi() + g_spring->GetCollisionPos(), g_spring->GetCollisionSize()))
			{
				c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_spring->GetPosi().y - g_spring->GetSize().y / 2 - c_player->GetSize().y / 2));
				c_player->SetBefPosi(D3DXVECTOR2(c_player->GetBefPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));


				if (!g_spring->GetOnSpring())
				{
					g_spring->SetOnSpring(true);
					c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, -15.0f));
				}
			}
			//	足場の下コリジョンとの当たり判定
			if (GetCollisionDown(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), g_spring->GetPosi() + g_spring->GetCollisionPos(), g_spring->GetCollisionSize()))
			{
				c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_spring->GetPosi().y + g_spring->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
				c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
			
				if (!g_spring->GetOnSpring())
				{
					g_spring->SetOnSpring(true);
					c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 5.0f));
				}
			}
			//	足場の右コリジョンとの当たり判定
			if (GetCollisionRight(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), g_spring->GetPosi() + g_spring->GetCollisionPos(), g_spring->GetCollisionSize()))
			{
				OnWall = true;
				c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
				c_player->SetPosi(D3DXVECTOR2(g_spring->GetPosi().x + g_spring->GetSize().x / 2 + c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
				c_player->SetBefPosi(D3DXVECTOR2(g_spring->GetPosi().x + g_spring->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
			}
			//	足場の左コリジョンとの当たり判定
			if (GetCollisionLeft(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), g_spring->GetPosi() + g_spring->GetCollisionPos(), g_spring->GetCollisionSize()))
			{
				OnWall = true;
				c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
				c_player->SetPosi(D3DXVECTOR2(g_spring->GetPosi().x - g_spring->GetSize().x / 2 - c_player->GetCollisionSize().x / 2, c_player->GetPosi().y));
				c_player->SetBefPosi(D3DXVECTOR2(g_spring->GetPosi().x - g_spring->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
			}

			//	足場の全体コリジョンによる誤作動修正
			//if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
			//	c_player->GetCollisionSize(), g_spring->GetPosi() + g_spring->GetCollisionPos(), g_spring->GetCollisionSize()) && !OnGround && !OnWall)
			//{
			//	if (fabs(c_player->GetMove().x) > fabs(c_player->GetMove().y))
			//	{
			//		//	足場より左にいる場合
			//		if (c_player->GetPosi().x - g_spring->GetPosi().x < 0 && c_player->GetMove().x > 0)
			//		{
			//			OnWall = true;
			//			c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
			//			c_player->SetPosi(D3DXVECTOR2(g_spring->GetPosi().x - g_spring->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetPosi().y));
			//			c_player->SetBefPosi(D3DXVECTOR2(g_spring->GetPosi().x - g_spring->GetSize().x / 2 - c_player->GetSize().x / 2, c_player->GetBefPosi().y));
			//		}
			//		//	足場より右にいる場合
			//		else if (c_player->GetPosi().x - g_spring->GetPosi().x > 0 && c_player->GetMove().x < 0)
			//		{
			//			OnWall = true;
			//			c_player->SetMove(D3DXVECTOR2(0, c_player->GetMove().y));
			//			c_player->SetPosi(D3DXVECTOR2(g_spring->GetPosi().x + g_spring->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetPosi().y));
			//			c_player->SetBefPosi(D3DXVECTOR2(g_spring->GetPosi().x + g_spring->GetSize().x / 2 + c_player->GetSize().x / 2, c_player->GetBefPosi().y));
			//		}
			//	}
			//	if (fabs(c_player->GetMove().x) < fabs(c_player->GetMove().y))
			//	{
			//		//	足場より下にいる場合
			//		if (c_player->GetPosi().y - g_spring->GetPosi().y > 0)
			//		{
			//			c_player->SetMove(D3DXVECTOR2(c_player->GetMove().x, 0));
			//			c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_spring->GetPosi().y + g_spring->GetSize().y / 2 + c_player->GetCollisionSize().y / 2));
			//			c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y + c_player->GetSize().y / 3));
			//		}
			//		//	足場より上にいる場合
			//		else if (c_player->GetPosi().y - g_spring->GetPosi().y < 0)
			//		{
			//			OnGround = true;
			//			c_player->SetPosi(D3DXVECTOR2(c_player->GetPosi().x, g_spring->GetPosi().y - g_spring->GetSize().y / 2 - c_player->GetSize().y / 2));
			//			c_player->SetBefPosi(D3DXVECTOR2(c_player->GetPosi().x, c_player->GetPosi().y - c_player->GetSize().y / 3));
			//		}
			//	}
			//}
		}
	}
}

//ENEMY
void	Collision_Enemy_VS_Ground()	//	エネミーvsグラウンドの当たり判定チェッカー
{
	bool	OnGround;
	bool	OnWall;	
	for (ENEMY* g_enemy = c_enemy; g_enemy < c_enemy + ENEMY_MAX; g_enemy++)
	{
		if (g_enemy->GetUse() && g_enemy->GetCollisionBool())
		{
			if (g_enemy->GetEnemyTyep() == ENEMY::Bound)	//	バネエネミーの処理
			{
				switch (CheckTouchGround(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi()
					+ g_enemy->GetCollisionPos(), g_enemy->GetCollisionSize()))
				{
				case	Up:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, -fabs(g_enemy->GetMove().y)));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Up);
					break;
				case	Down:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, fabs(g_enemy->GetMove().y)));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Down);
					break;
				case	Right:	g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Right);
					break;
				case	Left:	g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					g_enemy->SetBoundCount(g_enemy->GetBoundCount() + 1);
					g_enemy->SetBoundStand(Left);
					break;
				default:
					break;
				}
			}
			else if (g_enemy->GetEnemyTyep() == ENEMY::Spring)	//	バネエネミーの処理
			{
				switch (CheckTouchGround(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi()
					+ g_enemy->GetCollisionPos(), g_enemy->GetCollisionSize()))
				{
				case	Up:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, -g_enemy->GetRSpeed()));
					g_enemy->SetAnimation(true);	g_enemy->PlaySpringSE();
					break;
				case	Down:	g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
					break;
				case	Right:	g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					break;
				case	Left:	g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
					break;
				default:
					break;
				}
			}
			else if (g_enemy->GetEnemyTyep() != ENEMY::Sticky)
			{
				OnGround = false;
				OnWall = false;
				for (GROUND* g_ground = c_ground; g_ground < c_ground + GROUND_MAX; g_ground++)
				{
					if (g_ground->GetUse() && g_ground->GetCollisionBool())
					{
						//	バネエネミーの瞬間の当たり判定処理
						//	足場の上コリジョンとの当たり判定
						if (GetCollisionUp(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
						{
							OnGround = true;
							g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - g_enemy->GetSize().y / 2));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetBefPosi().x, g_enemy->GetPosi().y - g_enemy->GetSize().y / 3));
						}
						//	足場の下コリジョンとの当たり判定
						if (GetCollisionDown(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
						{
							g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
							g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + g_enemy->GetCollisionSize().y / 2));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y + g_enemy->GetSize().y / 3));
						}
						//	足場の右コリジョンとの当たり判定
						if (GetCollisionRight(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
						{
							OnWall = true;
							g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
							g_enemy->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
						}
						//	足場の左コリジョンとの当たり判定
						if (GetCollisionLeft(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
						{
							OnWall = true;
							g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
							g_enemy->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
							g_enemy->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
						}

						//	足場の全体コリジョンによる誤作動修正
						if (GetCollision(g_enemy->GetPosi() + g_enemy->GetCollisionPos(), g_enemy->GetBefPosi() + g_enemy->GetCollisionPos(),
							g_enemy->GetCollisionSize(), g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()) && !OnGround && !OnWall)
						{
							if (fabs(g_enemy->GetMove().x) > fabs(g_enemy->GetMove().y))
							{
								//	足場より左にいる場合
								if (g_enemy->GetPosi().x - g_ground->GetPosi().x < 0 && g_enemy->GetMove().x > 0)
								{
									OnWall = true;
									g_enemy->SetMove(D3DXVECTOR2(-fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
									g_enemy->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x - g_ground->GetSize().x / 2 - g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
								}
								//	足場より右にいる場合
								else if (g_enemy->GetPosi().x - g_ground->GetPosi().x > 0 && g_enemy->GetMove().x < 0)
								{
									OnWall = true;
									g_enemy->SetMove(D3DXVECTOR2(fabs(g_enemy->GetMove().x), g_enemy->GetMove().y));
									g_enemy->SetPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetPosi().y));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_ground->GetPosi().x + g_ground->GetSize().x / 2 + g_enemy->GetSize().x / 2, g_enemy->GetBefPosi().y));
								}
							}
							if (fabs(g_enemy->GetMove().x) < fabs(g_enemy->GetMove().y))
							{
								//	足場より下にいる場合
								if (g_enemy->GetPosi().y - g_ground->GetPosi().y > 0)
								{
									g_enemy->SetMove(D3DXVECTOR2(g_enemy->GetMove().x, 0));
									g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_ground->GetPosi().y + g_ground->GetSize().y / 2 + g_enemy->GetCollisionSize().y / 2));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y + g_enemy->GetSize().y / 3));
								}
								//	足場より上にいる場合
								else if (g_enemy->GetPosi().y - g_ground->GetPosi().y < 0)
								{
									OnGround = true;
									g_enemy->SetPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_ground->GetPosi().y - g_ground->GetSize().y / 2 - g_enemy->GetSize().y / 2));
									g_enemy->SetBefPosi(D3DXVECTOR2(g_enemy->GetPosi().x, g_enemy->GetPosi().y - g_enemy->GetSize().y / 3));
								}
							}
						}
					}
				}

				g_enemy->SetOnWall(OnWall);
				g_enemy->SetOnGround(OnGround);
			}
		}
	}
}
void	Collision_Enemy_VS_Ball()	//	エネミーvsボールの当たり判定チェッカー
{
	if (c_ball->GetUse() && c_ball->GetCollisionBool())
	{
		bool	GetAbilityBool = false;
		int	TouchNum = -1;

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (c_enemy[i].GetUse() && c_enemy[i].GetCollisionBool())
			{
				if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
					c_ball->GetCollisionSize(), c_enemy[i].GetPosi() + c_enemy[i].GetCollisionPos(), c_enemy[i].GetCollisionSize()))
				{
					TouchNum = i;
				}
			}
		}

		if (TouchNum >= 0)
		{
			if (c_ball->GetSituation() == BALL::Throwing || c_ball->GetSituation() == BALL::Free)
			{
				//=======================================================================================================
			//	軌道系能力の処理
				if (c_ball->GetAbilityMoveBall() == BALL::NONE_BALL)
				{
					//===================================================================================================
					//	軌道系能力の取得
					switch (c_enemy[TouchNum].GetEnemyTyep())
					{
					case	ENEMY::Bound:	c_ball->SetAbilityMoveBall(BALL::BOUNCE);
						GetAbilityBool = true; break;
					case	ENEMY::Homing:	c_ball->SetAbilityMoveBall(BALL::HOMING);
						GetAbilityBool = true; break;
					}
				}
				//=======================================================================================================
				//	移動系能力の取得
				if (c_ball->GetAbilityMovePlayer() == BALL::NONE_PLAYER)
				{
					switch (c_enemy[TouchNum].GetEnemyTyep())
					{
					case	ENEMY::Trace:	c_ball->SetAbilityMovePlayer(BALL::TRACE);
						GetAbilityBool = true; break;
					case	ENEMY::Spring:	c_ball->SetAbilityMovePlayer(BALL::SPRING);
						GetAbilityBool = true; break;
					}
				}

				//=======================================================================================================
				//	攻撃系能力の処理
				if (c_ball->GetAbilityAttack() == BALL::NONE_ATTACK)
				{
					//===================================================================================================
					//	攻撃系能力の取得
					switch (c_enemy[TouchNum].GetEnemyTyep())
					{
					case	ENEMY::Explosion:	c_ball->SetAbilityAttack(BALL::EXPLOSION);
						GetAbilityBool = true; break;
					case	ENEMY::Sticky:	c_ball->SetAbilityAttack(BALL::STICKY);
						GetAbilityBool = true; break;
					}
				}
				
				if (!GetAbilityBool)
				{
					//===================================================================================================
					//	敵に対する攻撃系能力の発動
					switch (c_ball->GetAbilityAttack())
					{
					case	BALL::EXPLOSION:
						SetExplosion(c_ball->GetPosi(), D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE * 5), EXPLOSION::PLAYER);	break;
					case	BALL::STICKY:	SetStickyBomb(c_enemy[TouchNum].GetPosi(), &c_enemy[TouchNum], 0.0f);
					}
				}

				//	追従能力
				if (c_ball->GetAbilityMovePlayer() == BALL::TRACE && c_ball->GetAbilityMoveBall() == BALL::HOMING)
					c_player->SetTracePos(c_enemy[TouchNum].GetPosi() + D3DXVECTOR2(0, c_player->GetSize().y / 2));

				//=======================================================================================================
				if (GetAbilityBool)
				{
					//===============================================================
					//	能力を取得、敵を吸収、ボールを強制帰還
					if (c_ball->GetAbilityMoveBall() != BALL::HOMING)
						c_ball->SetSituation(BALL::Return);

					c_ball->SetUse(false);
					SetStopBool(true);

					if (c_player->GetWayX() == 1)	SetEffects(c_enemy[TouchNum].GetPosi(), c_ball->GetSize(), EFFECT::ABSORB_R, &(c_enemy[TouchNum]));
					else if (c_player->GetWayX() == -1)	SetEffects(c_enemy[TouchNum].GetPosi(), c_ball->GetSize(), EFFECT::ABSORB_L, &(c_enemy[TouchNum]));

					return;
				}
				else
				{
					if (c_ball->GetAbilityAttack() != BALL::EXPLOSION)
					{
						if (c_enemy[TouchNum].GetUse() && c_enemy[TouchNum].GetCollisionBool())
						{
							bool	SEBool = c_ball->GetUsedSEBool();

							//================================================================================================================
							//	敵の上コリジョンとの当たり判定
							if (GetCollisionUp(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
								c_ball->GetCollisionSize(), c_enemy[TouchNum].GetPosi() + c_enemy[TouchNum].GetCollisionPos(), c_enemy[TouchNum].GetCollisionSize()))
							{
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, -fabs(c_ball->GetMove().y)));

								if (c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Bound ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Explosion ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Spring)
								{
									c_enemy[TouchNum].SetMove(D3DXVECTOR2(c_enemy[TouchNum].GetMove().x, fabs(c_enemy[TouchNum].GetMove().y)));
								}
								else if (c_enemy[TouchNum].GetEnemyTyep() != ENEMY::Homing)
								{
									c_enemy[TouchNum].SetPoint(D3DXVECTOR2(c_enemy[TouchNum].GetPoint().x, c_enemy[TouchNum].GetPosi().y + fabs(c_enemy[TouchNum].GetPoint().y - c_enemy[TouchNum].GetPosi().y)));
								}
							}
							//================================================================================================================
							//	敵の下コリジョンとの当たり判定
							if (GetCollisionDown(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
								c_ball->GetCollisionSize(), c_enemy[TouchNum].GetPosi() + c_enemy[TouchNum].GetCollisionPos(), c_enemy[TouchNum].GetCollisionSize()))
							{
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(c_ball->GetMove().x, fabs(c_ball->GetMove().y)));

								if (c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Bound ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Explosion ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Spring)
								{
									c_enemy[TouchNum].SetMove(D3DXVECTOR2(c_enemy[TouchNum].GetMove().x, -fabs(c_enemy[TouchNum].GetMove().y)));
								}
								else if (c_enemy[TouchNum].GetEnemyTyep() != ENEMY::Homing)
								{
									c_enemy[TouchNum].SetPoint(D3DXVECTOR2(c_enemy[TouchNum].GetPoint().x, c_enemy[TouchNum].GetPosi().y - fabs(c_enemy[TouchNum].GetPoint().y - c_enemy[TouchNum].GetPosi().y)));
								}
							}
							//================================================================================================================
							//	敵の右コリジョンとの当たり判定
							if (GetCollisionRight(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
								c_ball->GetCollisionSize(), c_enemy[TouchNum].GetPosi() + c_enemy[TouchNum].GetCollisionPos(), c_enemy[TouchNum].GetCollisionSize()))
							{
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(fabs(c_ball->GetMove().x), c_ball->GetMove().y));

								if (c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Bound ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Explosion ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Spring)
								{
									c_enemy[TouchNum].SetMove(D3DXVECTOR2(-fabs(c_enemy[TouchNum].GetMove().x), c_enemy[TouchNum].GetMove().y));
								}
								else if (c_enemy[TouchNum].GetEnemyTyep() != ENEMY::Homing)
								{
									c_enemy[TouchNum].SetPoint(D3DXVECTOR2(c_enemy[TouchNum].GetPosi().x - fabs(c_enemy[TouchNum].GetPoint().x - c_enemy[TouchNum].GetPosi().x), c_enemy[TouchNum].GetPoint().y));
								}
							}
							//================================================================================================================
							//	敵の左コリジョンとの当たり判定
							if (GetCollisionLeft(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
								c_ball->GetCollisionSize(), c_enemy[TouchNum].GetPosi() + c_enemy[TouchNum].GetCollisionPos(), c_enemy[TouchNum].GetCollisionSize()))
							{
								SEBool = true;
								c_ball->SetMove(D3DXVECTOR2(-fabs(c_ball->GetMove().x), c_ball->GetMove().y));

								if (c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Bound ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Explosion ||
									c_enemy[TouchNum].GetEnemyTyep() == ENEMY::Spring)
								{
									c_enemy[TouchNum].SetMove(D3DXVECTOR2(fabs(c_enemy[TouchNum].GetMove().x), c_enemy[TouchNum].GetMove().y));
								}
								else if (c_enemy[TouchNum].GetEnemyTyep() != ENEMY::Homing)
								{
									c_enemy[TouchNum].SetPoint(D3DXVECTOR2(c_enemy[TouchNum].GetPosi().x + fabs(c_enemy[TouchNum].GetPoint().x - c_enemy[TouchNum].GetPosi().x), c_enemy[TouchNum].GetPoint().y));
								}
							}

							//=================================================================================================
							//	ボールSE処理
							c_ball->PlayBallSE(SEBool);
							//=================================================================================================
						}
					}
				}
			}
		}
	}
}
void	Collision_Enemy_VS_Player()	//	プレイヤーvsエネミーの当たり判定チェッカー
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (c_enemy[i].GetUse() && c_enemy[i].GetCollisionBool())
		{
			if (GetCollision(c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetBefPosi() + c_player->GetCollisionPos(),
				c_player->GetCollisionSize(), c_enemy[i].GetPosi() + c_enemy[i].GetCollisionPos(), c_enemy[i].GetCollisionSize()))
			{
				c_player->SetUse(false);
			}
		}
	}
}

void	Collision_EnemyKnife()	//	PLAYER, GROUND, BALL
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		if (c_knife[i].GetUse() && c_knife[i].GetCollisionBool())
		{
			//PLAYER
			{
				if (c_player->GetUse() && c_player->GetCollisionBool())
				{
					if (GetCollision(c_knife[i].GetPosi() + c_knife[i].GetCollisionPos(), c_knife[i].GetBefPosi() + c_knife[i].GetCollisionPos(),
						c_knife[i].GetCollisionSize(), c_player->GetPosi() + c_player->GetCollisionPos(), c_player->GetCollisionSize()))
					{
						c_player->SetUse(false);
					}
				}
			}

			//GROUND
			{
				for (int j = 0; j < GROUND_MAX; j++)
				{
					if (c_ground[j].GetUse() && c_ground[j].GetCollisionBool())
					{
						if (GetCollision(c_knife[i].GetPosi() + c_knife[i].GetCollisionPos(), c_knife[i].GetBefPosi() + c_knife[i].GetCollisionPos(),
							c_knife[i].GetCollisionSize(), c_ground[j].GetPosi() + c_ground[j].GetCollisionPos(), c_ground[j].GetCollisionSize()))
						{
							c_knife[i].SetUse(false);
						}
					}
				}
			}

			//BALL
			{
				if (c_ball->GetUse() && c_ball->GetCollisionBool())
				{
					if (GetCollision(c_knife[i].GetPosi() + c_knife[i].GetCollisionPos(), c_knife[i].GetBefPosi() + c_knife[i].GetCollisionPos(),
						c_knife[i].GetCollisionSize(), c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetCollisionSize()))
					{
						c_knife[i].SetUse(false);
					}
				}
			}

			//StageGimmick
			{
				for (int j = 0; j < STAGEGIMMICK_MAX; j++)
				{
					if (c_stageGimmick[j].GetUse() && c_stageGimmick[j].GetCollisionBool())
					{
						if (GetCollision(c_knife[i].GetPosi() + c_knife[i].GetCollisionPos(), c_knife[i].GetBefPosi() + c_knife[i].GetCollisionPos(),
							c_knife[i].GetCollisionSize(), c_stageGimmick[j].GetPosi() + c_stageGimmick[j].GetCollisionPos(), c_stageGimmick[j].GetCollisionSize()))
						{
							c_knife[i].SetUse(false);
						}
					}
				}
			}
		}
	}
}

void	Collision_EnemyBullet()	//	GROUND, BALL
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (c_bullet[i].GetUse() && c_bullet[i].GetCollisionBool())
		{
			//GROUND
			{
				if (CheckTouchGround(c_bullet[i].GetPosi() + c_bullet[i].GetCollisionPos(), c_bullet[i].GetBefPosi() + c_bullet[i].GetCollisionPos(),
					c_bullet[i].GetCollisionSize()) != None)
				{
					c_bullet[i].SetUse(false);
					c_bullet[i].SetTime(0);
					SetExplosion(c_bullet[i].GetPosi(), D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2), EXPLOSION::ENEMY);
				}
			}

			//BALL
			if (c_ball->GetUse() && c_ball->GetCollisionBool())
			{
				if (GetCollision(c_ball->GetPosi() + c_ball->GetCollisionPos(), c_ball->GetBefPosi() + c_ball->GetCollisionPos(),
					c_ball->GetCollisionSize(), c_bullet[i].GetPosi() + c_bullet[i].GetCollisionPos(), c_bullet[i].GetCollisionSize()))
				{
					c_bullet[i].SetUse(false);
					SetExplosion(c_bullet[i].GetPosi(), D3DXVECTOR2(BASE_SIZE, BASE_SIZE), EXPLOSION::NONE);
					break;
				}
			}

			//STAGEGIMMICK
			{
				if (CheckTouchStageGimmick(c_bullet[i].GetPosi() + c_bullet[i].GetCollisionPos(), c_bullet[i].GetBefPosi() + c_bullet[i].GetCollisionPos(),
					c_bullet[i].GetCollisionSize()) != None)
				{
					c_bullet[i].SetUse(false);
					c_bullet[i].SetTime(0);
					SetExplosion(c_bullet[i].GetPosi(), D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2), EXPLOSION::ENEMY);
				}
			}

			//INTERLOCKARRAGEMENT
			{
				for (int j = 0; j < INTERLOCKARRANGEMENT_MAX; j++)
				{
					if (c_inter[j].GetUse() && c_inter[j].GetCollisionBool() && !c_inter[j].GetOn_Off_InterlockArrangement())
					{
						if (GetCollision(c_bullet[i].GetPosi() + c_bullet[i].GetCollisionPos(), c_bullet[i].GetBefPosi() + c_bullet[i].GetCollisionPos(),
							c_bullet[i].GetCollisionSize(), c_inter[j].GetPosi() + c_inter[j].GetCollisionPos(), c_inter[j].GetCollisionSize()))
						{
							c_bullet[i].SetUse(false);
							c_bullet[i].SetTime(0);
							SetExplosion(c_bullet[i].GetPosi(), D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2), EXPLOSION::ENEMY);
						
							break;
						}
					}
				}
			}
		}
	}
}

void	Collision_EnemySticky()	//	GROUND
{
	bool	onGround;
	for (int j = 0; j < ENEMY_STICKY_BOMB_MAX; j++)
	{
		if (c_enemy_sticky_bomb[j].GetUse() && c_enemy_sticky_bomb[j].GetCollisionBool())
		{
			onGround = false;
			for (int i = 0; i < GROUND_MAX; i++)
			{
				if (c_ground[i].GetUse() && c_ground[i].GetCollisionBool())
				{
					if (GetCollisionUp(c_enemy_sticky_bomb[j].GetPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(),
						c_enemy_sticky_bomb[j].GetBefPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(), c_enemy_sticky_bomb[j].GetCollisionSize(),
						c_ground[i].GetPosi() + c_ground[i].GetCollisionPos(), c_ground[i].GetCollisionSize()))
					{
						onGround = true;
						c_enemy_sticky_bomb[j].SetPosi(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetPosi().x, c_ground[i].GetPosi().y
							- c_ground[i].GetSize().y / 2 - c_enemy_sticky_bomb[j].GetCollisionSize().y / 2));
						c_enemy_sticky_bomb[j].SetBefPosi(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetPosi().x,
							c_enemy_sticky_bomb[j].GetPosi().y - c_enemy_sticky_bomb[j].GetCollisionSize().y / 2));
						c_enemy_sticky_bomb[j].SetMove(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetMove().x, 0));
					}
					else if (GetCollision(c_enemy_sticky_bomb[j].GetPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(),
						c_enemy_sticky_bomb[j].GetBefPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(), c_enemy_sticky_bomb[j].GetCollisionSize(),
						c_ground[i].GetPosi() + c_ground[i].GetCollisionPos(), c_ground[i].GetCollisionSize()))
					{
						c_enemy_sticky_bomb[j].SetUse(false);
						SetExplosion(c_enemy_sticky_bomb[j].GetPosi(), D3DXVECTOR2(BASE_SIZE * 4, BASE_SIZE * 4), EXPLOSION::ENEMY);
					}
				}
			}

			for (int i = 0; i < STAGEGIMMICK_MAX; i++)
			{
				if (c_stageGimmick[i].GetUse() && c_stageGimmick[i].GetCollisionBool())
				{
					if (GetCollisionUp(c_enemy_sticky_bomb[j].GetPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(),
						c_enemy_sticky_bomb[j].GetBefPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(), c_enemy_sticky_bomb[j].GetCollisionSize(),
						c_stageGimmick[i].GetPosi() + c_stageGimmick[i].GetCollisionPos(), c_stageGimmick[i].GetCollisionSize()))
					{
						onGround = true;
						c_enemy_sticky_bomb[j].SetPosi(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetPosi().x, c_stageGimmick[i].GetPosi().y
							- c_stageGimmick[i].GetSize().y / 2 - c_enemy_sticky_bomb[j].GetCollisionSize().y / 2));
						c_enemy_sticky_bomb[j].SetBefPosi(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetPosi().x,
							c_enemy_sticky_bomb[j].GetPosi().y - c_enemy_sticky_bomb[j].GetCollisionSize().y / 2));
						c_enemy_sticky_bomb[j].SetMove(D3DXVECTOR2(c_enemy_sticky_bomb[j].GetMove().x, 0));
					}
					else if (GetCollision(c_enemy_sticky_bomb[j].GetPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(),
						c_enemy_sticky_bomb[j].GetBefPosi() + c_enemy_sticky_bomb[j].GetCollisionPos(), c_enemy_sticky_bomb[j].GetCollisionSize(),
						c_stageGimmick[i].GetPosi() + c_stageGimmick[i].GetCollisionPos(), c_stageGimmick[i].GetCollisionSize()))
					{
						c_enemy_sticky_bomb[j].SetUse(false);
						SetExplosion(c_enemy_sticky_bomb[j].GetPosi(), D3DXVECTOR2(BASE_SIZE * 4, BASE_SIZE * 4), EXPLOSION::ENEMY);
					}
				}
			}

			c_enemy_sticky_bomb[j].SetOnGround(onGround);
		}
	}


}


//======================================================================================================================
//	足場に触れているか判定処理
const	COLLISION_WAY&	CheckTouchGround(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1)
{
	COLLISION_WAY	way = None;
	for (GROUND* g_ground = c_ground; g_ground < c_ground + GROUND_MAX; g_ground++)
	{
		if (g_ground->GetUse() && g_ground->GetCollisionBool())
		{
			//	足場の上コリジョンとの当たり判定
			if (GetCollisionUp(col_pos1, col_befpos1, col_size1, g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
			{
				way = Up;
				break;
			}
			//	足場の下コリジョンとの当たり判定
			if (GetCollisionDown(col_pos1, col_befpos1, col_size1, g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
			{
				way = Down;
				break;
			}
			//	足場の右コリジョンとの当たり判定
			if (GetCollisionRight(col_pos1, col_befpos1, col_size1, g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
			{
				way = Right;
				break;
			}
			//	足場の左コリジョンとの当たり判定
			if (GetCollisionLeft(col_pos1, col_befpos1, col_size1, g_ground->GetPosi() + g_ground->GetCollisionPos(), g_ground->GetCollisionSize()))
			{
				way = Left;
				break;
			}
		}
	}

	/*if (way == None)
		return	way;
	else*/
	return	way;
}

//======================================================================================================================
//	足場に触れているか判定処理
const	COLLISION_WAY&	CheckTouchStageGimmick(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1)
{
	COLLISION_WAY	way = None;
	for (STAGEGIMMICK* g_StageGimmik = c_stageGimmick; g_StageGimmik < c_stageGimmick + STAGEGIMMICK_MAX; g_StageGimmik++)
	{
		if (g_StageGimmik->GetUse() && g_StageGimmik->GetCollisionBool())
		{
			//	足場の上コリジョンとの当たり判定
			if (GetCollisionUp(col_pos1, col_befpos1, col_size1, g_StageGimmik->GetPosi() + g_StageGimmik->GetCollisionPos(), g_StageGimmik->GetCollisionSize()))
			{
				way = Up;
				break;
			}
			//	足場の下コリジョンとの当たり判定
			if (GetCollisionDown(col_pos1, col_befpos1, col_size1, g_StageGimmik->GetPosi() + g_StageGimmik->GetCollisionPos(), g_StageGimmik->GetCollisionSize()))
			{
				way = Down;
				break;
			}
			//	足場の右コリジョンとの当たり判定
			if (GetCollisionRight(col_pos1, col_befpos1, col_size1, g_StageGimmik->GetPosi() + g_StageGimmik->GetCollisionPos(), g_StageGimmik->GetCollisionSize()))
			{
				way = Right;
				break;
			}
			//	足場の左コリジョンとの当たり判定
			if (GetCollisionLeft(col_pos1, col_befpos1, col_size1, g_StageGimmik->GetPosi() + g_StageGimmik->GetCollisionPos(), g_StageGimmik->GetCollisionSize()))
			{
				way = Left;
				break;
			}
		}
	}

	/*if (way == None)
		return	way;
	else*/
	return	way;
}


/*=====================================================================================================================
	引数：col_pos:コリジョンの中心座標		：col_size:コリジョンのサイズ		*/
bool	GetCollision(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2)	//	オブジェクト同士の当たり判定
{
	D3DXVECTOR2	rightdown1, leftup1;
	D3DXVECTOR2	rightdown2, leftup2;

	rightdown1 = col_pos1 + col_size1 / 2;
	leftup1 = col_pos1 - col_size1 / 2;

	rightdown2 = col_pos2 + col_size2 / 2;
	leftup2 = col_pos2 - col_size2 / 2;

	if (rightdown1.x < leftup2.x)	return	false;
	if (rightdown1.y < leftup2.y)	return	false;
	if (rightdown2.x < leftup1.x)	return	false;
	if (rightdown2.y < leftup1.y)	return	false;

	return	true;
}

bool	GetCollisionUp(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2)	//	オブジェクト上部との当たり判定：返り値、bool
{
	D3DXVECTOR2	rightup, leftup;

	rightup = D3DXVECTOR2(col_pos2.x + col_size2.x / 2, col_pos2.y - col_size2.y / 2);
	leftup = col_pos2 - col_size2 / 2;

	if (rightup.x >= col_pos1.x - col_size1.x / 2 && leftup.x <= col_pos1.x + col_size1.x / 2)
	{
		if (col_pos1.y + col_size1.y / 2 >= rightup.y && col_befpos1.y + col_size1.y / 2 <= rightup.y)
		{
			return	true;
		}
	}

	return	false;

	/*D3DXVECTOR2	rightdown1, leftdown1;
	D3DXVECTOR2	rightdown2, leftup2;

	rightdown1 = col_pos1 + col_size1 / 2;
	leftdown1 = D3DXVECTOR2(col_pos1.x - col_size1.x / 2, rightdown1.y);

	leftup2 = col_pos2 - col_size2 / 2;
	rightdown2 = D3DXVECTOR2(col_pos2.x + col_size2.x / 2, leftup2.y + COLLISION_WIDTH);

	if (rightdown1.x < leftup2.x)
		return	false;
	if (rightdown1.y < leftup2.y)
		return	false;
	if (rightdown2.x < leftdown1.x)
		return	false;
	if (rightdown2.y < leftdown1.y)
		return	false;

	return	true;*/
}

bool	GetCollisionDown(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2)	//	オブジェクト下部との当たり判定：返り値、bool
{
	D3DXVECTOR2	rightdown, leftdown;

	rightdown = col_pos2 + col_size2 / 2;
	leftdown = D3DXVECTOR2(col_pos2.x - col_size2.x / 2, col_pos2.y + col_size2.y / 2);

	if (rightdown.x >= col_pos1.x - col_size1.x / 2 && leftdown.x <= col_pos1.x + col_size1.x / 2)
	{
		if (col_pos1.y - col_size1.y / 2 <= rightdown.y && col_befpos1.y - col_size1.y / 2 >= rightdown.y)
		{
			return	true;
		}
	}

	return	false;

	/*D3DXVECTOR2	rightup1, leftup1;
	D3DXVECTOR2	rightdown2, leftup2;

	rightup1 = D3DXVECTOR2(col_pos1.x + col_size1.x / 2, col_pos1.y - col_size1.y / 2);
	leftup1 = col_pos1 - col_size1 / 2;

	rightdown2 = col_pos2 + col_size2 / 2;
	rightdown2.x -= 2;
	leftup2 = D3DXVECTOR2(col_pos2.x - col_size2.x / 2 + 2, rightdown2.y - COLLISION_WIDTH);

	if (rightup1.x < leftup2.x)	return	false;
	if (rightup1.y < leftup2.y)	return	false;
	if (rightdown2.x < leftup1.x)	return	false;
	if (rightdown2.y < leftup1.y)	return	false;

	return	true;*/
}

bool	GetCollisionRight(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2)	//	オブジェクト右部分との当たり判定：返り値、bool
{
	D3DXVECTOR2	rightup, rightdown;
	rightup = D3DXVECTOR2(col_pos2.x + col_size2.x / 2, col_pos2.y - col_size2.y / 2);
	rightdown = col_pos2 + col_size2 / 2;

	if (rightup.y <= col_pos1.y + col_size1.y / 2 && rightdown.y >= col_pos1.y - col_size1.y / 2)
	{
		if (col_pos1.x - col_size1.x / 2 <= rightup.x && col_befpos1.x - col_size1.x / 2 >= rightup.x)
		{
			return	true;
		}
	}

	return	false;

	//D3DXVECTOR2	leftup1, leftdown1;
	//D3DXVECTOR2	rightdown2, leftup2;

	//leftup1 = col_pos1 - col_size1 / 2;
	////leftup1.y += COLLISION_WIDTH;
	//leftdown1 = D3DXVECTOR2(col_pos1.x - col_size1.x / 2, col_pos1.y + col_size1.y / 2);

	//rightdown2 = col_pos2 + col_size2 / 2;
	////rightdown2.y -= COLLISION_WIDTH;
	//leftup2 = D3DXVECTOR2(rightdown2.x - COLLISION_WIDTH, col_pos2.y - col_size2.y / 2);

	//if (rightdown2.x < leftup1.x)	return	false;
	//if (rightdown2.y < leftup1.y)	return	false;
	//if (leftdown1.x < leftup2.x)	return	false;
	//if (leftdown1.y < leftup2.y)	return	false;

	//return	true;
}

bool	GetCollisionLeft(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2)	//	オブジェクト左部分との当たり判定：返り値、bool
{
	D3DXVECTOR2	leftup, leftdown;
	leftup = col_pos2 - col_size2 / 2;
	leftdown = D3DXVECTOR2(col_pos2.x - col_size2.x / 2, col_pos2.y + col_size2.y / 2);

	if (leftup.y <= col_pos1.y + col_size1.y / 2 && leftdown.y >= col_pos1.y - col_size1.y / 2)
	{
		if (col_pos1.x + col_size1.x / 2 >= leftup.x && col_befpos1.x + col_size1.x / 2 <= leftup.x)
		{
			return	true;
		}
	}

	return	false;

	//D3DXVECTOR2	rightup1, rightdown1;
	//D3DXVECTOR2	leftup2, rightdown2;

	//rightup1 = D3DXVECTOR2(col_pos1.x + col_size1.x / 2, col_pos1.y - col_size1.y / 2);
	////rightup1.y += COLLISION_WIDTH;
	//rightdown1 = col_pos1 + col_size1 / 2;

	//leftup2 = col_pos2 - col_size2 / 2;
	//rightdown2 = D3DXVECTOR2(leftup2.x + COLLISION_WIDTH, col_pos2.y + col_size2.y / 2);

	//if (rightdown1.x < leftup2.x)	return	false;
	//if (rightdown1.y < leftup2.y)	return	false;
	//if (rightdown2.x < rightup1.x)	return	false;
	//if (rightdown2.y < rightup1.y)	return	false;

	//return	true;
}

bool	GetCollisionTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol)	//	オブジェクト同士の当たり判定
{
	if (!(*OnCol))
	{
		if (GetCollision(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = true;
			return	true;
		}
	}
	else
	{
		if (!GetCollision(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = false;
		}
	}

	return	false;
}

bool	GetCollisionUpTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol)	//	オブジェクト上部との当たり判定：返り値、bool
{
	if (!(*OnCol))
	{
		if (GetCollisionUp(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = true;
			return	true;
		}
	}
	else
	{
		if (!GetCollisionUp(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = false;
		}
	}

	return	false;
}

bool	GetCollisionDownTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol)	//	オブジェクト下部との当たり判定：返り値、bool
{
	if (!(*OnCol))
	{
		if (GetCollisionDown(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = true;
			return	true;
		}
	}
	else
	{
		if (!GetCollisionDown(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = false;
		}
	}

	return	false;
}

bool	GetCollisionRightTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol)	//	オブジェクト右部分との当たり判定：返り値、bool
{
	if (!(*OnCol))
	{
		if (GetCollisionRight(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = true;
			return	true;
		}
	}
	else
	{
		if (!GetCollisionRight(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = false;
		}
	}

	return	false;
}

bool	GetCollisionLeftTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol)	//	オブジェクト左部分との当たり判定：返り値、bool
{
	if (!(*OnCol))
	{
		if (GetCollisionLeft(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = true;
			return	true;
		}
	}
	else
	{
		if (!GetCollisionLeft(col_pos1, col_befpos1, col_size1, col_pos2, col_size2))
		{
			*OnCol = false;
		}
	}

	return	false;
}

void SetAllCollisionBool(const bool value)
{
	AllCollisionBool = value;
}
const bool& GetAllCollisionBool()
{
	return AllCollisionBool;
}