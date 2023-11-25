#pragma once

#include	"include_lib.h"

/*========================================================
	�{�[���A�v���C���[�A�G�l�~�[�A���̊�b�N���X

	���L�̃N���X���p�����č쐬���邱��
==========================================================*/
class BASE_OF_PERFORMER
{
public:
	enum ANIMATION_TYPE
	{
		Stand_R,	Stand_L,
		Run_R,	Run_L,
		Jump_R,	Jump_L,
		ThrowPose_R,	ThrowPose_L,
		ThrowWalk_R,	ThrowWalk_L,
		ThrowBack_R,	ThrowBack_L,
		AfterThrow_R,	AfterThrow_L,
		Fall_R,	Fall_L,
		ANIMATION_TYPE_MAX
	};

	enum MOVE_TYPE
	{
		Normal,
		Point,
		Straight,
	};

	

protected:

	MOVE_TYPE	move_type;				/*	�I�u�W�F�N�g�̈ړ����@
												Nomal:�ʏ�ړ��Bpos��move�����Z��������B�d�͂̉e�����󂯂�
												Point:point���W�Ɍ������Ē��i����B�d�͂̉e�����󂯂Ȃ��B
												Straight:�����ړ��B�d�͂̉e�����󂯂Ȃ��B*/


	bool	use;						//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	bool	active;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	bool	animation;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	bool	gravity;					//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����
	bool	onGround;					//	�n�ʂɒ��n���Ă��邩�A��
	bool	onWall;						//	�ǂɐڂ��Ă��邩�A��
	bool	animationOver;

	bool	MoveX;						//	�I�u�W�F�N�g�̉��ړ��̉s��
	bool	MoveY;						//	�I�u�W�F�N�g�̏c�ړ��̉s��
	bool	ArrivePoint;				//	�I�u�W�F�N�g�̃|�C���g�ړ��̖ړI���W�ɒ��������A��

	bool			collisionBool;		//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	bool			OnTrigger;			//	�ʂ̃I�u�W�F�N�g�̃R���W�����ɐG��Ă��邩Bool	false:�ʃI�u�W�F�N�g�ɐG��ĂȂ�	true:�ʃI�u�W�F�N�g�ɐG��Ă���
	static	bool	collisionTest;		//	DrawCollision�̕`��̋��ʎg�pBool

	int		movePointMax = 5;				//	�|�C���g�ړ��ňړ��o����|�C���g�̍ő�l
	float	gravityNum = 1.0f;		//	�d�͒l�Amove.y�ɉ��Z��������
	const	float	fallSpeedMax = 15.0f;	//	move.y�ɓ���ő�l
	float	airFrictionRate = 0.95f;	//	���V���̋�C��R
	const	float	stopSpeedMax = 0.05f;		//	�X�s�[�h�����l���̏ꍇ�A0�Ƃ݂Ȃ�
	float	frictionRate = 0.5f;	//	����Ƃ̖��C�W��

	unsigned	int	texNo;				//	LoadTexture�̖߂�l���L�^����ϐ�
	unsigned	int	col_TexNo;			//	DrawCollision�p�e�N�X�`���ԍ�
	unsigned	int	befPos_TexNo;		//	DrawCollision�pBefPosi�e�N�X�`���ԍ�

	float			animTimer;			//	�A�j���[�V�����^�C�}�[
	unsigned	int	animTimeMax;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	float			animOneFlameTime;	//	animTimer�ɉ��Z��������ϐ�

	unsigned	int	animFlame_W;		//	�e�N�X�`���̉�������
	unsigned	int	animFlame_H;		//	�e�N�X�`���̏c������

	unsigned	int		animationNo_H;	//	�e�N�X�`���̏c�̃A�j���[�V�����l
	float				animationNo_W;	//	�e�N�X�`���̉��̃A�j���[�V�����l

	float	texSize_W;					//	�e�N�X�`���̉��̕\���T�C�Y
	float	texSize_H;					//	�e�N�X�`���̏c�̕\���T�C�Y

	float	speed;						//	�I�u�W�F�N�g�̈ړ����x
	float	r_speed;					//	speed��Reset�l
	float	angle;						//	�I�u�W�F�N�g�̉�]�p�x

	D3DXVECTOR2	pos;					//	�I�u�W�F�N�g�̌��ݒn
	D3DXVECTOR2	pos_bef;				//	�I�u�W�F�N�g�̑O�t���[���ʒu
	D3DXVECTOR2	actionFirstPos;			//	�I�u�W�F�N�g�̓���A�N�V�����̏������W
	D3DXVECTOR2	r_pos;					//	pos��Reset�l
	D3DXVECTOR2	StagePos;				//	�X�e�[�W�S�̂ɒu������W
	D3DXVECTOR2	r_StagePos;				//	�X�e�[�W�S�̂ɒu���鏉�����W
	D3DXVECTOR2	size;					//	�I�u�W�F�N�g�̕`��͈�

