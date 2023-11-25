#pragma once

#ifndef GROUND_H_

#include	"include_lib.h"

#define	GROUND_MAX	(1000)
#define	OUT_LINE_MAX	(GROUND_MAX)

//===========================================================
//	グラウンドクラス
//		場所固定、ギミックなし、地面
//===========================================================
class GROUND : public	BASE_OF_PERFORMER
{
public:

private:


public:
	int counter = 0;
	bool display = true;
	void	Update();

	void	Prepare();
	void	Reset();

	void SetDisplay(const bool& value) { display = value; }
	const bool GetDisplay() { return display; }
};

typedef	struct OUT_LINE
{
	bool	use;

	unsigned	int	texNo;

	int	angle;
	float	texSize_W;					//	テクスチャの横の表示サイズ

	D3DXVECTOR2	pos;
	D3DXVECTOR2	size;
	D3DXCOLOR	color;					//	色
};

//============================================
//	地面管理プログラム
//============================================
void	InitGround();
void	UninitGround();
void	UpdateGround();
void	DrawGround();

void	InitOutLine();
void	DrawOutLine();
void	SetOutLine(const	int&	stage_num,	const	D3DXVECTOR2&	leftup, const	D3DXVECTOR2&	rightdown);
void	SetSideOutLine(const	int&	stage_num);

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size);	//	足場のセット

GROUND*	GetGround();
OUT_LINE*	GetOutLine();


#endif // !GROUND_H_

