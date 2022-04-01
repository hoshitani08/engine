#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModel.h"
#include "FbxLoader.h"
#include "Camera.h"
#include "LightGroup.h"

class FbxObject3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:// �萔
//�{�[���̍ő吔
	static const int MAX_BONES = 32;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\���́i���W�ϊ��s��p�j
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;    // �r���[�v���W�F�N�V�����s��
		XMMATRIX world; // ���[���h�s��
		XMFLOAT3 cameraPos; // �J�������W�i���[���h���W�j
	};

	// �萔�o�b�t�@�p�f�[�^�\���́i�X�L�j���O�j
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

	// �A�j���[�V�����p�f�[�^�\����
	struct Animation
	{
		FbxAnimStack* animstack;
		FbxTakeInfo* takeinfo;
	};

public: // �ÓI�����o�֐�
	// �ÓI������
	static void StaticInitialize(ID3D12Device* device, Camera* camera = nullptr);
	// �ÓI�j��
	static void StaticFinalize();
	// �O���t�B�b�N�p�C�v���C���̐���
	static void CreateGraphicsPipeline();
	// 3D�I�u�W�F�N�g����
	static std::unique_ptr<FbxObject3d> Create(FbxModel* model = nullptr, bool isAnimation = false);
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }
	static void SetLight(LightGroup* light) { FbxObject3d::light = light; }

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �J����
	static Camera* camera;
	//���C�g
	static LightGroup* light;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

public: // �����o�֐�
	//�f�X�g���N�^
	~FbxObject3d();
	// ������
	bool Initialize();
	// ���t���[������
	void Update();
	// �`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���f����ݒ�
	void SetModel(FbxModel* model) { this->model = model; }
	//�A�j���[�V�����̃��[�h
	void LoadAnimation();
	//�A�j���[�V�����J�n
	void PlayAnimation(int animationNumber = 0);

	// ���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }
	// ���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	// X,Y,Z�����̎擾
	const XMFLOAT3& GetRotation() { return rotation; }
	// X,Y,Z�����̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	// �X�P�[���̎擾
	const XMFLOAT3& GetScale() { return scale; }
	// �X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

protected: // �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	// �萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// ���f��
	FbxModel* model = nullptr;
	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
	//�A�j���[�V�����̃f�[�^
	std::vector<Animation> animationData;
};