
#include	"Result.h"
#include	"SavePoint.h"

unsigned	int	g_NumbersTexture;
unsigned	int	g_PlayerTexture;

int	resultSituNum;

int	timer = 0;
const	int	timeMax = 60 * 1;

bool	ClearBool;

SAVE_DATA*	result_data;

void	InitResult()		//	ステージ選択初期化
{
	g_NumbersTexture = LoadTexture((char*)"data/texture/data_numbers.png");
	g_PlayerTexture = LoadTexture((char*)"data/texture/Player/idle_R.png");

	resultSituNum = 0;
	timer = 0;

	result_data = GetSaveData();

	if (ClearBool)
	{
		switch (GetCurrentStageNum())
		{
		case 0:
		case 1:
		case 2:	resultSituNum = 2;	break;
		case 3:	resultSituNum = 3;	break;
		}

		if (result_data[GetSelectDataNum()].stageNum == GetCurrentStageNum() + 1 && result_data[GetSelectDataNum()].stageNum < STAGE_MAX)
		{
			result_data[GetSelectDataNum()].stageNum = GetCurrentStageNum() + 2;
		}

		if (result_data[GetSelectDataNum()].life + 5 < 100)	result_data[GetSelectDataNum()].life += 5;
		else result_data[GetSelectDataNum()].life = 99;
	}
	else
	{
		if (result_data[GetSelectDataNum()].life > 0)
		{
			result_data[GetSelectDataNum()].life--;
			resultSituNum = 0;
		}

		if (result_data[GetSelectDataNum()].life <= 0)
		{//　ライフが0以下のとき
			ResetSavePoint();	//	セーブポイントの情報をリセット
			resultSituNum = 1;
		}
	}

	SetFade(FADEIN);
}

void	UninitResult()	//	ステージ選択終了処理
{
	Save(result_data);
}

void	UpdateResult()	//	ステージ選択更新処理
{
	if (ClearBool)
	{
		Fader((GetButtonTriggerA() || (GetKeyboardTrigger(DIK_Z))), SELECT_STAGE);
	}
	else
	{
		if (resultSituNum == 0)
		{
			timer++;

			if (timer > timeMax)
				Fader(true, GAME);
		}
		else
		{
			bool	trigger = GetButtonTriggerA();

			Fader((trigger || (GetKeyboardTrigger(DIK_Z))), SELECT_STAGE);

			if (trigger)
			{
				result_data[GetSelectDataNum()].life = 10;
			}
		}
	}
}

void	DrawResult()		//	ステージ選択描画処理
{
	if (!ClearBool && resultSituNum == 0)
	{
		// テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PlayerTexture));

		//	ポリゴン配置
		DrawSpriteColorRotate(SCREEN_WIDTH * 3 / 10, SCREEN_HEIGHT / 2, 60 * 1.66f, 60 * 2, 0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f / 10, 1.0f, 0);

		// テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_NumbersTexture));

		//	ポリゴン配置
		DrawSpriteColorRotate(SCREEN_WIDTH * 7 / 10, SCREEN_HEIGHT / 2, 2 * 20, 3 * 20, 0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), result_data[GetSelectDataNum()].life % 10, 1.0f / 10, 1.0f, 0);

		if (result_data[GetSelectDataNum()].life > 9)
		{
			//	ポリゴン配置
			DrawSpriteColorRotate(SCREEN_WIDTH * 7 / 10 - 2 * 20, SCREEN_HEIGHT / 2, 2 * 20, 3 * 20, 0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), (int)(result_data[GetSelectDataNum()].life / 10), 1.0f / 10, 1.0f, 0);
		}
	}
}

void	SetClearBool(const	bool	new_Bool)
{
	ClearBool = new_Bool;
}

const	bool&	GetClearBool()
{
	return	ClearBool;
}

const	int&	GetResultSituNum()
{
	return	resultSituNum;
}













