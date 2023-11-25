
#include	"player.h"
#include	"Ball.h"
#include	"Direction.h"
#include	"xinput.h"
#include	"Enemy.h"
#include	"Waiver.h"
#include	"effect.h"

PLAYER	player;
BALL* ball;
DIRECTION* p_direction;
D3DXVECTOR2	way;
ENEMY* p_enemy;

int index = 0;
float ThrowTime;
//D3DXVECTOR2 checkerPos[10] = { D3DXVECTOR2(0.0f,0.0f) };	//飛ぶ先のベクトルに生成される点の座標
//==============================================================================================================================
//	プレイヤークラスプログラム
//==============================================================================================================================
void	PLAYER::Update()
{
	if (use)
	{
		if (!onWall)	pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		animation = !GetStopBool();

		if (pos.x - collisionSize.x / 2 > SCREEN_WIDTH)
		{
			//disable = true;
			SetMoveStage(-1, 0);

			if (ball->GetAbilityMovePlayer() != BALL::TRACE && !control)
			{
				move_type = Normal;
				control = true;

				ball->SetSituation(BALL::Return);

				speed = r_speed;
			}
		}
		else if (pos.x + collisionSize.x / 2 < 0)
		{
			SetMoveStage(1, 0);

			if (ball->GetAbilityMovePlayer() != BALL::TRACE && !control)
			{
				move_type = Normal;
				control = true;

				ball->SetSituation(BALL::Return);

				speed = r_speed;
			}
		}

		if (pos.y - collisionSize.y / 2 > SCREEN_HEIGHT)
		{
			SetMoveStage(0, -1);

			if (ball->GetAbilityMovePlayer() != BALL::TRACE && !control)
			{
				move_type = Normal;
				control = true;

				ball->SetSituation(BALL::Return);

				speed = r_speed;
			}
		}
		else if (pos.y + collisionSize.y / 2 < 0)
		{
			SetMoveStage(0, 1);

			if (ball->GetAbilityMovePlayer() != BALL::TRACE && !control)
			{
				move_type = Normal;
				control = true;

				ball->SetSituation(BALL::Return);

				speed = r_speed;
			}
		}

		//	Xinputに置けるジャンプボタンおよび処理
		if (control)
		{
			typeSE = None;

			//=====================================================================================================================
			//	プレイヤーの入力移動処理			
			if (way_x == 1 && texNo != TexNums[Stand_R]) { texNo = TexNums[Stand_R]; }
			if (way_x == -1 && texNo != TexNums[Stand_L]) { texNo = TexNums[Stand_L]; }

			if (GetStickL().x > 0 || GetKeyboardPress(DIK_RIGHT))	//	Xinputに置ける右移動
			{
				texNo = TexNums[Run_R];
				
				move.x = speed * fabs(GetStickL().x);
				//move.x = speed;
				way_x = 1;

				if (onGround)	typeSE = Run;
			}
			else if (GetStickL().x < 0 || GetKeyboardPress(DIK_LEFT))	//	Xinputに置ける左移動
			{
				texNo = TexNums[Run_L];
				
				move.x = -speed * fabs(GetStickL().x);
				//move.x = -speed;
				way_x = -1;

				if (onGround)	typeSE = Run;
			}
			else if (GetStickL().x == 0)	//	移動入力なし
			{
				move.x *= frictionRate;
			}

			//======================================================================================
			if ((GetBumperTriggerR() || GetKeyboardTrigger(DIK_SPACE)) && onGround)	//	ジャンプ
			{
				pos_bef.y = pos.y + size.y / 3;
				move.y = JumpSpeed_min;
				onGround = false;
				typeSE = Jump;
			}
			if ((GetBumperPressR() || GetKeyboardPress(DIK_SPACE)) && !onGround && move.y < 0)
			{
				move.y -= JumpAcceleration;
			}
			
			//======================================================================================

			if (move.y < 0 && !onGround)
			{
				if (way_x == 1)	texNo = TexNums[Jump_R];
				else			texNo = TexNums[Jump_L];
			}
			if (move.y > 0 && !onGround)
			{
				if (way_x == 1)	texNo = TexNums[Fall_R];
				else			texNo = TexNums[Fall_L];
			}
			//=====================================================================================================
			if (GetStickR().x * GetStickR().x + GetStickR().y * GetStickR().y > ThrowJudgeNum * ThrowJudgeNum && stockBall)
			{
				ChargeTimer++;
				stick = true;

				way = GetStickR();
				//way.y *= -1;
				
				if (GetStickL().x == 0)
				{
					if (way.x > 0)	texNo = TexNums[ThrowPose_R];
					else			texNo = TexNums[ThrowPose_L];
				}
				else
				{
					if (GetStickL().x > 0)
					{
						if (way.x > 0)	texNo = TexNums[ThrowWalk_R];
						else			texNo = TexNums[ThrowBack_L];
					}
					else
					{
						if (way.x > 0)	texNo = TexNums[ThrowBack_R];
						else			texNo = TexNums[ThrowWalk_L];
					}
				}

			}
			else	if (way_x * GetStickR().x == 0 && stockBall && ChargeTimer > 0)
			{
				stick = false;
			}

			if (ChargeTimer < ChargeTimeMax && ChargeTimer > 0)
			{
				//==============================================================================
				//	クイック投げ処理
				if (stockBall && ball->GetSituation() == BALL::Keep && !stick)
				{
					ChargeTimer = 0;
					stockBall = false;
					way.x = way.x / fabs(way.x);

					if (way.y > QuickBallWayDis)
					{
						way.y = -1;
					}
					else if (way.y < -QuickBallWayDis)
					{
						way.y = 1;
					}
					else
					{
						way.y = 0;
					}

					ball->SetSpeed(ball->GetRSpeed());
					ball->SetBall(pos, way);
					ball->SetSituation(BALL::Throwing);
					typeSE = Throw;

					animationOver = false;
					animTimer = 0;
					if (way > 0)	texNo = TexNums[AfterThrow_R];
					else			texNo = TexNums[AfterThrow_L];
					//==================================================================================
					//	追従能力使用準備
					if (ball->GetAbilityMovePlayer() == BALL::TRACE)
					{
						move_type = Point;
						active = false;
						control = false;
						StayTimeBefTrace = 0;
						TraceNum = 0;

						ArrivePoint = false;

						speed = 6.0f;
					}
					//==================================================================================
				}
			}
			else if (ChargeTimer > 0)
			{
			//===========================================================================================================
			//	チャージ投げの処理
			//===========================================================================================================
				if (stick && stockBall)
				{
					p_direction->SetSize(D3DXVECTOR2(BASE_SIZE * ThrowTime * 0.4f, BASE_SIZE));
					if (ThrowTime >= 30)
					{
						ThrowTime = 30;
					}
					else
					{
						ThrowTime += 0.4f;
					}

					ball->ThrowDisRateUp(ThrowTime / 30);

					way_x = way.x / fabs(way.x);

					ball->SetSituation(BALL::ChargeThrow);

					p_direction->SetUse(true);
				}
				else if (ball->GetSituation() == BALL::ChargeThrow && stockBall && !stick)
				{
					ChargeTimer = 0;
					stockBall = false;
					ball->SetSpeed(ball->GetRSpeed() * 3);
					ball->SetBall(pos, D3DXVECTOR2(way.x, -way.y));
					ball->SetSituation(BALL::Throwing);
					typeSE = Throw;

					animationOver = false;
					animTimer = 0;
					if (way > 0)	texNo = TexNums[AfterThrow_R];
					else			texNo = TexNums[AfterThrow_L];

					ThrowTime = 0;
					p_direction->SetUse(false);

					//==================================================================================
					//	追従能力使用準備
					if (ball->GetAbilityMovePlayer() == BALL::TRACE)
					{
						move_type = Point;
						active = false;
						control = false;
						StayTimeBefTrace = 0;
						TraceNum = 0;

						ArrivePoint = false;

						speed = 5.0f;
					}
					//==================================================================================
					//	ホーミング能力使用準備
					if (ball->GetAbilityMoveBall() == BALL::HOMING && ball->GetHomingNum() > 0)
					{
						ball->SetMoveType(BASE_OF_PERFORMER::Point);
					}
				}
			}

			//==========================================================
			//	SE処理
			if (typeSE == Run && !OneTimeSE)
			{
				OneTimeSE = true;
				PlaySound(SENums[typeSE], 1);
			}
			else if (typeSE == Jump || typeSE == Throw)
			{
				PlaySound(SENums[typeSE], 0);
			}
			else if (typeSE == None)
			{
				OneTimeSE = false;
				StopSound(SENums[Run]);
			}
		}

		//=====================================================================================================
		if (!stockBall && ball->GetSituation() == BALL::Throwing && !animationOver)
		{
			if (way_x == 1) { texNo = TexNums[AfterThrow_R]; }
			if (way_x == -1) { texNo = TexNums[AfterThrow_L]; }
		}

		//=====================================================================================================
		//	追従処理
		if (ball->GetAbilityMovePlayer() == BALL::TRACE && !control)
		{
			TracePos[TraceNum] = ball->GetPosi();
			if (active)
			{
				if (ArrivePoint)
				{
					ArrivePoint = false;
					if (TraceNum > 0 && TraceNum <= TRACE_POS_MAX)
					{
						for (int i = 0; i < TraceNum; i++)
						{
							TracePos[i] = TracePos[i + 1];
						}
						TraceNum--;
					}
					else if (TraceNum == 0)
					{
						move_type = Normal;
						control = true;

						ball->SetSituation(BALL::Return);

						speed = r_speed;
					}
				}

				point = TracePos[0];
				point.y -= size.y / 2;
			}
			else
			{
				StayTimeBefTrace++;
				if (StayTimeBefTrace >= StayTimeBefTraceMax)
				{
					active = true;
					point = TracePos[0];
					point.y -= size.y / 2;
				}
			}
		}
		else if (ball->GetAbilityMovePlayer() != BALL::TRACE && !control)
		{
			move_type = Normal;
			control = true;

			ball->SetSituation(BALL::Return);

			speed = r_speed;
		}
		//=====================================================================================================


		if (GetButtonTriggerA() || GetKeyboardPress(DIK_N) && stockBall)
		{
			if (ball->GetAbilityAttack() == BALL::EXPLOSION)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::EXPLOSION, BALL::NONE_BALL, BALL::NONE_PLAYER);
			}
			if (ball->GetAbilityAttack() == BALL::STICKY)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::STICKY, BALL::NONE_BALL, BALL::NONE_PLAYER);
			}
			if (ball->GetAbilityMoveBall() == BALL::HOMING)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::NONE_ATTACK, BALL::HOMING, BALL::NONE_PLAYER);
			}
			if (ball->GetAbilityMoveBall() == BALL::BOUNCE)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::NONE_ATTACK, BALL::BOUNCE, BALL::NONE_PLAYER);
			}
			if (ball->GetAbilityMovePlayer() == BALL::SPRING)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::NONE_ATTACK, BALL::NONE_BALL, BALL::SPRING);
			}
			if (ball->GetAbilityMovePlayer() == BALL::TRACE)
			{
				SetWaiver(pos, D3DXVECTOR2(-way_x, -1), BALL::NONE_ATTACK, BALL::NONE_BALL, BALL::TRACE);
			}
			ball->SetAbilityAttack(BALL::NONE_ATTACK);
			ball->SetAbilityMoveBall(BALL::NONE_BALL);
			ball->SetAbilityMovePlayer(BALL::NONE_PLAYER);

			timer = 0;
		}

		if (pos.y > SCREEN_HEIGHT + 100 || pos.y < -100 || pos.x > SCREEN_WIDTH + 100 || pos.x < -100) { use = false; }

		//==============================================================================
		//	能力所持時に発生するキラキラの発生処理
		if (ball->GetAbilityAttack() != BALL::NONE_ATTACK || ball->GetAbilityMoveBall() != BALL::NONE_BALL ||
			ball->GetAbilityMovePlayer() != BALL::NONE_PLAYER)
		{
			timer++;
			if (timer % MakeShineTimeMax == 0)
			{
				SetEffects(D3DXVECTOR2(pos.x + BASE_SIZE / 2 * cosf(D3DXToRadian(timer)), pos.y + BASE_SIZE / 2 * sinf(D3DXToRadian(timer))),
					D3DXVECTOR2(BASE_SIZE, BASE_SIZE), EFFECT::SHINE, nullptr);

				timer *= 4;
			}

			if (timer > 360)	timer -= 180;
		}
		//==============================================================================


		Gravity();
		Move();
	}
}


