#include "StickyBomb.h"
#include "Explosion.h"

STICKYBOMB	g_StickyBomb[STICKYBOMB_MAX];

void	STICKYBOMB::Update()
{
	if (use)
	{
		//�ύX==============================================================================================================
		counter += 1;

		if (counter % ExplosionTimeMax == 0)
		{
			counter = 0;
			SetExplosion(pos, D3DXVECTOR2(size.x * 2, size.x * 2), EXPLOSION::PLAYER);
			use = false;
			follower = nullptr;
		}

		if (animation)
		{
			if (animationOver)	animationOver = false;
		}
		else
		{
			if (counter >= ExplosionTimeMax / 2)	animation = true;
		}

		if (follower != nullptr)
		{
			pos = follower->GetPosi();

			if (follower->GetPosi().x + size.x < 0 || follower->GetPosi().x - size.x > SCREEN_WIDTH ||
				follower->GetPosi().y + size.y < 0 || follower->GetPosi().y - size.y > SCREEN_HEIGHT)	use = false;

			if (!(follower->GetUse()))	use = false;
		}

	}
}

void	STICKYBOMB::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	animationOver = false;

	animTimer = 0.0f;
	animTimeMax = 2.0f;
	animOneFlameTime = 0.1f;

	animFlame_W = 2;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/sticky_bomb.png");				//	LoadTexture�̖߂�l���L�^����ϐ�


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y

	follower = nullptr;

	counter = 0;

	//SetStickyBomb(pos, size);
}

void	STICKYBOMB::Reset()
{

}






//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================

/*==================================
	�O���E���h������
====================================*/
void	InitStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		g_StickyBomb[i].Init();
		g_StickyBomb[i].Prepare();
	}
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		g_StickyBomb[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == true) { g_StickyBomb[i].Update(); }
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == true) { g_StickyBomb[i].Draw(); }
	}


}

void	SetStickyBomb(D3DXVECTOR2 new_pos, ENEMY*	stickEnemy, float angle)
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse())
		{
			if (g_StickyBomb[i].GetFollower() != nullptr)
			{
				if (g_StickyBomb[i].GetFollower() == stickEnemy)	return;
			}
		}
	}

	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == false)
		{
			g_StickyBomb[i].SetUse(true);
			g_StickyBomb[i].SetPosi(new_pos);
			g_StickyBomb[i].SetAngle(angle);
			g_StickyBomb[i].follower = stickEnemy;
			g_StickyBomb[i].SetCounter(0);
			g_StickyBomb[i].SetAnimation(false);
			g_StickyBomb[i].SetAnimationOver(false);

			return;
		}
	}
}


/*==================================
	�O���E���h�擾
====================================*/

STICKYBOMB*	GetStickyBomb()
{
	return	&g_StickyBomb[0];
}