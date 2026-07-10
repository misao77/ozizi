#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"

namespace
{
	using std::vector;
	int model_t = -1;
	vector <vector<int>> mapData =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,0,1,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,1,0,1,1,1,1},
		{1,1,1,0,1,1,0,1,1,1},
		{1,1,1,0,0,1,1,1,1,1},
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,1,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1), hburokkuk(-1)
{
	mapData_ = mapData;//ファイルグローバルのmapDataをコピーして、メンバ変数に
}

void Ground::Initialize()
{
	hSilly = Model::Load("yukada.fbx");
	Model::SetAnimFrame(hSilly, 0, 59, 1.0);
	hburokkuk = Model::Load("rego.fbx");
	Model::SetAnimFrame(hburokkuk, 0, 59, 1.0);
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

	//ブロック
	//transform_.scale_ = { 0.3f, 0.3f, 0.4f };
	/*transform_.position_ = { 1.0f, -1.0f, 0 };
	Model::SetTransform(hburokkuk, transform_);
	Model::Draw(hburokkuk);*/
}

void Ground::Release()
{
}
