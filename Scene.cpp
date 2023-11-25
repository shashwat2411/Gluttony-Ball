
#include	"scene.h"

//======================================================
//	�V�[���i�[�ϐ�
//======================================================
static SCENE	g_SceneIndex = NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

void	InitScene(SCENE ScreenNo)	//	�V�[��������
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
		InitSelectStage();	//	�X�e�[�W�I���̏I������
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

void	UninitScene()	//	�V�[���I������
{
	UninitXinput();	//	���͏����̏I������
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
		UninitSelectStage();	//	�X�e�[�W�I���̏I������
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

void	UpdateScene()	//	�V�[���X�V����
{
	UpdateXinput();		//	���͏����̍X�V����	�K���ŏ��ɍX�V����
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

void	DrawScene()	//	�V�[���`�揈��
{
	DrawBG();	//	�w�i�̕`�揈��

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


void	SetScene(const	SCENE	new_Scene)	//	�V�[���ϐ��̃Z�b�g
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



