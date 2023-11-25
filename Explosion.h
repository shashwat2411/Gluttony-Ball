#pragma once

#ifndef EXPLOSION_H_

#include	"include_lib.h"

#define	EXPLOSION_MAX	(30)

class EXPLOSION : public	BASE_OF_PERFORMER
{
public:
	enum SOURCE	//î≠ê∂åπ
	{
		NONE,
		PLAYER,
		ENEMY
	};
private:
	SOURCE source;

public:

	void	Update();

	void	Prepare();
	void	Reset();

	void	SetSource(const	SOURCE	new_value) { source = new_value; }
	const	SOURCE&	GetSource(void) { return	source; }
	
};

//============================================
//	ínñ ä«óùÉvÉçÉOÉâÉÄ
//============================================
void	InitExplosion();
void	UninitExplosion();
void	UpdateExplosion();
void	DrawExplosion();

void SetExplosion(D3DXVECTOR2 new_pos, D3DXVECTOR2 new_size, EXPLOSION::SOURCE sourceValue);
EXPLOSION* GetExplosion();


#endif // !EXPLOSION_H_