	D3DXVECTOR2	move;					//	�I�u�W�F�N�g�̈ړ������A�m�[�}���C�Y���ꂽ�x�N�g����speed���������l��������
	D3DXVECTOR2	point;					//	�I�u�W�F�N�g�̃|�C���g�ړ��̖ڕW���W

	D3DXVECTOR2	collisionLocalPos;		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	D3DXVECTOR2	collisionSize;			//	�����蔻��̃T�C�Y

	D3DXCOLOR	color;					//	�F

public:

	void	Init();						//	�I�u�W�F�N�g�̏�����
	void	Uninit();					//	�I�u�W�F�N�g�̏I������
	virtual	void	Update() = 0;		//	�p����Ŏg�p����X�V����
	void	Draw();						//	�I�u�W�F�N�g�̕`�揈��
	void	DrawCollision();			//	�����蔻��ʒu�A�T�C�Y�m�F�`��

	void	Animation();				//	�I�u�W�F�N�g�̃A�j���[�V����

	//==============================================================================
	void	Move();						//	�I�u�W�F�N�g�̈ړ�����
	void	Gravity();					//	�I�u�W�F�N�g�̏d�͑���
	//==============================================================================

	virtual	void	Prepare() = 0;		//	�I�u�W�F�N�g�̏����Z�b�g����
	virtual	void	Reset() = 0;		//	�I�u�W�F�N�g�̏��������Z�b�g����

	void	SetUse(const	bool&	new_use) { use = new_use; }		//	�I�u�W�F�N�g�g�p�Z�b�g
	const	bool&	GetUse(void) { return	use; }					//	�I�u�W�F�N�g�g�p�擾

	void	SetActive(const	bool&	new_active) { active = new_active; }	//	�ړ��̉s�̃Z�b�g
	const	bool&	GetActive(void) { return	active; }					//	�ړ��̉s�̎擾

	void	SetAnimation(const	bool&	new_use) { animation = new_use; }		//	�I�u�W�F�N�g�A�j���[�V�����Z�b�g
	const	bool&	GetAnimation(void) { return	animation; }					//	�I�u�W�F�N�g�A�j���[�V�����擾

	void	SetMoveType(const	MOVE_TYPE&	new_type) { move_type = new_type; }	//	�ړ��^�C�v�Z�b�g
	const	MOVE_TYPE&	GetMoveType(void) { return	move_type; }				//	�ړ��^�C�v�擾

	void	SetTexNo(const	int&	new_TexNo) { texNo = new_TexNo; }	//	�e�N�X�`���ԍ��Z�b�g
	const	int&	GetTexNo(void) { return	texNo; }					//	�e�N�X�`���ԍ��擾

	void	SetPosi(const	D3DXVECTOR2&	new_Pos) { pos = new_Pos; }	//	���W�Z�b�g
	D3DXVECTOR2&	GetPosi(void) { return	pos; }				//	���W�擾

	void	SetBefPosi(const	D3DXVECTOR2&	new_BefPos) { pos_bef = new_BefPos; }	//	�O���W�̃Z�b�g
	const	D3DXVECTOR2&	GetBefPosi(void) { return	pos_bef; }						//	�O���W�̎擾

	void	SetRPos(const	D3DXVECTOR2&	new_RPos) { r_pos = new_RPos; }	//	�I�u�W�F�N�g�̏������W�̃Z�b�g
	const	D3DXVECTOR2&	GetRPos(void) { return	r_pos; }				//	�I�u�W�F�N�g�̏������W�̎擾

	void	SetStagePos(const	D3DXVECTOR2&	new_StPos) { StagePos = new_StPos; }	//	�X�e�[�W�S�̂ɒu������W�̃Z�b�g
	const	D3DXVECTOR2&	GetStagePos(void) { return	StagePos; }						//	�X�e�[�W�S�̂ɒu������W�̎擾

	void	SetRStagePos(const	D3DXVECTOR2&	new_RStPos) { r_StagePos = new_RStPos; }	//	�X�e�[�W�S�̂ɒu������W�̃Z�b�g
	const	D3DXVECTOR2&	GetRStagePos(void) { return	r_StagePos; }						//	�X�e�[�W�S�̂ɒu������W�̎擾

	void	SetAngle(const	float	new_Angle) { angle = new_Angle; }	//	��]�p�x�Z�b�g
	const	float&	GetAngle(void) { return	angle; }					//	��]�p�x�擾

	void	SetAnimTimer(const	float&	new_value) { animTimer = new_value; }	//	��]�p�x�Z�b�g
	const	float&	GetAnimTimer(void) { return	animTimer; }					//	��]�p�x�擾

	void	SetTexSizeWidth(const	float&	new_texSize) { texSize_W = new_texSize; }	//	�e�N�X�`���̉��\���T�C�Y�̃Z�b�g
	const	float&	GetTexSizeWidth(void) { return	texSize_W; }						//	�e�N�X�`���̉��\���T�C�Y�̎擾

	void	SetTexSizeHeight(const	float&	new_texSize) { texSize_H = new_texSize; }	//	�e�N�X�`���̏c�\���T�C�Y�̃Z�b�g
	const	float&	GetTexSizeHeight(void) { return	texSize_H; }						//	�e�N�X�`���̏c�\���T�C�Y�̎擾

