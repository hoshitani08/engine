#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ContactableObject.h"
#include "SceneManager.h"

using namespace DirectX;

GameScene::~GameScene()
{
	Finalize();
}

void GameScene::Initialize()
{
	collisionManager = CollisionManager::GetInstance();

	// �J��������
	camera = std::make_unique<Camera>(WinApp::window_width, WinApp::window_height);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera.get());
	// FBX�I�u�W�F�N�g�ɃJ�������Z�b�g
	FbxObject3d::SetCamera(camera.get());

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
	}
	// �f�o�b�O�e�L�X�g������
	DebugText::GetInstance()->Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/APEX_01.png"))
	{
		assert(0);
	}

	// �w�i�X�v���C�g����
	sprite = Sprite::Create(1, { 0.0f,0.0f });
	sprite->SetSize({ 100.0f,100.0f });
	sprite->SetPosition({ 100.0f,100.0f });

	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::Create(DirectXCommon::GetInstance()->GetDevice(), camera.get());

	//���C�g����
	light = LightGroup::Create();
	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLight(light.get());
	light->SetDirLightActive(0, true);
	light->SetDirLightActive(1, true);
	light->SetDirLightActive(2, true);
	light->SetPointLightActive(0, false);
	light->SetPointLightActive(1, false);
	light->SetPointLightActive(2, false);
	light->SetCircleShadowActive(0, true);

	// ���f���ǂݍ���
	modelSkydome = Model::CreateFromObject("skydome");
	modelGround = Model::CreateFromObject("ground");
	modelFighter = Model::CreateFromObject("chr_sword");
	modelSphere = Model::CreateFromObject("sphere", true);

	// 3D�I�u�W�F�N�g����
	objSkydome = Object3d::Create(modelSkydome.get());
	objGround = Object3d::Create(modelGround.get());
	objFighter = Object3d::Create(modelFighter.get());
	objSphere = Object3d::Create(modelSphere.get());

	objFighter->SetPosition(XMFLOAT3(fighterPos));
	objSphere->SetPosition({ -1, 1, 0 });

	//.fbx�̖��O���w�肵�ă��f����ǂݍ���
	fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("uma");
	// FBX�I�u�W�F�N�g����
	fbxObject3d = FbxObject3d::Create(fbxModel.get());
	//�A�j���[�V����
	fbxObject3d->PlayAnimation();

	//�T�E���h�Đ�
	Audio::GetInstance()->LoadWave(0, "Resources/Alarm01.wav");

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 0, 0 });
	camera->SetEye({ 0,10,-1 });
}

void GameScene::Finalize()
{
}

void GameScene::Update()
{
	Input* input = Input::GetInstance();
	light->Update();
	camera->Update();
	particleMan->Update();

	// �I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_W))
		{
			fighterPos[1] += 0.1f;
		}
		else if (input->PushKey(DIK_S))
		{
			fighterPos[1] -= 0.1f;
		}

		if (input->PushKey(DIK_D))
		{
			fighterPos[0] += 0.1f;
		}
		else if (input->PushKey(DIK_A))
		{
			fighterPos[0] -= 0.1f;
		}
	}

	if (input->TriggerKey(DIK_C))
	{
		SceneManager::GetInstance()->ChangeScene("ClearScene");
	}
	else if (input->TriggerKey(DIK_B))
	{
		SceneManager::GetInstance()->ChangeScene("GameOverScene");
	}

	XMFLOAT3 rot = objSphere->GetRotation();
	rot.y += 1.0f;
	objSphere->SetRotation(rot);
	objFighter->SetRotation(rot);

	light->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	light->SetCircleShadowCasterPos(0, XMFLOAT3({ fighterPos[0], fighterPos[1], fighterPos[2] }));
	light->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	light->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	objFighter->SetPosition(XMFLOAT3({ fighterPos[0], fighterPos[1], fighterPos[2] }));


	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();

	fbxObject3d->Update();
	// �S�Ă̏Փ˂��`�F�b�N
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	sprite->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�N�W�F�N�g�̕`��
	Object3d::PreDraw(cmdList);
	objSkydome->Draw();
	objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();
	Object3d::PostDraw();
#pragma endregion 3D�I�u�W�F�N�g�`��
#pragma region 3D�I�u�W�F�N�g(FBX)�`��
	fbxObject3d->Draw(cmdList);
#pragma endregion 3D�I�u�W�F�N�g(FBX)�`��
#pragma region �p�[�e�B�N��
	// �p�[�e�B�N���̕`��
	particleMan->Draw(cmdList);
#pragma endregion �p�[�e�B�N��
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}