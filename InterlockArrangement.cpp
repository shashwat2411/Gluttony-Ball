#include "InterlockArrangement.h"
#include "collision.h"
#include "Ball.h"
#include "Button.h"

INTERLOCKARRANGEMENT interlockarrangement[BUTTON_MAX];

static	D3DXCOLOR	ColorsType[10] = { D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f),
D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) };

void INTERLOCKARRANGEMENT::Update()
{
	if (use)
	{
		if (On_OffSwitch && texNo != texture2)	texNo = texture2;//�e�N�X�`����؂�ւ���
		else if (!On_OffSwitch && texNo != texture1)	texNo = texture1;
	}
}

void INTERLOCKARRANGEMENT::Prepare()
{
	use = false;						//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;					//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	MoveX = false;
	MoveY = false;
	ArrivePoint = false;

	texture1 = LoadTexture((char*)"data/texture/SwitchBlock_close.png");			//	LoadTexture�̖߂�l���L�^����ϐ�
	texture2 = LoadTexture((char*)"data/texture/SwitchBlock_open.png");

	texNo = texture1;

	size = D3DXVECTOR2(BASE_SIZE * 1, BASE_SIZE * 1);					//	�I�u�W�F�N�g�̕`��͈�
	collisionLocalPos = D3DXVECTOR2(0, 0);								//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size;												//	�����蔻��̃T�C�Y

	On_OffSwitch = false;												//true�Ȃ�X�C�b�`���I���ɂȂ�M�~�b�N���쓮����


}

void INTERLOCKARRANGEMENT::Reset()
{

}

void INTERLOCKARRANGEMENT::SetInterlockArrangement(D3DXVECTOR2 new_pos,D3DXVECTOR2 new_size)
{
	use = true;		//�g�p�t���O��true��
	pos = new_pos;	//���W���Z�b�g
	size = new_size;

	gravity = false;			//�d�͂𖳌���
	onGround = false;
	collisionBool = true;
}


//=============================================
//	�{�^���ɘA�����č쓮������̊Ǘ��v���O����
//=============================================
/*==================================
	�{�^���ɘA�����č쓮������̏�����
====================================*/
void	InitInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Init();
		interlockarrangement[i].Prepare();
	}
}

/*==================================
	�{�^���ɘA�����č쓮������̏I������
====================================*/
void	UninitInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Uninit();
	}
}

/*==================================
	�{�^���ɘA�����č쓮������̍X�V����
====================================*/
void	UpdateInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Update();
	}
}

/*==================================
	�{�^���ɘA�����č쓮������̕`�揈��
====================================*/
void	DrawInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Draw();
	}
}

/*==================================
	�{�^���ɘA�����č쓮������̂̃Z�b�g
====================================*/
void	SetInterlockArrangements(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	if (index < BUTTON_MAX)
	{
		if (!interlockarrangement[index].GetUse())
		{
			interlockarrangement[index].SetInterlockArrangement(pos, size * BASE_SIZE);

			interlockarrangement[index].SetColor(ColorsType[index]);

			interlockarrangement[index].SetCollisionSize(size * BASE_SIZE);
			interlockarrangement[index].SetTexSizeWidth(size.x);
			interlockarrangement[index].SetTexSizeHeight(size.y);
		}
	}
}

/*==================================
	�{�^���ɘA�����č쓮������̎擾
====================================*/
INTERLOCKARRANGEMENT* GetInterlockArrangement()
{
	return	interlockarrangement;
}

