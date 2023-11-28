#pragma once

#ifndef STEAL_BLOCK_H_

#define	STEALBLOCK_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	STEALBLOCK_MAX	(50)

class STEALBLOCK : public	BASE_OF_PERFORMER
{
private:

public:

	void	Update();

	void	Prepare();
	void	Reset();

};

//======================================================
//	能力没収ブロック管理プログラム
void	InitStealBlock();
void	UninitStealBlock();
void	UpdateStealBlock();
void	DrawStealBlock();

void	SetStealBlock(const	D3DXVECTOR2	new_Pos, const	D3DXVECTOR2	new_Size);
STEALBLOCK*	GetStealBlock(void);

#endif // !STEAL_BLOCK_H_

