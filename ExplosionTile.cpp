
#include	"explosionTile.h"
#include	"Explosion.h"

EXPLOSIONTILE	explosionTile[EXPLOSIONTILE_MAX];
//===============================================================================================================================================
//	グラウンドクラスプログラム
//===============================================================================================================================================
void	EXPLOSIONTILE::Update()
{
	if (use)
	{

	}
}


void	EXPLOSIONTILE::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	BallCollide = false;

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/ground_Test.png");				//	LoadTextureの戻り値を記録する変数
	

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(40.0f, 40.0f);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ
	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

}





void	EXPLOSIONTILE::Reset()
{

}



//===============================================================================================================================================
//	グラウンド管理プログラム
//===============================================================================================================================================

/*==================================
	グラウンド初期化
====================================*/
void	InitExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		explosionTile[i].Init();
		explosionTile[i].Prepare();
	}
	
	//explosionTile[1].SetUse(true);
	//explosionTile[2].SetUse(true);
	//explosionTile[3].SetUse(true);

	//explosionTile[1].SetPosi(D3DXVECTOR2(200, SCREEN_HEIGHT / 4 * 3));
	//explosionTile[2].SetPosi(D3DXVECTOR2(SCREEN_WIDTH - 200, SCREEN_HEIGHT / 4 * 3));
	//explosionTile[3].SetPosi(D3DXVECTOR2(SCREEN_WIDTH / 2, 120));

	//explosionTile[3].SetSize(D3DXVECTOR2(SCREEN_WIDTH, BASE_SIZE * 2));
	//explosionTile[3].SetCollisionSize(explosionTile[3].GetSize());
}

/*==================================
	グラウンド終了処理
====================================*/
void	UninitExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		explosionTile[i].Uninit();
	}
}

/*==================================
	グラウンド更新処理
====================================*/
void	UpdateExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{//変更===========================================================================
		if (explosionTile[i].GetBallCollide() == true)
		{
			explosionTile[i].SetUse(false);
			explosionTile[i].SetBallCollide(false);
		}
		if (explosionTile[i].GetUse() == true) { explosionTile[i].Update(); }
	}
}

/*==================================
	グラウンド描画処理
====================================*/
void	DrawExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		if (explosionTile[i].GetUse() == true) { explosionTile[i].Draw(); }
	}


}

void	SetExplosionTile(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size)	//	足場のセット
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		if (!explosionTile[i].GetUse())
		{
			explosionTile[i].SetUse(true);
			explosionTile[i].SetPosi(pos);
			explosionTile[i].SetSize(size);
			explosionTile[i].SetCollisionSize(size);

			//ground[i].SetPosi(D3DXVECTOR2(ground[i].GetPosi().x, (pos.y - ground_Player->GetStagePos().y) + ground_Player->GetPosi().y));

			break;
		}
	}
}


/*==================================
	グラウンド取得
====================================*/
EXPLOSIONTILE*	GetExplosionTile()
{
	return	explosionTile;
}
