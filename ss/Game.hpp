#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderTarget* mRenderTarget;
	bool mIsRunning;

public:
	Game(sf::RenderTarget& window);

	void init();

	void handleEvents(sf::Event event);
	void update(float dTime);
	void render();

	bool isRunning() const;

	~Game();
};

#endif
