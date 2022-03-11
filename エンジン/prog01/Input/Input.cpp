#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX;

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	//�������i��x�����s�������j
	result = DirectInput8Create
	(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr
	);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

#pragma region �L�[�{�[�h
	//�L�[�{�[�h�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel
	(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}
#pragma endregion
#pragma region �}�E�X
	// �}�E�X�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	// ���̓f�[�^�`���̃Z�b�g
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // �W���`��
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	// �r�����䃌�x���̃Z�b�g
	result = devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}
#pragma endregion
#pragma region �Q�[���p�b�h
	//�������i��x�����s�������j
	result = DirectInput8Create
	(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinputPad, nullptr
	);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	// �f�o�C�X�̗�
	if (FAILED(dinputPad->EnumDevices(DI8DEVTYPE_GAMEPAD, DeviceFindCallBack, &parameter, DIEDFL_ATTACHEDONLY)))
	{
		assert(0);
		return result;
	}

	result = dinputPad->CreateDevice(GUID_Joystick, &devGamePad, NULL);
	if (FAILED(result))
	{
		padFlag = false;
	}

	if (padFlag == true)
	{
		// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
		result = devGamePad->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// �����[�h���Βl���[�h�Ƃ��Đݒ�
		//ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.diph.dwObj = 0;
		diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h�̎w��(DIPROPAXISMODE_REL�ɂ����瑊�Βl)
		// �����[�h��ύX
		result = devGamePad->SetProperty(DIPROP_AXISMODE, &diprop.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// X���̒l�͈̔͐ݒ�
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.diph.dwObj = DIJOFS_X;
		diprg.lMin = -1000;
		diprg.lMax = 1000;
		result = devGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// Y���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		result = devGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// Z���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_Z;
		result = devGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// RX���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_RX;
		result = devGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		// RY���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_RY;
		result = devGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}

		result = devGamePad->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(result))
		{
			assert(0);
			return result;
		}
	}
#pragma endregion

	return true;
}

void Input::Update()
{
	HRESULT result;

#pragma region �L�[�{�[�h
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();
	// �O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));
	//�S�L�[�̓��͏�Ԃ��擾����
	result = devkeyboard->GetDeviceState(sizeof(key), key);
#pragma endregion
#pragma region �}�E�X
	//�}�E�X���̎擾�J�n
	result = devMouse->Acquire();
	// �O��̃L�[���͂�ۑ�
	memcpy(&mouseStatePre, &mouseState, sizeof(mouseState));
	//�}�E�X�̓��͏�Ԃ��擾����
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
#pragma endregion
#pragma region �Q�[���p�b�h
	if (padFlag == true)
	{
		// ����J�n
		result = devGamePad->Acquire();
		// �O��̃L�[���͂�ۑ�
		memcpy(&padDataPre, &padData, sizeof(padData));
		// �Q�[���p�b�h�̓��͏��擾
		result = devGamePad->GetDeviceState(sizeof(padData), &padData);
	}
#pragma endregion
}

bool Input::PushKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0�łȂ���Ή����Ă���
	if (key[keyNumber])
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!keyPre[keyNumber] && key[keyNumber])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

BOOL CALLBACK Input::DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

bool Input::PushPadStickUp()
{
	if (padData.lY < -angle)
	{
		return true;
	}

	return false;
}

bool Input::PushPadStickDown()
{
	if (padData.lY > angle)
	{
		return true;
	}

	return false;
}

bool Input::PushPadStickRight()
{
	if (padData.lX > angle)
	{
		return true;
	}

	return false;
}

bool Input::PushPadStickLeft()
{
	if (padData.lX < -angle)
	{
		return true;
	}

	return false;
}

XMFLOAT2& Input::PadStickGradient()
{
	float x = padData.lX / 1000;
	float y = padData.lY / 1000;
	return XMFLOAT2(x, y);
}

double Input::PadStickAngle()
{
	double radian = atan2(padData.lY - 0, padData.lX - 0);
	return radian * (180.0f / 3.14159265359f);
}

bool Input::TriggerPadLeft()
{
	if (padData.lZ > angle)
	{
		return true;
	}

	return false;
}

bool Input::TriggerPadRight()
{
	if (padData.lZ < -angle)
	{
		return true;
	}

	return false;
}

bool Input::PushPadKey(PadKey keyNumber)
{
	// 0�łȂ���Ή����Ă���
	if (padData.rgbButtons[keyNumber])
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerPadKey(PadKey keyNumber)
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!padDataPre.rgbButtons[keyNumber] && padData.rgbButtons[keyNumber])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::PushMouseLeft()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[0])
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::PushMouseMiddle()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[2])
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::PushMouseRight()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[1])
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerMouseLeft()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::TriggerMouseMiddle()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::TriggerMouseRight()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;
	return tmp;
}

Input::Input()
{
}

Input::~Input()
{
}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}
