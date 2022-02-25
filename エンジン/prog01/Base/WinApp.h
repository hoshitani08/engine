#pragma once
#include <Windows.h>

class WinApp
{
public: // �ÓI�����o�ϐ�
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280; // ����
	static const int window_height = 720; // �c��
	static const wchar_t windowClassName[];

public: // �ÓI�����o�֐�
	// �E�B���h�E�v���V�[�W��
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	// �Q�[���E�B���h�E�̍쐬
	void CreateGameWindow();
	// �Q�[���E�B���h�E�̔j��
	void TerminateGameWindow();
	// ���b�Z�[�W�̏���
	bool ProcessMessage();
	// �E�B���h�E�n���h���̎擾
	HWND GetHwnd() { return hwnd; }

	HINSTANCE GetInstance() { return wndClass.hInstance; }

private: // �����o�ϐ�
	// Window�֘A
	HWND hwnd = nullptr; // �E�B���h�E�n���h��
	WNDCLASSEX wndClass{}; // �E�B���h�E�N���X
};