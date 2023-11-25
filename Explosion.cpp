#include "Explosion.h"
#include "Ball.h"

EXPLOSION	Explosion[EXPLOSION_MAX];
BALL* e_ball;

unsigned	int	g_ExplosionSE;

void	EXPLOSION::Update()
{
	//�ύX==============================================================================================================
	if (use == true)
	{
		if (animationOver == true)
		{
			use = false;
		}
	}

}

void	EXPLOSION::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	animationOver = false;

	source = NONE;

	animTimer = 0.0f;
	animTimeMax = 13.0f;
	animOneFlameTime = 0.5f;

	animFlame_W = 5;
	animFlame_H = 3;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/explosion.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(-100, -100);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size * 1 / 2;				//	�����蔻��̃T�C�Y
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void	EXPLOSION::Reset()
{

}






//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================

/*==================================
	�O���E���h������
====================================*/
void	InitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Init();
		Explosion[i].Prepare();
	}

	g_ExplosionSE = LoadSound((char*)"data/SE/explosion.wav");
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Update();
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Draw();
	}


}

void SetExplosion(D3DXVECTOR2 new_pos, D3DXVECTOR2 new_size, EXPLOSION::SOURCE sourceValue)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (Explosion[i].GetUse() == false)
		{
			Explosion[i].SetUse(true);
			Explosion[i].SetSource(sourceValue);
			Explosion[i].SetPosi(new_pos);
			Explosion[i].SetSize(new_size);
			Explosion[i].SetCollisionSize(new_size * 3 / 4);
			Explosion[i].SetAnimation(true);
			Explosion[i].SetAnimTimer(0.0f);
			Explosion[i].SetAnimationOver(false);

			PlaySound(g_ExplosionSE, 0);

			return;
		}
	}
	

}


/*==================================
	�O���E���h�擾
====================================*/

EXPLOSION*	GetExplosion()
{
	return	&Explosion[0];
}