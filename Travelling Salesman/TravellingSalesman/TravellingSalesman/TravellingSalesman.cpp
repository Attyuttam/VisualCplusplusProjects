
#include<SFML/Graphics.hpp>
#include<math.h>
#include<iostream>

std::vector<std::pair<int, int>> ApplyHillClimbing(std::vector<std::pair<int, int>>,float);
float calcDistance(std::vector<std::pair<int, int>>);
int main() {
	std::srand(time(0));

	sf::RenderWindow window(sf::VideoMode(512, 512), "The Travelling Salesman",sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	const int numCities = 20;

	std::vector<sf::CircleShape> cities;
	
	std::vector<std::pair<int, int>> city_coordinates;

	float current_distance = 0.0f;

	int flag = 0;

	for (int i = 0;i < numCities;i++) {
		sf::CircleShape dot(5.0f);
		dot.setFillColor(sf::Color::Green);
		dot.setOrigin(2.5f,2.5f);
		int init_x = 10 + std::rand() % (500 - 10 + 1);
		int init_y = 10 + std::rand() % (500 - 10 + 1);
		dot.setPosition(init_x, init_y);
		
		cities.push_back(dot);
		city_coordinates.push_back(std::pair<int, int>(init_x, init_y));//this is how i check the distance

	}
	current_distance = calcDistance(city_coordinates);
	
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
	
		for (int i = 0;i < numCities;i++) {
			window.draw(cities[i]);
		}
		int start_x = city_coordinates[0].first;
		int start_y = city_coordinates[0].second;
		sf::VertexArray lines(sf::LineStrip, numCities);
		for (int i = 0;i < numCities;i++) {
			lines[i].position = sf::Vector2f(city_coordinates[i].first, city_coordinates[i].second);
		}
		window.draw(lines);
		window.display();
		std::vector<std::pair<int, int>> temp_city_coordinates;
		if (flag == 0) {
			std::cout <<std::endl<< "HIT" << std::endl;
			temp_city_coordinates = ApplyHillClimbing(city_coordinates, current_distance);

			/*for (int i = 0;i < numCities;i++) {
				std::cout <<"("<<temp_city_coordinates[i].first <<","<<temp_city_coordinates[i].second<<") ";
			}
			std::cout << std::endl;
			for (int i = 0;i < numCities;i++) {
				std::cout << "(" << city_coordinates[i].first << "," << city_coordinates[i].second << ") ";
			}*/
			
			if (city_coordinates != temp_city_coordinates) { flag = 0; city_coordinates = temp_city_coordinates; current_distance = calcDistance(city_coordinates); }
			else {
				flag = 1;
				std::cout << std::endl;
				for (int i = 0;i < numCities;i++) {
					std::cout << "(" << city_coordinates[i].first << "," << city_coordinates[i].second << ") ";
				}
				std::cout << std::endl;
				std::cout << "Minimum recorded distance: " << current_distance << std::endl;
			}
		}
	}
	return 0;
}