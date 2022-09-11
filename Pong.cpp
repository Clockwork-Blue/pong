// Pong.cpp : Defines the entry point for the console application.
//

#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int player1score = 0;
	int player2score = 0;
	RectangleShape centerbar;
	centerbar.setSize(sf::Vector2f(10, 1080));
	centerbar.setPosition((static_cast<float>(1920) / 2) + 20, 0);
	Texture texturebackround;
	texturebackround.loadFromFile("graphics/Background2.png");
	Sprite SpriteBackround;
	SpriteBackround.setTexture(texturebackround);
	SpriteBackround.setPosition(0, 0);
	bool isPaused = true;
	// Create 2 bats
	Bat bat(1920 - 40, 1080 / 2);
	Bat bat2(40, 1080 / 2);

	Ball ball(1920 / 2, 1080 / 2);

	// Create HUD for both players
	Text hudp1;
	Text hudp2;

	Text start;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/8bitOperatorPlus-Regular.ttf");

	// Set the font
	hudp1.setFont(font);
	hudp2.setFont(font);
	start.setFont(font);
	// Make it big
	hudp1.setCharacterSize(75);
	hudp2.setCharacterSize(75);
	start.setCharacterSize(75);
	// set color
	hudp1.setFillColor(Color::White);
	hudp2.setFillColor(Color::White);
	start.setFillColor(Color::White);
	hudp1.setPosition((1920 / 2) - 50, 20);
	hudp2.setPosition((1920 / 2) + 50, 20);
	start.setPosition(1920 / 2, 1080 / 2);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();

		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (!isPaused) {
			//handle the pressing and releasing of the z and s keys
			if (Keyboard::isKeyPressed(Keyboard::Z))
			{
				bat2.moveUp();
			}
			else
			{
				bat2.stopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				bat2.moveDown();
			}
			else
			{
				bat2.stopDown();
			}
			// Handle the pressing and releasing of the arrow keys
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				bat.moveUp();
			}
			else
			{
				bat.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				bat.moveDown();
			}
			else
			{
				bat.stopDown();
			}

			/*
			Update the bat, the ball and the HUD
			*/
			// Update the delta time
			Time dt = clock.restart();
			bat.update(dt);
			bat2.update(dt);
			ball.update(dt);
			// Update the HUD text
			std::stringstream ssp1;
			std::stringstream ssp2;
			ssp1 << player1score;
			ssp2 << player2score;
			hudp1.setString(ssp1.str());
			hudp2.setString(ssp2.str());


			// Handle ball hitting the bottom
			if (ball.getPosition().top + 40 > window.getSize().y)
			{
				// reverse the ball direction
				ball.reboundBottomOrTop();

			}

			// Handle ball hitting top
			if (ball.getPosition().top < 0)
			{
				//reverse ball direction
				ball.reboundBottomOrTop();

			}

			// Handle ball hitting sides
			if (ball.getPosition().left < 0)
			{
				//set ball position to middle of  screen, increment score, reverse X
				ball.reboundSides();
				player2score++;
				// Check for win score
				if (player1score == 5 || player2score == 5) {
					// reset the score
					player1score = 0;
					player2score = 0;
				}
			}
			//handle sides and score
			else if (ball.getPosition().left + 40 > window.getSize().x)
			{
				//set ball position to middle of  screen, increment score, reverse X
				ball.reboundSides();
				player1score++;
				// Check for win score
				if (player1score == 5 || player2score == 5) {
					// reset the score
					player1score = 0;
					player2score = 0;
				}
			}

			// Has the ball hit the bat?
			if (ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition()))
			{
				// Hit detected so reverse
				ball.reboundBat();
			}
			/*
			Draw the bats,ball and the HUD
			*/
			window.clear();
			window.draw(SpriteBackround);
			window.draw(hudp1);
			window.draw(hudp2);
			window.draw(centerbar);
			window.draw(bat.getShape());
			window.draw(bat2.getShape());
			window.draw(ball.getShape());
		}
		else if (isPaused)
		{
			Texture Texturethumbnail;
			Texturethumbnail.loadFromFile("graphics/thumbnail.png");
			Sprite SpriteThumbnail;
			SpriteThumbnail.setTexture(Texturethumbnail);
			SpriteThumbnail.setOrigin(250, 250);
			SpriteThumbnail.setPosition(600, 1080 / 2);
			std::stringstream startstring;
			startstring << "Press Enter To Start";
			window.draw(SpriteThumbnail);
			window.draw(start);
			start.setString(startstring.str());
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				isPaused = false;
			}
		}
		window.display();
	}

	return 0;
}