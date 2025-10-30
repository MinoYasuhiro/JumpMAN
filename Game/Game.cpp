#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Kuribo.h"
#include "Nokonoko.h"


Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0, "backGround");
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_kuribo = NewGO<Kuribo>(0, "kuribo");
	m_kuribo1 = NewGO<Kuribo>(0, "kuribo");
	m_kuribo2 = NewGO<Kuribo>(0, "kuribo");

	m_nokonoko = NewGO<Nokonoko>(0, "nokonoko");

	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}