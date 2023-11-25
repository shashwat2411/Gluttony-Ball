
#include	"homingMarker.h"
#include	"Ball.h"


void	HOMING_MARKER::Update()
{
	if (use)
	{
		if (homingEnemy != nullptr)
		{
			pos = homingEnemy->GetPosi();

			if (!homingEnemy->GetUse())
			{
				use = false;
				pos = D3DXVECTOR2(-200, -200);
			}
		}
		if (homingButton != nullptr)
		{
			pos = homingButton->GetPosi();

			if (!homingButton->GetUse())
			{
				use = false;
				pos = D3DXVECTOR2(-200, -200);
			}
		}

		if (GetBall()->GetAbilityMoveBall() != BALL::HOMING)	use = false;
	}
}

void	HOMING_MARKER::Prepare()
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

	collisionBool = false;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/homing_marker.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(-200, -200);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(0, 0);				//	�����蔻��̃T�C�Y
}

void	HOMING_MARKER::Reset()
{

}


//=========================================================
//	�z�[�~���O�}�[�J�[�Ǘ��v���O����
//=========================================================
HOMING_MARKER	homingMarker[HOMING_MARKER_MAX];

void	InitHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Init();
		homingMarker[i].Prepare();
	}
}

void	UninitHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Uninit();
	}
}

void	UpdateHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Update();
	}
}

void	DrawHomingMarker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].Draw();
	}
}

void	SetHomingMarker(ENEMY*	new_homingEnemy, BUTTON*	new_homingButton)
{
	if (new_homingEnemy != nullptr || new_homingButton != nullptr)
	{
		for (int i = 0; i < HOMING_MARKER_MAX; i++)
		{
			if (!homingMarker[i].GetUse())
			{
				homingMarker[i].SetUse(true);
				if (new_homingEnemy != nullptr)	homingMarker[i].SetHomingEnemy(new_homingEnemy);
				if (new_homingButton != nullptr)	homingMarker[i].SetHomingButton(new_homingButton);

				break;
			}
		}
	}
}

const	HOMING_MARKER*	GetHomingMarker()
{
	return	homingMarker;
}


void	ResetHomingMaker()
{
	for (int i = 0; i < HOMING_MARKER_MAX; i++)
	{
		homingMarker[i].SetUse(false);
		homingMarker[i].SetHomingButton(nullptr);
		homingMarker[i].SetHomingEnemy(nullptr);
	}
}










