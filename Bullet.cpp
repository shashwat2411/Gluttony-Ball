
#include	"bullet.h"
#include	"player.h"
#include	"Explosion.h"

PLAYER*		bullet_player;

unsigned	int	g_BulletSE;

void	BULLET::Update()
{
	if (use)
	{
		pos_bef = pos;

		point = bullet_player->GetPosi();

		angle = VecToAng(D3DXVECTOR2(0, -1), point - pos) * 2;

		timer++;
		if (timer > TimeMax || (point.x - pos.x) * (point.x - pos.x) + (point.y - pos.y) * (point.y - pos.y) < TouchDis * TouchDis)
		{
			use = false;
			timer = 0;
			SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2), EXPLOSION::ENEMY);
		}

		Move();
	}
}

void	BULLET::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	ArrivePoint = false;

	MoveX = true;
	MoveY = true;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/bullet.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(0, 0);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 2);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(BASE_SIZE * 3 / 2, BASE_SIZE * 3 / 2);				//	当たり判定のサイズ

	speed = bullet_player->GetSpeed() - 1;
	r_speed = speed;

	move_type = Point;
}

void	BULLET::Reset()
{

}


//=========================================================================================
//	バレット管理プログラム
//=========================================================================================
BULLET	bullet[BULLET_MAX];

void	InitBullet()	//	バレット初期化
{
	bullet_player = GetPlayer();
	g_BulletSE = LoadSound((char*)"data/SE/shoot_bullet_SE.wav");

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Init();
		bullet[i].Prepare();
	}
}

void	UninitBullet()	//	バレット終了処理
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Uninit();
	}
}

void	UpdateBullet()	//	バレット更新処理
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Update();
	}
}

void	DrawBullet()	//	バレット描画処理
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Draw();
	}
}

void	SetBullet(const	D3DXVECTOR2&	pos)	//	バレットのセット
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i].GetUse())
		{
			bullet[i].SetUse(true);
			bullet[i].SetPosi(pos);
			PlaySound(g_BulletSE, 0);
			SetVolume(g_BulletSE, 0.7f);

			break;
		}
	}
}


BULLET*	GetBullet()	//	バレットの取得
{
	return	bullet;
}
















