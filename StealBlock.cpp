
#include	"stealBlock.h"

void	STEALBLOCK::Update()
{
	if (use)
	{

	}
}

void	STEALBLOCK::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	MoveX = false;
	MoveY = false;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/steal_block.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y
}

void	STEALBLOCK::Reset()
{

}


//======================================================
//	�\�͖v���u���b�N�Ǘ��v���O����
STEALBLOCK	stealBlock[STEALBLOCK_MAX];

void	InitStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Init();
		stealBlock[i].Prepare();
	}
}

void	UninitStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Uninit();
	}
}

void	UpdateStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Update();
	}
}

void	DrawStealBlock()
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		stealBlock[i].Draw();
	}
}

void	SetStealBlock(const	D3DXVECTOR2	new_Pos, const	D3DXVECTOR2	new_Size)
{
	for (int i = 0; i < STEALBLOCK_MAX; i++)
	{
		if (!stealBlock[i].GetUse())
		{
			stealBlock[i].SetUse(true);
			stealBlock[i].SetPosi(new_Pos);
			stealBlock[i].SetSize(new_Size * BASE_SIZE);
			stealBlock[i].SetCollisionSize(new_Size * BASE_SIZE);

			stealBlock[i].SetTexSizeWidth(new_Size.x);
			stealBlock[i].SetTexSizeHeight(new_Size.y);

			break;
		}
	}
}

STEALBLOCK*	GetStealBlock(void)
{
	return	stealBlock;
}















