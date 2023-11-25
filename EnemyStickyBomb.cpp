
#include	"enemyStickyBomb.h"
#include	"Explosion.h"
#include	"player.h"

#include	"collision.h"

PLAYER*	enemy_sticky_bomb_player;

void	ENEMY_STICKY_BOMB::Update()	//	初期化
{
	if (use)
	{
		pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		if (pos.y + size.y > SCREEN_HEIGHT)	use = false;

		if (onGround)
		{
			timer++;

			if (timer >= ExpTimeOnGround)
			{
				use = false;
				timer = 0;
				SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 6), EXPLOSION::ENEMY);
			}
		}

		if (GetCollision(enemy_sticky_bomb_player->GetPosi() + enemy_sticky_bomb_player->GetCollisionPos(),
			enemy_sticky_bomb_player->GetBefPosi() + enemy_sticky_bomb_player->GetCollisionPos(), enemy_sticky_bomb_player->GetCollisionSize(),
			pos + collisionLocalPos, collisionSize))
		{
			use = false;
			SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 6), EXPLOSION::ENEMY);
		}

		Gravity();
		Move();
	}
}

void	ENEMY_STICKY_BOMB::Prepare()	//	準備処理
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = true;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	MoveX = false;
	MoveY = true;

	ArrivePoint = false;

	texNo = LoadTexture((char*)"data/texture/enemy_sticky_bomb.png");

	animTimeMax = 1;		//	animTimerがこの値を超えると0に戻る
	animOneFlameTime = 0.2f;			//	animTimerに加算し続ける変数

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size * 4 / 5;				//	当たり判定のサイズ

	move = D3DXVECTOR2(0, 0);

	gravityNum = 0.2f;
}

void	ENEMY_STICKY_BOMB::Reset()	//	リセット処理
{

}

//============================================================
//	スティッキー爆弾エネミーのスティッキー爆弾制御プログラム
//============================================================
ENEMY_STICKY_BOMB	enemy_sticky_bomb[ENEMY_STICKY_BOMB_MAX];

void	InitEnemyStickyBomb()	//	スティッキー爆弾初期化
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Init();
		enemy_sticky_bomb[i].Prepare();
	}

	enemy_sticky_bomb_player = GetPlayer();
}

void	UninitEnemyStickyBomb()	//	スティッキー爆弾終了処理
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Uninit();
	}
}

void	UpdateEnemyStickyBomb()	//	スティッキー爆弾更新処理
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Update();
	}
}

void	DrawEnemyStickyBomb()		//	スティッキー爆弾描画処理
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Draw();
	}
}

void	SetEnemyStickyBomb(const	D3DXVECTOR2	pos)
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		if (!enemy_sticky_bomb[i].GetUse())
		{
			enemy_sticky_bomb[i].SetUse(true);
			enemy_sticky_bomb[i].SetOnGround(false);
			enemy_sticky_bomb[i].SetPosi(pos);
			enemy_sticky_bomb[i].SetMove(D3DXVECTOR2(0, 0));
			enemy_sticky_bomb[i].SetTime(0);

			break;
		}
	}
}

ENEMY_STICKY_BOMB*	GetEnemyStickyBomb(void)
{
	return	enemy_sticky_bomb;
}












