#include "Spring.h"
#include "Explosion.h"
#include "Ball.h"

SPRING	g_Spring[SPRING_MAX];
BALL* spring_ball;

void	SPRING::Update()
{
	if (use == true)
	{
		timer++;

		if (timer >= DeleteTime && !OnSpring)	use = false;

		if (OnSpring)
		{
			if (animation)
			{
				if (animationOver)
				{
					animation = false;
					animationNo_W = animTimeMax - 1;
				}
			}
			else
			{
				if (animationOver)
				{
					if (timer > 60 / 2)
					{
						use = false;
						animationOver = false;
						animation = false;
						OnSpring = false;

						animationNo_W = 0.0f;
						timer = 0;
					}
				}
				else
				{
					animation = true;
					timer = 0;
				}
			}
		}
	}
}

void	SPRING::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	animationOver = false;

	animTimer = 0.0f;
	animTimeMax = 3.0f;
	animOneFlameTime = 0.5f;

	timer = 0;

	animFlame_W = 3;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/springBox.png");				//	LoadTexture�̖߂�l���L�^����ϐ�
	g_SpringSE = LoadSound((char*)"data/SE/spring_SE.wav");

	pos = D3DXVECTOR2(-100, -100);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 3);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);				//	�����蔻��̃T�C�Y
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	spring_ball = GetBall();
}

void	SPRING::Reset()
{

}






//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================

/*==================================
	�O���E���h������
====================================*/
void	InitSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Init();
		g_Spring[i].Prepare();
	}
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Update();
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Draw();
	}


}

void	SetSpring(D3DXVECTOR2 new_pos)
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		if (g_Spring[i].GetUse() == false)
		{
			g_Spring[i].SetUse(true);
			g_Spring[i].SetOnSpring(false);
			g_Spring[i].SetAnimation(false);
			g_Spring[i].SetAnimationOver(false);
			g_Spring[i].SetPosi(new_pos);
			g_Spring[i].SetTimer(0);

			break;
		}
	}


}


/*==================================
	�O���E���h�擾
====================================*/

SPRING*	GetSpring()
{
	return	&g_Spring[0];
}