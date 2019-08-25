#include<SFML/Graphics.hpp>
#include<iostream>

void RandomPointsDisplay() {
	sf::RenderWindow window(sf::VideoMode(512, 512), "Random Points Generator", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::CircleShape dot(3.0f);
	dot.setFillColor(sf::Color::Green);
	dot.setPosition(100.0f, 40.0f);
	int NumPoints = 500;
	int x, y;
	int f = 0;
	while (window.isOpen()) {
		window.clear();
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "Window height: " << evnt.size.width << " Window Height: " << evnt.size.height << std::endl;
				break;
			}
		}
		window.draw(dot);
		x = std::rand() % (512 + 1);
		y = std::rand() % (512 + 1);
		dot.setPosition(x, y);
		/*if (f == 0) {  f = 1; }
		else { dot.move(+x, +y);f = 0; }*/
		
		
		
		window.display();
	}
}