void	PLAYER::Prepare()
{
	use = true;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = true;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = true;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	onGround = false;
	stick = true;

	control = true;

	MoveX = true;
	MoveY = true;

	stockBall = true;

	move_type = Normal;

	TexNums[Stand_R] = LoadTexture((char*)"data/texture/Player/idle_R.png");	//	LoadTextureの戻り値を記録する変数
	TexNums[Stand_L] = LoadTexture((char*)"data/texture/Player/idle_L.png");

	TexNums[Run_R] = LoadTexture((char*)"data/texture/Player/run_R.png");	//	LoadTextureの戻り値を記録する変数
	TexNums[Run_L] = LoadTexture((char*)"data/texture/Player/run_L.png");

	TexNums[Jump_R] = LoadTexture((char*)"data/texture/Player/jump_R.png");
	TexNums[Jump_L] = LoadTexture((char*)"data/texture/Player/jump_L.png");

	TexNums[ThrowPose_R] = LoadTexture((char*)"data/texture/Player/throwPosing_R.png");
	TexNums[ThrowPose_L] = LoadTexture((char*)"data/texture/Player/throwPosing_L.png");

	TexNums[ThrowWalk_R] = LoadTexture((char*)"data/texture/Player/throwAdvance_R.png");
	TexNums[ThrowWalk_L] = LoadTexture((char*)"data/texture/Player/throwAdvance_L.png");

	TexNums[ThrowBack_R] = LoadTexture((char*)"data/texture/Player/throwBack_R.png");
	TexNums[ThrowBack_L] = LoadTexture((char*)"data/texture/Player/throwBack_L.png");

	TexNums[AfterThrow_R] = LoadTexture((char*)"data/texture/Player/afterThrow_R.png");
	TexNums[AfterThrow_L] = LoadTexture((char*)"data/texture/Player/afterThrow_L.png");

	TexNums[Fall_R] = LoadTexture((char*)"data/texture/Player/fall_R.png");
	TexNums[Fall_L] = LoadTexture((char*)"data/texture/Player/fall_L.png");

	texNo = TexNums[Stand_R];

	OneTimeSE = false;
	typeSE = Run;
	SENums[Run] = LoadSound((char*)"data/SE/playerWalk_SE.wav");
	SetVolume(SENums[Run], 0.3f);
	SENums[Jump] = LoadSound((char*)"data/SE/playerJump_SE.wav");
	SetVolume(SENums[Jump], 0.8f);
	SENums[Throw] = LoadSound((char*)"data/SE/throw_SE.wav");

	animTimeMax = 10;		//	animTimerがこの値を超えると0に戻る
	animOneFlameTime = 0.2f;			//	animTimerに加算し続ける変数

	animFlame_W = 10;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	speed = 5.0f;
	r_speed = speed;

	timer = 0;
	ChargeTimer = 0;

	TraceNum = 0;

	pos = D3DXVECTOR2(0, 0);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値

	size = D3DXVECTOR2(BASE_SIZE * 1.66f, BASE_SIZE * 2);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, (BASE_SIZE - BASE_SIZE * 0.85f));		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(BASE_SIZE / 2, size.y * 0.8f);				//	当たり判定のサイズ


	ball = GetBall();
	p_direction = GetDirection();
	p_enemy = GetEnemy();
}


