#pragma once

#ifndef PLAYER_H_

#define	PLAYER_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	TRACE_POS_MAX	(5)

class PLAYER :public	BASE_OF_PERFORMER
{
public:
	enum SE_TYPE
	{
		None,
		Run,
		Jump,
		Throw,
		SE_TYPE_MAX
	};

private:
	const	float	acceleration = 0.1f;		//	�v���C���[�̉����l

	const	float	JumpSpeed_min = -11;		//	�v���C���[�̍ŏ��̃W�����v�X�s�[�h
	const	float	JumpAcceleration = 0.55f;	//	�v���C���[�̃W�����v�����l

	const	float	QuickBallWayDis = 1.0f / 3;		//	�N�C�b�N�����̓��������̔���͈�
	const	float	ThrowJudgeNum = 0.5f;			//	�E�X�e�B�b�N�AX���̓�����l�͈̔�

	const	float	HomingLockAngle = 60.0f;			//	�z�[�~���O�\�͂Ń��b�N�o����p�x�͈�

	unsigned	int	TexNums[ANIMATION_TYPE_MAX];	//	�v���C���[�̊e�A�N�V�����̃e�N�X�`���ԍ����i�[����z��
	unsigned	int	SENums[SE_TYPE_MAX];		//

	bool	stockBall;		//	�{�[���������Ă��鎞�Atrue
	bool	stick;	//�v���[���[�̑���̗L��

	unsigned	int	ChargeTimer;	//	�E�X�e�B�b�N�̓��͎���
	const	int	ChargeTimeMax = 60 / 2;	//	�N�C�b�N��������`���[�W�����ɐ؂�ւ�鎞��

	bool	control;	//	�v���C���[�̃R���g���[���̉s��

	int		StayTimeBefTrace;	//	�Ǐ]�J�n�O�̑ҋ@��Ԃ��J�E���g����ϐ�
	const	int	StayTimeBefTraceMax = 60 / 2;	//	�Ǐ]�J�n�O�̑ҋ@��Ԃ̎���

	int		way_x = 1;			//	�E�F1	���F-1

	bool following;	//�Ǐ]�\�͂ŒǏ]���Ă��鎞�Atrue
	int FollowCount = 0;	//�Ǐ]�\�͂̍��W�J�E���g

	int	timer;
	const	int	MakeShineTimeMax = 60 / 6;	//	�L���L�����������鎞�ԊԊu

	SE_TYPE	typeSE;
	bool	OneTimeSE;

	int	TraceNum;
	D3DXVECTOR2	TracePos[TRACE_POS_MAX + 1];	//	�Ǐ]�\�͂Œʂ���W�z��

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	CorrectScreen();

	void	SetStockBall(bool	new_stock) { stockBall = new_stock; }	//	�{�[���ێ��Z�b�g
	const	bool& GetStockBall(void) { return	stockBall; }			//	�{�[���ێ��擾

	void	SetStick(bool	new_stock) { stick = new_stock; }	//	�{�[���ێ��Z�b�g
	const	bool& GetStick(void) { return	stick; }			//	�{�[���ێ��擾

	void	SetControl(bool	new_value) { control = new_value; }	//	�{�[���ێ��Z�b�g
	const	bool& GetControl(void) { return	control; }			//	�{�[���ێ��擾

	void	SetWayX(const	int	way) { way_x = way; }
	const	int&	GetWayX() { return	way_x; }

	void	SetTraceNum(const	int	new_num) { TraceNum = new_num; }
	const	int&	GetTraceNum() { return	TraceNum; }

	void	SetSeType(const	SE_TYPE	new_type) { typeSE = new_type; }
	const	SE_TYPE&	GetSeType() { return	typeSE; }

	void	SetTracePos(const	D3DXVECTOR2	new_pos) { if (TraceNum < TRACE_POS_MAX) {
		TracePos[TraceNum] = new_pos;
		TraceNum++;
	} }
	D3DXVECTOR2*	GetTracePos() { return	TracePos; }
};


//=============================================
//	�v���C���[�Ǘ��v���O����
//=============================================
void	InitPlayer();			//	�v���C���[������
void	UninitPlayer();			//	�v���C���[�I������
void	UpdatePlayer();			//	�v���C���[�X�V����
void	DrawPlayer();			//	�v���C���[�`�揈��

PLAYER* GetPlayer();	//	�v���C���[�擾
bool GetPlayerUse();
#endif // !PLAYER_H_





