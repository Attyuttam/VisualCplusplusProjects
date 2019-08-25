#include<SFML/Graphics.hpp>
#include <iostream>

void RandomPointsDisplay();

int main() {
	
	
	sf::RenderWindow window(sf::VideoMode(512, 512),"SFML Tutorial",sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	//player.setFillColor(sf::Color::Red);
	player.setPosition(200.0f, 200.0f);
	player.setOrigin(50.0f, 50.0f);//ensuring that when the mouse click happens, the rectangle's center comes to the mouse's arrow point

	sf::Texture playerTexture;
	playerTexture.loadFromFile("tux_from_linux.png");
	player.setTexture(&playerTexture);

	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 3;
	textureSize.y /= 9;

	player.setTextureRect(sf::IntRect(textureSize.x*0,textureSize.y*3,textureSize.x,textureSize.y));

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
					window.close();
					break;
			case sf::Event::Resized:
					std::cout << "Window height: " << evnt.size.width << " Window Height: " << evnt.size.height << std::endl;
					break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128) {
					std::cout << (char)evnt.text.unicode;
				}
			}
				
		}
		/*
		//WORKING WITH KEYBOARD INPUT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(0.0f, +0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(+0.1f, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(0.0f, -0.1f);
		}*/

		//WORKING WITH MOUSE INPUT
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePosition.x, (float)mousePosition.y);
		}
		window.clear();
		window.draw(player);
		window.display();
	}
	//RandomPointsDisplay();
	return 0;
}