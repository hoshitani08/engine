#pragma once
#include "BaseScene.h"

#include <string>

class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;
	//シーン生成
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};