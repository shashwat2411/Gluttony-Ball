#pragma once

#include "znoTouch_BaseOfPerformer.h"

#ifndef BUTTON_H_

#define	BUTTON_H_


//============================================================
//	ボタンブロッククラス
//=============================================================
#define BUTTON_MAX (10) //ボタンブロックの配置個数上限

class BUTTON :public	BASE_OF_PERFORMER
{
	private:
		unsigned	int	g_ButtonSE;

		bool	SwitchAble;

		bool	BallCollide = false;	//ボールに当たったかどうか, true:当たった, false:当たってない
		bool	On_OffSwitch;	//trueならスイッチがオンになりギミックが作動する

		bool	SaveAble;

	public:
		void	Update();
		void	Prepare();
		void	Reset();

		void	SetOn_OffSwitch(const bool on_off) { On_OffSwitch = on_off;	PlaySound(g_ButtonSE, 0); };
		bool	GetOn_OffSwitch() { return On_OffSwitch; };
		void	SetButton(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off);

		void	SetSaveAble(const	bool	new_bool) { SaveAble = new_bool; }
		const	bool&	GetSaveAble(void) { return	SaveAble; }

	private:

};

//=============================================
//	ボタン管理プログラム
//=============================================
void	InitButton();		//ボタンブロック初期化
void	UninitButton();		//ボタンブロック終了処理
void	UpdateButton();		//ボタンブロック更新処理
void	DrawButton();		//ボタンブロック描画処理

void	SetButtons(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off, int index);	//	ボタンのセット
//void SetButtons(const D3DXVECTOR2& pos, const D3DXVECTOR2& size); //ボタンブロックのセット
BUTTON* GetButton();//ボタンブロック取得


#endif