void	PLAYER::Reset()
{

}

void	PLAYER::CorrectScreen()
{
	bool	roop = false;

	do
	{
		roop = false;
		if (pos.x - size.x / 2 > SCREEN_WIDTH)
		{
			roop = true;
			SetMoveStage(-1, 0);
		}
		else if (pos.x + size.x / 2 < 0)
		{
			roop = true;
			SetMoveStage(1, 0);
		}

		if (pos.y - size.y / 2 > SCREEN_HEIGHT)
		{
			roop = true;
			SetMoveStage(0, -1);
		}
		else if (pos.y + size.y / 2 < 0)
		{
			roop = true;
			SetMoveStage(0, 1);
		}
	} while (roop);
}

/*==================================
	プレイヤー初期化
====================================*/
void	InitPlayer()
{
	player.Init();
	player.Prepare();
}

/*==================================
	プレイヤー終了処理
====================================*/
void	UninitPlayer()
{
	player.Uninit();
}

/*==================================
	プレイヤー更新処理
====================================*/
void	UpdatePlayer()
{
	player.Update();
}

/*==================================
	プレイヤー描画処理
====================================*/
void	DrawPlayer()
{
	player.Draw();
}

/*==================================
	プレイヤー取得
====================================*/
PLAYER* GetPlayer()
{
	return	&player;
}


bool GetPlayerUse()
{
	return player.GetUse();
}