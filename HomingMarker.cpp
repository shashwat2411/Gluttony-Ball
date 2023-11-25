
#include	"homingMarker.h"
#include	"Ball.h"


void	HOMING_MARKER::Update()
{
	if (use)
	{
		if (homingEnemy != nullptr)
		{
			pos = homingEnemy->GetPosi();

			if (!homingEnemy->GetUse())
			{
				use = false;
				pos = D3DXVECTOR2(-200, -200);
			}
		}
		if (homingButton != nullptr)
		{
			pos = homingButton->GetPosi();

			if (!homingButton->GetUse())
			{
				use = false;
				pos = D3DXVECTOR2(-200, -200);
			}
		}

		if (GetBall()->GetAbilityMoveBall() != BALL::HOMING)	use = false;
	}
}

void	HOMING_MARKER::Prepare()
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

	collisionBool = false;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/homing_marker.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(-200, -200);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(0, 0);				//	当たり判定のサイズ
}

void	HOMING_MARKER::Reset()
{

}


//=========================================================
//	ホーミングマーカー管理プログラム
//=========================================================
HOMING_MARKER	homingMarker[HOMING_MARKER_MAX];

void	InitHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Init();
		homingMarker[i].Prepare();
	}
}

void	UninitHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Uninit();
	}
}

void	UpdateHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Update();
	}
}

void	DrawHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Draw();
	}
}

void	SetHomingMarker(ENEMY*	new_homingEnemy, BUTTON*	new_homingButton)
{
	if (new_homingEnemy != nullptr || new_homingButton != nullptr)
	{
		for (int i = 0; i < HOMING_MARKER_MAX; i++)
		{
			if (!homingMarker[i].GetUse())
			{
				homingMarker[i].SetUse(true);
				if (new_homingEnemy != nullptr)	homingMarker[i].SetHomingEnemy(new_homingEnemy);
				if (new_homingButton != nullptr)	homingMarker[i].SetHomingButton(new_homingButton);

				break;
			}
		}
	}
}

const	HOMING_MARKER*	GetHomingMarker()
{
	return	homingMarker;
}


void	ResetHomingMaker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].SetUse(false);
		homingMarker[i].SetHomingButton(nullptr);
		homingMarker[i].SetHomingEnemy(nullptr);
	}
}










