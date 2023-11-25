
#include	"stage.h"
#include	<conio.h>
#include	"player.h"
#include	"ground.h"
#include	"SummonEnemy.h"
#include	"Button.h"
#include	"InterlockArrangement.h"
#include	"StageGimmick.h"
#include	"oneWayBlock.h"
#include	"SavePoint.h"
#include	"Text.h"

#define CHAR


char StageNumChar[STAGE_MAX + 1][STAGE_HEIGHT_MAX + 1][STAGE_WIDTH_MAX + 1];


/*	ステージ情報：0,empty	1,プレイヤー初期位置	2,地面ブロック	3,エネミー
*/

PLAYER*	s_player;
BUTTON*	s_button;

void	InitStage()	//	ステージ初期化
{
	s_player = GetPlayer();
	s_button = GetButton();

	InitializeStage();
}

void	UninitStage()	//	ステージ終了処理
{

}

void	UpdateStage()	//	ステージ更新処理
{

}

void	MakeStage(const	int	stage_num)	//	ステージ作成
{
	bool	PlayerPosBool = false;
	D3DXVECTOR2	playerPos = D3DXVECTOR2(0, 0);
	D3DXVECTOR2	leftup = D3DXVECTOR2(0, 0);
	D3DXVECTOR2	rightdown = D3DXVECTOR2(0, 0);

	for (int y = 0; y < STAGE_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < STAGE_WIDTH_MAX; x++)
		{
			//=====================================================================================================
			//	プレイヤー設置
			if (GetStageChar(stage_num, x, y) == 'P')
			{
				if (PlayerPosBool)
				{
					playerPos.x = ((float)x + 0.5f) * BASE_SIZE;
					playerPos.y = ((float)y - 0.5f) * BASE_SIZE;
					s_player->SetPosi((playerPos - s_player->GetPosi()) / 2 + s_player->GetPosi());
					s_player->SetBefPosi((playerPos - s_player->GetPosi()) / 2 + s_player->GetPosi());
				}
				else
				{
					PlayerPosBool = true;
					s_player->SetUse(true);
					s_player->SetPosi(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y - 0.5f) * BASE_SIZE));
					s_player->SetBefPosi(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y - 0.5f) * BASE_SIZE));
				}
			}
			//======================================================================================================
			//	グラウンド設置
			else if (GetStageChar(stage_num, x, y) == 'g')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'g'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'g'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetGround(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup));
				SetOutLine(stage_num, leftup, rightdown);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, 'Q');
					}
				}
			}
			//======================================================================================================
			//	壊れるブロック設置(塊)
			else if (GetStageChar(stage_num, x, y) == 'd')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'd'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'd'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetStageGimmicks(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), STAGEGIMMICK::BREAK_LARGE);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//=========================================================================================================
			//	ダメージ床の設置
			else if (GetStageChar(stage_num, x, y) == 'X')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'X'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'X'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetStageGimmicks(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), STAGEGIMMICK::DIE);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//=========================================================================================================
			//	ボタン式扉設置
			else if (GetStageChar(stage_num, x, y) == 'D')
			{
				int	ButtonNum = GetStageChar(stage_num, x - 1, y) - 48;

				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'D'; rightdown.y++)
				{
					bool	pass = false;
					for (int i = 0; i < 9; i++)
					{
						if (GetStageChar(stage_num, x - 1, rightdown.y) != ' ' && i != ButtonNum)
							if (GetStageChar(stage_num, x - 1, rightdown.y) - 48 == i)
							{
								pass = true;
								break;
							}
					}

					if (!pass)
					{
						int	count_width;
						for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'D'; count_width++);

						if (rightdown.x > count_width)	rightdown.x = count_width;
					}
					else break;
				}

				SetInterlockArrangements(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), ButtonNum);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			else if (GetStageChar(stage_num, x, y) == 'q')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'q'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'q'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetStageGimmicks(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), STAGEGIMMICK::STEAL);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//======================================================================================================
			//	中間保存ブロック設置
			else if (GetStageChar(stage_num, x, y) == 'S')
			{
			leftup.x = x;
			leftup.y = y;
			rightdown.x = STAGE_WIDTH_MAX * 2;

			for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'S'; rightdown.y++)
			{
				int	count_width;
				for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'S'; count_width++);

				if (rightdown.x > count_width)	rightdown.x = count_width;
			}

			SetSavePoint(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), (rightdown - leftup) * BASE_SIZE);	//　セーブポイントを設置

			for (int loop_y = y; loop_y < rightdown.y; loop_y++)
			{
				for (int loop_x = x; loop_x < rightdown.x; loop_x++)
				{
					SetStageChar(stage_num, loop_x, loop_y, '-');
				}
			}
			}
			//======================================================================================================
			//	一方通行ブロック設置：上
			else if (GetStageChar(stage_num, x, y) == '^')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == '^'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == '^'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetOneWayBlock(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), ONE_WAY_BLOCK::UP);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//======================================================================================================
			//	一方通行ブロック設置：下
			else if (GetStageChar(stage_num, x, y) == 'Y')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == 'Y'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == 'Y'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetOneWayBlock(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), ONE_WAY_BLOCK::DOWN);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//======================================================================================================
			//	一方通行ブロック設置：右
			else if (GetStageChar(stage_num, x, y) == '>')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == '>'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == '>'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetOneWayBlock(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), ONE_WAY_BLOCK::RIGHT);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//======================================================================================================
			//	一方通行ブロック設置：左
			else if (GetStageChar(stage_num, x, y) == '<')
			{
				leftup.x = x;
				leftup.y = y;
				rightdown.x = STAGE_WIDTH_MAX * 2;

				for (rightdown.y = y; GetStageChar(stage_num, x, rightdown.y) == '<'; rightdown.y++)
				{
					int	count_width;
					for (count_width = x; GetStageChar(stage_num, count_width, rightdown.y) == '<'; count_width++);

					if (rightdown.x > count_width)	rightdown.x = count_width;
				}

				SetOneWayBlock(((rightdown - leftup) / 2 + leftup) * BASE_SIZE, (rightdown - leftup), ONE_WAY_BLOCK::LEFT);

				for (int loop_y = y; loop_y < rightdown.y; loop_y++)
				{
					for (int loop_x = x; loop_x < rightdown.x; loop_x++)
					{
						SetStageChar(stage_num, loop_x, loop_y, '-');
					}
				}
			}
			//=========================================================================================================
			//	エネミー設置
			else //if (GetStageChar(stage_num, x, y) == 'e')
			{
				//SetEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(0.1f, 1));
				
				switch (GetStageChar(stage_num, x, y))
				{
				case	'b':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Bound);
					break;
				case	'h':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Homing);
					break;
				case	'e':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Explosion);
					break;
				case	's':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Sticky);
					break;
				case	't':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Trace);
					break;
				case	'p':	SetSummonEnemys(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), ENEMY::Spring);
					break;
				case	'W':	SetStageGimmicks(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(BASE_SIZE, BASE_SIZE), STAGEGIMMICK::WIN);
					break;
				case	'n':	SetStageGimmicks(D3DXVECTOR2(x, y), D3DXVECTOR2(BASE_SIZE, BASE_SIZE),STAGEGIMMICK::NEEDLE);
					break;
				case	'B':	SetStageGimmicks(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(BASE_SIZE, BASE_SIZE), STAGEGIMMICK::BREAK);
					break;
				case	'M':	SetStageGimmicks(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE), STAGEGIMMICK::MOVE);
					break;
				case	'V':	SetStageGimmicks(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(BASE_SIZE, BASE_SIZE), STAGEGIMMICK::FALL);
					break;
				case	'C':	SetButtons(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(1, 1), false, GetStageChar(stage_num, x - 1, y) - 48);
					if (stage_num == 1 && GetStageChar(stage_num, x - 1, y) - 48 >= 0 && GetStageChar(stage_num, x - 1, y) - 48 < 4)	s_button[GetStageChar(stage_num, x - 1, y) - 48].SetSaveAble(true);
					break;
				case	'c':	SetButtons(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), D3DXVECTOR2(1, 1), true, GetStageChar(stage_num, x - 1, y) - 48);
					if (stage_num == 1 && GetStageChar(stage_num, x - 1, y) - 48 >= 0 && GetStageChar(stage_num, x - 1, y) - 48 < 4)	s_button[GetStageChar(stage_num, x - 1, y) - 48].SetSaveAble(true);
					break;
				case	'T':	SetText(D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE), GetStageChar(stage_num, x - 1, y) - 48);
					break;
				default:
					break;
				}
			}

