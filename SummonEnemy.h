#pragma once
#include "Enemy.h"

#define		SUMMON_MAX (50)

class SUMMONENEMY :public BASE_OF_PERFORMER
{
private:
	ENEMY::ENEMY_TYPE	enemyType;

	ENEMY*	onlyOneEnemy;

public:

	float Su_collision_es;	//�G�l�~�[�Əo���u���b�N�̃x�N�g��
	float Su_collision_ps;	//�v���C���[�Əo���u���b�N�̃x�N�g��
	int e_Summon_count;		//�o���J�E���g

	void Update();

	void	SetSummonEnemy(D3DXVECTOR2 ss_pos, const	ENEMY::ENEMY_TYPE&	EnemyType);

	void	Prepare();
	void	Reset();
};
//=============================================
//	�G�l�~�[�����u���b�N�Ǘ��v���O����
//=============================================
void	InitSummonEnemy();		//	�G�l�~�[�����u���b�N������
void	UninitSummonEnemy();	//	�G�l�~�[�����u���b�N�I������
void	UpdateSummonEnemy();	//	�G�l�~�[�����u���b�N�X�V����
void	DrawSummonEnemy();		//	�G�l�~�[�����u���b�N�`�揈��

void	SetSummonEnemys(D3DXVECTOR2 s_pos, const	ENEMY::ENEMY_TYPE&	EnemyType);	//	�G�l�~�[�����u���b�N�̃Z�b�g

SUMMONENEMY* GetSummonEnemy();		//	�G�l�~�[�����u���b�N�擾