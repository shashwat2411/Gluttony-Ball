#pragma once

//======================================================
//	当たり判定ヘッダー
//======================================================

#ifndef COLLISION_H_

#define	COLLISION_H_

#include	"include_lib.h"

//==============================================================
//	当たり判定の方向
//==============================================================
enum COLLISION_WAY
{
	None, Up, Down, Right, Left,
};

//==============================================================
//	コリジョン検索
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
	引数：col_pos:コリジョンの中心座標		：col_size:コリジョンのサイズ		*/
bool	GetCollision(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	オブジェクト同士の当たり判定
bool	GetCollisionUp(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	オブジェクト上部との当たり判定：返り値、bool
bool	GetCollisionDown(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	オブジェクト下部との当たり判定：返り値、bool
bool	GetCollisionRight(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	オブジェクト右部分との当たり判定：返り値、bool
bool	GetCollisionLeft(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2);	//	オブジェクト左部分との当たり判定：返り値、bool
const	COLLISION_WAY&	CheckTouchStageGimmick(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);

//======================================================================================================================
//	足場に触れているか判定処理
const	COLLISION_WAY&	CheckTouchGround(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);

//======================================================================================================================
//	足場に触れているか判定処理
const	COLLISION_WAY&	CheckTouchStageGimmick(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1);


//bool	GetCollisionTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2,	bool*	OnCol);	//	オブジェクト同士の当たり判定
//bool	GetCollisionUpTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	オブジェクト上部との当たり判定：返り値、bool
//bool	GetCollisionDownTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	オブジェクト下部との当たり判定：返り値、bool
//bool	GetCollisionRightTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	オブジェクト右部分との当たり判定：返り値、bool
//bool	GetCollisionLeftTrigger(const	D3DXVECTOR2&	col_pos1, const	D3DXVECTOR2&	col_befpos1, const	D3DXVECTOR2&	col_size1,
//	const	D3DXVECTOR2&	col_pos2, const	D3DXVECTOR2&	col_size2, bool*	OnCol);	//	オブジェクト左部分との当たり判定：返り値、bool

void SetAllCollisionBool(const bool value);
const bool& GetAllCollisionBool();

#endif // !COLLISION_H_

