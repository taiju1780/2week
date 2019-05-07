#include "Game.h"
#include <DxLib.h>
#include "Scene/TitleScene.h"

Game::Game()
{
}

void Game::ChangeScene(Scene * scene)
{
	_scene.reset(scene);
}

Game::~Game()
{
}

void Game::Init()
{
	DxLib::SetGraphMode(650, 900, 32);
	DxLib::ChangeWindowMode(true);

	if (DxLib::DxLib_Init() == -1) {
		return;
	}

	DxLib::SetWindowText("1701315_ŒÃ‰ê‘åŽ÷_NINJA");
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	ChangeScene(new TitleScene(1500));
}

void Game::Run()
{
	Input input;

	while (DxLib::ProcessMessage() == 0) {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		DxLib::ClsDrawScreen();

		input.Update();

		_scene->Update(input);

		DxLib::ScreenFlip();
	}
}

void Game::End()
{
	DxLib_End();
}
