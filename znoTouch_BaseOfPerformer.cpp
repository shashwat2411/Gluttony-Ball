
#include	"znoTouch_BaseOfPerformer.h"

//=======================================================
//	�I�u�W�F�N�g�̏�����
//=======================================================
void	BASE_OF_PERFORMER::Init()
{
	col_TexNo = LoadTexture((char*)"data/texture/collision_sprite.png");
	befPos_TexNo = LoadTexture((char*)"data/texture/befPosition.png");

	use = false;
	active = false;
	animation = false;
	gravity = false;
	collisionBool = false;
	onGround = false;
	animationOver = false;

	MoveX = false;
	MoveY = false;

	collisionBool = false;

	texNo = -1;

	animTimer = 0.0f;					//	�A�j���[�V�����^�C�}�[
	animTimeMax = 0.0f;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.0f;			//	animTimer�ɉ��Z��������ϐ�

	animationNo_H = 0;
	animationNo_W = 0.0f;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	speed = 0.0f;
	angle = 0.0f;

	pos = D3DXVECTOR2(0, 0);
	pos_bef = pos;
	actionFirstPos = pos;
	size = D3DXVECTOR2(0, 0);
	move = D3DXVECTOR2(0, 0);
	point = D3DXVECTOR2(0, 0);

	collisionLocalPos = D3DXVECTOR2(0, 0);
	collisionSize = D3DXVECTOR2(0, 0);

	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=======================================================
//	�I�u�W�F�N�g�̏I������
//=======================================================
void	BASE_OF_PERFORMER::Uninit()
{

}

//=======================================================
//	�I�u�W�F�N�g�̕`�揈��
//=======================================================
void	BASE_OF_PERFORMER::Draw()
{
	if (use)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		//	�|���S���z�u
		DrawSpriteColorRotate(pos.x, pos.y, size.x, size.y, angle, color,
			animationNo_W, texSize_W, texSize_H, animationNo_H);

		Animation();

		if (collisionTest)	DrawCollision();
	}
}

//=======================================================
//	�I�u�W�F�N�g�̈ړ�����
//=======================================================
void	BASE_OF_PERFORMER::Move()
{
	if (use && active)
	{
		if (move_type == Normal || move_type == Straight)
		{
			if (MoveX)	pos.x += move.x;
			if (MoveY)	pos.y += move.y;
		}
		else if (move_type == Point)
		{
			if (!ArrivePoint)
			{
				D3DXVECTOR2	dis = point - pos;
				D3DXVECTOR2	normalize;
				D3DXVec2Normalize(&normalize, &dis);

				if (MoveX)	pos.x += normalize.x * speed;
				if (MoveY)	pos.y += normalize.y * speed;

				if (dis.x * dis.x + dis.y * dis.y < speed * speed * 2)	ArrivePoint = true;
			}
		}
	}
}

//=======================================================
//	�I�u�W�F�N�g�̃A�j���[�V�����Ǘ�����
//=======================================================
void	BASE_OF_PERFORMER::Animation()
{
	if (animation && use)
	{
		animTimer += animOneFlameTime;


		if (animTimer >= animTimeMax)
		{
			animTimer = 0.0f; 
			animationOver = true;
		}

		animationNo_W = (int)animTimer % animFlame_W;
		animationNo_H = (int)(animTimer / animFlame_W);
	}
}

//=======================================================
//	�d�͑���
//=======================================================
void	BASE_OF_PERFORMER::Gravity()
{
	if (gravity && use && move.y < fallSpeedMax && !onGround && move_type == Normal)
	{
		move.y += gravityNum;
	}
}

//=======================================================
//	�����蔻��ʒu�A�T�C�Y�`��
//=======================================================
void	BASE_OF_PERFORMER::DrawCollision()
{
	if (collisionBool && use)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(col_TexNo));

		//	�|���S���z�u
		DrawSpriteColorRotate(pos.x + collisionLocalPos.x, pos.y + collisionLocalPos.y, collisionSize.x, collisionSize.y, angle,
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 0, 1.0f, 1.0f, 0.0f);
	}
	if (active && use)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(befPos_TexNo));

		//	�|���S���z�u
		DrawSpriteColorRotate(pos_bef.x, pos_bef.y, 15, 15, 0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 0.0f);
	}
}
