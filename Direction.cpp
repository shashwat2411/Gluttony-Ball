
#include	"Direction.h"
#include	"player.h"
#include	"xinput.h"
#include	"Ball.h"
#include	"collision.h"
#include	"homingMarker.h"

DIRECTION direction;
PLAYER*	d_player;
ENEMY* d_enemy;
BUTTON*	d_button;
D3DXVECTOR2 size2;

void DIRECTION::Update()
{
	if (use)
	{
		if (GetBall()->GetAbilityMoveBall() != BALL::NONE_BALL && color != D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))	color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		else if (GetBall()->GetAbilityMoveBall() == BALL::NONE_BALL && color != D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		angle = VecToAng(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(GetStickR().x, -GetStickR().y));
		pos = D3DXVECTOR2(d_player->GetPosi().x, d_player->GetPosi().y - 10.0f);

		if (GetBall()->GetAbilityMoveBall() == BALL::HOMING)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (d_enemy[i].GetUse() && d_enemy[i].GetCollisionBool() &&
					d_enemy[i].GetPosi().x > 0 && d_enemy[i].GetPosi().x < SCREEN_WIDTH &&
					d_enemy[i].GetPosi().y > 0 && d_enemy[i].GetPosi().y < SCREEN_HEIGHT)
				{
					D3DXVECTOR2	serDis;
					serDis.x = SCREEN_WIDTH * cosf(D3DXToRadian(angle)) + pos.x;
					serDis.y = SCREEN_WIDTH * sinf(D3DXToRadian(angle)) + pos.y;

					if ((serDis.x - d_enemy[i].GetPosi().x) * (serDis.x - d_enemy[i].GetPosi().x) +
						(serDis.y - d_enemy[i].GetPosi().y) * (serDis.y - d_enemy[i].GetPosi().y) +
						(d_player->GetPosi().x - d_enemy[i].GetPosi().x) * (d_player->GetPosi().x - d_enemy[i].GetPosi().x) +
						(d_player->GetPosi().y - d_enemy[i].GetPosi().y) * (d_player->GetPosi().y - d_enemy[i].GetPosi().y) <
						(SER_HOMING_DIS) * (SER_HOMING_DIS))
					{
						//float	test = VecToAng(serDis - d_player->GetPosi(), d_enemy[i].GetPosi() - d_player->GetPosi());

						GetBall()->SetTarget(&d_enemy[i], nullptr);
					}
				}
			}

			for (int i = 0; i < BUTTON_MAX; i++)
			{
				if (d_button[i].GetUse() && d_button[i].GetCollisionBool() &&
					d_button[i].GetPosi().x > 0 && d_button[i].GetPosi().x < SCREEN_WIDTH &&
					d_button[i].GetPosi().y > 0 && d_button[i].GetPosi().y < SCREEN_HEIGHT)
				{
					D3DXVECTOR2	serDis;
					serDis.x = SCREEN_WIDTH * cosf(D3DXToRadian(angle)) + pos.x;
					serDis.y = SCREEN_WIDTH * sinf(D3DXToRadian(angle)) + pos.y;

					if ((serDis.x - d_button[i].GetPosi().x) * (serDis.x - d_button[i].GetPosi().x) +
						(serDis.y - d_button[i].GetPosi().y) * (serDis.y - d_button[i].GetPosi().y) +
						(d_player->GetPosi().x - d_button[i].GetPosi().x) * (d_player->GetPosi().x - d_button[i].GetPosi().x) +
						(d_player->GetPosi().y - d_button[i].GetPosi().y) * (d_player->GetPosi().y - d_button[i].GetPosi().y) <
						(SER_HOMING_DIS) * (SER_HOMING_DIS))
					{
						GetBall()->SetTarget(nullptr, &d_button[i]);
					}
				}
			}
		}
	}
}

void DIRECTION::Prepare()
{

	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	onGround = false;

	MoveX = true;
	MoveY = true;

	texNo = LoadTexture((char*)"data/texture/arrow.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE);					//	オブジェクトの描画範囲

	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	d_player = GetPlayer();
	d_enemy = GetEnemy();
	d_button = GetButton();
}


void DIRECTION::Reset()
{
}


//==============================================================================================================================
//	プレーヤー管理プログラム
//==============================================================================================================================

/*==================================
	プレーヤー初期化
====================================*/
void	InitDirection()
{
	direction.Init();
	direction.Prepare();
}

/*==================================
	プレーヤー終了処理
====================================*/
void	UninitDirection()
{
	direction.Uninit();
}

/*==================================
	プレーヤー更新処理
====================================*/
void	UpdateDirection()
{
	direction.Update();


}

/*==================================
	プレーヤー描画処理
====================================*/
void	DrawDirection()
{
	direction.Draw();
}

/*==================================
	プレーヤー取得
====================================*/
DIRECTION* GetDirection()
{
	return	&direction;
}