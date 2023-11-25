
#include	"select_stage.h"
#include	"SavePoint.h"

unsigned	int		g_ButtonNum[STAGE_MAX];
unsigned	int		g_SelectStageSE;

int		g_StageNum = 0;
bool	KeyPressBool = false;
bool	StickBool2 = false;

SAVE_DATA*	sel_data;

void	InitSelectStage()		//	�X�e�[�W�I��������
{
	ResetSavePoint();	//�X�e�[�W�̃Z�[�u�|�C���g��������

	g_ButtonNum[0] = LoadTexture((char*)"data/texture/button_stage1.png");
	g_ButtonNum[1] = LoadTexture((char*)"data/texture/button_stage2.png");
	g_ButtonNum[2] = LoadTexture((char*)"data/texture/button_stage3.png");
	g_ButtonNum[3] = LoadTexture((char*)"data/texture/button_stage4.png");

	g_SelectStageSE = LoadSound((char*)"data/SE/select_SE.wav");

	sel_data = GetSaveData();

	SetFade(FADEIN);
}

void	UninitSelectStage()	//	�X�e�[�W�I���I������
{

}

void	UpdateSelectStage()	//	�X�e�[�W�I���X�V����
{
	Fader((GetButtonTriggerA() || GetKeyboardTrigger(DIK_Z)), GAME);
	if (GetButtonPressA() || GetKeyboardPress(DIK_Z))
	{
		SetClearBool(false);
	}

	//=============================================================================
	//	�X�e�[�W�I���v���O����       /*�㉺�ɕύX����*/
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

void	DrawSelectStage()		//	�X�e�[�W�I��`�揈��
{
	for (int i = 0; i < STAGE_MAX; i++)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ButtonNum[i]));

		D3DXCOLOR	color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		if (i == g_StageNum)	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if (i >= sel_data[GetSelectDataNum()].stageNum)
			color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		
		//	�|���S���z�u �@�@�@�@�@�@�@�@�@/*�㉺�Ή��ɕύX����: Width���Œ�ɁAHeight���ςɁAsize_w��{���x�ɁAsize_h����⌸�炷    */
		//DrawSpriteColorRotate((i - 1) * BUTTON_SIZE_W * 3 / 2 + (SCREEN_WIDTH / 2-180), SCREEN_HEIGHT / 2, BUTTON_SIZE_W, BUTTON_SIZE_H,
			//0.0f, color, 0.0f, 1.0f, 1.0f, 0);
		
		//�X�e�[�W���T�̎��̕\���v���O����
		DrawSpriteColorRotate(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2 + 180) +(i*-120) , BUTTON_SIZE_W *3, BUTTON_SIZE_H,
		0.0f, color, 0.0f, 1.0f, 1.0f, 0);
		
		//�X�e�[�W���S�̕\���v���O����
		//DrawSpriteColorRotate(BUTTON_SIZE_W * 2 / 2 + (SCREEN_WIDTH / 2 - 130), (SCREEN_HEIGHT / 2 + 220) +(i*-100) , BUTTON_SIZE_W *3, BUTTON_SIZE_H,
			//0.0f, color, 0.0f, 1.0f, 1.0f, 0);
	}
}

const	int&	GetCurrentStageNum()
{
	return g_StageNum;
}