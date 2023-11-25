
#include	"game.h"
#include	"player.h"
#include	"collision.h"
#include	"Direction.h"
#include	"ground.h"
#include	"xinput.h"
#include	"Ball.h"
#include	"Enemy.h"
#include	"Explosion.h"
#include	"StickyBomb.h"
#include	"Spring.h"
#include	"SummonEnemy.h"
#include	"bullet.h"
#include	"enemyStickyBomb.h"
#include	"Waiver.h"
#include	"Button.h"
#include	"InterlockArrangement.h"
#include	"knife.h"
#include	"StageGimmick.h"
#include	"homingMarker.h"
#include	"effect.h"
#include	"abilityMark.h"
#include	"oneWayBlock.h"
#include	"SavePoint.h"
#include	"Text.h"

bool	stop = false;
bool	giveUp = false;
int		stopCounter = 0;
bool	BASE_OF_PERFORMER::collisionTest = false;
FADE	stopTime;
char	textNoFade[] = "data/texture/fade.png";

unsigned	int	g_StageBGM00;

void	InitGame()
{
	stopCounter = 0;
	giveUp = false;

	InitGround();	//	�O���E���h����������
	InitExplosion();
	InitStickyBomb();
	InitSummonEnemy();
	InitButton();
	InitInterlockArrangement();
	InitStageGimmick();
	InitHomingMarker();
	InitSpring();
	InitPlayer();	//	�v���C���[����������
	InitDirection();
	InitBall();		//	�{�[������������
	InitEnemy();	//	�G�l�~�[����������
	InitKnife();
	InitBullet();	//	�o���b�g����������
	InitEnemyStickyBomb();	//	�X�e�B�b�L�[���e������
	InitWaiver();	//	�����A�r���e�B������
	InitStage();
	InitEffect();	//	�G�t�F�N�g������
	InitAbilityMark();	//	�\�̓}�[�N�̏�����
	InitOneWayBlock();	//	����ʍs�u���b�N�̏�����
	InitSavePoint();	//�@�Z�[�u�|�C���g�̏�����
	InitTextT();		//�@TEXT�u���b�N�̏�����

	InitCollision();
	InitMoveStage();	//	�X�e�[�W�ړ�������

	MakeStage(GetCurrentStageNum());

	AdjustText();	// TEXT�u���b�N�̍��W��ݒ�

	GetPlayer()->CorrectScreen();

	SetFade(FADEIN);

	g_StageBGM00 = LoadSound((char*)"data/BGM/stage_test.wav");
	SetVolume(g_StageBGM00, 0.1f);
	
	PlaySound(g_StageBGM00, 1);

	{
		stopTime.TextNo = LoadTexture(textNoFade);

		stopTime.Position.x = SCREEN_WIDTH / 2;
		stopTime.Position.y = SCREEN_HEIGHT / 2;

		stopTime.Size.x = SCREEN_WIDTH;
		stopTime.Size.y = SCREEN_HEIGHT;

		stopTime.use = false;

		stopTime.rotation = 0.0f;

		stopTime.Offset = D3DXVECTOR2(0.0f, 0.0f);
		stopTime.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		stopTime.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	}
}

void	UninitGame()
{
	StopSoundAll();

	UninitBall();		//	�{�[���I������
	UninitPlayer();		//	�v���C���[�I������
	UninitDirection();
	UninitEnemy();		//	�G�l�~�[�I������
	UninitGround();		//	�O���E���h�I������
	UninitButton();
	UninitHomingMarker();
	UninitKnife();
	UninitStageGimmick();
	UninitInterlockArrangement();
	UninitExplosion();
	UninitBullet();		//	�o���b�g�I������
	UninitEnemyStickyBomb();	//	�X�e�B�b�L�[���e�I������
	UninitStickyBomb();
	UninitSummonEnemy();
	UninitSpring();
	UninitWaiver();	//	�����A�r���e�B�I������
	UninitEffect();	//	�G�t�F�N�g�I������
	UninitStage();
	UninitAbilityMark();	//	�\�̓}�[�N�̏I������
	UninitOneWayBlock();	//	����ʍs�u���b�N�̏I������
	UninitSavePoint();		//�@�Z�[�u�|�C���g�̏I������
	UninitTextT();			//�@TEXT�u���b�N�̏I������

	UninitBG();			//	�w�i�I������
}

