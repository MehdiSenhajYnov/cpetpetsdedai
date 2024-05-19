#include "../../Headers/Scenes/GameScene.h"

#include "../../Headers/Components/Animator.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/PhysicsComponents/BoxCollider.h"
#include "../../Headers/Scenes/SceneManager.h"
#include "../../Headers/PhysicsComponents/CustomCollider.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/GameSystem/PhysicsEngine.h"

GameScene::GameScene() : Scene("GameScene", Scene::GetStaticType())
{
}

void GameScene::InitializeScene(sf::RenderWindow* _window)
{
	Scene::InitializeScene(_window);

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

	
	PhysicsEngine::GetInstance()->Init(this);

	SetupMapElements();
	SetupElements();

	//PhysicsEngine::GetInstance()->SwitchModifyMode();
	PhysicsEngine::GetInstance()->SetModifyMode(false);
	std::cout << "Game Scene initialize end" << std::endl;

	InitLevel();

	LevelText.setString("Level" + std::to_string(currentLevel));
	LevelText.setPosition(sf::Vector2f(window->getSize().x / 2, 20));

	mainCamera->AddToTexts(&ThrowsText);
	mainCamera->AddToTexts(&LevelText);

	PhysicsEngine::GetInstance()->EnterModifyMode();
}

void GameScene::UpdatePreComponent(float deltaTime)
{
	
}

void GameScene::UpdatePostComponent(float deltaTime)
{
	PhysicsEngine::GetInstance()->UpdatePhysics(deltaTime);
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
	if (_collideWith->GetAttachedObject()->GetName() == "Target")
	{
		SceneManager::GetInstance()->SetLevel(currentLevel + 1);
	}
}

void GameScene::OnSceneChanged()
{
	sceneChanged = true;
}





GameObject* GameScene::CreateBackground()
{
	auto tempBackground = Create<GameObject>();
	tempBackground->Init("Background");
	//tempBackground->SetSprite("./Assets/Background.png");
	return tempBackground;
}

std::tuple<GameObject*, Collider*> GameScene::CreatePlayer()
{
	auto _tempPlayer = Create<GameObject>();
	_tempPlayer->Init("Player");
	SpriteRenderer* playerSpriteRenderer = _tempPlayer->AddComponent<SpriteRenderer>();
	playerSpriteRenderer->SetSprite("PLAYERIDLE001");
	playerSpriteRenderer->SetZIndex(20);
	playerSpriteRenderer->SetScale(sf::Vector2f(1.25f, 1.25f));
	
	_tempPlayer->SetPosition(300, 400);

	auto _tempPlayerCollider = PhysicsEngine::GetInstance()->CreateBoxCollider(_tempPlayer, sf::Vector2f(290, 150), sf::Vector2f(90, 160));
	//auto _tempPlayerCollider = PhysicsEngine::GetInstance()->CreateCustomCollider(_tempPlayer, {sf::Vector2f(0,0), sf::Vector2f(50,50), sf::Vector2f(0,100)});
	//_tempPlayerCollider->OnCollisionEnter()->Subscribe(&GameScene::OnPlayerCollisionEnter, this);
	_tempPlayerCollider->Gravity = true;

	// create animator for player
	Animator* playerAnimator = _tempPlayer->AddComponent<Animator>();
	playerAnimator->Init(playerSpriteRenderer);
	Animation* IdleAnimation = playerAnimator->CreateAnimation("Idle", 0.5f, true, {"PLAYERIDLE001", "PLAYERIDLE002", "PLAYERIDLE003", "PLAYERIDLE004", "PLAYERIDLE005", "PLAYERIDLE006"});

	playerAnimator->Play("Idle");
	
	// create animations for player
	
	return std::make_tuple(_tempPlayer, _tempPlayerCollider);
}

std::tuple<GameObject*, CustomCollider*> GameScene::CreateTarget()
{

	GameObject* target = Create<GameObject>();
	target->Init("Target");
	
	CustomCollider* targetCollider = PhysicsEngine::GetInstance()->CreateCustomCollider(target, {
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
