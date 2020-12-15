#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

void winpage(sf::RenderWindow & window) {

	sf::Texture winBackground, winExit, winTomenu;
	winBackground.loadFromFile("Images/win.png");
	winExit.loadFromFile("Images/quit.png");
	winTomenu.loadFromFile("Images/exit.png");

	sf::Sprite winpage1(winBackground), winpage2(winExit), winpage3(winTomenu);
	bool areuwinningson = 1;
	int winnum;
	winpage3.setPosition(50, 350);
	winpage2.setPosition(400, 350);
	winpage1.setPosition(-80, 0);

	while (areuwinningson && window.isOpen()) {
		winpage2.setColor(sf::Color::Black);
		winpage3.setColor(sf::Color::Black);
		winnum = 0;
		window.clear(sf::Color::White);

		if (sf::IntRect(50, 350, 300, 50).contains(sf::Mouse::getPosition(window))) {
			winpage3.setColor(sf::Color::Red);
			winnum = 3;
		}
		if (sf::IntRect(400, 350, 300, 50).contains(sf::Mouse::getPosition(window))) {
			winpage2.setColor(sf::Color::Red);
			winnum = 2;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (winnum == 2) {
				window.close();
				areuwinningson = false;
			}
			if (winnum == 3) {
				menu(window);
				areuwinningson = false;
			}
			sf::Event event;
			while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

		}
		window.draw(winpage1);
		window.draw(winpage2);
		window.draw(winpage3);
		window.display();
		}

}