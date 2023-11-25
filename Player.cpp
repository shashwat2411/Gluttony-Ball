
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
//D3DXVECTOR2 checkerPos[10] = { D3DXVECTOR2(0.0f,0.0f) };	//��Ԑ�̃x�N�g���ɐ��������_�̍��W
//==============================================================================================================================
//	�v���C���[�N���X�v���O����
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

		//	Xinput�ɒu����W�����v�{�^������я���
		if (control)
		{
			typeSE = None;

			//=====================================================================================================================
			//	�v���C���[�̓��͈ړ�����			
			if (way_x == 1 && texNo != TexNums[Stand_R]) { texNo = TexNums[Stand_R]; }
			if (way_x == -1 && texNo != TexNums[Stand_L]) { texNo = TexNums[Stand_L]; }

			if (GetStickL().x > 0 || GetKeyboardPress(DIK_RIGHT))	//	Xinput�ɒu����E�ړ�
			{
				texNo = TexNums[Run_R];
				
				move.x = speed * fabs(GetStickL().x);
				//move.x = speed;
				way_x = 1;

				if (onGround)	typeSE = Run;
			}
			else if (GetStickL().x < 0 || GetKeyboardPress(DIK_LEFT))	//	Xinput�ɒu���鍶�ړ�
			{
				texNo = TexNums[Run_L];
				
				move.x = -speed * fabs(GetStickL().x);
				//move.x = -speed;
				way_x = -1;

				if (onGround)	typeSE = Run;
			}
			else if (GetStickL().x == 0)	//	�ړ����͂Ȃ�
			{
				move.x *= frictionRate;
			}

			//======================================================================================
			if ((GetBumperTriggerR() || GetKeyboardTrigger(DIK_SPACE)) && onGround)	//	�W�����v
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
				//	�N�C�b�N��������
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
					//	�Ǐ]�\�͎g�p����
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
			//	�`���[�W�����̏���
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
					//	�Ǐ]�\�͎g�p����
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
					//	�z�[�~���O�\�͎g�p����
					if (ball->GetAbilityMoveBall() == BALL::HOMING && ball->GetHomingNum() > 0)
					{
						ball->SetMoveType(BASE_OF_PERFORMER::Point);
					}
				}
			}

			//==========================================================
			//	SE����
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
		//	�Ǐ]����
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
		//	�\�͏������ɔ�������L���L���̔�������
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
	use = true;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = true;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = true;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = true;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	onGround = false;
	stick = true;

	control = true;

	MoveX = true;
	MoveY = true;

	stockBall = true;

	move_type = Normal;

	TexNums[Stand_R] = LoadTexture((char*)"data/texture/Player/idle_R.png");	//	LoadTexture�̖߂�l���L�^����ϐ�
	TexNums[Stand_L] = LoadTexture((char*)"data/texture/Player/idle_L.png");

	TexNums[Run_R] = LoadTexture((char*)"data/texture/Player/run_R.png");	//	LoadTexture�̖߂�l���L�^����ϐ�
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

	animTimeMax = 10;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 10;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	speed = 5.0f;
	r_speed = speed;

	timer = 0;
	ChargeTimer = 0;

	TraceNum = 0;

	pos = D3DXVECTOR2(0, 0);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l

	size = D3DXVECTOR2(BASE_SIZE * 1.66f, BASE_SIZE * 2);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, (BASE_SIZE - BASE_SIZE * 0.85f));		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(BASE_SIZE / 2, size.y * 0.8f);				//	�����蔻��̃T�C�Y


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
	�v���C���[������
====================================*/
void	InitPlayer()
{
	player.Init();
	player.Prepare();
}

/*==================================
	�v���C���[�I������
====================================*/
void	UninitPlayer()
{
	player.Uninit();
}

/*==================================
	�v���C���[�X�V����
====================================*/
void	UpdatePlayer()
{
	player.Update();
}

/*==================================
	�v���C���[�`�揈��
====================================*/
void	DrawPlayer()
{
	player.Draw();
}

/*==================================
	�v���C���[�擾
====================================*/
PLAYER* GetPlayer()
{
	return	&player;
}


bool GetPlayerUse()
{
	return player.GetUse();
}