#pragma once

#include "znoTouch_BaseOfPerformer.h"
#include	"collision.h"

//============================================================
//	�v���C���[�N���X
//		�L�[�ړ��A�d�́A�W�����v
//=============================================================
#define	ENEMY_MAX	(10)

class ENEMY : public	BASE_OF_PERFORMER
{
public:
	enum ENEMY_TYPE
	{
		Bound,		//	�o�E���h�G�l�~�[
		Homing,		//	�z�[�~���O�G�l�~�[
		Explosion,	//	�����G�l�~�[
		Sticky,		//	�X�e�B�b�L�[���e�G�l�~�[
		Trace,		//	�Ǐ]�G�l�~�[
		Spring,		//	�o�l�G�l�~�[

		enemy_type_max
	};

	enum ENEMY_ANIMATION
	{
		bound_stand_R,
		bound_move_R,
		bound_stand_L,
		bound_move_L,
		homing,
		explosion,
		sticky,
		trace,
		spring_R,
		spring_L,

		enemy_anim_max
	};

private:
	ENEMY_TYPE	enemy_type;		//	�G�l�~�[�̎��
	ENEMY_ANIMATION	animation_type;
	unsigned	int	TexNums[enemy_anim_max];	//	�G�l�~�[�̊e�^�C�v�̃e�N�X�`���ԍ�
	unsigned	int	TraceMarkNum;				//	�Ǐ]�G�l�~�[�̒Ǐ]�}�[�J�[�̃e�N�X�`���ԍ�
	unsigned	int	g_EnemyBoundSE;
	unsigned	int	g_EnemySpringSE;

	bool	BallCollide = false;	//�{�[���ɓ����������ǂ���, true:��������, false:�������ĂȂ�
	bool	DrawTraceBool;


	int	timer;		//	�e�G�l�~�[�Ŏg���^�C�}�[�ϐ�

	int	boundCount;	//	�o�E���h�G�l�~�[�̃o�E���h�����񐔃J�E���g
	const	int	boundMax = 3;	//	�o�E���h�G�l�~�[�̃o�E���h����ő��

	const	int	HomingShootTime = 60 * 5;	//	�z�[�~���O�G�l�~�[�̃o���b�g���ˊԊu����

	const	int	UseStickyBombTime = 60 * 5;	//	�X�e�B�b�L�[���e���o�����ԊԊu

	const	int	BoundStayTime = 60 * 3;	//	�o�E���h�G�l�~�[�̑ҋ@���ԁi3�b�j

	const	int	TraceSearchDis = BASE_SIZE * 20;	//	�Ǐ]�G�l�~�[�̒Ǐ]����͈͋���

	const	float	ExpAcceleration = 2.0f;	//	�����G�l�~�[�̈ړ������x�Amove.x�ɉ��Z��������
	const	float	ExpDis = BASE_SIZE * 2.0f;	//	�����G�l�~�[����������v���C���[�Ƃ̋���

	const	float	FlyingMoveX = BASE_SIZE * 7;	//	�X�e�B�b�L�[���e�G�l�~�[�̉����ɓ����͈�

public:
	
	void	Update();

	void	Prepare();
	void	Reset();

	void	DrawTraceMark();	//	�Ǐ]�G�l�~�[�̒Ǐ]�ꏊ�������}�[�J�[��`�悷�鏈��

	void	SetEnemy(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	ENEMY_TYPE&	EnemyType);

	void SetBallCollide(const bool col) { BallCollide = col; }
	const bool GetBallCollide() { return BallCollide; }

	void	SetEnemyType(const	ENEMY_TYPE	new_type) { enemy_type = new_type; }	//	�G�l�~�[�^�C�v�̃Z�b�g
	const	ENEMY_TYPE&	GetEnemyTyep(void) { return	enemy_type; }					//	�G�l�~�[�^�C�v�̎擾
	
	void	SetBoundCount(const	int	new_Count) {
		boundCount = new_Count;	if (boundCount <= boundMax)	PlaySound(g_EnemyBoundSE, 0);
	}	//	�o�E���h�񐔂̃Z�b�g
	const	int&	GetBoundCount(void) { return	boundCount; }			//	�o�E���h�񐔂̎擾

	void	PlaySpringSE() { PlaySound(g_EnemySpringSE, 0); }

	void	SetTime(const	int	new_Time) { timer = new_Time; }		//	�^�C�}�[�̃Z�b�g
	const	int&	GetTime(void) { return	timer; }				//	�^�C�}�[�̎擾

	void	SetBoundStand(const	COLLISION_WAY&	way);
};


//=============================================
//	�v���C���[�Ǘ��v���O����
//=============================================
void	InitEnemy();		//	�{�[��������
void	UninitEnemy();	//	�{�[���I������
void	UpdateEnemy();	//	�{�[���X�V����
void	DrawEnemy();		//	�{�[���`�揈��

void	SetEnemys(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	ENEMY::ENEMY_TYPE&	EnemyType);	//	�G�l�~�[�̃Z�b�g

ENEMY*	GetEnemy();		//	�{�[���擾

