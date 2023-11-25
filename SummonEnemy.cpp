
#include	"SummonEnemy.h"
#include	"collision.h"
#include	"player.h"

ENEMY* Su_enemy;
PLAYER* Su_player;

void SUMMONENEMY::Update()
{
	if (use && pos.x < SCREEN_WIDTH && pos.x > 0)
	{
		bool	exitBool = false;
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (Su_enemy[i].GetUse() == true) 
			{

				Su_collision_es = (Su_enemy[i].GetPosi().x - pos.x) * (Su_enemy[i].GetPosi().x - pos.x) + (Su_enemy[i].GetPosi().y - pos.y) * (Su_enemy[i].GetPosi().y - pos.y);
				//Su_collision_es = (Su_enemy->GetPosi().x - pos.x) * (Su_enemy->GetPosi().x - pos.x) + (Su_enemy->GetPosi().y - pos.y) * (Su_enemy->GetPosi().y - pos.y);
				Su_collision_ps = (Su_player->GetPosi().x - pos.x) * (Su_player->GetPosi().x - pos.x) + (Su_player->GetPosi().y - pos.y) * (Su_player->GetPosi().y - pos.y);

				if (Su_collision_es < powf((float)BASE_SIZE * 2.5, 2) ||
					Su_collision_ps < powf((float)BASE_SIZE * 2.5, 2)
					/*�͈͓��ɏo������G������ ||
					�͈͓��Ƀv���C���[������*/)
				{
					//color = D3DXCOLOR(0, 1, 0, 1);
					e_Summon_count = 0; //�J�E���g���Z�b�g
				}
				
				if (onlyOneEnemy != nullptr)
				{
					if (onlyOneEnemy == &(Su_enemy[i]))	exitBool = true;
				}
				
				/*
				if (Su_enemy[i].GetEnemyTyep() == ENEMY::Trace && enemyType == ENEMY::Trace ||
					Su_enemy[i].GetEnemyTyep() == ENEMY::Homing && enemyType == ENEMY::Homing)	e_Summon_count = 0;*/
			}
		}
		if (exitBool)	e_Summon_count = 0;
		else			onlyOneEnemy = nullptr;

		e_Summon_count += 1;
		if (e_Summon_count >= 60 * 5)
		{
			if (enemyType == ENEMY::Homing && onlyOneEnemy == nullptr)
			{
				//�G���o��
				SetEnemys(D3DXVECTOR2(pos.x, pos.y - BASE_SIZE / 2), D3DXVECTOR2(-1, -1), enemyType);
				e_Summon_count = 0;

				for (int i = 0; Su_enemy[i].GetUse(); i++)
				{
					onlyOneEnemy = &(Su_enemy[i]);
				}
			}
			else
			{
				//�G���o��
				SetEnemys(pos, D3DXVECTOR2(-1, -1), enemyType);
				e_Summon_count = 0;

				if (enemyType == ENEMY::Trace && onlyOneEnemy == nullptr)
				{
					for (int i = 0; Su_enemy[i].GetUse(); i++)
					{
						onlyOneEnemy = &(Su_enemy[i]);
					}
				}
			}
		}

	}
}

void SUMMONENEMY::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	MoveX = true;
	MoveY = true;

	ArrivePoint = false;

	texNo = LoadTexture((char*)"data/texture/SummonEnemy.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	e_Summon_count = 0;		//�J�E���g�̃��Z�b�g


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size;				//	�����蔻��̃T�C�Y
	
	move = D3DXVECTOR2(0, 0);		//�ړ��������Z�b�g

	onlyOneEnemy = nullptr;

	//SetSummonEnemys(pos,move);
}

void SUMMONENEMY::Reset()
{
}


void SUMMONENEMY::SetSummonEnemy(D3DXVECTOR2 ss_pos, const	ENEMY::ENEMY_TYPE&	EnemyType)
{
	use = true;		//�g�p�t���O��true��
	pos = ss_pos;	//���W���Z�b�g

	onGround = false;
	collisionBool = true;

	enemyType = EnemyType;

	Su_collision_es = 0;
	Su_collision_ps = 0;
	e_Summon_count = 0;

	//												�X�e�[�W�L��
	//Bound,			�o�E���h�G�l�~�[			b
	//Homing,			�z�[�~���O�G�l�~�[			h
	//Explosion,		�����G�l�~�[				e
	//Sticky,			�X�e�B�b�L�[���e�G�l�~�[	s
	//Trace,			�Ǐ]�G�l�~�[				t
	//Spring,			�o�l�G�l�~�[				p

	switch (EnemyType)
	{
	case	ENEMY::Bound:	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Homing:	color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Explosion:	color = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case	ENEMY::Sticky:	color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Trace:	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case	ENEMY::Spring:	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}

//==============================================================================================================================
//	�G�l�~�[�����u���b�N�Ǘ��v���O����
//==============================================================================================================================
SUMMONENEMY	summon_enemy[SUMMON_MAX];

/*==================================
	�G�l�~�[�����u���b�N������
====================================*/
void	InitSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Init();
		summon_enemy[i].Prepare();
	}

	Su_enemy = GetEnemy();
	Su_player = GetPlayer();
}

/*==================================
	�G�l�~�[�����u���b�N�I������
====================================*/
void	UninitSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Uninit();
	}
}

/*==================================
	�G�l�~�[�����u���b�N�X�V����
====================================*/
void	UpdateSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Update();
	}
}

/*==================================
	�G�l�~�[�����u���b�N�`�揈��
====================================*/
void	DrawSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Draw();
	}
}

/*==================================
	�G�l�~�[�����u���b�N�̃Z�b�g
====================================*/
void	SetSummonEnemys(D3DXVECTOR2 s_pos, const	ENEMY::ENEMY_TYPE&	EnemyType)	//	�G�l�~�[�̃Z�b�g
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		if (!summon_enemy[i].GetUse())
		{
			summon_enemy[i].SetSummonEnemy(s_pos, EnemyType);
			break;
		}
	}
}

/*==================================
	�G�l�~�[�����u���b�N�擾
====================================*/
SUMMONENEMY* GetSummonEnemy()
{
	return	summon_enemy;
}
