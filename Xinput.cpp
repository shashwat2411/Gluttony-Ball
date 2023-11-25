
#include	"xinput.h"

#include	<xinput.h>
#include	<Windows.h>
#include	"game.h"
#pragma comment(lib,"xinput.lib")

_XINPUT_STATE state;
XINPUT_GAMEPAD pstate;

bool	PressBumperR;			//	�E�l�h���w�{�^���̏u�ԓ��͂𐧌䂷��bool
bool	PressBumperL;			//	���l�h���w�{�^���̏u�ԓ��͂𐧌䂷��bool

bool	PressTriggerR;			//	�E�l�g���K�[�{�^���̏u�ԓ��͂𐧌䂷��bool
bool	PressTriggerL;			//	���l�g���K�[�{�^���̏u�ԓ��͂𐧌䂷��bool

bool	PressButtonA;		//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂𐧌䂷��bool
bool	PressButtonB;		//	Xinput�R���g���[���[��B�{�^���̏u�ԓ��͂𐧌䂷��bool
bool	PressButtonX;		//	Xinput�R���g���[���[��X�{�^���̏u�ԓ��͂𐧌䂷��bool
bool	PressButtonY;		//	Xinput�R���g���[���[��Y�{�^���̏u�ԓ��͂𐧌䂷��bool

bool	PressButtonStart;		//	Xinput�R���g���[���[��START�{�^���̏u�ԓ��͂𐧌䂷��bool

bool	PressButtonUp;
bool	PressButtonDown;
bool	PressButtonRight;
bool	PressButtonLeft;

bool	PressLeftTrigger;				//	���l�g���K�[�{�^���̏u�ԓ��͂𐧌䂷��bool ??

void	InitXinput()	//	Xinput������
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

void	UninitXinput()	//	Xinput�I������
{

}

void	UpdateXinput()	//	Xinput�X�V����
{
	//UpdateInput();

	XInputGetState(0, &state);

	//�f�b�h�]�[�����̓��͂� 0 �Ɋۂ߂�T���v���v���O�����B
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
	//	���͂��m�F����Ȃ��ꍇ�A���L�œ��͐���Bool��false�ɂ���
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
//	���͎擾�֐�
//=================================================================================================
//STICK
const	D3DXVECTOR2&	GetStickL()	//	���X�e�B�b�N�̓��̓x�N�g���擾
{
	/*if (GetKeyboardPress(DIK_RIGHT))	return	D3DXVECTOR2(1, 0);
	else if (GetKeyboardPress(DIK_LEFT))	return	D3DXVECTOR2(-1, 0);
	else return	D3DXVECTOR2(0, 0);*/

	return	D3DXVECTOR2((float)state.Gamepad.sThumbLX / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4,
		(float)state.Gamepad.sThumbLY / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4);
}
const	D3DXVECTOR2&	GetStickR()	//	�E�X�e�B�b�N�̓��̓x�N�g���擾
{
	return	D3DXVECTOR2((float)state.Gamepad.sThumbRX / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4,
		(float)state.Gamepad.sThumbRY / XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 4);
}

//TRIGGER
const	bool&	GetBumperTriggerR()	//	�E�l�h���w�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetBumperTriggerL()	//	���l�h���w�{�^���̏u�ԓ��͂̎擾
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

const	bool&	GetTriggerTriggerR()	//	�E�l�h���w�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetTriggerTriggerL()	//	���l�h���w�{�^���̏u�ԓ��͂̎擾
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

const	bool&	GetButtonTriggerA()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerB()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerX()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerY()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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

const	bool&	GetButtonTriggerStart()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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

const	bool&	GetButtonTriggerUp()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerDown()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerRight()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetButtonTriggerLeft()	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
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
const	bool&	GetBumperPressR()		//	�E�l�h���w�{�^���̒��������͂̎擾
{
	//if (GetKeyboardPress(DIK_SPACE))	return	true;
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER)	return	true;

	return	false;
}
const	bool&	GetBumperPressL()		//	���l�h���w�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER)		return	true;

	return	false;
}

const	bool&	GetTriggerPressR()		//	�E�l�h���w�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_THUMB)	return	true;

	return	false;
}
const	bool&	GetTriggerPressL()		//	���l�h���w�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_THUMB)		return	true;

	return	false;
}

const	bool&	GetButtonPressA()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	//if (GetKeyboardPress(DIK_A))	return	true;
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_A)	return	true;

	return	false;
}
const	bool&	GetButtonPressB()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_B)	return	true;

	return	false;
}
const	bool&	GetButtonPressX()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_X)	return	true;

	return	false;
}
const	bool&	GetButtonPressY()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_Y)	return	true;

	return	false;
}

const	bool&	GetButtonPressStart()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_START)	return	true;

	return	false;
}

const	bool&	GetButtonPressUp()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP)	return	true;

	return	false;
}
const	bool&	GetButtonPressDown()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN)	return	true;

	return	false;
}
const	bool&	GetButtonPressRight()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT)	return	true;

	return	false;
}
const	bool&	GetButtonPressLeft()		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
{
	if (state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)	return	true;

	return	false;
}



const bool& GetPressLeftTrigger_Press()
{

	if (state.Gamepad.bLeftTrigger > 0)		return	true;

	return	false;
}







