#pragma once
#include "BaseGame.h"

class MyGame : public BaseGame
{
public:
	// 初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;
	// 描画
	void Draw() override;
};