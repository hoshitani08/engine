#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "Input.h"
#include "SceneManager.h"
#include "AbstractSceneFactory.h"

#include <memory>

class BaseGame
{
public:
	//���s
	void Run();
	// ������
	virtual void Initialize();
	//�I��
	virtual void Finalize();
	// ���t���[������
	virtual void Update();
	// �`��
	virtual void Draw();

protected:
	bool endRequst = false;
	std::unique_ptr<WinApp> win;
	//�V�[���t�@�N�g��
	AbstractSceneFactory* sceneFactory = nullptr;
};