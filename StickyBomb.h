#pragma once

#ifndef STICKYBOMB_H_

#include	"enemy.h"

#define	STICKYBOMB_MAX	(10)

class STICKYBOMB : public	BASE_OF_PERFORMER
{
private:

public:
	int counter;

	const	int	ExplosionTimeMax = 60 * 4;

	ENEMY* follower;

	void	Update();

	void	Prepare();
	void	Reset();

	void	SetFollower(ENEMY*	new_Follower) { follower = new_Follower; }
	ENEMY*	GetFollower() { return	follower; }

	void	SetCounter(const	int	new_Counter) { counter = new_Counter; }
	const	int&	GetCounter() { return	counter; }

};

//============================================
//	ínñ ä«óùÉvÉçÉOÉâÉÄ
//============================================
void	InitStickyBomb();
void	UninitStickyBomb();
void	UpdateStickyBomb();
void	DrawStickyBomb();

void SetStickyBomb(D3DXVECTOR2 new_pos, ENEMY*	stickEnemy, float angle);
STICKYBOMB* GetStickyBomb();


#endif // !STICKYBOMB_H_