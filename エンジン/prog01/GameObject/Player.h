#pragma once

#include "Object3d.h"
#include "ParticleManager.h"
#include "Input.h"

class Player : public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Player* Create(Model* model = nullptr);

public:
	// ������
	bool Initialize() override;
	// ���t���[������
	void Update() override;
	// �Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;
	// �}�l�[�W���[�̐ݒ�
	void SetParticleManager(ParticleManager* particleMan) { this->particleMan = particleMan; }
	void SetInput(Input* input) { this->input = input; }

private: // �����o�ϐ�
	ParticleManager* particleMan = nullptr;
	Input* input = nullptr;
	//�ڒn�t���O
	bool onGround = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV;
};