void	UpdateGame()
{
	UpdateEffect();	//	�G�t�F�N�g�X�V����
	if (stop == false)
	{
		ChangeBG();		//�@�`���[�g���A���w�i�����ւ�����
		UpdateBG();		//	�w�i�X�V����

		UpdateGround();	//	�O���E���h�X�V����
		UpdateStickyBomb();
		UpdateSummonEnemy();
		UpdateSpring();
		UpdateExplosion();
		UpdateButton();
		UpdateInterlockArrangement();
		UpdateHomingMarker();
		UpdateStageGimmick();
		UpdatePlayer();	//	�v���C���[�X�V����
		UpdateDirection();
		UpdateBall();	//	�{�[���X�V����
		UpdateEnemy();	//	�G�l�~�[�X�V����
		UpdateBullet();	//	�o���b�g�X�V����
		UpdateKnife();
		UpdateEnemyStickyBomb();	//	�X�e�B�b�L�[���e�X�V����
		UpdateWaiver();	//	�����A�r���e�B�X�V����
		UpdateOneWayBlock();	//	����ʍs�u���b�N�X�V����
		UpdateSavePoint();		//�@�Z�[�u�|�C���g�̍X�V����

		UpdateCollision();	//	�����蔻��̌���
		UpdateTextT();		// TEXT�u���b�N�̍X�V����

		UpdateStage();

		UpdateAbilityMark();	//	�\�̓}�[�N�̍X�V����
	}
	else if (stop == true)
	{
		stopTime.use = true;
		stopCounter += 1;
		if (stopCounter % (60 * 5 / 4) == 0)
		{
			stopCounter = 0;
			stop = false;
			stopTime.use = false;
		}
	}

	if (GetButtonTriggerStart())	giveUp = true;

	if (giveUp)	Fader(true, SELECT_STAGE);
	else	Fader((GetWin() || !GetPlayerUse() || (GetKeyboardPress(DIK_R))), RESULT);
}

void	DrawGame()
{
	DrawBG();		//	�w�i�`�揈��

	DrawTextT();	// 	TEXT�u���b�N�̕`�揈��
	DrawGround();	//	�O���E���h�`�揈��

	DrawInterlockArrangement();
	DrawSummonEnemy();
	DrawButton();
	DrawOneWayBlock();	//	����ʍs�u���b�N�`�揈��
	DrawSavePoint();	//�@�Z�[�u�|�C���g�̕`�揈��
	DrawStageGimmick();
	DrawPlayer();	//	�v���C���[�`�揈��
	DrawDirection();
	DrawEnemy();	//	�G�l�~�[�`�揈��
	DrawKnife();
	DrawBall();		//	�{�[���`�揈��
	DrawBullet();	//	�o���b�g�`�揈��
	DrawEnemyStickyBomb();		//	�X�e�B�b�L�[���e�`�揈��
	DrawHomingMarker();
	DrawWaiver();	//	�����A�r���e�B�`�揈��
	DrawStickyBomb();
	DrawSpring();
	DrawExplosion();

	if (stopTime.use == true)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stopTime.TextNo));
		DrawSpriteColorRotate(stopTime.Position.x, stopTime.Position.y, stopTime.Size.x, stopTime.Size.y, stopTime.rotation, stopTime.color, 0, 1, 1, 1);
		GetDeviceContext()->Draw(4, 0);
	}
	DrawEffect();	//	�G�t�F�N�g�`�揈��
	DrawAbilityMark();	//	�\�̓}�[�N�̕`�揈��
}


void SetStopBool(bool value)
{
	stop = value;
}
bool GetStopBool()
{
	return stop;
}