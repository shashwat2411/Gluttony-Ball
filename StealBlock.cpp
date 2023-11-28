
#include	"stealBlock.h"

void	STEALBLOCK::Update()
{
	if (use)
	{

	}
}

void	STEALBLOCK::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	MoveX = false;
	MoveY = false;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/steal_block.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ
}

void	STEALBLOCK::Reset()
{

}


//======================================================
//	能力没収ブロック管理プログラム
STEALBLOCK	stealBlock[STEALBLOCK_MAX];

void	InitStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Init();
		stealBlock[i].Prepare();
	}
}

void	UninitStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Uninit();
	}
}

void	UpdateStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Update();
	}
}

void	DrawStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Draw();
	}
}

void	SetStealBlock(const	D3DXVECTOR2	new_Pos, const	D3DXVECTOR2	new_Size)
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		if (!stealBlock[i].GetUse())
		{
			stealBlock[i].SetUse(true);
			stealBlock[i].SetPosi(new_Pos);
			stealBlock[i].SetSize(new_Size * BASE_SIZE);
			stealBlock[i].SetCollisionSize(new_Size * BASE_SIZE);

			stealBlock[i].SetTexSizeWidth(new_Size.x);
			stealBlock[i].SetTexSizeHeight(new_Size.y);

			break;
		}
	}
}

STEALBLOCK*	GetStealBlock(void)
{
	return	stealBlock;
}















