#pragma once
#include <SFML/Graphics.hpp>
void menu(sf::RenderWindow & window) {

	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("Images/111.png");
	menuTexture2.loadFromFile("Images/222.png");
	menuTexture3.loadFromFile("Images/333.png");
	aboutTexture.loadFromFile("Images/about.png");
	menuBackground.loadFromFile("Images/back.png");

	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 50);

	while (isMenu && window.isOpen()) {
		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);
		menuNum = 0;
		window.clear(sf::Color(59, 35, 20));

		if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu1.setColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu2.setColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu3.setColor(sf::Color::Blue);
			menuNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
				sf::Music music;
				music.openFromFile("Music/music.ogg");
				music.play();
			}
			if (menuNum == 2) {
				window.draw(about);
				window.display();
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			if (menuNum == 3) {
				window.close();
				isMenu = false;
			}
			sf::Event event;
			while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();

	}

}

