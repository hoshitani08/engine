#pragma once

#include "Object3d.h"

class ContactableObject : public Object3d
{
public:
	// �I�u�W�F�N�g����
	static ContactableObject* Create(Model* model = nullptr);
	// ������
	bool Initialize(Model* model);
};