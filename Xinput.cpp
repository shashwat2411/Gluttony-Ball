
#include	"xinput.h"

#include	<xinput.h>
#include	<Windows.h>
#include	"game.h"
#pragma comment(lib,"xinput.lib")

_XINPUT_STATE state;
XINPUT_GAMEPAD pstate;

bool	PressBumperR;			//	右人刺し指ボタンの瞬間入力を制御するbool
bool	PressBumperL;			//	左人刺し指ボタンの瞬間入力を制御するbool

bool	PressTriggerR;			//	右人トリガーボタンの瞬間入力を制御するbool
bool	PressTriggerL;			//	左人トリガーボタンの瞬間入力を制御するbool

bool	PressButtonA;		//	XinputコントローラーのAボタンの瞬間入力を制御するbool
bool	PressButtonB;		//	XinputコントローラーのBボタンの瞬間入力を制御するbool
bool	PressButtonX;		//	XinputコントローラーのXボタンの瞬間入力を制御するbool
bool	PressButtonY;		//	XinputコントローラーのYボタンの瞬間入力を制御するbool

bool	PressButtonStart;		//	XinputコントローラーのSTARTボタンの瞬間入力を制御するbool

bool	PressButtonUp;
bool	PressButtonDown;
bool	PressButtonRight;
bool	PressButtonLeft;

bool	PressLeftTrigger;				//	左人トリガーボタンの瞬間入力を制御するbool ??

void	InitXinput()	//	Xinput初期化
{

	PressBumperR = false;
	PressBumperL = false;

	PressTriggerR = false;
	PressTriggerL = false;

	PressButtonA = false;
	PressButtonB = false;
	PressButtonX = false;
	PressButtonY = false;

	PressButtonStart = false;

	PressButtonUp = false;
	PressButtonDown = false;
	PressButtonRight = false;
	PressButtonLeft = false;

	PressLeftTrigger = false;
}

void	UninitXinput()	//	Xinput終了処理
{

}

void	UpdateXinput()	//	Xinput更新処理
{
	//UpdateInput();

	XInputGetState(0, &state);

	//デッドゾーン内の入力を 0 に丸めるサンプルプログラム。
		//===============================================================================
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}
	//===============================================================================

	//
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		if (state.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			int a;
			a = 0;
		}
	}


	//===============================================================================
	//	入力が確認されない場合、下記で入力制御Boolをfalseにする
	//===============================================================================
	if (!GetBumperPressR() && PressBumperR)	PressBumperR = false;
	if (!GetBumperPressL() && PressBumperL)	PressBumperL = false;

	if (!GetTriggerPressR() && PressTriggerR)	PressTriggerR = false;
	if (!GetTriggerPressL() && PressTriggerL)	PressTriggerL = false;

	if (!GetButtonPressA() && PressButtonA)	PressButtonA = false;
	if (!GetButtonPressB() && PressButtonB)	PressButtonB = false;
	if (!GetButtonPressX() && PressButtonX)	PressButtonX = false;
	if (!GetButtonPressY() && PressButtonY)	PressButtonY = false;

	if (!GetButtonPressStart() && PressButtonStart)	PressButtonStart = false;

	if (!GetButtonPressUp() && PressButtonUp)	PressButtonUp = false;
	if (!GetButtonPressDown() && PressButtonDown)	PressButtonDown = false;
	if (!GetButtonPressRight() && PressButtonRight)	PressButtonRight = false;
	if (!GetButtonPressLeft() && PressButtonLeft)	PressButtonLeft = false;

	if (!GetPressLeftTrigger_Press() && PressLeftTrigger)	PressLeftTrigger = false;
}

//=================================================================================================
//	入力取得関数
//=================================================================================================
//STICK
const	D3DXVECTOR2&	GetStickL()	//	左スティックの入力ベクトル取得
{
	/*if (GetKeyboardPress(DIK_RIGHT))	return	D3DXVECTOR2(1, 0);
	else if (GetKeyboardPress(DIK_LEFT))	return	D3DXVECTOR2(-1, 0);
	else return	D3DXVECTOR2(0, 0);*/

	return	D3DXVECTOR2((float)state.Gamepad.sThumbLX / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4,
		(float)state.Gamepad.sThumbLY / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4);
}
const	D3DXVECTOR2&	GetStickR()	//	右スティックの入力ベクトル取得
{
	return	D3DXVECTOR2((float)state.Gamepad.sThumbRX / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4,
		(float)state.Gamepad.sThumbRY / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4);
}

