#include	"player.h"
#include	"Text.h"
#include	"stage.h"
#include	"bg.h"

int num = 0;
D3DXVECTOR2 SizeBackUp[TEXT_MAX];
void	TEXT::Update()
{
	if (use)
	{

	}
}

void	TEXT::Prepare()
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
	collisionBool = false;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/tutorial/RB_Button.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標6
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ
}

void	TEXT::Reset()
{

}


//======================================================
//	能力没収ブロック管理プログラム
TEXT	TextureText[TEXT_MAX];

void	InitTextT()
{
	for (int i = 0; i < TEXT_MAX; i++)
	{
		TextureText[i].Init();
		TextureText[i].Prepare();
	}

	TextureText[0].SetTexNo(LoadTexture((char*)"data/texture/tutorial/RB_Button.png"));
	TextureText[1].SetTexNo(LoadTexture((char*)"data/texture/tutorial/R_JoyStick.png"));
	TextureText[2].SetTexNo(LoadTexture((char*)"data/texture/tutorial/Charge.png"));
	TextureText[3].SetTexNo(LoadTexture((char*)"data/texture/tutorial/Absorb.png"));
	TextureText[4].SetTexNo(LoadTexture((char*)"data/texture/tutorial/BlockDestruction.png"));
	TextureText[5].SetTexNo(LoadTexture((char*)"data/texture/tutorial/ForcedEject.png"));
	TextureText[6].SetTexNo(LoadTexture((char*)"data/texture/tutorial/Bounce.png"));
	TextureText[7].SetTexNo(LoadTexture((char*)"data/texture/tutorial/AbilityThrowAway.png"));
	TextureText[8].SetTexNo(LoadTexture((char*)"data/texture/tutorial/Switch.png"));

	TextureText[0].SetSize(D3DXVECTOR2(0.95, 1));
	TextureText[1].SetSize(D3DXVECTOR2(0.88, 1));
	TextureText[2].SetSize(D3DXVECTOR2(0.75, 1));
	TextureText[3].SetSize(D3DXVECTOR2(1.45, 1));
	TextureText[4].SetSize(D3DXVECTOR2(1.04, 1));
	TextureText[5].SetSize(D3DXVECTOR2(1.31, 1));
	TextureText[6].SetSize(D3DXVECTOR2(1.32, 1));
	TextureText[7].SetSize(D3DXVECTOR2(2.06, 1));
	TextureText[8].SetSize(D3DXVECTOR2(1.48, 1));

	TextureText[0].SetSize(TextureText[0].GetSize() * BASE_SIZE * 4.5f);
	TextureText[1].SetSize(TextureText[1].GetSize() * BASE_SIZE * 4.5f);
	TextureText[2].SetSize(TextureText[2].GetSize() * BASE_SIZE * 5.0f);
	TextureText[3].SetSize(TextureText[3].GetSize() * BASE_SIZE * 5.0f);
	TextureText[4].SetSize(TextureText[4].GetSize() * BASE_SIZE * 5.5f);
	TextureText[5].SetSize(TextureText[5].GetSize() * BASE_SIZE * 4.0f);
	TextureText[6].SetSize(TextureText[6].GetSize() * BASE_SIZE * 6.5f);
	TextureText[7].SetSize(TextureText[7].GetSize() * BASE_SIZE * 8.0f);
	TextureText[8].SetSize(TextureText[8].GetSize() * BASE_SIZE * 6.0f);

	for (int i = 0; i < TEXT_MAX; i++)
	{
		SizeBackUp[i] = TextureText[i].GetSize();
	}
}

void	UninitTextT()
{
	for (int i = 0; i < TEXT_MAX; i++)
	{
		TextureText[i].Uninit();
	}
}

void	UpdateTextT()
{
	//for (int i = 0; i < TEXT_MAX; i++)
	//{
	//	TextureText[i].Update();
	//}

	//if (GetKeyboardTrigger(DIK_E)) { num++; if (num >= TEXT_MAX) { num = 0; } }
	//if (GetKeyboardTrigger(DIK_Q)) { num--; if (num < 0) { num = TEXT_MAX-1; }}

	//if (GetKeyboardTrigger(DIK_W)) { TextureText[num].SetPosi(D3DXVECTOR2(TextureText[num].GetPosi().x, TextureText[num].GetPosi().y - BASE_SIZE)); }
	//if (GetKeyboardTrigger(DIK_S)) { TextureText[num].SetPosi(D3DXVECTOR2(TextureText[num].GetPosi().x, TextureText[num].GetPosi().y + BASE_SIZE)); }
	//if (GetKeyboardTrigger(DIK_D)) { TextureText[num].SetPosi(D3DXVECTOR2(TextureText[num].GetPosi().x + BASE_SIZE, TextureText[num].GetPosi().y)); }
	//if (GetKeyboardTrigger(DIK_A)) { TextureText[num].SetPosi(D3DXVECTOR2(TextureText[num].GetPosi().x - BASE_SIZE, TextureText[num].GetPosi().y)); }

	//if (GetKeyboardTrigger(DIK_Z)) { TextureText[num].SetSize(TextureText[num].GetSize()+SizeBackUp[num]*0.1f); }
	//if (GetKeyboardTrigger(DIK_X)) { TextureText[num].SetSize(TextureText[num].GetSize()-SizeBackUp[num]*0.1f); }
	//if (GetKeyboardTrigger(DIK_C)) { TextureText[num].SetSize(SizeBackUp[num]); }

	//char* str = GetDebugStr();
	//sprintf(str, "Position : X = %.2f, Y = %.2f     Size : X = %.2f, Y = %.2f",TextureText[num].GetPosi().x, TextureText[num].GetPosi().y, TextureText[num].GetSize().x/BASE_SIZE, TextureText[num].GetSize().y/BASE_SIZE);
}

void AdjustText()
{
	TextureText[3].SetPosi(D3DXVECTOR2(TextureText[3].GetPosi().x, TextureText[3].GetPosi().y + 15.0f));
	TextureText[4].SetPosi(D3DXVECTOR2(TextureText[4].GetPosi().x + 15.0f, TextureText[4].GetPosi().y + 15.0f));
	TextureText[8].SetPosi(D3DXVECTOR2(TextureText[8].GetPosi().x, TextureText[8].GetPosi().y + 15.0f));
}

void ChangeBG()
{
	if (GetCurrentStageNum() == 0)
	{
		if (GetPlayer()->GetPosi().y >= SCREEN_HEIGHT - 5.0f)
		{
			//SetBGScene(true);
		}
		else if (GetPlayer()->GetPosi().y <= 5.0f)
		{
			//SetBGScene(false);
		}
	}

}

void	DrawTextT()
{
	for (int i = 0; i < TEXT_MAX; i++)
	{
		TextureText[i].Draw();
	}
}

void	SetText(const	D3DXVECTOR2	new_Pos, int num)
{
	TextureText[num].SetUse(true);
	TextureText[num].SetPosi(new_Pos);
}

TEXT* GetText()
{
	return &TextureText[0];
}











