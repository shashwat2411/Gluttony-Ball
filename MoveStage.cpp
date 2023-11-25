
#include	"moveStage.h"

#include	"player.h"
#include	"Enemy.h"
#include	"Ball.h"
#include	"ground.h"
#include	"SummonEnemy.h"
#include	"collision.h"
#include	"Button.h"
#include	"InterlockArrangement.h"
#include	"StageGimmick.h"
#include	"knife.h"
#include	"StickyBomb.h"
#include	"enemyStickyBomb.h"
#include	"Spring.h"
#include	"Explosion.h"
#include	"Waiver.h"
#include	"effect.h"
#include	"oneWayBlock.h"
#include	"bullet.h"
#include	"SavePoint.h"
#include	"Text.h"

PLAYER*	moveStage_player;
ENEMY*	moveStage_enemy;
BALL*	moveStage_ball;
GROUND*	moveStage_ground;
OUT_LINE*	moveStage_outLine;
BUTTON*	moveStage_button;
INTERLOCKARRANGEMENT*	moveStage_interLock;
STAGEGIMMICK* moveStage_stageGimmick;
SUMMONENEMY*	moveStage_summonEnemy;
KNIFE*	moveStage_knife;
STICKYBOMB*	moveStage_stickyBomb;
ENEMY_STICKY_BOMB*	moveStage_enemyStickyBomb;
SPRING*	moveStage_spring;
EXPLOSION*	moveStage_explosion;
WAIVER*	moveStage_waiver;
EFFECT*	moveStage_effect;
ONE_WAY_BLOCK*	moveStage_oneWayBlock;
BULLET*	moveStage_bullet;
SAVE_POINT* moveStage_savePoint;
TEXT* moveStage_text;

int	CountMoveY;

void	InitMoveStage()	//	ステージ移動初期化
{
	CountMoveY = 0;

	moveStage_player = GetPlayer();
	moveStage_enemy = GetEnemy();
	moveStage_ball = GetBall();
	moveStage_ground = GetGround();
	moveStage_outLine = GetOutLine();
	moveStage_summonEnemy = GetSummonEnemy();
	moveStage_button = GetButton();
	moveStage_interLock = GetInterlockArrangement();
	moveStage_stageGimmick = GetStageGimmick();
	moveStage_knife = GetKnife();
	moveStage_spring = GetSpring();
	moveStage_explosion = GetExplosion();
	moveStage_stickyBomb = GetStickyBomb();
	moveStage_enemyStickyBomb = GetEnemyStickyBomb();
	moveStage_waiver = GetWaiver();
	moveStage_effect = GetEffects();
	moveStage_oneWayBlock = GetOneWayBlock();
	moveStage_bullet = GetBullet();
	moveStage_savePoint = GetSavePoint();
	moveStage_text = GetText();
}

