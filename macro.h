#pragma once

#ifndef MACRO_H_

#define	MACRO_H_

#define DEBUG
/*======================================================
	マクロ定義：
		ゲーム全体に共通して存在する定数をここに記述する
========================================================*/

#define	BASE_SIZE	(30)

enum SCENE
{
	NONE = 0,
	TITLE,
	SELECT_DATA,
	SELECT_STAGE,
	GAME,
	RESULT,

	MAX
};

#endif // !MACRO_H_

