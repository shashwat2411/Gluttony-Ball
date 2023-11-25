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

void	InitKnife();	//	�i�C�t�̏�����
void	UninitKnife();	//	�i�C�t�̏I������
void	UpdateKnife();	//	�i�C�t�̍X�V����
void	DrawKnife();	//	�i�C�t�̕`�揈��

void	SetKnife(const	D3DXVECTOR2	pos,	D3DXVECTOR2	way);	//	�i�C�t�̃Z�b�g
KNIFE*	GetKnife();

#endif // !TRACE_KNIFE_H_

