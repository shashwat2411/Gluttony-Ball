
#include	"explosionTile.h"
#include	"Explosion.h"

EXPLOSIONTILE	explosionTile[EXPLOSIONTILE_MAX];
//===============================================================================================================================================
//	�O���E���h�N���X�v���O����
//===============================================================================================================================================
void	EXPLOSIONTILE::Update()
{
	if (use)
	{

	}
}


void	EXPLOSIONTILE::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	BallCollide = false;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/ground_Test.png");				//	LoadTexture�̖߂�l���L�^����ϐ�
	

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(40.0f, 40.0f);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y
	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

}





void	EXPLOSIONTILE::Reset()
{

}



//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================

/*==================================
	�O���E���h������
====================================*/
void	InitExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		explosionTile[i].Init();
		explosionTile[i].Prepare();
	}
	
	//explosionTile[1].SetUse(true);
	//explosionTile[2].SetUse(true);
	//explosionTile[3].SetUse(true);

	//explosionTile[1].SetPosi(D3DXVECTOR2(200, SCREEN_HEIGHT / 4 * 3));
	//explosionTile[2].SetPosi(D3DXVECTOR2(SCREEN_WIDTH - 200, SCREEN_HEIGHT / 4 * 3));
	//explosionTile[3].SetPosi(D3DXVECTOR2(SCREEN_WIDTH / 2, 120));

	//explosionTile[3].SetSize(D3DXVECTOR2(SCREEN_WIDTH, BASE_SIZE * 2));
	//explosionTile[3].SetCollisionSize(explosionTile[3].GetSize());
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		explosionTile[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{//�ύX===========================================================================
		if (explosionTile[i].GetBallCollide() == true)
		{
			explosionTile[i].SetUse(false);
			explosionTile[i].SetBallCollide(false);
		}
		if (explosionTile[i].GetUse() == true) { explosionTile[i].Update(); }
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawExplosionTile()
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		if (explosionTile[i].GetUse() == true) { explosionTile[i].Draw(); }
	}


}

void	SetExplosionTile(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size)	//	����̃Z�b�g
{
	for (int i = 0; i < EXPLOSIONTILE_MAX; i++)
	{
		if (!explosionTile[i].GetUse())
		{
			explosionTile[i].SetUse(true);
			explosionTile[i].SetPosi(pos);
			explosionTile[i].SetSize(size);
			explosionTile[i].SetCollisionSize(size);

			//ground[i].SetPosi(D3DXVECTOR2(ground[i].GetPosi().x, (pos.y - ground_Player->GetStagePos().y) + ground_Player->GetPosi().y));

			break;
		}
	}
}


/*==================================
	�O���E���h�擾
====================================*/
EXPLOSIONTILE*	GetExplosionTile()
{
	return	explosionTile;
}