//TRIGGER
const	bool&	GetBumperTriggerR()	//	右人刺し指ボタンの瞬間入力の取得
{
	if (GetBumperPressR())
	{
		if (!PressBumperR)
		{
			PressBumperR = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetBumperTriggerL()	//	左人刺し指ボタンの瞬間入力の取得
{
	if (GetBumperPressL())
	{
		if (!PressBumperL)
		{
			PressBumperL = true;
			return	true;
		}
	}

	return	false;
}

const	bool&	GetTriggerTriggerR()	//	右人刺し指ボタンの瞬間入力の取得
{
	if (GetTriggerPressR())
	{
		if (!PressTriggerR)
		{
			PressTriggerR = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetTriggerTriggerL()	//	左人刺し指ボタンの瞬間入力の取得
{
	if (GetTriggerPressL())
	{
		if (!PressTriggerL)
		{
			PressTriggerL = true;
			return	true;
		}
	}

	return	false;
}

const	bool&	GetButtonTriggerA()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressA())
	{
		if (!PressButtonA)
		{
			PressButtonA = true;
			return	true;
		}
		return false;
	}

	return	false;
}
const	bool&	GetButtonTriggerB()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressB())
	{
		if (!PressButtonB)
		{
			PressButtonB = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetButtonTriggerX()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressX())
	{
		if (!PressButtonX)
		{
			PressButtonX = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetButtonTriggerY()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressY())
	{
		if (!PressButtonY)
		{
			PressButtonY = true;
			return	true;
		}
	}

	return	false;
}

const	bool&	GetButtonTriggerStart()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressStart())
	{
		if (!PressButtonStart)
		{
			PressButtonStart = true;
			return	true;
		}
	}

	return	false;
}

const	bool&	GetButtonTriggerUp()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressUp())
	{
		if (!PressButtonUp)
		{
			PressButtonUp = true;
			return	true;
		}
		return false;
	}

	return	false;
}
const	bool&	GetButtonTriggerDown()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressDown())
	{
		if (!PressButtonDown)
		{
			PressButtonDown = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetButtonTriggerRight()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressRight())
	{
		if (!PressButtonRight)
		{
			PressButtonRight = true;
			return	true;
		}
	}

	return	false;
}
const	bool&	GetButtonTriggerLeft()	//	XinputコントローラーのAボタンの瞬間入力の取得
{
	if (GetButtonPressLeft())
	{
		if (!PressButtonLeft)
		{
			PressButtonLeft = true;
			return	true;
		}
	}

	return	false;
}

const bool& GetPressLeftTrigger_Trigger()
{

	if (GetPressLeftTrigger_Press())
	{
		if (!PressLeftTrigger)
		{
			PressLeftTrigger = true;
			return	true;
		}
	}

	return	false;
}



//PRESS
const	bool&	GetBumperPressR()		//	右人刺し指ボタンの長押し入力の取得
{
	//if (GetKeyboardPress(DIK_SPACE))	return	true;
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER)	return	true;

	return	false;
}
const	bool&	GetBumperPressL()		//	左人刺し指ボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER)		return	true;

	return	false;
}

const	bool&	GetTriggerPressR()		//	右人刺し指ボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_THUMB)	return	true;

	return	false;
}
const	bool&	GetTriggerPressL()		//	左人刺し指ボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_THUMB)		return	true;

	return	false;
}

const	bool&	GetButtonPressA()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	//if (GetKeyboardPress(DIK_A))	return	true;
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_A)	return	true;

	return	false;
}
const	bool&	GetButtonPressB()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_B)	return	true;

	return	false;
}
const	bool&	GetButtonPressX()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_X)	return	true;

	return	false;
}
const	bool&	GetButtonPressY()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_Y)	return	true;

	return	false;
}

const	bool&	GetButtonPressStart()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_START)	return	true;

	return	false;
}

const	bool&	GetButtonPressUp()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP)	return	true;

	return	false;
}
const	bool&	GetButtonPressDown()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN)	return	true;

	return	false;
}
const	bool&	GetButtonPressRight()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT)	return	true;

	return	false;
}
const	bool&	GetButtonPressLeft()		//	XinputコントローラーのAボタンの長押し入力の取得
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)	return	true;

	return	false;
}



const bool& GetPressLeftTrigger_Press()
{

	if (state.Gamepad.bLeftTrigger > 0)		return	true;

	return	false;
}







