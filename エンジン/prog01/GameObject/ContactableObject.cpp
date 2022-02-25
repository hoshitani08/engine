#include "ContactableObject.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"

ContactableObject* ContactableObject::Create(Model* model)
{
	// �I�u�W�F�N�g�̃C���X�^���X�𐶐�
	ContactableObject* instance = new ContactableObject();
	if (instance == nullptr)
	{
		return nullptr;
	}

	// ������
	if (!instance->Initialize(model))
	{
		delete instance;
		assert(0);
	}

	return instance;
}

bool ContactableObject::Initialize(Model* model)
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	SetModel(model);

	// �R���C�_�[�̒ǉ�
	MeshCollider* collider = new MeshCollider;
	SetCollider(collider);
	collider->ConstructTriangles(model);
	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);

	return true;
}