
#include	"StageGimmick.h"
#include	"player.h"
#include	"collision.h"
#include	"ground.h"
#include	"Ball.h"
#include	"Explosion.h"
#include	"InterlockArrangement.h"
#include	"Waiver.h"

PLAYER*			sg_player;
GROUND*			sg_ground;
BALL*			sg_ball;
EXPLOSION*		sg_explosion;
INTERLOCKARRANGEMENT*	sg_inter;

STAGEGIMMICK		StageGimmick[STAGEGIMMICK_MAX];

unsigned	int	g_StealBlock;

int	breakCount;

//===============================================================================================================================================
//	�O���E���h�N���X�v���O����
//===============================================================================================================================================
void	STAGEGIMMICK::Update()
{
	if (use)
	{
		//BreakableBlock
		if (block_type == BREAK || block_type == BREAK_LARGE)
		{
			if (sg_ball->GetUse() && sg_ball->GetCollisionBool() && sg_ball->GetAbilityAttack() == BALL::EXPLOSION)
			{
				if (GetCollision(sg_ball->GetPosi() + sg_ball->GetCollisionPos(), sg_ball->GetBefPosi() + sg_ball->GetCollisionPos(),
					sg_ball->GetCollisionSize(), pos + collisionLocalPos, D3DXVECTOR2(size.x + BASE_SIZE * 2, size.y + BASE_SIZE * 2)))
				{
					SetExplosion(sg_ball->GetPosi(), D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE * 5), EXPLOSION::PLAYER);
				}
			}

			for (int i = 0; i < EXPLOSION_MAX; i++)
			{
				if (sg_explosion[i].GetUse() && sg_explosion[i].GetCollisionBool())
				{
					if (GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize,
						sg_explosion[i].GetPosi() + sg_explosion[i].GetCollisionPos(), sg_explosion[i].GetCollisionSize()))
					{
						use = false;

						breakCount++;
						if (breakCount % 2 == 0)
						{
							PlaySound(g_GimmickSE[BREAK], 0);
							breakCount = 0;
						}
						else
						{
							PlaySound(g_GimmickSE[BREAK_LARGE], 0);
						}
					}
				}
			}
		}

		//MovingFloor
		else if (block_type == MOVE)
		{
			if (pos.x - size.x / 2 < from || pos.x + size.x / 2 > to)
			{
				moveDirection *= -1;
			}
			for (int i = 0; i < GROUND_MAX; i++)
			{
				if (sg_ground[i].GetUse() && sg_ground[i].GetCollisionBool())
				{
					if (GetCollision(sg_ground[i].GetPosi(), sg_ground[i].GetPosi(), sg_ground[i].GetSize(), pos, size))
					{
						moveDirection *= -1;
					}
				}
			}
			/*for (int i = 0; i < STAGEGIMMICK_MAX; i++)
			{
				if (StageGimmick[i].GetUse() && StageGimmick[i].GetCollisionBool() && pos != StageGimmick[i].GetPosi())
				{
					if (GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize,
						StageGimmick[i].GetPosi(), StageGimmick[i].GetCollisionSize()))
					{
						moveDirection *= -1;
					}
				}
			}*/
			for (int i = 0; i < INTERLOCKARRANGEMENT_MAX; i++)
			{
				if (sg_inter[i].GetUse() && sg_inter[i].GetCollisionBool() && !sg_inter[i].GetOn_Off_InterlockArrangement())
				{
					if (GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize,
						sg_inter[i].GetPosi(), sg_inter[i].GetCollisionSize()))
					{
						moveDirection *= -1;
					}
				}
			}
			move = D3DXVECTOR2(moveDirection * 2, 0);
			if (OnPlayer == true)
			{
				/*mf_Player->SetPosi(D3DXVECTOR2(pos.x+mf_Player->GetMove().x, pos.y - size.y / 2 -mf_Player->GetSize().y/2));*/
				sg_player->SetMove(sg_player->GetMove() + move);
			}
			Move();
		}
		//Needle
		else if (block_type == NEEDLE)
		{
			if (gravity)
			{
				if (pos.y >= pos_bef.y + fallSerColSize.y)	use = false;

				Gravity();
				Move();
			}
			else
			{
				if (GetCollision(sg_player->GetPosi() + sg_player->GetCollisionPos(), sg_player->GetBefPosi() + sg_player->GetCollisionPos(),
					sg_player->GetCollisionSize(), D3DXVECTOR2(pos.x, pos.y + fallSerColSize.y / 2 + BASE_SIZE / 2), fallSerColSize))
				{
					gravity = true;
				}
			}

			if (GetCollision(sg_player->GetPosi() + sg_player->GetCollisionPos(), sg_player->GetPosi() + sg_player->GetCollisionPos(),
				sg_player->GetCollisionSize(), pos + collisionLocalPos, collisionSize) || playerHit)	sg_player->SetUse(false);
		}
		//ShinuYuka
		else if (block_type == DIE)
		{
			if (playerHit == true)
			{
				sg_player->SetUse(false);
			}
		}

		//VulnerableBlock
		else if (block_type == FALL)
		{
			if (OnPlayer == true) { starter = true; }

			if(starter == true)
			{
				counter += 1;
				if (counter % (60 / 2) == 0)
				{
					move.y = 2;
					counter = 0;
				}
				if (pos.y - size.y >= SCREEN_HEIGHT && move.y > 0)
				{
					use = false;
					move.y = 0;
					counter = 0;
				}
			}
			Move();
		}
		else if (block_type == STEAL)
		{
			if (sg_player->GetUse() && sg_player->GetCollisionBool())
			{
				if (GetCollision(sg_player->GetPosi() + sg_player->GetCollisionPos(), sg_player->GetBefPosi() + sg_player->GetCollisionPos(),
					sg_player->GetCollisionSize(), pos + collisionLocalPos, collisionSize))
				{
					if (sg_ball->GetAbilityAttack() == BALL::EXPLOSION)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::EXPLOSION, BALL::NONE_BALL, BALL::NONE_PLAYER);
					}
					if (sg_ball->GetAbilityAttack() == BALL::STICKY)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::STICKY, BALL::NONE_BALL, BALL::NONE_PLAYER);
					}
					if (sg_ball->GetAbilityMoveBall() == BALL::HOMING)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::NONE_ATTACK, BALL::HOMING, BALL::NONE_PLAYER);
					}
					if (sg_ball->GetAbilityMoveBall() == BALL::BOUNCE)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::NONE_ATTACK, BALL::BOUNCE, BALL::NONE_PLAYER);
					}
					if (sg_ball->GetAbilityMovePlayer() == BALL::SPRING)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::NONE_ATTACK, BALL::NONE_BALL, BALL::SPRING);
					}
					if (sg_ball->GetAbilityMovePlayer() == BALL::TRACE)
					{
						SetWaiver(sg_player->GetPosi(), D3DXVECTOR2(-sg_player->GetWayX(), -1), BALL::NONE_ATTACK, BALL::NONE_BALL, BALL::TRACE);
					}

					sg_ball->SetAbilityAttack(BALL::NONE_ATTACK);
					sg_ball->SetAbilityMoveBall(BALL::NONE_BALL);
					sg_ball->SetAbilityMovePlayer(BALL::NONE_PLAYER);
				}
			}
		}
		//WinningBlock
		else if (block_type == WIN)
		{
			if (GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize, sg_player->GetPosi() + sg_player->GetCollisionPos(),
				sg_player->GetCollisionSize()))
			{
				sg_player->SetControl(false);
				sg_player->SetMove(D3DXVECTOR2(0, 0));
				//sg_player->SetTexNo(PLAYER::Stand_R);

				winCondition = true;
				SetClearBool(true);
			}
		}
	}
	else if (ActiveInEmpty)
	{
		//	Needle
		if (block_type == NEEDLE)
		{
			counter++;
			if (counter >= 60 * 2)
			{
				use = true;
				gravity = false;
				pos = pos_bef;
				counter = 0;
				move = D3DXVECTOR2(0, 0);
			}
		}
		//VulnerableBlockAfterDeath
		if (block_type == FALL)
		{
			counter += 1;
			if (counter == 120 && starter)
			{
				use = true;
				pos = pos_bef;
				counter = 0;
				starter = false;
			}
		}
	}
}


