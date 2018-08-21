#include "EnemySelectScene.h"
#include "Define.h"
#include "Graphics.h"
#include <vector>
#include <array>
using namespace std;

EnemySelectScene::EnemySelectScene(SceneChanger * impl, const Parameter & parameter) :
  AbstractScene(impl, parameter),
  //{left, top}, {width, height}
  background {{0.f, 0.f}, {static_cast<float>(Define::WIN_W), static_cast<float>(Define::WIN_H)}},
  prevButton {"test-button", {10.f, 10.f}, {100.f, 100.f}}
{
  printfDx("%d\n", Graphics::getIns()->getHandle("resource/image/UI/g4.png"));
  prevButton.addDrawer(array<int, 4>{
    Graphics::getIns()->getHandle("resource/image/UI/g4.png"), 
    Graphics::getIns()->getHandle("resource/image/UI/g2.png"),
    Graphics::getIns()->getHandle("resource/image/UI/g4.png"),
    Graphics::getIns()->getHandle("resource/image/UI/g4.png")
  });
}

void EnemySelectScene::update()
{
  prevButton.update();
  if (prevButton.pressUp()) {
    _implSceneChanged->onScenePoped();
  }
}

void EnemySelectScene::draw() const
{
  background.draw();
  prevButton.draw();
}
