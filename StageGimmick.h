
#pragma once

#ifndef STAGEGIMMICK_H_

#include	"ground.h"

#define	STAGEGIMMICK_MAX	(400)


//===========================================================
//	グラウンドクラス
//		場所固定、ギミックなし、地面
//===========================================================
class STAGEGIMMICK : public	GROUND
{
public:
	enum BLOCK_TYPE
	{
		BREAK,
		BREAK_LARGE,
		MOVE,
		NEEDLE,
		DIE,
		FALL,
		STEAL,
		WIN,
		BLOCK_TYPE_MAX
	};

private:
	unsigned	int	g_GimmickSE[BLOCK_TYPE_MAX];

	bool	ActiveInEmpty;

	//BreakableBlock
	bool breakHit = false;

	//movingFloor
	float	moveDirection = 1;
	float from;
	float to;
	bool OnPlayer;

	//Needle
	D3DXVECTOR2	fallSerColSize;

	//ShinuYuka
	bool playerHit = false;

	//VulnerableBlock
	bool starter = false;
	int counter = 0;

	//WinningBlock
	bool winCondition = false;

public:

	void	Update();

	void	Prepare();
	void	Reset();

	BLOCK_TYPE block_type;
	unsigned	int	TexNums[BLOCK_TYPE_MAX];


	//BreakableBlock
	void SetBreakHit(const bool value) { breakHit = value; }
	const bool& GetBreakHit() { return breakHit; }

	//movingFloor
	void SetOnPlayer(const bool value) { OnPlayer = value; }
	const bool& GetOnPlayer() { return OnPlayer; }

	//Needle

	//ShinuYuka
	void SetPlayerHit(const bool value) { playerHit = value; }
	const bool& GetPlayerHit() { return playerHit; }

	//VulnerableBlock

	//WinningBlock
	void SetWinCondition(const bool value) { winCondition = value; }
	const bool& GetWinCondition() { return winCondition; }


	void	SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2	way, const	BLOCK_TYPE&	BlockType);
};



//============================================
//	地面管理プログラム
//============================================
void	InitStageGimmick();
void	UninitStageGimmick();
void	UpdateStageGimmick();
void	DrawStageGimmick();

void	SetStageGimmicks(const D3DXVECTOR2& pos, const	D3DXVECTOR2& size, STAGEGIMMICK::BLOCK_TYPE type);	//	足場のセット

STAGEGIMMICK*	GetStageGimmick();
bool GetWin();



#endif // !STAGEGIMMICK_H_









