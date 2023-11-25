
#include	"enemyStickyBomb.h"
#include	"Explosion.h"
#include	"player.h"

#include	"collision.h"

PLAYER*	enemy_sticky_bomb_player;

void	ENEMY_STICKY_BOMB::Update()	//	������
{
	if (use)
	{
		pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		if (pos.y + size.y > SCREEN_HEIGHT)	use = false;

		if (onGround)
		{
			timer++;

			if (timer >= ExpTimeOnGround)
			{
				use = false;
				timer = 0;
				SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 6), EXPLOSION::ENEMY);
			}
		}

		if (GetCollision(enemy_sticky_bomb_player->GetPosi() + enemy_sticky_bomb_player->GetCollisionPos(),
			enemy_sticky_bomb_player->GetBefPosi() + enemy_sticky_bomb_player->GetCollisionPos(), enemy_sticky_bomb_player->GetCollisionSize(),
			pos + collisionLocalPos, collisionSize))
		{
			use = false;
			SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 6), EXPLOSION::ENEMY);
		}

		Gravity();
		Move();
	}
}

void	ENEMY_STICKY_BOMB::Prepare()	//	��������
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = true;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	MoveX = false;
	MoveY = true;

	ArrivePoint = false;

	texNo = LoadTexture((char*)"data/texture/enemy_sticky_bomb.png");

	animTimeMax = 1;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size * 4 / 5;				//	�����蔻��̃T�C�Y

	move = D3DXVECTOR2(0, 0);

	gravityNum = 0.2f;
}

void	ENEMY_STICKY_BOMB::Reset()	//	���Z�b�g����
{

}

//============================================================
//	�X�e�B�b�L�[���e�G�l�~�[�̃X�e�B�b�L�[���e����v���O����
//============================================================
ENEMY_STICKY_BOMB	enemy_sticky_bomb[ENEMY_STICKY_BOMB_MAX];

void	InitEnemyStickyBomb()	//	�X�e�B�b�L�[���e������
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Init();
		enemy_sticky_bomb[i].Prepare();
	}

	enemy_sticky_bomb_player = GetPlayer();
}

void	UninitEnemyStickyBomb()	//	�X�e�B�b�L�[���e�I������
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Uninit();
	}
}

void	UpdateEnemyStickyBomb()	//	�X�e�B�b�L�[���e�X�V����
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Update();
	}
}

void	DrawEnemyStickyBomb()		//	�X�e�B�b�L�[���e�`�揈��
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		enemy_sticky_bomb[i].Draw();
	}
}

void	SetEnemyStickyBomb(const	D3DXVECTOR2	pos)
{
	for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
	{
		if (!enemy_sticky_bomb[i].GetUse())
		{
			enemy_sticky_bomb[i].SetUse(true);
			enemy_sticky_bomb[i].SetOnGround(false);
			enemy_sticky_bomb[i].SetPosi(pos);
			enemy_sticky_bomb[i].SetMove(D3DXVECTOR2(0, 0));
			enemy_sticky_bomb[i].SetTime(0);

			break;
		}
	}
}

ENEMY_STICKY_BOMB*	GetEnemyStickyBomb(void)
{
	return	enemy_sticky_bomb;
}












