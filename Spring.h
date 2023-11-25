#pragma once

#ifndef SPRING_H_

#include	"include_lib.h"

#define	SPRING_MAX	(10)

//#define SPRING_SIZE_Y (BASE_SIZE * 1)

class SPRING : public	BASE_OF_PERFORMER
{
private:
	unsigned	int	g_SpringSE;

	bool	OnSpring;

	int	timer;

	const	int	DeleteTime = 60 * 5;

public:

	void	Update();

	void	Prepare();
	void	Reset();

	void	SetOnSpring(const	bool	new_Bool) {
		OnSpring = new_Bool;
	if (new_Bool)	PlaySound(g_SpringSE, 0); SetVolume(g_SpringSE, 0.7f);
	}

	const	bool&	GetOnSpring() { return	OnSpring; }

	void	SetTimer(const	int	new_Time) { timer = new_Time; }
	const	int&	GetTimer(void) { return	timer; }
};

//============================================
//	ínñ ä«óùÉvÉçÉOÉâÉÄ
//============================================
void	InitSpring();
void	UninitSpring();
void	UpdateSpring();
void	DrawSpring();

void SetSpring(D3DXVECTOR2 new_pos);
SPRING* GetSpring();


#endif // !SPRING_H_