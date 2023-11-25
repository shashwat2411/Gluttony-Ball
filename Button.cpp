#include "Button.h"
#include "collision.h"
#include "Ball.h"
#include "InterlockArrangement.h"

BUTTON button[BUTTON_MAX];

BALL*	b_ball;
INTERLOCKARRANGEMENT*	b_inter;

static	D3DXCOLOR	ColorsType[10] = { D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f), D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f), D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 1.0f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f),
D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) };

void BUTTON::Update()
{
	if (use)
	{
		if (collisionBool)
		{
			if (On_OffSwitch && animationNo_W != 1)			animationNo_W = 1;
			else if (!On_OffSwitch && animationNo_W != 0)	animationNo_W = 0;
		}
		else
		{
			if (!GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize, b_ball->GetPosi() + b_ball->GetCollisionPos(),
				b_ball->GetCollisionSize()))
			{
				collisionBool = true;
			}
		}
	}
}


void BUTTON::Prepare()
{
	use = false;						//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;					//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	MoveX = false;
	MoveY = false;
	ArrivePoint = false;

	SaveAble = false;

	texNo = LoadTexture((char*)"data/texture/laver_button.png");			//	LoadTexture�̖߂�l���L�^����ϐ�
	g_ButtonSE = LoadSound((char*)"data/SE/switchLaber_SE.wav");

	animFlame_W = 2;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	size = D3DXVECTOR2(BASE_SIZE*1, BASE_SIZE*1);						//	�I�u�W�F�N�g�̕`��͈�
	collisionLocalPos = D3DXVECTOR2(0, 0);								//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size;												//	�����蔻��̃T�C�Y

	On_OffSwitch = false;	//true�Ȃ�X�C�b�`���I���ɂȂ�M�~�b�N���쓮����

	b_ball = GetBall();
	b_inter = GetInterlockArrangement();
}

void BUTTON::Reset()
{

}

void BUTTON::SetButton(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off)
{
	use = true;		//�g�p�t���O��true��
	SetPosi(pos);	//���W���Z�b�g

	gravity = false;			//�d�͂𖳌���
	onGround = false;
	BallCollide = false;
	collisionBool = true;
	On_OffSwitch = button_off;

	if (On_OffSwitch)	animationNo_W = 1;
	else				animationNo_W = 0;
}



//=============================================
//	�{�^���Ǘ��v���O����
//=============================================

/*==================================
	�{�^���u���b�N������
====================================*/
void	InitButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Init();
		button[i].Prepare();
	}
}

/*==================================
	�{�^���u���b�N�I������
====================================*/
void	UninitButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Uninit();
	}
}

/*==================================
	�{�^���u���b�N�X�V����
====================================*/
void	UpdateButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Update();
	}
}

/*==================================
	�{�^���u���b�N�`�揈��
====================================*/
void	DrawButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Draw();
	}
}

/*==================================
	�{�^���u���b�N�̃Z�b�g
====================================*/
void	SetButtons(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off, int index)	//	�{�^���̃Z�b�g
{
	if (index < BUTTON_MAX)
	{
		if (!button[index].GetUse())
		{
			button[index].SetButton(pos, size, button_off);
			button[index].SetColor(ColorsType[index]);

			b_inter[index].SetOn_Off_InterlockArrangement(button_off);
		}
	}
}
/*==================================
	�{�^���u���b�N�擾
====================================*/
BUTTON* GetButton()
{
	return	button;
}

