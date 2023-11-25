
#include	"Enemy.h"
#include	"player.h"

#include	"Explosion.h"
#include	"bullet.h"
#include	"enemyStickyBomb.h"
#include	"knife.h"

PLAYER*	e_player;

const	D3DXVECTOR2	knifeWay[8] = { D3DXVECTOR2(0, -1),D3DXVECTOR2(-1, -1), D3DXVECTOR2(-1, 0),
D3DXVECTOR2(-1, 1),D3DXVECTOR2(0, 1),D3DXVECTOR2(1, 1), 
D3DXVECTOR2(1, 0), D3DXVECTOR2(1, -1) };

//==============================================================================================================================
//	�{�[���N���X�v���O����
//==============================================================================================================================
void	ENEMY::Update()
{
	if (use)
	{
		if ((pos.x < 0 || SCREEN_WIDTH < pos.x) || (pos.y < 0 || pos.y > SCREEN_HEIGHT))
		{
			use = false;
		}


		if (!onWall)	pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		//=============================================================
		//	�o�E���h�G�l�~�[�̈ړ��J�n�A�I������
		if (enemy_type == Bound)
		{
			if (boundCount > boundMax && active)
			{
				if (angle == 0)
				{
					if (move.x > 0)	animation_type = bound_stand_R;
					if (move.x < 0)	animation_type = bound_stand_L;
				}
				else if (angle == 180)
				{
					if (move.x > 0)	animation_type = bound_stand_L;
					if (move.x < 0)	animation_type = bound_stand_R;
				}
				else if (angle == 90)
				{
					if (move.y > 0)	animation_type = bound_stand_R;
					if (move.y < 0)	animation_type = bound_stand_L;
				}
				else if (angle == 270)
				{
					if (move.y > 0)	animation_type = bound_stand_L;
					if (move.y < 0)	animation_type = bound_stand_R;
				}

				active = false;
				texNo = TexNums[animation_type];
				animOneFlameTime = 0.1f;
				animTimer = 0.0f;
			}
			else if (!active)
			{
				timer++;

				if (timer >= BoundStayTime && animationOver)
				{
					timer = 0;
					boundCount = 0;
					active = true;
					animationOver = false;

					if (animation_type == bound_stand_R)	animation_type = bound_move_R;
					if (animation_type == bound_stand_L)	animation_type = bound_move_L;
					
					texNo = TexNums[animation_type];
					animOneFlameTime = 1.0f;
					angle = 0;
				}
			}
		}
		//=============================================================
		//	�z�[�~���O�G�l�~�[�̃o���b�g���ː���
		else if (enemy_type == Homing && pos.x < SCREEN_WIDTH && pos.x > 0)
		{
			timer++;

			if (timer > HomingShootTime)
			{
				timer = 0;
				SetBullet(pos);
			}
		}
		//=============================================================
		//	�X�e�B�b�L�[���e�G�l�~�[�̐���
		else if (enemy_type == Sticky)
		{
			timer++;

			if (timer > UseStickyBombTime)
			{
				timer = 0;
				SetEnemyStickyBomb(pos);
			}

			if (ArrivePoint)
			{
				if (point.x - actionFirstPos.x > 0)	point.x = actionFirstPos.x - FlyingMoveX;
				else if (point.x - actionFirstPos.x < 0)	point.x = actionFirstPos.x + FlyingMoveX;

				ArrivePoint = false;
			}
		}
		//=============================================================
		//	�Ǐ]�G�l�~�[�̈ړ�����
		else if (enemy_type == Trace)
		{
			if (active)
			{
				if (ArrivePoint)
				{
					for (int i = 0; i < 8; i++)
					{
						SetKnife(pos, knifeWay[i]);
					}

					ArrivePoint = false;
					active = false;
				}
			}
			else
			{
				if ((e_player->GetPosi().x - pos.x) * (e_player->GetPosi().x - pos.x) +
					(e_player->GetPosi().y - pos.y) * (e_player->GetPosi().y - pos.y) < TraceSearchDis * TraceSearchDis)
				{
					timer++;

					DrawTraceBool = true;

					point = e_player->GetPosi();
					point.y -= 10.0f;
					if (timer >= 60)
					{
						timer = 0;

						active = true;
					}
				}
				else if (DrawTraceBool)
				{
					DrawTraceBool = false;

					timer = 0;
				}
			}
		}
		//=============================================================
		//	�����G�l�~�[�̈ړ�����
		else if (enemy_type == Explosion && onGround)
		{
			move.x += ExpAcceleration * (e_player->GetPosi().x - pos.x) / fabs(e_player->GetPosi().x - pos.x);

			if (fabs(move.x) < speed)	move.x = (e_player->GetPosi().x - pos.x) / fabs(e_player->GetPosi().x - pos.x);

			if (animationNo_W == 0 && move.x > 0)	animationNo_W = 1.0f;
			else if (animationNo_W == 1 && move.x < 0)	animationNo_W = 0.0f;

			if ((e_player->GetPosi().x - pos.x) * (e_player->GetPosi().x - pos.x)
				+ (e_player->GetPosi().y - pos.y) * (e_player->GetPosi().y - pos.y) < ExpDis * ExpDis)
			{
				use = false;
				SetExplosion(pos, D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE * 5), EXPLOSION::ENEMY);
			}
		}
		//=============================================================
		//	�o�l�A�j���[�V��������
		else if (enemy_type == Spring)
		{
			if (move.x > 0)	texNo = TexNums[spring_R];
			else if (move.x < 0)	texNo = TexNums[spring_L];

			if (animationOver)
			{
				animationOver = false;
				animation = false;
			}
		}

		Gravity();
		Move();
	}
}

