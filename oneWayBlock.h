#pragma once

#ifndef ONE_WAY_BLOCK_H_

#define	ONE_WAY_BLOCK_H_

#include	"znoTouch_BaseOfPerformer.h"

#define	ONE_WAY_BLOCK_MAX	(50)

class ONE_WAY_BLOCK : public	BASE_OF_PERFORMER
{
public:
	enum WAY
	{
		UP,	DOWN,	RIGHT,	LEFT,
		num_max
	};

private:
	WAY	way;

	unsigned	int	TexNums[num_max];

public:

	void	Update();

	void	Prepare();
	void	Reset();

	void	SetWay(const	WAY	new_way) { way = new_way; }
	const	WAY&	GetWay() { return	way; }

	void	SetTexNums(const	WAY	way) { texNo = TexNums[way]; }
};

//============================================
//	����ʍs�u���b�N�Ǘ��v���O����
//============================================
void	InitOneWayBlock();		//	����ʍs�u���b�N�̏�����
void	UninitOneWayBlock();	//	����ʍs�u���b�N�̏I������
void	UpdateOneWayBlock();	//	����ʍs�u���b�N�̍X�V����
void	DrawOneWayBlock();		//	����ʍs�u���b�N�̕`�揈��

void	SetOneWayBlock(const	D3DXVECTOR2 new_pos, const	D3DXVECTOR2	new_size, ONE_WAY_BLOCK::WAY	new_way);
ONE_WAY_BLOCK*	GetOneWayBlock();

#endif // !ONE_WAY_BLOCK_H_

















