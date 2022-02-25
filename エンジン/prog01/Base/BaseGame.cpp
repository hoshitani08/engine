#include "BaseGame.h"
#include "LightGroup.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

void BaseGame::Run()
{
	Initialize();

	while (true)  // �Q�[�����[�v
	{
		Update();

		if (endRequst)
		{
			break;
		}

		Draw();
	}

	Finalize();
}

void BaseGame::Initialize()
{
	// �Q�[���E�B���h�E�̍쐬
	win = std::make_unique<WinApp>();
	win->CreateGameWindow();

	//DirectX����������
	DirectXCommon::GetInstance()->Initialize(win.get());

	//���͂̏�����
	//input = std::make_unique<Input>();
	Input::GetInstance()->Initialize(win->GetInstance(), win->GetHwnd());

	// �I�[�f�B�I�̏�����
	if (!Audio::GetInstance()->Initialize())
	{
		assert(0);
		return;
	}
	// �X�v���C�g�ÓI������
	if (!Sprite::StaticInitialize(DirectXCommon::GetInstance()->GetDevice(), WinApp::window_width, WinApp::window_height))
	{
		assert(0);
		return;
	}

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(DirectXCommon::GetInstance()->GetDevice());
	//���C�g�ÓI������
	LightGroup::StaticInitialize(DirectXCommon::GetInstance()->GetDevice());
	// FBX�I�u�W�F�N�g�ÓI������
	FbxObject3d::StaticInitialize(DirectXCommon::GetInstance()->GetDevice());
	//FBX�I�u�W�F�N�g������
	FbxLoader::GetInstance()->Initialize(DirectXCommon::GetInstance()->GetDevice());
}

void BaseGame::Finalize()
{
	delete sceneFactory;
	Sprite::StaticFinalize();
	Object3d::StaticFinalize();
	FbxObject3d::StaticFinalize();
	FbxLoader::GetInstance()->Finalize();
	// �Q�[���E�B���h�E�̔j��
	win->TerminateGameWindow();
}

void BaseGame::Update()
{
	// ���b�Z�[�W����
	if (win->ProcessMessage())
	{
		endRequst = true;
		return;
	}

	// ���͊֘A�̖��t���[������
	Input::GetInstance()->Update();

	// �Q�[���V�[���̖��t���[������
	SceneManager::GetInstance()->Update();
}

void BaseGame::Draw()
{
	// �`��J�n
	DirectXCommon::GetInstance()->PreDraw();

	// �Q�[���V�[���̕`��
	SceneManager::GetInstance()->Draw();

	// �`��I��
	DirectXCommon::GetInstance()->PostDraw();
}