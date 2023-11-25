
#include	"scene.h"

//======================================================
//	シーン格納変数
//======================================================
static SCENE	g_SceneIndex = NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

void	InitScene(SCENE ScreenNo)	//	シーン初期化
{
	g_SceneIndex = g_SceneNextIndex = ScreenNo;

	InitBG();

	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case TITLE:
		InitFade();
		break;
	case	SELECT_DATA:
		InitSaveData();
		break;
	case SELECT_STAGE:
		InitSelectStage();	//	ステージ選択の終了処理
		break;
	case GAME:
		InitGame();
		break;
	case RESULT:
		InitResult();
		break;
	default:
		exit(999);
		break;
	}

}

void	UninitScene()	//	シーン終了処理
{
	UninitXinput();	//	入力処理の終了処理
	UninitBG();

	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case TITLE:
		break;
	case	SELECT_DATA:
		UninitSaveData();
		break;
	case SELECT_STAGE:
		UninitSelectStage();	//	ステージ選択の終了処理
		break;
	case GAME:
		UninitGame();
		break;
	case RESULT:
		UninitResult();
		break;
	default:
		exit(999);
		break;
	}
}

void	UpdateScene()	//	シーン更新処理
{
	UpdateXinput();		//	入力処理の更新処理	必ず最初に更新する
	UpdateBG();

	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case	TITLE:
		Fader((GetButtonTriggerA() || (GetKeyboardTrigger(DIK_Z))), SELECT_DATA);
		break;
	case	SELECT_DATA:
		UpdateSaveData();
		break;
	case	SELECT_STAGE:	UpdateSelectStage();
		break;
	case	GAME:
		UpdateGame();
		break;
	case	RESULT:	UpdateResult();
		break;
	default:
		exit(999);
		break;
	}

}

void	DrawScene()	//	シーン描画処理
{
	DrawBG();	//	背景の描画処理

	switch (g_SceneIndex)
	{
	case	TITLE:
		break;
	case	SELECT_DATA:
		DrawSaveData();
		break;
	case	SELECT_STAGE:	
		DrawSelectStage();
		break;
	case	GAME:
		DrawGame();
		break;
	case	RESULT:
		DrawResult();
		break;
	}
}


void	SetScene(const	SCENE	new_Scene)	//	シーン変数のセット
{
	g_SceneNextIndex = new_Scene;
}
const	SCENE& GetScene()
{
	return g_SceneIndex;
}

void CheckScene()
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		UninitScene();
		InitScene(g_SceneNextIndex);
	}
}



