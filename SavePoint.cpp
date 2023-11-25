#include "SavePoint.h"

#include "player.h"
#include "Ball.h"
#include "collision.h"
#include	"InterlockArrangement.h"

//============================
//�@�O���[�o���ϐ�
//============================
SAVE_POINT savePointList[SAVE_POINT_MAX];
int cur_save_point = -1; 

PLAYER*  saveP_player;
BALL* saveP_ball;
BUTTON*	saveP_button;
INTERLOCKARRANGEMENT*	saveP_inter;

void SAVE_POINT::Prepare()
{
	use = false;
	active = false;
	animation = false;
	gravity = false;

	MoveX = false;
	MoveY = false;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;

	texNo = LoadTexture((char*)"data/texture/SummonEnemy.png");
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);
	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y
}

//�@�Z�[�u�������݂̂�������
void SAVE_POINT::Reset()
{
	saveState = SAVE_STATE::NONE;	//�Z�[�u����Ă��Ȃ���ԂɕύX
	ability_attack = BALL::ABILITY_ATTACK::NONE_ATTACK;
	ability_move_ball = BALL::ABILITY_MOVE_BALL::NONE_BALL;
	ability_move_player = BALL::ABILITY_MOVE_PLAYER::NONE_PLAYER;
}

void SAVE_POINT::Update()
{
	if (use == true)
	{
		if (GetCollision(saveP_player->GetCollisionPos() + saveP_player->GetPosi(), saveP_player->GetCollisionPos(), saveP_player->GetCollisionSize(),
			collisionLocalPos + pos, collisionSize) && saveState == SAVE_STATE::NONE)
		{
			//�@�v���C���[�ƃZ�[�u�|�C���g�ɐڐG���肪���������ǂ���
			saveState = SAVE_STATE::SAVING;

			for (int i = 0; i < BUTTON_MAX; i++)
			{
				if (saveP_button[i].GetSaveAble())
				{
					saveButtons[i] = saveP_button[i].GetOn_OffSwitch();
				}
				else saveButtons[i] = false;
			}
		}
	}
}

//�@�v���C���[�̍��W
void SAVE_POINT::Save()
{
	//�@�Z�[�u������ԂɕύX
	saveState = SAVE_STATE::SAVED;
}

void SAVE_POINT::SaveBallAbility(BALL::ABILITY_ATTACK attack, BALL::ABILITY_MOVE_BALL ball, BALL::ABILITY_MOVE_PLAYER player)
{
	ability_attack = attack;
	ability_move_ball = ball;
	ability_move_player = player;
}

BALL::ABILITY_ATTACK SAVE_POINT::GetBallAbilityAttack()
{
	return ability_attack;
}

BALL::ABILITY_MOVE_BALL SAVE_POINT::GetBallAbilityMove()
{
	return ability_move_ball;
}

BALL::ABILITY_MOVE_PLAYER SAVE_POINT::GetBallAbilityPlayer()
{
	return ability_move_player;
}

//�@�Z�[�u�|�C���g�̏�����
void InitSavePoint()
{
	for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		savePointList[i].Init();
		savePointList[i].Prepare();
	}
	saveP_player = GetPlayer();
	saveP_ball = GetBall();
	saveP_button = GetButton();
	saveP_inter = GetInterlockArrangement();
}

//	�Z�[�u�|�C���g�̏I������
void UninitSavePoint()
{
	for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		savePointList[i].Uninit();
	}
}

//	�Z�[�u�|�C���g�̍X�V����
void UpdateSavePoint()
{
	for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		savePointList[i].Update();
		if (savePointList[i].GetUse() == true && savePointList[i].GetSaveState() == SAVE_POINT::SAVE_STATE::SAVING)
		{//�Z�[�u�|�C���g�Ƀv���C���[������������
			savePointList[i].SaveBallAbility(saveP_ball->GetAbilityAttack(), saveP_ball->GetAbilityMoveBall(), saveP_ball->GetAbilityMovePlayer());
			savePointList[i].Save();
			cur_save_point = i;
		}
	}
}

//	�Z�[�u�|�C���g�̕`�揈��
void DrawSavePoint()
{
	/*for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		savePointList[i].Draw();
	}*/
}

//�@�Z�[�u�|�C���g�ŃZ�[�u�����f�[�^�̓ǂݍ���
void LoadSavePoint()
{
	if (cur_save_point == -1)
	{	//�@�Z�[�u�����f�[�^���Ȃ����̓��[�h���Ȃ�
		return;
	}
	if (savePointList[cur_save_point].GetSaveState() == SAVE_POINT::SAVE_STATE::SAVED)
	{
		//�v���C���[�̍��W���Z�[�u�����|�C���g�Ɉړ�
		D3DXVECTOR2	position = savePointList[cur_save_point].GetPosi();
		position.y += savePointList[cur_save_point].GetSize().y / 2 - saveP_player->GetSize().y / 2;

		saveP_player->SetPosi(position);
		saveP_player->SetBefPosi(position);

		//�e�{�[���\�͂��Z�b�g
		saveP_ball->SetAbilityAttack(savePointList[cur_save_point].GetBallAbilityAttack());
		saveP_ball->SetAbilityMoveBall(savePointList[cur_save_point].GetBallAbilityMove());
		saveP_ball->SetAbilityMovePlayer(savePointList[cur_save_point].GetBallAbilityPlayer());

		for (int i = 0; i < BUTTON_MAX; i++)
		{
			if (saveP_button[i].GetSaveAble())
			{
				saveP_button[i].SetOn_OffSwitch(savePointList[cur_save_point].GetSaveButtons()[i]);
				saveP_inter[i].SetOn_Off_InterlockArrangement(savePointList[cur_save_point].GetSaveButtons()[i]);
			}
		}
	}
}

//�@�S�ẴZ�[�u�|�C���g�ŃZ�[�u�����������Z�b�g
void ResetSavePoint()
{
	for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		savePointList[i].Reset();
	}
}

void SetSavePoint(const	D3DXVECTOR2 pos, const	D3DXVECTOR2	size)
{
	for (int i = 0; i < SAVE_POINT_MAX; i++)
	{
		if (savePointList[i].GetUse() == false)
		{
			savePointList[i].SetUse(true);
			savePointList[i].SetPosi(pos);
			savePointList[i].SetSize(size);
			savePointList[i].SetCollisionSize(size);

			break;
		}
	}
}

//�@�Z�[�u�|�C���g�z��̐擪���擾
SAVE_POINT * GetSavePoint()
{
	return savePointList;
}
