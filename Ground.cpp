#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine/CsvReader.h"
#include "Food.h"

namespace
{
	using std::vector;
	int model_t = -1;
	/*vector <vector<int>> mapData =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,0,1,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	};*/
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1), hburokkuk(-1),mapWidth_(-1),mapHeight_(-1)
{
	CsvReader csvData;
	csvData.Load("csv1.csv");
	mapWidth_ = csvData.GetWidth();
	mapHeight_ = csvData.GetHeight()/2;

	mapData_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));
	ballData_ = std::vector<std::vector<int>>(mapHeight_, std::vector<int>(mapWidth_, 0));

	for(int x = 0; x < mapWidth_; x++)
	{
		for (int y = 0; y < mapHeight_; y++)
		{
			mapData_[y][x] = csvData.GetValue(x, y);
		}

	}
	for (int x = 0; x < mapWidth_; x++)
	{
		for (int y = 0; y < mapHeight_; y++)
		{
			ballData_[y][x] = csvData.GetValue(x, y+mapHeight_);
			if (ballData_[y][x] > 0) {
				Food* food = Instantiate<Food>(this);
				food->SetPosition({ -9.0f + x * 2.0f,1.0f,9.0f - y * 2.0f });
				if (ballData_[y][x] == 1)
				{
					food->SetFoodType(FoodType::FOODTYPE_NORMAL);

				}
				else if (ballData_[y][x] == 2)
				{
					food->SetFoodType(FoodType::FOODTYPE_POWER);

				}

			}
			
		}

	}


	//mapData_ = mapData;//ファイルグローバルのmapDataをコピーして、メンバ変数に
}

void Ground::Initialize()
{
	hSilly = Model::Load("yukada.fbx");
	Model::SetAnimFrame(hSilly, 0, 59, 1.0);
	hburokkuk = Model::Load("rego.fbx");
	Model::SetAnimFrame(hburokkuk, 0, 59, 1.0);
	/*hSmallBall = Model::Load("tama.fbx");
	Model::SetAnimFrame(hSmallBall, 0, 59, 1.0);*/
}

void Ground::Update()
{
}

void Ground::Draw()
{

	//transform_.position_ = { 0, 0, 0 };
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);
	for (int j = 0; j < 10; j++){
		for (int i = 0; i < 10; i++) {
			if (mapData_[j][i] == 1) {
				Transform tr;
				tr.position_ = { -9.0f + i * 2.0f, 0.0f, 9.0f - j * 2.0f };
				Model::SetTransform(hburokkuk, tr);
				Model::Draw(hburokkuk);
			}
		}
		//transform_.position_ = { 1.0f, -1.0f, 1.0 };
	}

	/*for (int j = 0; j < mapHeight_; j++)
	{
		for (int i = 0; i < mapWidth_; i++)
		{
			if (ballData_[j][i] == 1)
			{
				Transform tr;
				tr.position_ = { -9.0f + i * 2.0f, 0.5f, 9.0f - j * 2.0f };
				tr.scale_ = { 0.3f,0.3f,0.3f };

				Model::SetTransform(hSmallBall, tr);
				Model::Draw(hSmallBall);
			}
		}
	}*/

}

void Ground::Release()
{
}