//												ステージ記号
//Bound,			バウンドエネミー			b
//Homing,			ホーミングエネミー			h
//Explosion,		爆発エネミー				e
//Sticky,			スティッキー爆弾エネミー	s
//Trace,			追従エネミー				t
//Spring,			バネエネミー				p

		}
	}

	SetSideOutLine(stage_num);
	LoadSavePoint();	//セーブポイントでセーブした情報をロード
}



void	SetStageChar(const	int	stage_num, const	int	x, const	int	y, const	char	num)	//	ステージ情報セット
{
	StageNumChar[stage_num][y][x] = num;
}

const	char&	GetStageChar(const	int	stage_num, const	int	x, const	int	y)				//	ステージ情報取得
{
	return	StageNumChar[stage_num][y][x];
}

//												ステージ記号
//Bound,			バウンドエネミー			b
//Homing,			ホーミングエネミー			h
//Explosion,		爆発エネミー				e
//Sticky,			スティッキー爆弾エネミー	s
//Trace,			追従エネミー				t
//Spring,			バネエネミー				p

//WinningBlock		勝利条件のブロック			W
//
//StealBlock		能力没収ブロック			q

//画面分けの目印								x

//==================================================================================================================

//==================================================================================================================
//
void InitializeStage()
{
	sprintf(StageNumChar[0][0],		"gGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][1],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][2],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][3],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][4],		"g                               g                              gg                              x               4T              g                                g                              g|");
	sprintf(StageNumChar[0][5],		"g                               g    0T        1T      2T      gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][6],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][7],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][8],		"g                               g                              gg                              x                               g                                g                              g|");
	sprintf(StageNumChar[0][9],		"g                               g                              gg                    ggggggggggggggggg    gggg                 g                                g                              g|");
	sprintf(StageNumChar[0][10],	"g                               g                              gg                              gg                gggg          g                                g                              g|");
	sprintf(StageNumChar[0][11],	"g                               g                              gg                              gg                              g                                g                              g|");
	sprintf(StageNumChar[0][12],	"g                               g                              gg                        3T    gg                              g                                g                              g|");
	sprintf(StageNumChar[0][13],	"g                               g        gg                    x                               gg                      ggggggggg                                g                              g|");
	sprintf(StageNumChar[0][14],	"g                               g        gg                    x                               gg            g         ddddd   g                                g                              g|");
	sprintf(StageNumChar[0][15],	"g                               g P      gg                    x                p              gg     e      g         ddddd   g                                g                              g|");
	sprintf(StageNumChar[0][16],	"g                               g P      gg                    x         gggggggggggggggggggggggg            g         ddddd   g                                g                              g|");
	sprintf(StageNumChar[0][17],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][18],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][19],	"g                              gg                              gggggggggggggggggggggggggggggggggg                          q   gg                               g                              g|");
	sprintf(StageNumChar[0][20],	"g                              gg                              ggggggggg                 gggggggg                          q   gg                               g                              g|");
	sprintf(StageNumChar[0][21],	"g                              gg                              ggggggggg                 gggggggg                     5T   gggggg                               g                              g|");
	sprintf(StageNumChar[0][22],	"g                              gg                              ggggggggg                 gggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][23],	"g                              gg     8T                  1C   ggggggggg                 gggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][24],	"g                              gg                  ggggggggggggggggggggg       7T        gggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][25],	"g                              gg                              ggggggggg                 gggggggg                          gggggg                               g                              g|");
	sprintf(StageNumChar[0][26],	"g                              gg                              ggggggggg                 gggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][27],	"g                              gg                              ggggggggg                 gggggggg           b                  gg                               g                              g|");
	sprintf(StageNumChar[0][28],	"g                              1DDDDDDDDDDDgg                  ggggggggg                 gggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][29],	"g                              gg          gg                  gggggggggggggggggggggggggggggggggg                          gggggg                               g                              g|");
	sprintf(StageNumChar[0][30],	"g                              gg          gg                  gggggggggggggggggggggggggggggggggg   6T                         gg                               g                              g|");
	sprintf(StageNumChar[0][31],	"g                              gg W        gg                  gggggggggggggggggggggggggggggggggg                              gg                               g                              g|");
	sprintf(StageNumChar[0][32],	"g                              gggggggggggggg                  x                                x                              gg                               g                              g|");
	sprintf(StageNumChar[0][33],	"g                              gggggggggggggg                  x      p                         x                          gggggg                               g                              g|");
	sprintf(StageNumChar[0][34],	"g                              gggggggggggggg                  x                                x                          gggggg                               g                              g|");
	sprintf(StageNumChar[0][35],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][36],	"________________________________________________________________________________________________________________________________________________________________________________________________|");

	//	ホーミング、スティッキー爆弾、スプリング
	sprintf(StageNumChar[1][0],		"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][1],		"g                              gg                              gg         0D1D2D3D   g         gg   g                         ggg          d         d         xS     g8C                      g|");
	sprintf(StageNumChar[1][2],		"g                              gg                           4C gg          D D D D   g         gg h g                         ggg          d         d         xS     g                     9c g|");
	sprintf(StageNumChar[1][3],		"g 6c                       5C  gg  h                           gg          D D D D   g         gg   g                         ggg          d         d         xS     gggggggggggggggggggggg   g|");
	sprintf(StageNumChar[1][4],		"g                              gg         ggggggggggggggggggggggg          D D D D W g         gg   g               g         ggg          d         d^^^^^^^^^gg                          g   g|");
	sprintf(StageNumChar[1][5],		"g     ggggggggggggggggggggYYYYYgg                              gg        ggggggggggggg         gg   g       s       g         ggg          d         d       < gg^^                        g   g|");
	sprintf(StageNumChar[1][6],		"g     g                        gg                              gg                              gg   g               g         ggg          d         d       < gg         ^^       ^^      g   g|");
	sprintf(StageNumChar[1][7],		"g     g                        gg                              gg                              gg   ggggggggggggggggg         ggg          d         d       < gg                          g   g|");
	sprintf(StageNumChar[1][8],		"g     >                        gg                              xq    ^^^^                      q                    g         ggg          d         d       < gg                          gdddg|");
	sprintf(StageNumChar[1][9],		"g     >                        4D                              xq                              q                    g         ggg          d^^^^^^^^^^^^^^^^^< gg^^                        gdddg|");
	sprintf(StageNumChar[1][10],	"g 7C  >                        xD                              xq                              gggg                 g p       ggg          d                 < gg                              g|");
	sprintf(StageNumChar[1][11],	"g     >                        xD                              gggggg^^^^g            g^^^^gggggggg                 ggggg     ggg          d                 < gg                              g|");
	sprintf(StageNumChar[1][12],	"g    7DDDDDDDDDDDDDDDDDDDDDDDDDggggggggggggggggggggggggggggggggg     SSS g            g SSS    gggg                           ggg          d                 < gg                              g|");
	sprintf(StageNumChar[1][13],	"g                             5D                              qx     SSS g            g SSS    xq 8D                        dd x           d                 < gg^^YYYYYYYYYYYYYYYYYYYYYYYYg   g|");
	sprintf(StageNumChar[1][14],	"g                              D                              qx     ggggggg        ggggggg    xq  D                        dd x           d                 < gg                          g   g|");
	sprintf(StageNumChar[1][15],	"g                              D                              qx         g            g        xq  D                        dd x           d                 < gg 9DDDDDDDDDDDDDDDDDDDDDDDDg   g|");
	sprintf(StageNumChar[1][16],	"6DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD                              qx      2C g            g3C      xq  D                        dd g^^^^^^^^^^^^^^^^^^^^^^^^^^^^^< gg  BBBBBBBBBBBBBBBBBBBBBBBBg   g|");
	sprintf(StageNumChar[1][17],	"gXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXggggggggggggggggggggggggggggggggggggggggggg   ^^^^^^   gggggggggggggggggggggggggggggggggggggggggg                             < ggggXXXXXXXXXXXXXXXXXXXXXXXXggggg|");
	sprintf(StageNumChar[1][18],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   ^^^^^^   gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][19],	"g    ddddddddddddddddddddddddddx                               q      0C g            g1C      xq                              x                               x                               g|");
	sprintf(StageNumChar[1][20],	"g    ddddddddddddddddddddddddddx                               q         g   VV       g        xq                              x                               x                               g|");
	sprintf(StageNumChar[1][21],	"g  ddddddddddddddddddddddddddddx                               q     ggggg            ggggg    xq                              x                      g       gx                               g|");
	sprintf(StageNumChar[1][22],	"g  dd                          ggggggggggggggggggggggggggggggggg       S >            < S      xggggggggggggggggggggggggggggggggg            VV       gg      gggggg          M           g    g|");
	sprintf(StageNumChar[1][23],	"g    ddddddddddddddddddddddddddgg                              g       S >       VV   < S      xg          g    g    g         gg                             ggg                         g    g|");
	sprintf(StageNumChar[1][24],	"g    ddddd ddddddddddddddddddddgg        s                     gggggggggg>            <gggggggggg          g         g         gg                             ggg                         g    g|");
	sprintf(StageNumChar[1][25],	"g    ddddd ddddddddddddddddddddgg                              gg                              gg          g         g    g    gg                             ggg                         g    g|");
	sprintf(StageNumChar[1][26],	"gddddddddd ddddddddddddddddddddgg                              gg                              gg          g         g    g    gggg                           ggg                         g    g|");
	sprintf(StageNumChar[1][27],	"gddddddddd ddddddddddddddddddddgg                              gg            VV                gg          g    g    g    g    gggg                           ggg                         g    g|");
	sprintf(StageNumChar[1][28],	"gdddd      ddddddddddddddddddddgg                              gg                              gg               g    g    g    x  g                           ggg                         g    g|");
	sprintf(StageNumChar[1][29],	"gddddddddd ddddddddddddddddddddgg                              gg                              gg               g    g    g    x  g                           ggg                         g    g|");
	sprintf(StageNumChar[1][30],	"gddddddddd    ddddddddddddddd  gg                              gg                              gg               g    g    g    gg g                           ggg                         g    g|");
	sprintf(StageNumChar[1][31],	"gddddddddddddd           dddd  x                               xq                VV            q           g    g         g    gg g                           ggg                         g    g|");
	sprintf(StageNumChar[1][32],	"gdddddddddddddddddddddddddddd  x                               xq                              q           g    g         g    gg gYYYYYXXXYYYYYYXXXYYYYYXXXYYggg                         g    g|");
	sprintf(StageNumChar[1][33],	"gdddd     ddddddddddddddd      x                               xq              P               q           g    g    g    g    gg                              x SSS                           g|");
	sprintf(StageNumChar[1][34],	"gdddddddddddddddddddddddddddd  x       e        e              xq              P               q      p    g    g    g    g    gg                              x SSS                           g|");
	sprintf(StageNumChar[1][35],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg    ggggggggggggggggggggggggggggggggggggggggggg         gg         ggggggg|");
	sprintf(StageNumChar[1][36],	"________________________________________________________________________________________________________________________________________________________________________________________________|");

	//	ホーミング、爆発、追従
	sprintf(StageNumChar[2][0], "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[2][1], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB S                              gg                              x  g                          q gg                              gg                              g|");
	sprintf(StageNumChar[2][2], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB S                              gg                              x  g                          q gg                              gg                              g|");
	sprintf(StageNumChar[2][3], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB S                              gg                              x  g                          q gg                              gg h                          h g|");
	sprintf(StageNumChar[2][4], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBggdddddg                        gg                              gg g                          q gg                              gg   ggggggXXXXXXXXXXXXXXXXXX   g|");
	sprintf(StageNumChar[2][5], "g               M              ggdddddg                        gg                              gg g                          q gg                              gg        g                 X   g|");
	sprintf(StageNumChar[2][6], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBggdddddg                        ggYYYYYYYYYYYYYYYYYYYYYYYYYYY   gg g                          q gg                              gg        g                 X   g|");
	sprintf(StageNumChar[2][7], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBgg^^   g       M                gg              M           g^^^gg g   gggggggggggggggggggggggg gg                              gg h    W g                 X   g|");
	sprintf(StageNumChar[2][8], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBggdddddg                        gg                              gg g                          g gg                              ggggggggggg                 X   g|");
	sprintf(StageNumChar[2][9], "gggg           VV           gggggdddddg                        gg                              gg g                          g gg                              gg            ggggggggggggggX   g|");
	sprintf(StageNumChar[2][10], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBggdddddg                        gg                              gg g                          g gg                              gg                              g|");
	sprintf(StageNumChar[2][11], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBgg^^   g           M            gg                              gg g                          g gg                              gg                              g|");
	sprintf(StageNumChar[2][12], "gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBggdddddg                        gg         g         g          gg gXXXXggggggggggggggggggg   g gg                              gg                            h g|");
	sprintf(StageNumChar[2][13], "g         VV        VV         ggdddddgXXXXXXXXXXXXXXXXXXXXXXXXgg         g         g          gg                            g gg             ggggggggggggggggggg     ^^^^^^^XXXXXXXXXXXXXXXXXXg|");
	sprintf(StageNumChar[2][14], "g                              ggddddd                         gg         g         g          gg                            g gg             g                x                         SSS   g|");
	sprintf(StageNumChar[2][15], "g                              gg                              ggSSS      g         g          gg                            g gg             g                x                         SSS   g|");
	sprintf(StageNumChar[2][16], "g                           e  ggdddddddddd                    ggSSS      g         g          gg                            g gg             g e              x                         SSS   g|");
	sprintf(StageNumChar[2][17], "g^^^gggggggggggggggggggggggggggggXXXXXXXXXXggggggggggggggggg   gg^^^gggggggggggggggggggggggggggggggggggggggggggggggggggggXXXXg ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg^^^g|");
	sprintf(StageNumChar[2][18], "g^^^gggggggggggggggggggggggggggggggggggggggggggggggggggggggg   gg^^^gggggggggggggggggggggggggggggggggggggggggggggggggggggggggg ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg^^^g|");
	sprintf(StageNumChar[2][19], "g   g                      <   gg                           SSSgg                         g    gg                           SSSgg    4DD               3DD     gg   g                          g|");
	sprintf(StageNumChar[2][20], "g^^^g                      <   gg                           SSSgg                         g  t gg                           SSSgg6C   DD       7c       DD  8C gg t g                          g|");
	sprintf(StageNumChar[2][21], "g   g                      g   gg                           SSSggg                        g    gg                           SSSgg     DD                DD     gg   g    ^^^^^^^^^^^^^^^^^^^^^^g|");
	sprintf(StageNumChar[2][22], "g   g                      g   gg           q    q    q     SSSggggg                      g    gg^ggg   ggggggggggggggggggggggggg   gggg                gggg   gg   g                          g|");
	sprintf(StageNumChar[2][23], "g^^^g                      g   ggddd        q    q    q     SSSgg                         g    gg   g                          gg   g                      g   gg   g                          g|");
	sprintf(StageNumChar[2][24], "g   g                      g   ggdddggggggggggggggggggggggggggggg            gg           g    gg   g                          gg           2DD 7DD            gg   g^^^^                      g|");
	sprintf(StageNumChar[2][25], "g   g            M         g   ggddd     qqqqqqqqqqqqqq        gg                         g    gg   g                          gg4C          DD  DD         5c gg   g                          g|");
	sprintf(StageNumChar[2][26], "g^^^g                      g   gg        qqqqqqqqqqqqqq        gg                       ggg    gg h g^^^               ddddg   gg            DD  DD            gg   g                          g|");
	sprintf(StageNumChar[2][27], "g   g                      g   gg        qqqqqqqqqqqqqq        gg                         g    gg   g             ^^^^^g   g   ggYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYgg   g                          g|");
	sprintf(StageNumChar[2][28], "g   g                      g   gg^^^^gggggggggggggggggggg      gg            gg           g    gg   g                  g   gggggg                        8DD  6DD   g                          g|");
	sprintf(StageNumChar[2][29], "g^^^g  P    ggg            g   gg                              gg                         g    g1DDDg      ^^^^^       g    SSSx                          DD   DD   g                          g|");
	sprintf(StageNumChar[2][30], "g   g  P                   g   gg                              gg                         g    gg                      g    SSSx                          DD   DD   g                          g|");
	sprintf(StageNumChar[2][31], "g   gggggg                 g   gggggg                     gggggggggg                      g    gg                      g    SSSx    gggggggggggggggggggggggg^^^gg   g                          g|");
	sprintf(StageNumChar[2][32], "g^^^0D          ggg        g   gg                         dd  qx                               gg       ggggggggggggggggggggggggg^^^                       5DDDgg                              g|");
	sprintf(StageNumChar[2][33], "g    D                     g   gg                         dd  qx                               gg       <                      gg2C                         3C gg                              g|");
	sprintf(StageNumChar[2][34], "g    D                     g0C gg                         dd  qx                               gg       <                    1Cgg                              gg                           9c g|");
	sprintf(StageNumChar[2][35], "ggggggg       M            ggggggggggggggggggXXXXXXggggggggggggggggggggggggggggggggggggggggggggggggggggggXXXXXXXXXXXXXXXXXXXXXXgggggggggggggggggggggggggggggggggggggg            9DDD          g|");
	sprintf(StageNumChar[2][36], "________________________________________________________________________________________________________________________________________________________________________________________________|");

	/*	ステージ2
			バウンド能力、スティッキー爆弾、追従
	*/
	sprintf(StageNumChar[3][0], "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[3][1], "g                           q  x            dd  <ddddddddddddg x    <dddddd  ddddd  dddddd     gg    <                       g qBB                             gg n                          n g|");
	sprintf(StageNumChar[3][2], "g                           q  x            dd  <ddddddddddddg x    <dddddd  ddddd  dddddd     gg    <                       g qBB          s       s          gg              s               g|");
	sprintf(StageNumChar[3][3], "g W                         q  x            dd  <ddddddddddddg x g  <dddddd  ddddd  dddddd     gg g  <                       g qBB                             gg                              g|");
	sprintf(StageNumChar[3][4], "ggggggggYYYYYYYYYYYYYYYYYYYYgggggggggggggggggggggddddddddddddg ggggg<ddddddXX     XXddddddX  ^^gg g  <                       g qBB                             gg          nnnnnnnnn           g|");
	sprintf(StageNumChar[3][5], "g     dddddddddddddddddddddd>  x                             g ggggg ddddddX       XddddddX    gg ggggXXXXXXXXXXXXXXXXXXXX^^^g gg B B B B B B B B B B B B B B  gg     ggg               ggg    g|");
	sprintf(StageNumChar[3][6], "g     dddddddddddddddddddddd>  x                             g ggggg dddddd         ddddddX    gg g                       >  g ggB B B B B B B B B B B B B B   gg                              g|");
	sprintf(StageNumChar[3][7], "g     dddddddddddddddddddddd>  g                             g ggggg dddddd         ddddddX    gg g                       >  g gg B B B B B B B B B B B B B B  gg                              g|");
	sprintf(StageNumChar[3][8], "g     dddddddddddddddddddddd>  g                             g ggggg dddddd    X    ddddddX  ^^gg g                       >  g ggB B B B B B B B B B B B B B   gg                              g|");
	sprintf(StageNumChar[3][9], "g^^^^^ddddddddddddddddddddddggggggYYYYYYYYYYYYYYYYYYYYYYYYYYYg ggggg dddddd    g    ddddddX    gg g^^^XXXXXXXXXXXXXXXXXXXXgggg gggB B B B B B B B B B B B B B  gggg                          ggg|");
	sprintf(StageNumChar[3][10], "g     dd                       x  dddddddddddddddddddddddddddg gggggXXXXXXX    g    XXXXXXX    gg g  <                       g ggB B B B B B B B B B B B B B   gg                              g|");
	sprintf(StageNumChar[3][11], "g     dd                       x  dddddddddddddddddddddddddddg gg              g               gg g  <                       g gg B B B B B B B B B B B B B B  gg                              g|");
	sprintf(StageNumChar[3][12], "g     dd                     g x  dddddddddddddddddddddddddddg gg              g             ^^gg g  <                       g ggBgB B B B B B B B B B B B B   gg                              g|");
	sprintf(StageNumChar[3][13], "g     dd                    gggggg                           g gg             ggg              gg ggggXXXXXXXXXXXXXXXXXX  ^^^g gggB B B B B B B B B B B B B B  gggggggg                 gggggggg|");
	sprintf(StageNumChar[3][14], "g             X             g  x                             g gg      s      ggg              x  g                     SSSSS  ggB B B B B B B B B B B B B B   x  ddd                   S q    g|");
	sprintf(StageNumChar[3][15], "g             X             g  x                         SSSSS gg             ggg              x  g    t          b     SSSSS  gg B B B B B B B B B B B B B B  x  ddd                   S q    g|");
	sprintf(StageNumChar[3][16], "g             X             g  x                         SSSSS gg             ggg         gggg x  g                     SSSSS  ggB B B B B B B B B B B B B B   x  ddd                   S q    g|");
	sprintf(StageNumChar[3][17], "gXXXXXgggXXXXXXXXXXXXXXXXXXXgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggXXXXXXXXXXXXXXXXXXXXXXXXXXXXgggggggggggggggggggggggggggggg  ^^g|");
	sprintf(StageNumChar[3][18], "ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg  ^^g|");
	sprintf(StageNumChar[3][19], "g       n                      x                               gg                              q S                         0C  gggggggXXX                      gg                    9C g 9D   g|");
	sprintf(StageNumChar[3][20], "g                              x                             t gg                              q S                             ggg                             gg                       g  D ggg|");
	sprintf(StageNumChar[3][21], "g                              x                               gg            M                ggggggg                          ggg               XXX           gg                       g  D ggg|");
	sprintf(StageNumChar[3][22], "g                           ggggggggggggggggggXXXXXXXXXXXXXXXXXgg                    XXXXXXXXXXgg0DDDDDDDDDDDDDDDDDDDDDDDDDDDDDggg               XXX      g    gg                       g  ggggg|");
	sprintf(StageNumChar[3][23], "g M                         gggg    n                n         gg                              ggg                             ggg               XXX      ggg  gg8C        XXXXXXXXXXXXXg 8D   g|");
	sprintf(StageNumChar[3][24], "g                          Xgggg                           X   gggg                            ggg                  1C         ggg    gX                 X     gg                       g  D   g|");
	sprintf(StageNumChar[3][25], "g            X             ngggg             X             n   gg                              gg1DDDDDDDDDDDDDDDDDDDDDDDDDDDDDggX    g X               X      gg                       g  D   g|");
	sprintf(StageNumChar[3][26], "g            n              gggg             n                 gg                              ggg            XX               ggX    g  X             X       gg                       gggg   g|");
	sprintf(StageNumChar[3][27], "g                  M        gggg                 X             gg                              ggg 2C      3C XX               ggX    g   X           X      ggggXXXXXXXXX           7C g 7D   g|");
	sprintf(StageNumChar[3][28], "g                           gggg       X         n             ggXXXXgggg  XXXX  gggggXXXXXX   gg2DDDDDDDDDDDDX3DDDDDDDDDDDDDDDggX    g    X         X         gg                       g  D   g|");
	sprintf(StageNumChar[3][29], "g                           gggg       n                       x                               ggg            XX      5C       ggX  6Cg     X       X          gg                       g  D   g|");
	sprintf(StageNumChar[3][30], "g                           gggg                               x                               ggg     4C     XXggggggggggggggggggggggg      XXXXXXX           gg                XXXXXXXg  ggggg|");
	sprintf(StageNumChar[3][31], "g                       M   gggg                               x                             gggg4DDDDDDDDDDDDX5DDDDDDDDDDDDDDDgg                         ggggggg                              g|");
	sprintf(StageNumChar[3][32], "g                              xSSS                            x                               ggX  X  X  X     DDDDDDDDDDDDDDDx                              6D     g                         g|");
	sprintf(StageNumChar[3][33], "g  P                           xSSS                            x                               ggX  X  X  X     DDDDDDDDDDDDDDDx                      b        D     g                         g|");
	sprintf(StageNumChar[3][34], "g  P                           xSSS                            x                               gg     M         DDDDDDDDDDDDDDDx                               D     g                   ggggggg|");
	sprintf(StageNumChar[3][35], "gggggggggggggggggggggggggggggggggggg         ggggg         ggggggggg        gggg        gggg   gg                             gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[3][36], "________________________________________________________________________________________________________________________________________________________________________________________________|");

	sprintf(StageNumChar[4][0],  "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[4][1],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][2],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][3],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][4],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][5],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][6],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][7],  "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][8],  "g       h               0C      x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][9],  "g                               x                              gg                              gx             b                g|");
	sprintf(StageNumChar[4][10], "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][11], "g                               x                              gg   0DDDDD                     gx                              g|");
	sprintf(StageNumChar[4][12], "g                               x                              gg    DDDDD                     gx                              g|");
	sprintf(StageNumChar[4][13], "g                               x                              gg    DDDDD                     gx                              g|");
	sprintf(StageNumChar[4][14], "g                               x                              gg                              gx                              g|");
	sprintf(StageNumChar[4][15], "g    P                          x                              gx                               x                              g|");
	sprintf(StageNumChar[4][16], "g    P                          x                              gx                               x                              g|");
	sprintf(StageNumChar[4][17], "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[4][18], "________________________________________________________________________________________________________________________________|");

	/*	//旧ステージ1
	sprintf(StageNumChar[0][0], "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][1], "g                              gg                              gg                              gx                                g|");
	sprintf(StageNumChar[0][2], "g                              gg                              gg                              gx                                g|");
	sprintf(StageNumChar[0][3], "g                              gg                              gg                              gx                                g|");
	sprintf(StageNumChar[0][4], "g                              gg          ggggg  gggg         gg     ggggggggggggggg      g   gx                                g|");
	sprintf(StageNumChar[0][5], "g                              gg                              gg     g             g      g   gx                                g|");
	sprintf(StageNumChar[0][6], "g   ggggggggggggggggg          gg                              gg     g             g      g   gx                                g|");
	sprintf(StageNumChar[0][7], "g                   g          gg                              gg     g             g      g   gx                                g|");
	sprintf(StageNumChar[0][8], "g                   g          q                               gg     g    b        g      g   gx                                g|");
	sprintf(StageNumChar[0][9], "g                   g          q                               gg     g             g      g   gx                                g|");
	sprintf(StageNumChar[0][10], "g             p     g          q        ggg           ggg      gg     ggggggggggg          g W gx                                g|");
	sprintf(StageNumChar[0][11], "gggggggggg   ggg    g          q                               gg                          gggggx                                g|");
	sprintf(StageNumChar[0][12], "g                   g          q                               gg           p           ggg    gx                                g|");
	sprintf(StageNumChar[0][13], "g                   g          q                               q                               gx                                g|");
	sprintf(StageNumChar[0][14], "g  P                g          q                               q                               gx                                g|");
	sprintf(StageNumChar[0][15], "g  P                g        e q                p              q                               gx                                g|");
	sprintf(StageNumChar[0][16], "ggggggg   gg   ggggggggggggggggggggggggg        g        ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][17], "ggggggg   gg   ggggggggggggggggggggggggg        g        ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[0][18], "__________________________________________________________________________________________________________________________________|");
	*/
	/*
	sprintf(StageNumChar[1][0],		"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][1],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][2],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][3],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][4],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][5],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][6],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][7],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][8],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][9],		"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][10],	"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][11],	"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][12],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][13],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][14],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][15],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][16],	"g                              x                               x                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][17],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][18],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][19],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][20],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][21],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][22],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][23],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][24],	"g                              g                               g                               g                               g                               g                               g|");
	sprintf(StageNumChar[1][25],	"g                              g                               g                               g                               x                               g                               g|");
	sprintf(StageNumChar[1][26],	"g                              g                               g                               g                               x                               x                               g|");
	sprintf(StageNumChar[1][27],	"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][28],	"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][29],	"g                              g                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][30],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][31],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][32],	"g                              x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][33],	"g P                            x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][34],	"g P                            x                               x                               x                               x                               x                               g|");
	sprintf(StageNumChar[1][35],	"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg|");
	sprintf(StageNumChar[1][36],	"________________________________________________________________________________________________________________________________________________________________________________________________|");
*/

}



//												ステージ記号
//Bound,			バウンドエネミー			b
//Homing,			ホーミングエネミー			h
//Explosion,		爆発エネミー				e
//Sticky,			スティッキー爆弾エネミー	s
//Trace,			追従エネミー				t
//Spring,			バネエネミー				p

//WinningBlock		勝利条件のブロック			W
//
//画面分けの目印								x