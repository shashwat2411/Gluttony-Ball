#pragma once

#ifndef XINPUT_H_

#define	XINPUT_H_

#include	"include_lib.h"

void	InitXinput();	//	Xinput初期化
void	UninitXinput();	//	Xinput終了処理
void	UpdateXinput();	//	Xinput更新処理

const	D3DXVECTOR2&	GetStickL();	//	左スティックの入力ベクトル取得
const	D3DXVECTOR2&	GetStickR();	//	右スティックの入力ベクトル取得




const	bool&	GetBumperTriggerR();	//	右人刺し指ボタンの瞬間入力の取得
const	bool&	GetBumperTriggerL();	//	左人刺し指ボタンの瞬間入力の取得

const	bool&	GetTriggerTriggerR();	//	右人刺し指ボタンの瞬間入力の取得
const	bool&	GetTriggerTriggerL();	//	右人刺し指ボタンの瞬間入力の取得

const	bool&	GetButtonTriggerA();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerB();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerX();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerY();	//	XinputコントローラーのAボタンの瞬間入力の取得

const	bool&	GetButtonTriggerStart();	//	XinputコントローラーのAボタンの瞬間入力の取得

const	bool&	GetButtonTriggerUp();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerDown();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerRight();	//	XinputコントローラーのAボタンの瞬間入力の取得
const	bool&	GetButtonTriggerLeft();	//	XinputコントローラーのAボタンの瞬間入力の取得

const	bool&	GetPressLeftTrigger_Trigger();		//	



const	bool&	GetBumperPressR();		//	右人刺し指ボタンの長押し入力の取得
const	bool&	GetBumperPressL();		//	左人刺し指ボタンの長押し入力の取得

const	bool&	GetTriggerPressR();		//	右人刺し指ボタンの長押し入力の取得
const	bool&	GetTriggerPressL();		//	右人刺し指ボタンの長押し入力の取得

const	bool&	GetButtonPressA();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressB();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressX();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressY();		//	XinputコントローラーのAボタンの長押し入力の取得

const	bool&	GetButtonPressStart();		//	XinputコントローラーのAボタンの長押し入力の取得

const	bool&	GetButtonPressUp();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressDown();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressRight();		//	XinputコントローラーのAボタンの長押し入力の取得
const	bool&	GetButtonPressLeft();		//	XinputコントローラーのAボタンの長押し入力の取得

const	bool&	GetPressLeftTrigger_Press();		//	XinputコントローラーのAボタンの長押し入力の取得

#endif // !XINPUT_H_

