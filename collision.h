#pragma once

//======================================================
//	�����蔻��w�b�_�[
//======================================================

#ifndef COLLISION_H_

#define	COLLISION_H_

#include	"include_lib.h"

//==============================================================
//	�����蔻��̕���
//==============================================================
enum COLLISION_WAY
{
	None, Up, Down, Right, Left,
};

//==============================================================
//	�R���W��������
//==============================================================
void	InitCollision();
void	UpdateCollision();






//PLAYER & BALL
void	Collision_Player_VS_Ground();	//	PLAYER VS GROUND
void	Collision_Ball_VS_Ground();	//	BALL VS GROUND

//EXPLOSION
void	Collision_Explosion();	//	PLAYER, ENEMY

//WAIVER
void	Collision_Waiver();	//	PLAYER, GROUND

//STAGE GIMMICK
void	Collision_StageGimmick();	//	PLAYER, ENEMY, BALL

//OneWayBlock
void	Collision_OneWayBlock();	//	PLAYER, ENEMY, BALL

//BUTTON
void	Collision_Button();	//  PLAYER, BALL

//DOOR
void	Collision_InterlockArrangement();	//	PLAYER, BALL

//SPRING
void	Collision_Spring();	//PLAYER

//ENEMY
void	Collision_Enemy_VS_Ground();	//	ENEMY VS GROUND
void	Collision_Enemy_VS_Ball();	//	ENEMY VS BALL
void	Collision_Enemy_VS_Player();	//	ENEMY VS PLAYER

void	Collision_EnemyKnife();	//	PLAYER, GROUND, BALL

void	Collision_EnemyBullet();	//	GROUND, BALL

void	Collision_EnemySticky();	//	GROUND


/*=====================================================================================================================
	�����Fcol_pos:�R���W�����̒��S���W		�Fcol_size:�R���W�����̃T�C�Y		*/
bool	GetCollision(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	�I�u�W�F�N�g���m�̓����蔻��
bool	GetCollisionUp(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	�I�u�W�F�N�g�㕔�Ƃ̓����蔻��F�Ԃ�l�Abool
bool	GetCollisionDown(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	�I�u�W�F�N�g�����Ƃ̓����蔻��F�Ԃ�l�Abool
bool	GetCollisionRight(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	�I�u�W�F�N�g�E�����Ƃ̓����蔻��F�Ԃ�l�Abool
bool	GetCollisionLeft(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	�I�u�W�F�N�g�������Ƃ̓����蔻��F�Ԃ�l�Abool
const	COLLISION_WAY&	CheckTouchStageGimmick(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);

//======================================================================================================================
//	����ɐG��Ă��邩���菈��
const	COLLISION_WAY&	CheckTouchGround(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);

//======================================================================================================================
//	����ɐG��Ă��邩���菈��
const	COLLISION_WAY&	CheckTouchStageGimmick(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);


//bool	GetCollisionTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2,	bool*	OnCol);	//	�I�u�W�F�N�g���m�̓����蔻��
//bool	GetCollisionUpTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	�I�u�W�F�N�g�㕔�Ƃ̓����蔻��F�Ԃ�l�Abool
//bool	GetCollisionDownTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	�I�u�W�F�N�g�����Ƃ̓����蔻��F�Ԃ�l�Abool
//bool	GetCollisionRightTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	�I�u�W�F�N�g�E�����Ƃ̓����蔻��F�Ԃ�l�Abool
//bool	GetCollisionLeftTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	�I�u�W�F�N�g�������Ƃ̓����蔻��F�Ԃ�l�Abool

void SetAllCollisionBool(const bool value);
const bool& GetAllCollisionBool();

#endif // !COLLISION_H_

