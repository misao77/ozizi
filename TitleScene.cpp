#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/sceneManager.h"
#include "Engine/Text.h"

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene"),pText_(nullptr)
{
}

void TitleScene::Initialize()
{
    pText_ = new Text;
    pText_->Initialize();

}

void TitleScene::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        SceneManager* sceneManager = dynamic_cast<SceneManager*>(GetParent());

        sceneManager->ChangeScene(SCENE_ID_TEST);

    }
}

void TitleScene::Draw()
{
    if (pText_ != nullptr)
    {
        pText_->Draw(300, 200, "OZIZI PAKU");
        pText_->Draw(320, 300, "PRESS SPACE");
    }
}

void TitleScene::Release()
{
    if (pText_ != nullptr)
    {
        pText_->Release();
    }
}