
#include	"SummonEnemy.h"
#include	"collision.h"
#include	"player.h"

ENEMY* Su_enemy;
PLAYER* Su_player;

void SUMMONENEMY::Update()
{
	if (use && pos.x < SCREEN_WIDTH && pos.x > 0)
	{
		bool	exitBool = false;
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (Su_enemy[i].GetUse() == true) 
			{

				Su_collision_es = (Su_enemy[i].GetPosi().x - pos.x) * (Su_enemy[i].GetPosi().x - pos.x) + (Su_enemy[i].GetPosi().y - pos.y) * (Su_enemy[i].GetPosi().y - pos.y);
				//Su_collision_es = (Su_enemy->GetPosi().x - pos.x) * (Su_enemy->GetPosi().x - pos.x) + (Su_enemy->GetPosi().y - pos.y) * (Su_enemy->GetPosi().y - pos.y);
				Su_collision_ps = (Su_player->GetPosi().x - pos.x) * (Su_player->GetPosi().x - pos.x) + (Su_player->GetPosi().y - pos.y) * (Su_player->GetPosi().y - pos.y);

				if (Su_collision_es < powf((float)BASE_SIZE * 2.5, 2) ||
					Su_collision_ps < powf((float)BASE_SIZE * 2.5, 2)
					/*範囲内に出現する敵がいる ||
					範囲内にプレイヤーがいる*/)
				{
					//color = D3DXCOLOR(0, 1, 0, 1);
					e_Summon_count = 0; //カウントリセット
				}
				
				if (onlyOneEnemy != nullptr)
				{
					if (onlyOneEnemy == &(Su_enemy[i]))	exitBool = true;
				}
				
				/*
				if (Su_enemy[i].GetEnemyTyep() == ENEMY::Trace && enemyType == ENEMY::Trace ||
					Su_enemy[i].GetEnemyTyep() == ENEMY::Homing && enemyType == ENEMY::Homing)	e_Summon_count = 0;*/
			}
		}
		if (exitBool)	e_Summon_count = 0;
		else			onlyOneEnemy = nullptr;

		e_Summon_count += 1;
		if (e_Summon_count >= 60 * 5)
		{
			if (enemyType == ENEMY::Homing && onlyOneEnemy == nullptr)
			{
				//敵を出現
				SetEnemys(D3DXVECTOR2(pos.x, pos.y - BASE_SIZE / 2), D3DXVECTOR2(-1, -1), enemyType);
				e_Summon_count = 0;

				for (int i = 0; Su_enemy[i].GetUse(); i++)
				{
					onlyOneEnemy = &(Su_enemy[i]);
				}
			}
			else
			{
				//敵を出現
				SetEnemys(pos, D3DXVECTOR2(-1, -1), enemyType);
				e_Summon_count = 0;

				if (enemyType == ENEMY::Trace && onlyOneEnemy == nullptr)
				{
					for (int i = 0; Su_enemy[i].GetUse(); i++)
					{
						onlyOneEnemy = &(Su_enemy[i]);
					}
				}
			}
		}

	}
}

void SUMMONENEMY::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	MoveX = true;
	MoveY = true;

	ArrivePoint = false;

	texNo = LoadTexture((char*)"data/texture/SummonEnemy.png");				//	LoadTextureの戻り値を記録する変数

	e_Summon_count = 0;		//カウントのリセット


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size;				//	当たり判定のサイズ
	
	move = D3DXVECTOR2(0, 0);		//移動方向をセット

	onlyOneEnemy = nullptr;

	//SetSummonEnemys(pos,move);
}

void SUMMONENEMY::Reset()
{
}


void SUMMONENEMY::SetSummonEnemy(D3DXVECTOR2 ss_pos, const	ENEMY::ENEMY_TYPE&	EnemyType)
{
	use = true;		//使用フラグをtrueに
	pos = ss_pos;	//座標をセット

	onGround = false;
	collisionBool = true;

	enemyType = EnemyType;

	Su_collision_es = 0;
	Su_collision_ps = 0;
	e_Summon_count = 0;

	//												ステージ記号
	//Bound,			バウンドエネミー			b
	//Homing,			ホーミングエネミー			h
	//Explosion,		爆発エネミー				e
	//Sticky,			スティッキー爆弾エネミー	s
	//Trace,			追従エネミー				t
	//Spring,			バネエネミー				p

	switch (EnemyType)
	{
	case	ENEMY::Bound:	color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Homing:	color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Explosion:	color = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case	ENEMY::Sticky:	color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case	ENEMY::Trace:	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case	ENEMY::Spring:	color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}

//==============================================================================================================================
//	エネミー生成ブロック管理プログラム
//==============================================================================================================================
SUMMONENEMY	summon_enemy[SUMMON_MAX];

/*==================================
	エネミー生成ブロック初期化
====================================*/
void	InitSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Init();
		summon_enemy[i].Prepare();
	}

	Su_enemy = GetEnemy();
	Su_player = GetPlayer();
}

/*==================================
	エネミー生成ブロック終了処理
====================================*/
void	UninitSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Uninit();
	}
}

/*==================================
	エネミー生成ブロック更新処理
====================================*/
void	UpdateSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Update();
	}
}

/*==================================
	エネミー生成ブロック描画処理
====================================*/
void	DrawSummonEnemy()
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		summon_enemy[i].Draw();
	}
}

/*==================================
	エネミー生成ブロックのセット
====================================*/
void	SetSummonEnemys(D3DXVECTOR2 s_pos, const	ENEMY::ENEMY_TYPE&	EnemyType)	//	エネミーのセット
{
	for (int i = 0; i < SUMMON_MAX; i++)
	{
		if (!summon_enemy[i].GetUse())
		{
			summon_enemy[i].SetSummonEnemy(s_pos, EnemyType);
			break;
		}
	}
}

/*==================================
	エネミー生成ブロック取得
====================================*/
SUMMONENEMY* GetSummonEnemy()
{
	return	summon_enemy;
}
