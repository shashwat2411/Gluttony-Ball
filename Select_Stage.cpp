
#include	"select_stage.h"
#include	"SavePoint.h"

unsigned	int		g_ButtonNum[STAGE_MAX];
unsigned	int		g_SelectStageSE;

int		g_StageNum = 0;
bool	KeyPressBool = false;
bool	StickBool2 = false;

SAVE_DATA*	sel_data;

void	InitSelectStage()		//	ステージ選択初期化
{
	ResetSavePoint();	//ステージのセーブポイントを初期化

	g_ButtonNum[0] = LoadTexture((char*)"data/texture/button_stage1.png");
	g_ButtonNum[1] = LoadTexture((char*)"data/texture/button_stage2.png");
	g_ButtonNum[2] = LoadTexture((char*)"data/texture/button_stage3.png");
	g_ButtonNum[3] = LoadTexture((char*)"data/texture/button_stage4.png");

	g_SelectStageSE = LoadSound((char*)"data/SE/select_SE.wav");

	sel_data = GetSaveData();

	SetFade(FADEIN);
}

void	UninitSelectStage()	//	ステージ選択終了処理
{

}

void	UpdateSelectStage()	//	ステージ選択更新処理
{
	Fader((GetButtonTriggerA() || GetKeyboardTrigger(DIK_Z)), GAME);
	if (GetButtonPressA() || GetKeyboardPress(DIK_Z))
	{
		SetClearBool(false);
	}

	//=============================================================================
	//	ステージ選択プログラム       /*上下に変更する*/
	if(GetButtonTriggerUp()&& !KeyPressBool)
	{
		KeyPressBool = true;
		g_StageNum++;
		PlaySound(g_SelectStageSE, 0);
	}
	if (GetStickL().y > 0.5f && !StickBool2)
	{
		StickBool2 = true;
		g_StageNum++;
		PlaySound(g_SelectStageSE, 0);
	}
	if(GetButtonTriggerDown() && !KeyPressBool)
	{
		KeyPressBool = true;
		g_StageNum--;
		PlaySound(g_SelectStageSE, 0);
	}
	if (GetStickL().y < -0.5f && !StickBool2)
	{
		StickBool2 = true;
		g_StageNum--;
		PlaySound(g_SelectStageSE, 0);
	}


	if (g_StageNum < 0)	g_StageNum = sel_data[GetSelectDataNum()].stageNum - 1;
	if (g_StageNum >= (sel_data[GetSelectDataNum()].stageNum))	g_StageNum = 0;

	if (!GetButtonTriggerUp() || !GetButtonTriggerDown() && KeyPressBool)
	{
		KeyPressBool = false;
	}
	if (GetStickL().y == 0 && StickBool2)
	{
		StickBool2 = false;
	}
	//=============================================================================
}

void	DrawSelectStage()		//	ステージ選択描画処理
{
	for (int i = 0; i < STAGE_MAX; i++)
	{
		// テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ButtonNum[i]));

		D3DXCOLOR	color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		if (i == g_StageNum)	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if (i >= sel_data[GetSelectDataNum()].stageNum)
			color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		
		//	ポリゴン配置 　　　　　　　　　/*上下対応に変更する: Widthを固定に、Heightを可変に、size_wを倍程度に、size_hをやや減らす    */
		//DrawSpriteColorRotate((i - 1) * BUTTON_SIZE_W * 3 / 2 + (SCREEN_WIDTH / 2-180), SCREEN_HEIGHT / 2, BUTTON_SIZE_W, BUTTON_SIZE_H,
			//0.0f, color, 0.0f, 1.0f, 1.0f, 0);
		
		//ステージ数５個の時の表示プログラム
		DrawSpriteColorRotate(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2 + 180) +(i*-120) , BUTTON_SIZE_W *3, BUTTON_SIZE_H,
		0.0f, color, 0.0f, 1.0f, 1.0f, 0);
		
		//ステージ数４個の表示プログラム
		//DrawSpriteColorRotate(BUTTON_SIZE_W * 2 / 2 + (SCREEN_WIDTH / 2 - 130), (SCREEN_HEIGHT / 2 + 220) +(i*-100) , BUTTON_SIZE_W *3, BUTTON_SIZE_H,
			//0.0f, color, 0.0f, 1.0f, 1.0f, 0);
	}
}

const	int&	GetCurrentStageNum()
{
	return g_StageNum;
}