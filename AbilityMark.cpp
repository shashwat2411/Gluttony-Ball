
#include	"abilityMark.h"
#include	"player.h"
#include	"Ball.h"

bool	OpenBool;

unsigned	int	g_AbilityMarksNum;

int	g_Timer;
int	g_AbilityNum;

PLAYER*	a_Player;
BALL*	a_Ball;

D3DXVECTOR2	size;
D3DXVECTOR2	abilityNums[3] = { D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) };

D3DXCOLOR	color;

void	InitAbilityMark()
{
	a_Player = GetPlayer();
	a_Ball = GetBall();

	g_AbilityMarksNum = LoadTexture((char*)"data/texture/ability_marks.png");

	OpenBool = false;
	g_Timer = 0;
	g_AbilityNum = 0;

	size.x = BASE_SIZE * 2;
	size.y = BASE_SIZE * 2;

	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
}

void	UninitAbilityMark()
{

}

void	UpdateAbilityMark()
{
	if (fabs(GetStickL().x) < 0.01f && fabs(GetStickL().y) < 0.01f &&
		fabs(GetStickR().x) < 0.01f && fabs(GetStickR().y) < 0.01f &&
		a_Player->GetMove().y > 0.0f && a_Player->GetMoveType() == BASE_OF_PERFORMER::Normal)	g_Timer++;
	else g_Timer = 0;

	if (OpenBool)
	{
		if (g_Timer == 0)
		{
			OpenBool = false;

			size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);
			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		}
	}
	else
	{
		if (g_Timer >= 60 * 2)
		{
			OpenBool = true;

			size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);
			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//===============================================================================
	g_AbilityNum = 0;
	switch (a_Ball->GetAbilityAttack())
	{
	case	BALL::NONE_ATTACK:	abilityNums[g_AbilityNum] = D3DXVECTOR2(0.0f, 0.0f);	break;
	case	BALL::EXPLOSION:	abilityNums[g_AbilityNum++] = D3DXVECTOR2(0.0f, 1.0f);	break;
	case	BALL::STICKY:		abilityNums[g_AbilityNum++] = D3DXVECTOR2(1.0f, 1.0f);	break;
	default:	break;
	}

	switch (a_Ball->GetAbilityMovePlayer())
	{
	case	BALL::NONE_PLAYER:	abilityNums[g_AbilityNum] = D3DXVECTOR2(0.0f, 0.0f);	break;
	case	BALL::TRACE:		abilityNums[g_AbilityNum++] = D3DXVECTOR2(0.0f, 2.0f);	break;
	case	BALL::SPRING:		abilityNums[g_AbilityNum++] = D3DXVECTOR2(1.0f, 2.0f);	break;
	default:	break;
	}

	switch (a_Ball->GetAbilityMoveBall())
	{
	case	BALL::NONE_BALL:	abilityNums[g_AbilityNum] = D3DXVECTOR2(0.0f, 0.0f);	break;
	case	BALL::HOMING:		abilityNums[g_AbilityNum++] = D3DXVECTOR2(0.0f, 3.0f);	break;
	case	BALL::BOUNCE:		abilityNums[g_AbilityNum++] = D3DXVECTOR2(1.0f, 3.0f);	break;
	default:	break;
	}
	//===============================================================================
}

void	DrawAbilityMark()
{
	for (int i = 0; i < 3; i++)
	{
		if (g_AbilityNum > i || i == 0)
		{
			// テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_AbilityMarksNum));

			//	ポリゴン配置
			DrawSpriteColorRotate(SCREEN_WIDTH - size.x / 2, size.y / 2 + size.y * i, size.x, size.y, 0.0f,
				color, (int)(abilityNums[i].x), 1.0f / 2, 1.0f / 4, abilityNums[i].y);
		}
	}
}




















