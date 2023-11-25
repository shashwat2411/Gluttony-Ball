#pragma once

#include	"znoTouch_BaseOfPerformer.h"

#define	SER_HOMING_DIS	(BASE_SIZE * 32)

//============================================================
//	ディレクションクラス
//		キー移動、重力、ジャンプ
//=============================================================
class DIRECTION :public BASE_OF_PERFORMER
{
private:

public:
	void	Update();

	void	Prepare();
	void	Reset();


};

void InitDirection();
void UninitDirection();
void UpdateDirection();
void DrawDirection();

DIRECTION* GetDirection();