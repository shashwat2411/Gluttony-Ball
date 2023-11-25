#pragma once

#include "Enemy.h"
#include "Button.h"


#define BOUNCE_COUNT (2)
#define	HOMING_POS_MAX (10)
#define FOCUS_MAX (100)
//============================================================
//	�v���C���[�N���X
//		�L�[�ړ��A�d�́A�W�����v
//=============================================================
class BALL : public	BASE_OF_PERFORMER
{
public:
	enum BALL_SITU
	{
		Keep,
		Throwing,
		ChargeThrow,
		Free,
		Stay,
		Return,
	};
	//	�U���n�\��
	enum ABILITY_ATTACK
	{
		NONE_ATTACK,
		EXPLOSION,
		STICKY,
	};

	//	�O���n�\��
	enum ABILITY_MOVE_BALL
	{
		NONE_BALL,
		BOUNCE,
		HOMING,
	};

	//	�ړ��n�\��
	enum ABILITY_MOVE_PLAYER
	{
		NONE_PLAYER,
		SPRING,
		TRACE,
	};

private:
	BALL_SITU	situation;	//	�{�[���̏�ԁBKeep:�v���C���[���{�[�����������Ă���B
							//				  Throwing:�v���C���[�������āA�ړ����Ă���B
							//				  ChargeThrow:�`���[�W�����A�`���[�W��
							//				  Stay:�{�[��������̓�����������A�ҋ@��Ԃɓ���B
							//				  Return:�{�[��������̓�����������A�v���C���[�̌��ɖ߂�B


	ABILITY_ATTACK	ability_attack;
	ABILITY_MOVE_BALL	ability_move_ball;
	ABILITY_MOVE_PLAYER	ability_move_player;

	D3DXVECTOR2*	HomingPos[HOMING_POS_MAX];

	unsigned	int	g_BallSE;

	bool	UsedAttackBool;	//	�U���n�\�͂��g�p������Bool
	bool	UsedSpringBool;	//	�o�l��ݒu������Bool
	bool	UsedSEBool;		//	�{�[��SE�𗬂�����Bool

	int		HomingNum;		//	�z�[�~���O�Ń��b�N�����G�̐�
	int		TargetNum;		//	�z�[�~���O�ő_���Ă���G�̔ԍ�

	int		BounceCount;	//�o�E���X������

	float	MovedDisSq;	//	�{�[������񂾑�����

	float	ThrowDis;	//	�{�[�����o�������ʒu����d�͂������Ȃ������B
	const	float	ThrowDisMin = BASE_SIZE * 3;
	const	float	ThrowDisMax = BASE_SIZE * 8;

	D3DXVECTOR2	posBefForDis;	//	�{�[������񂾑��������v�Z���邽�߂̍��W

public:
	int counter = 0;
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetBallReturn();
	void	SetBallPoint(D3DXVECTOR2 new_point);

	void	SetBall(D3DXVECTOR2 pos, D3DXVECTOR2	way);

	void	PlayBallSE(const	bool	new_bool) {
		if (new_bool && !UsedSEBool) { PlaySound(g_BallSE, 0); }
		UsedSEBool = new_bool; }

	void	SetAbilityAttack(const	ABILITY_ATTACK	new_attack) { ability_attack = new_attack; }	//	�U���n�\�͂̃Z�b�g
	const	ABILITY_ATTACK&	GetAbilityAttack(void) { return	ability_attack; }						//	�U���n�\�͂̎擾

	void	SetAbilityMoveBall(const	ABILITY_MOVE_BALL	new_ball) { ability_move_ball = new_ball; }	//	�O���n�\�͂̃Z�b�g
	const	ABILITY_MOVE_BALL&	GetAbilityMoveBall(void) { return	ability_move_ball; }				//	�O���n�\�͂̎擾

	void	SetAbilityMovePlayer(const	ABILITY_MOVE_PLAYER	new_player) { ability_move_player = new_player; }	//	�ړ��n�\�͂̃Z�b�g
	const	ABILITY_MOVE_PLAYER&	GetAbilityMovePlayer(void) { return	ability_move_player; }					//	�ړ��n�\�͂̎擾

	void	SetUsedAttackBool(const	bool	new_bool) { UsedAttackBool = new_bool; }	//	�U���n�\�͂��g�p������Bool�̃Z�b�g
	const	bool&	GetUsedAttackBool(void) { return	UsedAttackBool; }				//	�U���n�\�͂��g�p������Bool�̎擾

	void	SetUsedSpringBool(const	bool	new_bool) { UsedSpringBool = new_bool; }	//	�o�l��ݒu������Bool�̃Z�b�g
	const	bool&	GetUsedSpringBool(void) { return	UsedSpringBool; }				//	�o�l��ݒu������Bool�̎擾

	void	SetUsedSEBool(const	bool	new_bool) { UsedSEBool = new_bool; }
	const	bool&	GetUsedSEBool() { return	UsedSEBool; }

	void	ThrowDisRateUp(const	float	rate) { ThrowDis = (ThrowDisMax - ThrowDisMin) * rate + ThrowDisMin; }
	void	SetThrowDis(const	float&	new_dis) { ThrowDis = new_dis; }	//	�����鋗���Z�b�g
	const	float&	GetThrowDis(void) { return	ThrowDis; }					//	�����鋗���擾

	void	SetSituation(const	BALL_SITU&	new_Situ) { situation = new_Situ; }	//	�{�[����ԃZ�b�g
	const	BALL_SITU&	GetSituation(void) { return	situation; }				//	�{�[����Ԏ擾

	float	GetMoveDistance() { return sqrt((pos.x - actionFirstPos.x) * (pos.x - actionFirstPos.x) + (pos.y - actionFirstPos.y) * (pos.y - actionFirstPos.y)); };

	void SetBounceCount(const int& newCount) { BounceCount = newCount; }
	const int& GetBounceCount() { return BounceCount; }
	//void AddBounceCount(int add) { BounceCount += add; }

	void	SetHomingNum(const	int	new_Num) {	HomingNum = new_Num; }
	const	int&	GetHomingNum(void) { return	HomingNum; }

	void	SetTarget(ENEMY*	new_Enemy, BUTTON*	new_Button);		//	�z�[�~���O�Ń��b�N�����G�l�~�[�̒ǉ�
	D3DXVECTOR2**	GetTargetEnemy(void) { return	HomingPos; }
};


//=============================================
//	�v���C���[�Ǘ��v���O����
//=============================================
void	InitBall();		//	�{�[��������
void	UninitBall();	//	�{�[���I������
void	UpdateBall();	//	�{�[���X�V����
void	DrawBall();		//	�{�[���`�揈��

BALL*	GetBall();		//	�{�[���擾

//void UpdateAbilityBounce(bool onWall);
//void UpdateAbilityHoming();
//void UpdateAbilityExplode();
//void UpdateAbilitySticky(bool onWall, ENEMY* follow);
//void UpdateAbilityFollow();
//void UpdateAbilitySpring();