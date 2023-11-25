
#include	"oneWayBlock.h"
#include	"player.h"
#include	"collision.h"

PLAYER*	one_player;

void	ONE_WAY_BLOCK::Update()
{
	if (use)
	{
		if (!collisionBool)
		{
			if (!GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize,
				one_player->GetPosi() + one_player->GetCollisionPos(), one_player->GetCollisionSize()))
			{
				collisionBool = true;
			}
		}
	}
}

void	ONE_WAY_BLOCK::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	MoveX = false;
	MoveY = false;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	TexNums[UP] = LoadTexture((char*)"data/texture/OneWayBlock_up.png");				//	LoadTexture�̖߂�l���L�^����ϐ�
	TexNums[DOWN] = LoadTexture((char*)"data/texture/OneWayBlock_down.png");				//	LoadTexture�̖߂�l���L�^����ϐ�
	TexNums[RIGHT] = LoadTexture((char*)"data/texture/OneWayBlock_left.png");				//	LoadTexture�̖߂�l���L�^����ϐ�
	TexNums[LEFT] = LoadTexture((char*)"data/texture/OneWayBlock_right.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	texNo = TexNums[UP];
	way = UP;

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y

	one_player = GetPlayer();
}

void	ONE_WAY_BLOCK::Reset()
{

}

//============================================
//	����ʍs�u���b�N�Ǘ��v���O����
//============================================
ONE_WAY_BLOCK	oneWayBlock[ONE_WAY_BLOCK_MAX];

void	InitOneWayBlock()		//	����ʍs�u���b�N�̏�����
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Init();
		oneWayBlock[i].Prepare();
	}
}

void	UninitOneWayBlock()	//	����ʍs�u���b�N�̏I������
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Uninit();
	}
}

void	UpdateOneWayBlock()	//	����ʍs�u���b�N�̍X�V����
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Update();
	}
}

void	DrawOneWayBlock()		//	����ʍs�u���b�N�̕`�揈��
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		oneWayBlock[i].Draw();
	}
}

void	SetOneWayBlock(const	D3DXVECTOR2 new_pos, const	D3DXVECTOR2	new_size, ONE_WAY_BLOCK::WAY	new_way)
{
	for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
	{
		if (!oneWayBlock[i].GetUse())
		{
			oneWayBlock[i].SetUse(true);
			oneWayBlock[i].SetCollisionBool(true);
			oneWayBlock[i].SetPosi(new_pos);
			oneWayBlock[i].SetSize(new_size * BASE_SIZE);
			oneWayBlock[i].SetCollisionSize(new_size * BASE_SIZE);
			oneWayBlock[i].SetTexSizeWidth(new_size.x);
			oneWayBlock[i].SetTexSizeHeight(new_size.y);
			oneWayBlock[i].SetWay(new_way);

			oneWayBlock[i].SetTexNums(new_way);

			break;
		}
	}
}

ONE_WAY_BLOCK*	GetOneWayBlock()
{
	return	oneWayBlock;
}
























