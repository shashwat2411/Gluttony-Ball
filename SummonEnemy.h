#pragma once
#include "Enemy.h"

#define		SUMMON_MAX (50)

class SUMMONENEMY :public BASE_OF_PERFORMER
{
private:
	ENEMY::ENEMY_TYPE	enemyType;

	ENEMY*	onlyOneEnemy;

public:

	float Su_collision_es;	//エネミーと出現ブロックのベクトル
	float Su_collision_ps;	//プレイヤーと出現ブロックのベクトル
	int e_Summon_count;		//出現カウント

	void Update();

	void	SetSummonEnemy(D3DXVECTOR2 ss_pos, const	ENEMY::ENEMY_TYPE&	EnemyType);

	void	Prepare();
	void	Reset();
};
//=============================================
//	エネミー生成ブロック管理プログラム
//=============================================
void	InitSummonEnemy();		//	エネミー生成ブロック初期化
void	UninitSummonEnemy();	//	エネミー生成ブロック終了処理
void	UpdateSummonEnemy();	//	エネミー生成ブロック更新処理
void	DrawSummonEnemy();		//	エネミー生成ブロック描画処理

void	SetSummonEnemys(D3DXVECTOR2 s_pos, const	ENEMY::ENEMY_TYPE&	EnemyType);	//	エネミー生成ブロックのセット

SUMMONENEMY* GetSummonEnemy();		//	エネミー生成ブロック取得