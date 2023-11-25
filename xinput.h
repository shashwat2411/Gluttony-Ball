#pragma once

#ifndef XINPUT_H_

#define	XINPUT_H_

#include	"include_lib.h"

void	InitXinput();	//	Xinput������
void	UninitXinput();	//	Xinput�I������
void	UpdateXinput();	//	Xinput�X�V����

const	D3DXVECTOR2&	GetStickL();	//	���X�e�B�b�N�̓��̓x�N�g���擾
const	D3DXVECTOR2&	GetStickR();	//	�E�X�e�B�b�N�̓��̓x�N�g���擾




const	bool&	GetBumperTriggerR();	//	�E�l�h���w�{�^���̏u�ԓ��͂̎擾
const	bool&	GetBumperTriggerL();	//	���l�h���w�{�^���̏u�ԓ��͂̎擾

const	bool&	GetTriggerTriggerR();	//	�E�l�h���w�{�^���̏u�ԓ��͂̎擾
const	bool&	GetTriggerTriggerL();	//	�E�l�h���w�{�^���̏u�ԓ��͂̎擾

const	bool&	GetButtonTriggerA();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerB();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerX();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerY();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾

const	bool&	GetButtonTriggerStart();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾

const	bool&	GetButtonTriggerUp();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerDown();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerRight();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾
const	bool&	GetButtonTriggerLeft();	//	Xinput�R���g���[���[��A�{�^���̏u�ԓ��͂̎擾

const	bool&	GetPressLeftTrigger_Trigger();		//	



const	bool&	GetBumperPressR();		//	�E�l�h���w�{�^���̒��������͂̎擾
const	bool&	GetBumperPressL();		//	���l�h���w�{�^���̒��������͂̎擾

const	bool&	GetTriggerPressR();		//	�E�l�h���w�{�^���̒��������͂̎擾
const	bool&	GetTriggerPressL();		//	�E�l�h���w�{�^���̒��������͂̎擾

const	bool&	GetButtonPressA();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressB();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressX();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressY();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾

const	bool&	GetButtonPressStart();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾

const	bool&	GetButtonPressUp();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressDown();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressRight();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾
const	bool&	GetButtonPressLeft();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾

const	bool&	GetPressLeftTrigger_Press();		//	Xinput�R���g���[���[��A�{�^���̒��������͂̎擾

#endif // !XINPUT_H_