void	ENEMY::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	MoveX = true;
	MoveY = true;

	ArrivePoint = false;

	TexNums[bound_stand_R] = LoadTexture((char*)"data/texture/boundEnemy_stand_R.png");
	TexNums[bound_move_R] = LoadTexture((char*)"data/texture/boundEnemy_move_R.png");
	TexNums[bound_stand_L] = LoadTexture((char*)"data/texture/boundEnemy_stand_L.png");
	TexNums[bound_move_L] = LoadTexture((char*)"data/texture/boundEnemy_move_L.png");

	TexNums[homing] = LoadTexture((char*)"data/texture/homing_enemy.png");
	TexNums[explosion] = LoadTexture((char*)"data/texture/explosionRobo.png");
	TexNums[sticky] = LoadTexture((char*)"data/texture/flying_enemy.png");
	TexNums[trace] = LoadTexture((char*)"data/texture/trace_enemy.png");
	TexNums[spring_R] = LoadTexture((char*)"data/texture/spring_R.png");
	TexNums[spring_L] = LoadTexture((char*)"data/texture/spring_L.png");

	texNo = TexNums[spring_L];

	TraceMarkNum = LoadTexture((char*)"data/texture/target_mark.png");

	g_EnemyBoundSE = LoadSound((char*)"data/SE/boundEnemy_SE.wav");
	g_EnemySpringSE = LoadSound((char*)"data/SE/enemySpring_SE.wav");

	timer = 0;
	boundCount = 0;

	animTimeMax = 5;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 5;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE*2, BASE_SIZE*2);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x * 3 / 4, size.y * 3 / 4);				//	�����蔻��̃T�C�Y

	speed = 5.0f;
	r_speed = speed;//�X�s�[�h���Z�b�g
	move = D3DXVECTOR2(1, -1);		//�ړ��������Z�b�g
	D3DXVec2Normalize(&move, &move);//�x�N�g���̐��K��
	move *= speed;					//�ړ��������v�Z

	//SetEnemy(D3DXVECTOR2(SCREEN_WIDTH / 2-340, SCREEN_HEIGHT / 2), D3DXVECTOR2(1, -1));


}

void	ENEMY::Reset()
{

}

void	ENEMY::DrawTraceMark()	//	�Ǐ]�G�l�~�[�̒Ǐ]�ꏊ�������}�[�J�[��`�悷�鏈��
{
	if (DrawTraceBool && use && enemy_type == Trace)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TraceMarkNum));

		//	�|���S���z�u
		DrawSpriteColorRotate(point.x, point.y, (float)BASE_SIZE * 2.0f, (float)BASE_SIZE * 2.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0, 1.0f, 1.0f, 0.0f);
	}
}

