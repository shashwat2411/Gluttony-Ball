#pragma once

#ifndef GROUND_H_

#include	"include_lib.h"

#define	GROUND_MAX	(1000)
#define	OUT_LINE_MAX	(GROUND_MAX)

//===========================================================
//	�O���E���h�N���X
//		�ꏊ�Œ�A�M�~�b�N�Ȃ��A�n��
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
	float	texSize_W;					//	�e�N�X�`���̉��̕\���T�C�Y

	D3DXVECTOR2	pos;
	D3DXVECTOR2	size;
	D3DXCOLOR	color;					//	�F
};

//============================================
//	�n�ʊǗ��v���O����
//============================================
void	InitGround();
void	UninitGround();
void	UpdateGround();
void	DrawGround();

void	InitOutLine();
void	DrawOutLine();
void	SetOutLine(const	int&	stage_num,	const	D3DXVECTOR2&	leftup, const	D3DXVECTOR2&	rightdown);
void	SetSideOutLine(const	int&	stage_num);

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size);	//	����̃Z�b�g

GROUND*	GetGround();
OUT_LINE*	GetOutLine();


#endif // !GROUND_H_

