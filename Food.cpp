#include "Food.h"
#include "Engine/Model.h"

Food::Food(GameObject* parent)
	:GameObject(parent, "Food"), type_(FOODTYPE_NORMAL),hModel_(-1),score_(0)
{
}

//Food::Food()
//{
//}

Food::~Food()
{
}

void Food::Initialize()
{
	//transform_.scale_ = { 0.3f,0.3f,0.3f };
	
}

void Food::Update()
{
	if (type_ == FoodType::FOODTYPE_POWER)
	{
		transform_.rotate_.y += 1.0f;
	}
}

void Food::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Food::Release()
{
}

void Food::SetFoodType(FoodType type)
{
	type_ = type;
	if (type_ == FoodType::FOODTYPE_NORMAL)
	{
		SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5, 0), 0.3f);
		AddCollider(collision);
		transform_.scale_ = { 0.3f,0.3f,0.3f };
		hModel_ = Model::Load("tama.fbx");
		score_ = 1;
	}
	else if (type_ == FoodType::FOODTYPE_POWER)
	{
		SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5, 0), 0.7f);
		AddCollider(collision);
		transform_.scale_ = { 0.7f,0.7f,0.7f };
		hModel_ = Model::Load("tama1.fbx");
		score_ = 5;
	}
}

void Food::OnCollision(GameObject* pTarget)
{
}