void ENEMY::SetEnemy(D3DXVECTOR2 pos, D3DXVECTOR2	way,	const	ENEMY_TYPE&	EnemyType)
{
	use = true;		//�g�p�t���O��true��
	active = true;
	animation = false;
	SetPosi(pos);	//���W���Z�b�g
	pos_bef = pos;
	actionFirstPos = pos;	//���ˍ��W��ۑ�
	speed = r_speed;
	move_type = Normal;

	MoveY = true;

	animationNo_W = 0;
	animationNo_H = 0.0f;
	angle = 0;

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	//D3DXVec2Normalize(&move, &way);//�x�N�g���̐��K��
	//move *= speed;
	onGround = false;
	collisionBool = true;

	enemy_type = EnemyType;

	if (enemy_type == Bound)
	{
		gravity = false;
		animation = true;

		animTimeMax = 20;		//	animTimer�����̒l�𒴂����0�ɖ߂�
		animOneFlameTime = 1.0f;			//	animTimer�ɉ��Z��������ϐ�

		animFlame_W = 5;
		animFlame_H = 4;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);
		collisionSize = size / 2;
		D3DXVec2Normalize(&move, &way);//�x�N�g���̐��K��
		move *= speed;
		animation_type = bound_move_L;
	}
	else if (enemy_type == Homing)
	{
		animTimeMax = 5;		//	animTimer�����̒l�𒴂����0�ɖ߂�
		animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

		animFlame_W = 1;
		animFlame_H = 1;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 2);
		collisionSize = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 7 / 4);
		collisionLocalPos = D3DXVECTOR2(0, BASE_SIZE / 8);

		gravity = false;
		active = false;
		animation_type = homing;
	}
	else if (enemy_type == Explosion)
	{
		animTimeMax = 5;		//	animTimer�����̒l�𒴂����0�ɖ߂�
		animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

		animFlame_W = 2;
		animFlame_H = 1;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		gravity = true;
		size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 3);
		collisionSize = D3DXVECTOR2(BASE_SIZE * 7 / 4, BASE_SIZE * 5 / 2);
		collisionLocalPos = D3DXVECTOR2(0, BASE_SIZE / 4);

		speed = e_player->GetSpeed() + 1;
		move = D3DXVECTOR2(0, 0);
		animation_type = explosion;
	}
	else if (enemy_type == Sticky)
	{
		animFlame_W = 1;
		animFlame_H = 1;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		gravity = false;
		MoveY = false;
		size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);
		collisionSize = size;

		speed = 2.0f;

		move = D3DXVECTOR2(0, 0);

		move_type = Point;
		point = pos;
		point.x += FlyingMoveX;

		animation_type = sticky;
	}
	else if (enemy_type == Trace)
	{
		animFlame_W = 1;
		animFlame_H = 1;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		gravity = false;
		active = false;

		size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);
		collisionSize = size * 4 / 5;

		speed = e_player->GetRSpeed() - 1;

		move = D3DXVECTOR2(0, 0);

		move_type = Point;

		animation_type = trace;
	}
	else if (enemy_type == Spring)
	{
		animTimeMax = 10;		//	animTimer�����̒l�𒴂����0�ɖ߂�
		animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

		animFlame_W = 5;
		animFlame_H = 2;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		gravity = true;
		size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 2);
		collisionSize = D3DXVECTOR2(BASE_SIZE * 4 / 5, BASE_SIZE);
		collisionLocalPos = D3DXVECTOR2(0, BASE_SIZE / 2);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
		//==============================================================
		//	1�b�łT�}�X��ԏ����x�Əd�͉����x�����߂�v�Z
		//	BASE_SIZE * 5 = gravityNum * 120 * 120 - speed * 120
		//==============================================================
		gravityNum = 0.036f;
		speed = gravityNum * 120 - BASE_SIZE * 5 / 120;

		move = D3DXVECTOR2(((float)BASE_SIZE / 220) * -1, -speed);

		animation_type = spring_L;
	}

	texNo = TexNums[animation_type];
}

void	ENEMY::SetBoundStand(const	COLLISION_WAY&	way)
{
	if (boundCount > boundMax)
	{
		if (way == COLLISION_WAY::Up)
		{
			angle = 0;
			pos.y -= BASE_SIZE / 2;
		}
		if (way == COLLISION_WAY::Down)
		{
			angle = 180;
			pos.y += BASE_SIZE / 2;
		}
		if (way == COLLISION_WAY::Right)
		{
			angle = 90;
			pos.x += BASE_SIZE / 2;
		}
		if (way == COLLISION_WAY::Left)
		{
			angle = 270;
			pos.x -= BASE_SIZE / 2;
		}
	}
}


//==============================================================================================================================
//	�{�[���Ǘ��v���O����
//==============================================================================================================================
ENEMY	enemy[ENEMY_MAX];

/*==================================
	�{�[��������
====================================*/
void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].Init();
		enemy[i].Prepare();
	}

	e_player = GetPlayer();
}

/*==================================
	�{�[���I������
====================================*/
void	UninitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].Uninit();
	}
}

/*==================================
	�{�[���X�V����
====================================*/
void	UpdateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].Update();
	}
}

/*==================================
	�{�[���`�揈��
====================================*/
void	DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].GetEnemyTyep() == ENEMY::Bound)	enemy[i].SetAnimation(!GetStopBool());

		enemy[i].Draw();
		enemy[i].DrawTraceMark();
	}
}

/*==================================
	�G�l�~�[�̃Z�b�g
====================================*/
void	SetEnemys(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	ENEMY::ENEMY_TYPE&	EnemyType)	//	�G�l�~�[�̃Z�b�g
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!enemy[i].GetUse())
		{
			enemy[i].SetEnemy(pos, way, EnemyType);

			break;
		}
	}
}

/*==================================
	�{�[���擾
====================================*/
ENEMY*	GetEnemy()
{
	return	enemy;
}




