
#include	"bullet.h"
#include	"player.h"
#include	"Explosion.h"

PLAYER*		bullet_player;

unsigned	int	g_BulletSE;

void	BULLET::Update()
{
	if (use)
	{
		pos_bef = pos;

		point = bullet_player->GetPosi();

		angle = VecToAng(D3DXVECTOR2(0, -1), point - pos) * 2;

		timer++;
		if (timer > TimeMax || (point.x - pos.x) * (point.x - pos.x) + (point.y - pos.y) * (point.y - pos.y) < TouchDis * TouchDis)
		{
			use = false;
			timer = 0;
			SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2), EXPLOSION::ENEMY);
		}

		Move();
	}
}

void	BULLET::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	ArrivePoint = false;

	MoveX = true;
	MoveY = true;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/bullet.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(0, 0);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 2);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(BASE_SIZE * 3 / 2, BASE_SIZE * 3 / 2);				//	�����蔻��̃T�C�Y

	speed = bullet_player->GetSpeed() - 1;
	r_speed = speed;

	move_type = Point;
}

void	BULLET::Reset()
{

}


//=========================================================================================
//	�o���b�g�Ǘ��v���O����
//=========================================================================================
BULLET	bullet[BULLET_MAX];

void	InitBullet()	//	�o���b�g������
{
	bullet_player = GetPlayer();
	g_BulletSE = LoadSound((char*)"data/SE/shoot_bullet_SE.wav");

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Init();
		bullet[i].Prepare();
	}
}

void	UninitBullet()	//	�o���b�g�I������
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Uninit();
	}
}

void	UpdateBullet()	//	�o���b�g�X�V����
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Update();
	}
}

void	DrawBullet()	//	�o���b�g�`�揈��
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].Draw();
	}
}

void	SetBullet(const	D3DXVECTOR2&	pos)	//	�o���b�g�̃Z�b�g
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullet[i].GetUse())
		{
			bullet[i].SetUse(true);
			bullet[i].SetPosi(pos);
			PlaySound(g_BulletSE, 0);
			SetVolume(g_BulletSE, 0.7f);

			break;
		}
	}
}


BULLET*	GetBullet()	//	�o���b�g�̎擾
{
	return	bullet;
}
















