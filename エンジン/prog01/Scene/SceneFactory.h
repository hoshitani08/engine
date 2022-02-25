#pragma once
#include "AbstractSceneFactory.h"

class SceneFactory : public AbstractSceneFactory
{
public:
	//�V�[������
	BaseScene* CreateScene(const std::string& sceneName) override;
};