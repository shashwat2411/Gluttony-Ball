#pragma once

#ifndef KNIFE_H_

#define	KNIFE_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	KNIFE_MAX	(50)

class KNIFE : public	BASE_OF_PERFORMER
{
private:

public:
	void	Update();

	void	Prepare();
	void	Reset();

};

void	InitKnife();	//	ナイフの初期化
void	UninitKnife();	//	ナイフの終了処理
void	UpdateKnife();	//	ナイフの更新処理
void	DrawKnife();	//	ナイフの描画処理

void	SetKnife(const	D3DXVECTOR2	pos,	D3DXVECTOR2	way);	//	ナイフのセット
KNIFE*	GetKnife();

#endif // !TRACE_KNIFE_H_

