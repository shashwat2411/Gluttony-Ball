
#include	"game.h"
#include	"player.h"
#include	"collision.h"
#include	"Direction.h"
#include	"ground.h"
#include	"xinput.h"
#include	"Ball.h"
#include	"Enemy.h"
#include	"Explosion.h"
#include	"StickyBomb.h"
#include	"Spring.h"
#include	"SummonEnemy.h"
#include	"bullet.h"
#include	"enemyStickyBomb.h"
#include	"Waiver.h"
#include	"Button.h"
#include	"InterlockArrangement.h"
#include	"knife.h"
#include	"StageGimmick.h"
#include	"homingMarker.h"
#include	"effect.h"
#include	"abilityMark.h"
#include	"oneWayBlock.h"
#include	"SavePoint.h"
#include	"Text.h"

bool	stop = false;
bool	giveUp = false;
int		stopCounter = 0;
bool	BASE_OF_PERFORMER::collisionTest = false;
FADE	stopTime;
char	textNoFade[] = "data/texture/fade.png";

unsigned	int	g_StageBGM00;

void	InitGame()
{
	stopCounter = 0;
	giveUp = false;

	InitGround();	//	グラウンド初期化処理
	InitExplosion();
	InitStickyBomb();
	InitSummonEnemy();
	InitButton();
	InitInterlockArrangement();
	InitStageGimmick();
	InitHomingMarker();
	InitSpring();
	InitPlayer();	//	プレイヤー初期化処理
	InitDirection();
	InitBall();		//	ボール初期化処理
	InitEnemy();	//	エネミー初期化処理
	InitKnife();
	InitBullet();	//	バレット初期化処理
	InitEnemyStickyBomb();	//	スティッキー爆弾初期化
	InitWaiver();	//	放棄アビリティ初期化
	InitStage();
	InitEffect();	//	エフェクト初期化
	InitAbilityMark();	//	能力マークの初期化
	InitOneWayBlock();	//	一方通行ブロックの初期化
	InitSavePoint();	//　セーブポイントの初期化
	InitTextT();		//　TEXTブロックの初期化

	InitCollision();
	InitMoveStage();	//	ステージ移動初期化

	MakeStage(GetCurrentStageNum());

	AdjustText();	// TEXTブロックの座標を設定

	GetPlayer()->CorrectScreen();

	SetFade(FADEIN);

	g_StageBGM00 = LoadSound((char*)"data/BGM/stage_test.wav");
	SetVolume(g_StageBGM00, 0.1f);
	
	PlaySound(g_StageBGM00, 1);

	{
		stopTime.TextNo = LoadTexture(textNoFade);

		stopTime.Position.x = SCREEN_WIDTH / 2;
		stopTime.Position.y = SCREEN_HEIGHT / 2;

		stopTime.Size.x = SCREEN_WIDTH;
		stopTime.Size.y = SCREEN_HEIGHT;

		stopTime.use = false;

		stopTime.rotation = 0.0f;

		stopTime.Offset = D3DXVECTOR2(0.0f, 0.0f);
		stopTime.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		stopTime.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	}
}

void	UninitGame()
{
	StopSoundAll();

	UninitBall();		//	ボール終了処理
	UninitPlayer();		//	プレイヤー終了処理
	UninitDirection();
	UninitEnemy();		//	エネミー終了処理
	UninitGround();		//	グラウンド終了処理
	UninitButton();
	UninitHomingMarker();
	UninitKnife();
	UninitStageGimmick();
	UninitInterlockArrangement();
	UninitExplosion();
	UninitBullet();		//	バレット終了処理
	UninitEnemyStickyBomb();	//	スティッキー爆弾終了処理
	UninitStickyBomb();
	UninitSummonEnemy();
	UninitSpring();
	UninitWaiver();	//	放棄アビリティ終了処理
	UninitEffect();	//	エフェクト終了処理
	UninitStage();
	UninitAbilityMark();	//	能力マークの終了処理
	UninitOneWayBlock();	//	一方通行ブロックの終了処理
	UninitSavePoint();		//　セーブポイントの終了処理
	UninitTextT();			//　TEXTブロックの終了処理

	UninitBG();			//	背景終了処理
}

void	UpdateGame()
{
	UpdateEffect();	//	エフェクト更新処理
	if (stop == false)
	{
		ChangeBG();		//　チュートリアル背景差し替え処理
		UpdateBG();		//	背景更新処理

		UpdateGround();	//	グラウンド更新処理
		UpdateStickyBomb();
		UpdateSummonEnemy();
		UpdateSpring();
		UpdateExplosion();
		UpdateButton();
		UpdateInterlockArrangement();
		UpdateHomingMarker();
		UpdateStageGimmick();
		UpdatePlayer();	//	プレイヤー更新処理
		UpdateDirection();
		UpdateBall();	//	ボール更新処理
		UpdateEnemy();	//	エネミー更新処理
		UpdateBullet();	//	バレット更新処理
		UpdateKnife();
		UpdateEnemyStickyBomb();	//	スティッキー爆弾更新処理
		UpdateWaiver();	//	放棄アビリティ更新処理
		UpdateOneWayBlock();	//	一方通行ブロック更新処理
		UpdateSavePoint();		//　セーブポイントの更新処理

		UpdateCollision();	//	当たり判定の検索
		UpdateTextT();		// TEXTブロックの更新処理

		UpdateStage();

		UpdateAbilityMark();	//	能力マークの更新処理
	}
	else if (stop == true)
	{
		stopTime.use = true;
		stopCounter += 1;
		if (stopCounter % (60 * 5 / 4) == 0)
		{
			stopCounter = 0;
			stop = false;
			stopTime.use = false;
		}
	}

	if (GetButtonTriggerStart())	giveUp = true;

	if (giveUp)	Fader(true, SELECT_STAGE);
	else	Fader((GetWin() || !GetPlayerUse() || (GetKeyboardPress(DIK_R))), RESULT);
}

void	DrawGame()
{
	DrawBG();		//	背景描画処理

	DrawTextT();	// 	TEXTブロックの描画処理
	DrawGround();	//	グラウンド描画処理

	DrawInterlockArrangement();
	DrawSummonEnemy();
	DrawButton();
	DrawOneWayBlock();	//	一方通行ブロック描画処理
	DrawSavePoint();	//　セーブポイントの描画処理
	DrawStageGimmick();
	DrawPlayer();	//	プレイヤー描画処理
	DrawDirection();
	DrawEnemy();	//	エネミー描画処理
	DrawKnife();
	DrawBall();		//	ボール描画処理
	DrawBullet();	//	バレット描画処理
	DrawEnemyStickyBomb();		//	スティッキー爆弾描画処理
	DrawHomingMarker();
	DrawWaiver();	//	放棄アビリティ描画処理
	DrawStickyBomb();
	DrawSpring();
	DrawExplosion();

	if (stopTime.use == true)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stopTime.TextNo));
		DrawSpriteColorRotate(stopTime.Position.x, stopTime.Position.y, stopTime.Size.x, stopTime.Size.y, stopTime.rotation, stopTime.color, 0, 1, 1, 1);
		GetDeviceContext()->Draw(4, 0);
	}
	DrawEffect();	//	エフェクト描画処理
	DrawAbilityMark();	//	能力マークの描画処理
}


void SetStopBool(bool value)
{
	stop = value;
}
bool GetStopBool()
{
	return stop;
}