#pragma once
#include "Scene/Scene.h"
#include <memory>

class Game
{
private:

	//ƒVƒ“ƒOƒ‹ƒgƒ“
	Game();
	Game(const Game&) {};
	void operator=(const Game&) {};

public:
	static Game& Instance() {
		static Game instance;
		return instance;
	}

	~Game();

	void Init();

	void Run();

	void End();

	void ChangeScene(Scene *scene);

	std::shared_ptr<Scene> _scene;
};
