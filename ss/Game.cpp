#include "Game.hpp"

Game::Game(sf::RenderTarget& window) : mRenderTarget(&window)
{
}

void Game::init()
{
	mIsRunning = true;
}

void Game::handleEvents(sf::Event event)
{
}

void Game::update(float dTime)
{
}

void Game::render()
{
}

bool Game::isRunning() const
{
	return mIsRunning;
}

Game::~Game()
{
}