	void	SetSize(const	D3DXVECTOR2&	new_Size) { size = new_Size; }	//	�T�C�Y�Z�b�g
	const	D3DXVECTOR2&	GetSize(void) { return	size; }					//	�T�C�Y�擾

	void	SetMove(const	D3DXVECTOR2&	new_Move) { move = new_Move; }	//	�ړ��x�N�g���Z�b�g
	const	D3DXVECTOR2&	GetMove(void) { return	move; }					//	�ړ��x�N�g���擾

	void	SetSpeed(const	float&	new_Speed) { speed = new_Speed; }		//	�ړ��X�s�[�h�Z�b�g
	const	float&	GetSpeed(void) { return	speed; }						//	�ړ��X�s�[�h�擾

	void	SetRSpeed(const	float&	new_Speed) { r_speed = new_Speed; }		//	�ړ��X�s�[�h�Z�b�g
	const	float&	GetRSpeed(void) { return	r_speed; }						//	�ړ��X�s�[�h�擾

	void	SetFrictionRate(const	float&	newValue) { frictionRate = newValue; }		//	�ړ��X�s�[�h�Z�b�g
	const	float&	GetFrictionRate(void) { return	frictionRate; }						//	�ړ��X�s�[�h�擾

	void	SetCollisionPos(const	D3DXVECTOR2&	new_CollisionPos) { collisionLocalPos = new_CollisionPos; }	//	�����蔻����W�Z�b�g
	const	D3DXVECTOR2&	GetCollisionPos(void) { return	collisionLocalPos; }								//	�����蔻����W�擾

	void	SetCollisionSize(const	D3DXVECTOR2&	new_CollisionSize) { collisionSize = new_CollisionSize; }	//	�����蔻��T�C�Y�Z�b�g
	const	D3DXVECTOR2&	GetCollisionSize(void) { return	collisionSize; }									//	�����蔻����W�擾

	void	SetPoint(const	D3DXVECTOR2&	new_Point) { point = new_Point; }	//	�|�C���g�ړ����W�Z�b�g
	const	D3DXVECTOR2&	GetPoint(void) { return	point; }					//	�|�C���g�ړ����W�擾

	void	SetColor(const	D3DXCOLOR&	new_Color) { color = new_Color; }	//	�F�Z�b�g
	const	D3DXCOLOR	GetColor(void) { return	color; }					//	�F�擾

	void	SetGravity(bool	new_Gravity) { gravity = new_Gravity; }		//	�d�̓u�[���Z�b�g
	const	bool&	GetGravity(void) { return	gravity; }				//	�d�̓u�[���擾

	void	SetMoveX(bool	new_MoveX) { MoveX = new_MoveX; }	//	���ړ��Z�b�g
	const	bool&	GetMoveX(void) { return	MoveX; }			//	���ړ��擾

	void	SetMoveY(bool	new_MoveY) { MoveY = new_MoveY; }	//	�c�ړ��Z�b�g
	const	bool&	GetMoveY(void) { return	MoveY; }			//	�c�ړ��擾

	void	SetOnGround(bool	new_OnGround) { onGround = new_OnGround; }	//	���n���Ă��邩Bool�̃Z�b�g
	const	bool&	GetOnGround(void) { return	onGround; }					//	���n���Ă��邩Bool�̎擾

	void	SetOnWall(bool	new_onWall) { onWall = new_onWall; }	//	�ǂɐڂ��Ă��邩Bool�̃Z�b�g
	const	bool&	GetOnWall(void) { return	onWall; }			//	�ǂɐڂ��Ă��邩Bool�̎擾

	void	SetArrivePoint(const	bool&	new_Arrive) {	ArrivePoint = new_Arrive; }	//	�|�C���g�ɓ������Ă��邩Bool�̃Z�b�g
	const	bool&	GetArrivePoint(void) { return	ArrivePoint; }						//	�|�C���g�ɓ������Ă��邩Bool�̎擾

	void	SetCollisionBool(bool	new_col) { collisionBool = new_col; }	//	�����蔻��g�p�Z�b�g
	const	bool&	GetCollisionBool(void) { return	collisionBool; }		//	�����蔻��擾

	void	SetOnTrigger(bool	new_bool) { OnTrigger = new_bool; }	//	�ʃR���W�����ɐG��Ă��邩Bool�̃Z�b�g
	bool*	GetOnTrigger(void) { return	&OnTrigger; }				//	�ʃR���W�����ɐG��Ă��邩Bool�̎擾

	void	SetAnimationOver(bool	new_col) { animationOver = new_col; }	//	�A�j���[�V�����I���Z�b�g
	const	bool&	GetAnimationOver(void) { return	animationOver; }		//	�A�j���[�V�����I���̗L���擾

	static	void	SetCollitionTest(const	bool&	Switch) { collisionTest = Switch; }		//	DrawCollision�̎g�pBool�؂�ւ�
};