void	SetMoveStage(const	int&	way_x, const	int&	way_y)		//	ステージ移動のセット
{
	if (CountMoveY - way_y < STAGE_HEIGHT_MAX / 18)
	{
		CountMoveY -= way_y;

		//	プレイヤーの移動
		moveStage_player->SetUse(false);
		moveStage_player->SetPosi(D3DXVECTOR2(moveStage_player->GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_player->GetPosi().y + BASE_SIZE * 18 * way_y));
		moveStage_player->SetBefPosi(D3DXVECTOR2(moveStage_player->GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_player->GetBefPosi().y + BASE_SIZE * 18 * way_y));

		if (moveStage_ball->GetAbilityMovePlayer() == BALL::TRACE)
		{
			for (int i = 0; i < moveStage_player->GetTraceNum(); i++)
			{
				moveStage_player->GetTracePos()[i] = D3DXVECTOR2(moveStage_player->GetTracePos()[i].x + BASE_SIZE * 32 * way_x,
					moveStage_player->GetTracePos()[i].y + BASE_SIZE * 18 * way_y);
			}
		}

		if (moveStage_ball->GetUse())
		{
			moveStage_ball->SetPosi(D3DXVECTOR2(moveStage_ball->GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_ball->GetPosi().y + BASE_SIZE * 18 * way_y));
			moveStage_ball->SetBefPosi(D3DXVECTOR2(moveStage_ball->GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_ball->GetBefPosi().y + BASE_SIZE * 18 * way_y));

			moveStage_ball->SetSituation(BALL::Return);
		}

		//	エネミーの移動
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (moveStage_enemy[i].GetUse())
			{
				moveStage_enemy[i].SetPosi(D3DXVECTOR2(moveStage_enemy[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_enemy[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_enemy[i].SetBefPosi(D3DXVECTOR2(moveStage_enemy[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_enemy[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		//	グラウンドの移動
		for (int i = 0; i < GROUND_MAX; i++)
		{
			if (moveStage_ground[i].GetUse())
			{
				moveStage_ground[i].SetPosi(D3DXVECTOR2(moveStage_ground[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_ground[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_ground[i].SetBefPosi(D3DXVECTOR2(moveStage_ground[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_ground[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		//　TEXTの移動
		for (int i = 0; i < TEXT_MAX; i++)
		{
			if (moveStage_text[i].GetUse())
			{
				moveStage_text[i].SetPosi(D3DXVECTOR2(moveStage_text[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_text[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_text[i].SetBefPosi(D3DXVECTOR2(moveStage_text[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_text[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		//	アウトラインの移動
		for (int i = 0; i < OUT_LINE_MAX; i++)
		{
			if (moveStage_outLine[i].use)
			{
				moveStage_outLine[i].pos = D3DXVECTOR2(moveStage_outLine[i].pos.x + BASE_SIZE * 32 * way_x, moveStage_outLine[i].pos.y + BASE_SIZE * 18 * way_y);
			}
		}

		//	エネミー発生ブロックの移動
		for (int i = 0; i < SUMMON_MAX; i++)
		{
			if (moveStage_summonEnemy[i].GetUse())
			{
				moveStage_summonEnemy[i].SetPosi(D3DXVECTOR2(moveStage_summonEnemy[i].GetPosi().x + (BASE_SIZE * 32 * way_x), moveStage_summonEnemy[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_summonEnemy[i].SetBefPosi(D3DXVECTOR2(moveStage_summonEnemy[i].GetBefPosi().x + BASE_SIZE * 32, moveStage_summonEnemy[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}
		//	壊れるブロックの移動

		for (int i = 0; i < STAGEGIMMICK_MAX; i++)
		{
			moveStage_stageGimmick[i].SetPosi(D3DXVECTOR2(moveStage_stageGimmick[i].GetPosi().x + (BASE_SIZE * 32 * way_x), moveStage_stageGimmick[i].GetPosi().y + BASE_SIZE * 18 * way_y));
			moveStage_stageGimmick[i].SetBefPosi(D3DXVECTOR2(moveStage_stageGimmick[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_stageGimmick[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));

			if (moveStage_stageGimmick[i].block_type == STAGEGIMMICK::BREAK ||
				moveStage_stageGimmick[i].block_type == STAGEGIMMICK::BREAK_LARGE)	moveStage_stageGimmick[i].SetUse(true);
		}

		for (int i = 0; i < BUTTON_MAX; i++)
		{
			if (moveStage_button[i].GetUse())
			{
				moveStage_button[i].SetPosi(D3DXVECTOR2(moveStage_button[i].GetPosi().x + (BASE_SIZE * 32 * way_x), moveStage_button[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_button[i].SetBefPosi(D3DXVECTOR2(moveStage_button[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_button[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		for (int i = 0; i < INTERLOCKARRANGEMENT_MAX; i++)
		{
			if (moveStage_interLock[i].GetUse())
			{
				moveStage_interLock[i].SetPosi(D3DXVECTOR2(moveStage_interLock[i].GetPosi().x + (BASE_SIZE * 32 * way_x), moveStage_interLock[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_interLock[i].SetBefPosi(D3DXVECTOR2(moveStage_interLock[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_interLock[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		for (int i = 0; i < SPRING_MAX; i++)
		{
			if (moveStage_spring[i].GetUse())
			{
				moveStage_spring[i].SetPosi(D3DXVECTOR2(moveStage_spring[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_spring[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_spring[i].SetBefPosi(D3DXVECTOR2(moveStage_spring[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_spring[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		for (int i = 0; i < ONE_WAY_BLOCK_MAX; i++)
		{
			if (moveStage_oneWayBlock[i].GetUse())
			{
				moveStage_oneWayBlock[i].SetPosi(D3DXVECTOR2(moveStage_oneWayBlock[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_oneWayBlock[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_oneWayBlock[i].SetBefPosi(D3DXVECTOR2(moveStage_oneWayBlock[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_oneWayBlock[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		//　セーブポイントの移動
		for (int i = 0; i < SAVE_POINT_MAX; i++)
		{
			if (moveStage_savePoint[i].GetUse())
			{
				moveStage_savePoint[i].SetPosi(D3DXVECTOR2(moveStage_savePoint[i].GetPosi().x + BASE_SIZE * 32 * way_x, moveStage_savePoint[i].GetPosi().y + BASE_SIZE * 18 * way_y));
				moveStage_savePoint[i].SetBefPosi(D3DXVECTOR2(moveStage_savePoint[i].GetBefPosi().x + BASE_SIZE * 32 * way_x, moveStage_savePoint[i].GetBefPosi().y + BASE_SIZE * 18 * way_y));
			}
		}

		for (int i = 0; i < KNIFE_MAX; i++)
		{
			if (moveStage_knife[i].GetUse())
			{
				moveStage_knife[i].SetUse(false);
			}
		}

		for (int i = 0; i < STICKYBOMB_MAX; i++)
		{
			if (moveStage_stickyBomb[i].GetUse())
			{
				moveStage_stickyBomb[i].SetUse(false);
			}
		}

		for (int i = 0; i < ENEMY_STICKY_BOMB_MAX; i++)
		{
			if (moveStage_enemyStickyBomb[i].GetUse())
			{
				moveStage_enemyStickyBomb[i].SetUse(false);
			}
		}

		for (int i = 0; i < EXPLOSION_MAX; i++)
		{
			if (moveStage_explosion[i].GetUse())
			{
				moveStage_explosion[i].SetUse(false);
			}
		}

		for (int i = 0; i < WAIVER_MAX; i++)
		{
			if (moveStage_waiver[i].GetUse())
			{
				moveStage_waiver[i].SetUse(false);
			}
		}

		for (int i = 0; i < EFFECT_MAX; i++)
		{
			if (moveStage_effect[i].GetUse())
			{
				moveStage_effect[i].SetUse(false);
			}
		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (moveStage_bullet[i].GetUse())
			{
				moveStage_bullet[i].SetUse(false);
			}
		}

		moveStage_player->SetUse(true);
	}
}












