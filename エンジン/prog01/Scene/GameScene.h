#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "Model.h"
#include "ParticleManager.h"
#include "ParticleEmitter.h"
#include "CollisionPrimitive.h"
#include "Camera.h"
#include "LightGroup.h"
#include "FbxObject3d.h"
#include "FbxModel.h"
#include "FbxLoader.h"

#include <vector>
#include <memory>

#include "BaseScene.h"

class CollisionManager;
class Player;
class ContactableObject;

class GameScene : public BaseScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�
	// �f�X�g���N�^
	~GameScene();
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�ϐ�
	//�J����
	std::unique_ptr<Camera> camera;
	//�X�v���C�g
	std::unique_ptr<Sprite> sprite;
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> particleMan;
	//�I�u�W�F�N�g
	std::unique_ptr<Model> modelSkydome;
	std::unique_ptr<Model> modelGround;
	std::unique_ptr<Model> modelFighter;
	std::unique_ptr<Model> modelSphere;

	std::unique_ptr<Object3d> objSkydome;
	std::unique_ptr<Object3d> objGround;
	std::unique_ptr<Object3d> objFighter;
	std::unique_ptr<Object3d> objSphere;

	std::unique_ptr<FbxObject3d> fbxObject3d;
	std::unique_ptr<FbxModel> fbxModel;

	//���C�g
	std::unique_ptr<LightGroup> light;
	//�������������l
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	float fighterPos[3] = { 1, 0.0f, 0 };
	//�����蔻��
	CollisionManager* collisionManager = nullptr;
};