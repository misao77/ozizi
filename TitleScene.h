#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//class Text;

class TitleScene : public GameObject
{
public:
    TitleScene(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Text* pText_;
};