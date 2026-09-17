#pragma once
#include "Engine/GameObject.h"
#include <vector>
class Ground :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);

	//初期化
	void Initialize() override;
	std::vector<std::vector<int>>& GetMapData() { return mapData_; }
	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	/*void DecEsaCount(int type)
	{
		esaCount_--;
		if (type == 1)
		{
			normalEsaCount_--;
		}
		else if (type == 2)
		{
			powerEsaCount_--;
		}
	}*/

private:
	int hSilly;
	int hburokkuk;
	//int hSmallBall;
	std::vector<std::vector<int>> mapData_;
	std::vector<std::vector<int>> ballData_;
	int mapWidth_;
	int mapHeight_;
	int esaCount_ = 0;
	int normalEsaCount_;
	int powerEsaCount_;
};

