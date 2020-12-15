#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Game.h"
#include "Menu.h"
#include "Win.h"
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>
#include <time.h>


int main() {
	srand(time(NULL));
	//Русскоязычный текст
	setlocale(LC_ALL, "rus");
	sf::RenderWindow window(sf::VideoMode(750, 600), L"Пятнашки");
	//Иконка окна
	sf::Image icon;
	if (!icon.loadFromFile("Images/icon.png")) {
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());
	//Курсор
	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Hand))
		window.setMouseCursor(cursor);
	//Музыка в меню
	sf::Music menumus;
	menumus.openFromFile("Music/menu.ogg");
	menumus.play();
	//Вызов меню
	menu(window);
	window.setFramerateLimit(60);
	//Загружаем шрифт
	sf::Font font;
	font.loadFromFile("times-new-roman.ttf");
	//Управление
	sf::Text wow(L"F2 - Новая игра / Esc - Выход / Стрелки или WASD - движение плашки", font, 20);
	wow.setFillColor(sf::Color::White);
	wow.setPosition(50.f, 5.f);
	//Часы
	sf::Clock clock;
	clock.restart();
	sf::Time time = clock.getElapsedTime();

	sf::Text gametime(L"Время: ", font, 20);
	gametime.setFillColor(sf::Color::Green);
	gametime.setPosition(580.f, 80.f);
	//Музыка игры
	sf::Music music;
	music.openFromFile("Music/music.ogg");
	// Создаем объект игры
	Game game;
	game.setPosition(50.f, 50.f);

	sf::Event event;
	int move_counter = 0;	// Счетчик случайных ходов для перемешивания головоломки

	int hod = 0;

	while (window.isOpen()) {
		
		time = clock.getElapsedTime();
		int sec = time.asSeconds() - 2 ;
		std::string s = std::to_string(sec);

		sf::Text showtime(s, font, 20);
		showtime.setFillColor(sf::Color::Green);
		showtime.setPosition(650, 80);
		

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) {
					music.stop();
					menu(window);					
				}
			
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
					game.Move(Direction::Left); 
					hod++;
				}
				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
					game.Move(Direction::Right);
					hod++;
				}
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
					game.Move(Direction::Up); 
					hod++;
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					game.Move(Direction::Down); 
					hod++;
				}
				// Новая игра
				if (event.key.code == sf::Keyboard::F2)
				{
					game.Init();
					move_counter = 100;					
					menumus.stop();
					music.play();
					music.setLoop(true);
					clock.restart();
							
				}
			}
		}

		// Если счетчик ходов больше нуля, продолжаем перемешивать головоломку
		if (move_counter-- > 0) game.Move((Direction)(rand() % 4));

		if (game.Check() && hod > 0) {
			menumus.stop();
			music.stop();
			sf::Music win;
			win.openFromFile("Music/win.ogg");
			win.play();
			winpage(window);
			hod = 0;
			
		}
		
		// Выполняем необходимые действия по отрисовке
		window.clear();
		window.draw(game);
		window.draw(wow);
		window.draw(gametime);
		window.draw(showtime);
		window.display();
	}

	return 0;
}