#pragma once
#include "BaseGame.h"

class MyGame : public BaseGame
{
public:
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;
};