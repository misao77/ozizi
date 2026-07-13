#pragma once
#include "Engine/GameObject.h"

class Ground;//前方宣言

class Enemy :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	//void SetGround(Ground* ground) { ground_ = ground; }
private:
	int hModel_;//歩き
	//int hIdleModel_;//待機
	//Ground* ground_;//地面オブジェクトのポインタ
};

