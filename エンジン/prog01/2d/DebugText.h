#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>

class DebugText final
{
private: // �G�C���A�X
	using XMVECTOR = DirectX::XMVECTOR;

public:
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	static const int maxCharCount = 256; // �ő啶����
	static const int fontWidth = 9; // �t�H���g�摜��1�������̉���
	static const int fontHeight = 18; // �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14; // �t�H���g�摜��1�s���̕�����

public:// �ÓI�����o�֐�
	static DebugText* GetInstance();

public:// �����o�֐�

	void Initialize(UINT texnumber);

	void Print(const std::string& text, float x, float y, float size);

	void VariablePrint(float x, float y, const std::string& text, float i, float size);

	void DrawAll(ID3D12GraphicsCommandList* cmdList);

	DebugText(const DebugText&) = delete;
	DebugText& operator=(const DebugText&) = delete;

private:
	DebugText();
	~DebugText();

private:
	// �X�v���C�g�f�[�^�̔z��
	std::unique_ptr<Sprite> spriteDatas[maxCharCount];
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;

	XMVECTOR variable;
};