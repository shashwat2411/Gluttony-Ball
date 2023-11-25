
#include	"Direction.h"
#include	"player.h"
#include	"xinput.h"
#include	"Ball.h"
#include	"collision.h"
#include	"homingMarker.h"

DIRECTION direction;
PLAYER*	d_player;
ENEMY* d_enemy;
BUTTON*	d_button;
D3DXVECTOR2 size2;

void DIRECTION::Update()
{
	if (use)
	{
		if (GetBall()->GetAbilityMoveBall() != BALL::NONE_BALL && color != D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))	color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		else if (GetBall()->GetAbilityMoveBall() == BALL::NONE_BALL && color != D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		angle = VecToAng(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(GetStickR().x, -GetStickR().y));
		pos = D3DXVECTOR2(d_player->GetPosi().x, d_player->GetPosi().y - 10.0f);

		if (GetBall()->GetAbilityMoveBall() == BALL::HOMING)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (d_enemy[i].GetUse() && d_enemy[i].GetCollisionBool() &&
					d_enemy[i].GetPosi().x > 0 && d_enemy[i].GetPosi().x < SCREEN_WIDTH &&
					d_enemy[i].GetPosi().y > 0 && d_enemy[i].GetPosi().y < SCREEN_HEIGHT)
				{
					D3DXVECTOR2	serDis;
					serDis.x = SCREEN_WIDTH * cosf(D3DXToRadian(angle)) + pos.x;
					serDis.y = SCREEN_WIDTH * sinf(D3DXToRadian(angle)) + pos.y;

					if ((serDis.x - d_enemy[i].GetPosi().x) * (serDis.x - d_enemy[i].GetPosi().x) +
						(serDis.y - d_enemy[i].GetPosi().y) * (serDis.y - d_enemy[i].GetPosi().y) +
						(d_player->GetPosi().x - d_enemy[i].GetPosi().x) * (d_player->GetPosi().x - d_enemy[i].GetPosi().x) +
						(d_player->GetPosi().y - d_enemy[i].GetPosi().y) * (d_player->GetPosi().y - d_enemy[i].GetPosi().y) <
						(SER_HOMING_DIS) * (SER_HOMING_DIS))
					{
						//float	test = VecToAng(serDis - d_player->GetPosi(), d_enemy[i].GetPosi() - d_player->GetPosi());

						GetBall()->SetTarget(&d_enemy[i], nullptr);
					}
				}
			}

			for (int i = 0; i < BUTTON_MAX; i++)
			{
				if (d_button[i].GetUse() && d_button[i].GetCollisionBool() &&
					d_button[i].GetPosi().x > 0 && d_button[i].GetPosi().x < SCREEN_WIDTH &&
					d_button[i].GetPosi().y > 0 && d_button[i].GetPosi().y < SCREEN_HEIGHT)
				{
					D3DXVECTOR2	serDis;
					serDis.x = SCREEN_WIDTH * cosf(D3DXToRadian(angle)) + pos.x;
					serDis.y = SCREEN_WIDTH * sinf(D3DXToRadian(angle)) + pos.y;

					if ((serDis.x - d_button[i].GetPosi().x) * (serDis.x - d_button[i].GetPosi().x) +
						(serDis.y - d_button[i].GetPosi().y) * (serDis.y - d_button[i].GetPosi().y) +
						(d_player->GetPosi().x - d_button[i].GetPosi().x) * (d_player->GetPosi().x - d_button[i].GetPosi().x) +
						(d_player->GetPosi().y - d_button[i].GetPosi().y) * (d_player->GetPosi().y - d_button[i].GetPosi().y) <
						(SER_HOMING_DIS) * (SER_HOMING_DIS))
					{
						GetBall()->SetTarget(nullptr, &d_button[i]);
					}
				}
			}
		}
	}
}

void DIRECTION::Prepare()
{

	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	onGround = false;

	MoveX = true;
	MoveY = true;

	texNo = LoadTexture((char*)"data/texture/arrow.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 5, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	d_player = GetPlayer();
	d_enemy = GetEnemy();
	d_button = GetButton();
}


void DIRECTION::Reset()
{
}


//==============================================================================================================================
//	�v���[���[�Ǘ��v���O����
//==============================================================================================================================

/*==================================
	�v���[���[������
====================================*/
void	InitDirection()
{
	direction.Init();
	direction.Prepare();
}

/*==================================
	�v���[���[�I������
====================================*/
void	UninitDirection()
{
	direction.Uninit();
}

/*==================================
	�v���[���[�X�V����
====================================*/
void	UpdateDirection()
{
	direction.Update();


}

/*==================================
	�v���[���[�`�揈��
====================================*/
void	DrawDirection()
{
	direction.Draw();
}

/*==================================
	�v���[���[�擾
====================================*/
DIRECTION* GetDirection()
{
	return	&direction;
}