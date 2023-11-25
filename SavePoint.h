#pragma once

#include "znoTouch_BaseOfPerformer.h"
#include "Ball.h" 

#define SAVE_POINT_MAX (10)

class SAVE_POINT :public BASE_OF_PERFORMER
{
public:
	enum class SAVE_STATE {
		NONE,
		SAVING,
		SAVED
	};//NONE:�Z�[�u����Ă��Ȃ� SAVING:�Z�[�u�� SAVED:�Z�[�u�ς�

private:
	bool	saveButtons[BUTTON_MAX];

	SAVE_STATE saveState;
	BALL::ABILITY_ATTACK ability_attack;
	BALL::ABILITY_MOVE_BALL ability_move_ball;
	BALL::ABILITY_MOVE_PLAYER ability_move_player;

public:
	SAVE_POINT() {
		Reset();
	}
	void Prepare();
	void Reset();
	void Update();

	void Save();
	void SaveBallAbility(BALL::ABILITY_ATTACK attack, BALL::ABILITY_MOVE_BALL ball, BALL::ABILITY_MOVE_PLAYER player);

	void	SetSaveButtons(const	int	index, const	bool	new_bool) { saveButtons[index] = new_bool; }
	const	bool*	GetSaveButtons() { return	saveButtons; }

	BALL::ABILITY_ATTACK GetBallAbilityAttack();
	BALL::ABILITY_MOVE_BALL GetBallAbilityMove();
	BALL::ABILITY_MOVE_PLAYER GetBallAbilityPlayer();
	
	SAVE_STATE GetSaveState() { return saveState; }
};

void InitSavePoint();	//�@�Z�[�u�|�C���g�̏�����
void UninitSavePoint();	//	�Z�[�u�|�C���g�̏I������
void UpdateSavePoint();	//	�Z�[�u�|�C���g�̍X�V����
void DrawSavePoint();	//	�Z�[�u�|�C���g�̕`�揈��

void LoadSavePoint();
void ResetSavePoint();

void SetSavePoint(const	D3DXVECTOR2 pos, const	D3DXVECTOR2	size);
SAVE_POINT* GetSavePoint();