void	STAGEGIMMICK::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	ActiveInEmpty = false;

	MoveX = true;
	MoveY = true;
	starter = false;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	move_type = Normal;


	animTimeMax = 1;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	texNo = LoadTexture((char*)"data/texture/BreakBlock_test.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	TexNums[BREAK] = LoadTexture((char*)"data/texture/BreakBlock_test.png");
	TexNums[BREAK_LARGE] = LoadTexture((char*)"data/texture/BreakBlock_test.png");
	TexNums[MOVE] = LoadTexture((char*)"data/texture/moveBlock.png");
	TexNums[NEEDLE] = LoadTexture((char*)"data/texture/fall_needle.png");
	TexNums[DIE] = LoadTexture((char*)"data/texture/damage_floor.png");
	TexNums[FALL] = LoadTexture((char*)"data/texture/fallBlock.png");
	TexNums[STEAL] = LoadTexture((char*)"data/texture/steal_lazer.png");
	TexNums[WIN] = LoadTexture((char*)"data/texture/goal.png");

	g_StealBlock = LoadTexture((char*)"data/texture/steal_block.png");

	g_GimmickSE[BREAK] = LoadSound((char*)"data/SE/BreakBlock_SE.wav");
	g_GimmickSE[BREAK_LARGE] = LoadSound((char*)"data/SE/BreakBlock_SE2.wav");

	pos = D3DXVECTOR2(-100, -100);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	pos_bef = D3DXVECTOR2(-100, -100);
	size = D3DXVECTOR2(40.0f, 40.0f);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y
	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	sg_player = GetPlayer();
	sg_ground = GetGround();
	sg_ball = GetBall();
	sg_explosion = GetExplosion();
	sg_inter = GetInterlockArrangement();

	breakCount = 0;
}





void	STAGEGIMMICK::Reset()
{

}

