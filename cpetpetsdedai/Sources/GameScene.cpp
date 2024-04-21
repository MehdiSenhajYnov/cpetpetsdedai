#include "../Headers/GameScene.h"

GameScene::GameScene()
{
}

void GameScene::InitializeScene(sf::RenderWindow* _window)
{


	if (!font.loadFromFile("./Fonts/Arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	ThrowsText.setFont(font);


	ThrowsText.setCharacterSize(48);
	ThrowsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	ThrowsText.setFillColor(sf::Color::Black);

	LevelText.setFont(font);
	LevelText.setCharacterSize(48);
	LevelText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	LevelText.setFillColor(sf::Color::Black);


	std::cout << "Game Scene initialize begin" << std::endl;
	window = _window;

	mainCameraObject = CreateGameObject("mainCameraObject",0);
	mainCamera = Camera();
	mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);

	AddComponent(mainCameraObject, &mainCamera);
	graphicDebugger = GraphicDebugger();
	graphicDebugger.Init(&mainCamera);
	
	physicsEngine = PhysicsEngine();
	physicsEngine.Init(this, &graphicDebugger);

	SetupMapElements();
	SetupElements();

	graphicDebugger.Disable();
	//physicsEngine.SwitchModifyMode();
	physicsEngine.SetModifyMode(false);
	std::cout << "Game Scene initialize end" << std::endl;

	InitLevel();

	LevelText.setString("Level" + std::to_string(currentLevel));
	LevelText.setPosition(sf::Vector2f(window->getSize().x / 2, 20));

	mainCamera.AddToTexts(&ThrowsText);
	mainCamera.AddToTexts(&LevelText);

	physicsEngine.EnterModifyMode();

}

void GameScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}


void GameScene::GameLoop(float deltaTime)
{

	mainCameraObject->SetPosition(sf::Vector2(Player->GetPosition().x - window->getSize().x/2, mainCameraObject->GetPosition().y));

	CalUpdateOnAll(deltaTime);
	physicsEngine.UpdatePhysics(deltaTime);
}


void GameScene::DestroyScene()
{

}

void GameScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{
	float forceToAdd = 10;
	float multiplier = 0.05f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerCollider->AddForce(sf::Vector2f(-forceToAdd * multiplier, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerCollider->AddForce(sf::Vector2f(forceToAdd * multiplier, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerCollider->AddForce(sf::Vector2f(0, -forceToAdd * multiplier));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerCollider->AddForce(sf::Vector2f(0, forceToAdd * multiplier));
	}

}

void GameScene::OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint)
{
	if (_collideWith->GetAttachedObject()->Name == "Target")
	{
		SceneManager::SetLevel(currentLevel + 1);
	}
}

void GameScene::OnSceneChanged()
{
	sceneChanged = true;
}





std::shared_ptr<GameObject> GameScene::CreateBackground()
{
	auto tempBackground = CreateGameObject("Background", 0);
	//tempBackground->SetSprite("./Assets/Background.png");
	return tempBackground;
}

std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<BoxCollider>> GameScene::CreatePlayer()
{
	auto _tempPlayer = CreateGameObject("Player", 20);
	_tempPlayer->SetSprite("PLAYERIDLE");
	_tempPlayer->GetSprite()->setScale(sf::Vector2f(1.25f, 1.25f));
	_tempPlayer->SetPosition(300, 400);

	auto _tempPlayerCollider = physicsEngine.CreateBoxCollider(_tempPlayer, sf::Vector2f(290, 150), sf::Vector2f(90, 160));
	//_tempPlayerCollider->OnCollisionEnter()->Subscribe(&GameScene::OnPlayerCollisionEnter, this);
	_tempPlayerCollider->Gravity = true;

	// create animator for player
	// playerAnimator = Animator();

	// create animations for player
	
	
	
	return std::make_tuple(_tempPlayer, _tempPlayerCollider);
}

std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreateTarget()
{

	std::shared_ptr<GameObject> target = CreateGameObject("Target", 20);
	//target->SetSprite("./Assets/Target.png");
	target->GetSprite()->setScale(sf::Vector2f(0.05f, 0.05f));
	std::shared_ptr<CustomCollider> targetCollider = physicsEngine.CreateCustomCollider(target, {
		sf::Vector2f(15,70),
		sf::Vector2f(45,70),
		sf::Vector2f(60,79),
		sf::Vector2f(60,90),

		sf::Vector2f(45,100),
		sf::Vector2f(15,100),
		sf::Vector2f(0, 90),
		sf::Vector2f(0,79),
		});
	targetCollider->SetIsStatic(true);

	return std::make_tuple(target, targetCollider);

}
