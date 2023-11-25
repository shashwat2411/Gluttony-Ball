
#include	"oneWayBlock.h"
#include	"player.h"
#include	"collision.h"

PLAYER*	one_player;

void	ONE_WAY_BLOCK::Update()
{
	if (use)
	{
		if (!collisionBool)
		{
			if (!GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize,
				one_player->GetPosi() + one_player->GetCollisionPos(), one_player->GetCollisionSize()))
			{
				collisionBool = true;
			}
		}
	}
}

void	ONE_WAY_BLOCK::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	MoveX = false;
	MoveY = false;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	TexNums[UP] = LoadTexture((char*)"data/texture/OneWayBlock_up.png");				//	LoadTextureの戻り値を記録する変数
	TexNums[DOWN] = LoadTexture((char*)"data/texture/OneWayBlock_down.png");				//	LoadTextureの戻り値を記録する変数
	TexNums[RIGHT] = LoadTexture((char*)"data/texture/OneWayBlock_left.png");				//	LoadTextureの戻り値を記録する変数
	TexNums[LEFT] = LoadTexture((char*)"data/texture/OneWayBlock_right.png");				//	LoadTextureの戻り値を記録する変数

	texNo = TexNums[UP];
	way = UP;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ

	one_player = GetPlayer();
}

void	ONE_WAY_BLOCK::Reset()
{

}

//============================================
//	一方通行ブロック管理プログラム
//============================================
ONE_WAY_BLOCK	oneWayBlock[ONE_WAY_BLOCK_MAX];

void	InitOneWayBlock()		//	一方通行ブロックの初期化
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Init();
		oneWayBlock[i].Prepare();
	}
}

void	UninitOneWayBlock()	//	一方通行ブロックの終了処理
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Uninit();
	}
}

void	UpdateOneWayBlock()	//	一方通行ブロックの更新処理
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Update();
	}
}

void	DrawOneWayBlock()		//	一方通行ブロックの描画処理
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Draw();
	}
}

void	SetOneWayBlock(const	D3DXVECTOR2 new_pos, const	D3DXVECTOR2	new_size, ONE_WAY_BLOCK::WAY	new_way)
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		if (!oneWayBlock[i].GetUse())
		{
			oneWayBlock[i].SetUse(true);
			oneWayBlock[i].SetCollisionBool(true);
			oneWayBlock[i].SetPosi(new_pos);
			oneWayBlock[i].SetSize(new_size * BASE_SIZE);
			oneWayBlock[i].SetCollisionSize(new_size * BASE_SIZE);
			oneWayBlock[i].SetTexSizeWidth(new_size.x);
			oneWayBlock[i].SetTexSizeHeight(new_size.y);
			oneWayBlock[i].SetWay(new_way);

			oneWayBlock[i].SetTexNums(new_way);

			break;
		}
	}
}

ONE_WAY_BLOCK*	GetOneWayBlock()
{
	return	oneWayBlock;
}
























