
#include	"bg.h"
#include	"select_stage.h"

SCENE	g_BackScreenNum = TITLE;

unsigned	int		g_TitleNum;
unsigned	int		g_SelectDataNum;
unsigned	int		g_BackStageScreen[STAGE_MAX];
unsigned	int		g_ResultScreen[4];

void	InitBG()	//	背景初期化
{
	g_TitleNum = LoadTexture((char*)"data/texture/backScreen/title.png");
	g_SelectDataNum = LoadTexture((char*)"data/texture/backScreen/back_SelectData0.png");

	g_BackStageScreen[0] = LoadTexture((char*)"data/texture/backScreen/stage_screen01.png");
	g_BackStageScreen[1] = LoadTexture((char*)"data/texture/backScreen/back_screen_test.png");
	g_BackStageScreen[2] = LoadTexture((char*)"data/texture/backScreen/stage_screen02.png");
	g_BackStageScreen[3] = LoadTexture((char*)"data/texture/backScreen/stage_screen04.png");

	g_ResultScreen[0] = LoadTexture((char*)"data/texture/backScreen/result_screen.png");	//	死亡
	g_ResultScreen[1] = LoadTexture((char*)"data/texture/backScreen/GameOver.png");			//	ゲームオーバー
	g_ResultScreen[2] = LoadTexture((char*)"data/texture/backScreen/StageClear.png");		//	ステージクリア
	g_ResultScreen[3] = LoadTexture((char*)"data/texture/backScreen/GameClear.png");		//	ゲームクリア
}

void	UninitBG()	//	背景終了処理
{

}

void	UpdateBG()	//	背景更新処理
{
	g_BackScreenNum = GetScene();
}

void	DrawBG()	//	背景描画処理
{
	SetWorldViewProjection2D();
	// テクスチャのセット

	D3DXCOLOR	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (g_BackScreenNum == TITLE)	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TitleNum));
	else if (g_BackScreenNum == SELECT_DATA)	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectDataNum));
	else if (g_BackScreenNum == GAME || g_BackScreenNum == SELECT_STAGE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BackStageScreen[GetCurrentStageNum()]));

		if (GetCurrentStageNum() == 3)	color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}
	else if (g_BackScreenNum == RESULT)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultScreen[GetResultSituNum()]));
	}

	//	ポリゴン配置
	DrawSpriteColorRotate(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, color, 0.0f, 1.0f, 1.0f, 0);				
}