void	STAGEGIMMICK::SetBlock(D3DXVECTOR2 new_pos, D3DXVECTOR2	new_size, const	BLOCK_TYPE&	new_BlockType)
{
	use = true;		//�g�p�t���O��true��
	active = true;
	gravity = false;
	collisionBool = true;
	playerHit = false;
	ActiveInEmpty = false;

	pos = new_pos;	//���W���Z�b�g
	actionFirstPos = new_pos;	//���ˍ��W��ۑ�
	SetSize(new_size);
	collisionSize = new_size;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	move = D3DXVECTOR2(0, 0);

	speed = r_speed;
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pos_bef = new_pos;

	block_type = new_BlockType;

	texNo = TexNums[block_type];

	if (block_type == BREAK)
	{
		breakHit = false;
		texNo = TexNums[BREAK];
	}
	else if (block_type == BREAK_LARGE)
	{
		texNo = TexNums[BREAK_LARGE];
		breakHit = false;

		size = new_size * BASE_SIZE;
		collisionSize = new_size * BASE_SIZE;

		/*texSize_W = new_size.x;
		texSize_H = new_size.y;*/
	}
	else if (block_type == MOVE)
	{
		texNo = TexNums[MOVE];
		moveDirection = 1;
		from = 0.0f;
		to = SCREEN_WIDTH;
		OnPlayer = false;
	}
	else if (block_type == NEEDLE)
	{
		ActiveInEmpty = true;

		counter = 0;
		texNo = TexNums[NEEDLE];

		pos = D3DXVECTOR2((new_pos.x + 0.5f) * BASE_SIZE, (new_pos.y + 0.5f) * BASE_SIZE);
		pos_bef = D3DXVECTOR2((new_pos.x + 0.5f) * BASE_SIZE, (new_pos.y + 0.5f) * BASE_SIZE);
		actionFirstPos = D3DXVECTOR2((new_pos.x + 0.5f) * BASE_SIZE, (new_pos.y + 0.5f) * BASE_SIZE);

		fallSerColSize = D3DXVECTOR2(1, 0);
		for (int i = new_pos.y + 1; i < STAGE_HEIGHT_MAX; i++)
		{
			if (GetStageChar(GetCurrentStageNum(), new_pos.x, i) != ' ')	break;

			fallSerColSize.y++;
		}
		fallSerColSize *= BASE_SIZE;
	}
	else if (block_type == DIE)
	{
		texNo = TexNums[DIE];

		size = new_size * BASE_SIZE;
		collisionSize = new_size * BASE_SIZE;

		texSize_W = new_size.x;
		texSize_H = new_size.y;
	}
	else if (block_type == FALL)
	{
		ActiveInEmpty = true;
		texNo = TexNums[FALL];
		starter = false;
		counter = 0;
	}
	else if (block_type == STEAL)
	{
		texNo = TexNums[STEAL];
		collisionBool = false;

		size = new_size * BASE_SIZE;
		collisionSize = new_size * BASE_SIZE;

		texSize_W = new_size.x;
		texSize_H = new_size.y;
	}
	else if (block_type == WIN)
	{
		size = D3DXVECTOR2(2 * BASE_SIZE, 3 * BASE_SIZE);
		pos.y -= BASE_SIZE;
		collisionBool = false;

		texNo = TexNums[WIN];
		winCondition = false;
	}
}

//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================

/*==================================
	�O���E���h������
====================================*/
void	InitStageGimmick()
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		StageGimmick[i].Init();
		StageGimmick[i].Prepare();
	}
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitStageGimmick()
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		StageGimmick[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateStageGimmick()
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		StageGimmick[i].Update();
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawStageGimmick()
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		StageGimmick[i].Draw();

		if (StageGimmick[i].block_type == STAGEGIMMICK::STEAL && StageGimmick[i].GetUse())
		{
			// �e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StealBlock));

			//	�|���S���z�u
			DrawSpriteColorRotate(StageGimmick[i].GetPosi().x, StageGimmick[i].GetPosi().y - (StageGimmick[i].GetSize().y - BASE_SIZE) / 2,
				StageGimmick[i].GetSize().x, BASE_SIZE, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, StageGimmick[i].GetTexSizeWidth(), 1, 0);
		}
	}
}

void	SetStageGimmicks(const D3DXVECTOR2& pos, const	D3DXVECTOR2& size, STAGEGIMMICK::BLOCK_TYPE type)	//	����̃Z�b�g
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		if (StageGimmick[i].GetUse() == false)
		{
			StageGimmick[i].SetBlock(pos, size, type);
			break;
		}
	}
}


/*==================================
	�O���E���h�擾
====================================*/
STAGEGIMMICK*	GetStageGimmick()
{
	return	&StageGimmick[0];
}

bool GetWin()
{
	for (int i = 0; i < STAGEGIMMICK_MAX; i++)
	{
		if (StageGimmick[i].GetUse() == true)
		{
			if (StageGimmick[i].block_type == STAGEGIMMICK::WIN)
			{
				if (StageGimmick[i].GetWinCondition() == true)
				{
					return true;
				}
			}
		}
	}

	return false;
}