#pragma once

#ifndef HOMING_MARKER_H_

#define	HOMING_MARKER_H_

#include	"Enemy.h"
#include	"Button.h"

#define	HOMING_MARKER_MAX	(10)

class HOMING_MARKER:	public	BASE_OF_PERFORMER
{
private:

	ENEMY*	homingEnemy;
	BUTTON*	homingButton;

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetHomingEnemy(ENEMY*	new_enemy) { homingEnemy = new_enemy; }
	ENEMY*	GetHomingEnemy(void) { return	homingEnemy; }

	void	SetHomingButton(BUTTON*	new_button) { homingButton = new_button; }
	BUTTON*	GetHomingButton(void) { return	homingButton; }
};

//=========================================================
//	ホーミングマーカー管理プログラム
//=========================================================
void	InitHomingMarker();
void	UninitHomingMarker();
void	UpdateHomingMarker();
void	DrawHomingMarker();

void	SetHomingMarker(ENEMY*	new_homingEnemy, BUTTON*	new_homingButton);
const	HOMING_MARKER*	GetHomingMarker();

void	ResetHomingMaker();

#endif // !HORMING_MARKER_H_


