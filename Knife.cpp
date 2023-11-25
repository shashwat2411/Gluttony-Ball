
#include	"knife.h"

void	KNIFE::Update()
{
	if (use)
	{
		if (!(pos.x > 0 && pos.x < SCREEN_WIDTH))	use = false;
		if (!(pos.y > 0 && pos.y < SCREEN_HEIGHT))	use = false;

		pos_bef = pos;

		Move();
	}
}

void	KNIFE::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = true;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = true;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	onGround = false;

	MoveX = true;
	MoveY = true;

	texNo = LoadTexture((char*)"data/texture/trace_knife.png");

	animTimeMax = 1;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 1.0f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	speed = 5.0f;

	pos = D3DXVECTOR2(0, 0);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 2);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(BASE_SIZE / 2, BASE_SIZE / 2);				//	�����蔻��̃T�C�Y
}

void	KNIFE::Reset()
{

}


//===================================================================================
//	�i�C�t�Ǘ��v���O����
//===================================================================================
KNIFE	knife[KNIFE_MAX];

void	InitKnife()	//	�i�C�t�̏�����
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Init();
		knife[i].Prepare();
	}
}

void	UninitKnife()	//	�i�C�t�̏I������
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Uninit();
	}
}

void	UpdateKnife()	//	�i�C�t�̍X�V����
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Update();
	}
}

void	DrawKnife()	//	�i�C�t�̕`�揈��
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Draw();
	}
}

void	SetKnife(const	D3DXVECTOR2	pos,	D3DXVECTOR2	way)	//	�i�C�t�̃Z�b�g
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		if (!knife[i].GetUse())
		{
			knife[i].SetUse(true);
			knife[i].SetPosi(pos);

			D3DXVec2Normalize(&way, &way);
			knife[i].SetMove(way * knife[i].GetSpeed());

			knife[i].SetAngle(VecToAng(D3DXVECTOR2(0, -1), way) * 2);

			break;
		}
	}
}

KNIFE*	GetKnife()
{
	return	knife;
}




















