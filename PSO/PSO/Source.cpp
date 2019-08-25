#include<SFML/Graphics.hpp>
#include<math.h>
#include<iostream>
#include<vector>
//std::vector<std::pair<int, int>> PSO(std::vector<std::pair<int, int>>, float);
double random_between_two_int(double min, double max) {
	return (min + 1) + (((double)rand()) / (double)RAND_MAX) * (max - (min + 1));
}
float fitness(float val, float target) {
	return abs(val - target);
}
int main() {
	std::srand(time(0));

	sf::RenderWindow window(sf::VideoMode(512, 512), "Function approximation using swarm", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	const int numParticles = 10000;

	std::vector<sf::CircleShape> particles;

	std::vector<std::pair<double, double> >present_co_ordinates;//these are the coordinates of the particels
	std::vector<double> present;//this is the current value

	std::vector<std::pair<double, double> >pBest_co_ordinates;
	std::pair<double, double> gBest_co_ordinate;

	std::vector<double> pBest;
	double gBest;
	std::vector<double> velocity;
	std::vector<double> velocity_x;
	std::vector<double> velocity_y;


	double target = 1;
	double target_error = 0.000001;

	double c1 = 0.5;
	double c2 = 0.9;



	//setting up the particles on the screen

	for (int i = 0;i < numParticles;i++) {
		double x = random_between_two_int(10, 500);
		double y = random_between_two_int(10, 500);

		sf::CircleShape dot(3.0f);
		dot.setFillColor(sf::Color::Green);
		dot.setOrigin(1.5f, 1.5f);
	
		dot.setPosition(x, y);

		particles.push_back(dot);

		present_co_ordinates.push_back(std::pair<double, double>(x, y));

		double f = pow(present_co_ordinates[i].first, 2) + pow(present_co_ordinates[i].second, 2) + 1.0;
		present.push_back(f);
		pBest.push_back(f);//initial selection is the best selection
	}

	pBest_co_ordinates = present_co_ordinates;

	int numIter = 1000;
	int count_Iter = 0;

	for (int i = 0;i < numParticles;i++) {
		pBest.push_back(FLT_MAX);
		velocity.push_back(0.0);
		velocity_x.push_back(0.0);
		velocity_y.push_back(0.0);
	}
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

		for (int i = 0;i < numParticles;i++) {
			window.draw(particles[i]);
		}
		window.display();
		//---------------
		while (count_Iter < numIter) {
			window.clear();
			//initializing each particle with its personal fitness value
			for (int i = 0;i < numParticles;i++) {

				if (fitness(pBest[i], target) > fitness(present[i], target)) {
					pBest[i] = present[i];
					pBest_co_ordinates[i] = std::pair<double, double>(present_co_ordinates[i].first, present_co_ordinates[i].second);
				}
			}
			//now we will start estimating the global minimum
			//start with the particle which has the best fitness value and assign it as the global best(gBest)
			gBest = INT_MAX;
			for (int i = 0;i < numParticles;i++) {
				if (fitness(gBest, target) > fitness(pBest[i], target)) {
					gBest = pBest[i];
					gBest_co_ordinate = std::make_pair(pBest_co_ordinates[i].first, pBest_co_ordinates[i].second);
				}
			}

			if (abs(gBest - target) < target_error)
				break;

			for (int i = 0;i < numParticles;i++) {
				//approximating the solution
				window.clear();
				float randVal1 = random_between_two_int(-1, 1);//[0,1]
				float randVal2 = random_between_two_int(-1, 1);

				velocity_x[i] = velocity_x[i] + c1 * randVal1 * (pBest_co_ordinates[i].first - present_co_ordinates[i].first) + c1 * randVal1 * (gBest_co_ordinate.first - present_co_ordinates[i].first);
				velocity_y[i] = velocity_y[i] + c1 * randVal1 * (pBest_co_ordinates[i].second - present_co_ordinates[i].second) + c1 * randVal1 * (gBest_co_ordinate.second - present_co_ordinates[i].second);

				present_co_ordinates[i].first = pBest_co_ordinates[i].first + velocity_x[i];
				present_co_ordinates[i].second = pBest_co_ordinates[i].second + velocity_y[i];

				//particles[i].setPosition(present_co_ordinates[i].first + 256, present_co_ordinates[i].second + 256);
				particles[i].move(present_co_ordinates[i].first + 256-particles[i].getPosition().x, present_co_ordinates[i].second + 256- particles[i].getPosition().y);
				present[i] = pow(present_co_ordinates[i].first, 2) + pow(present_co_ordinates[i].second, 2) + 1;


			}
			for (int i = 0;i < numParticles;i++) {
				sf::Vector2f position = particles[i].getPosition();
				//std::cout << "(" << position.x << ", " << position.y << "), ";
				window.draw(particles[i]);
			}
			std::cout << std::endl;
			window.display();
			std::cout << gBest << std::endl;
			std::cout << gBest_co_ordinate.first << " " << gBest_co_ordinate.second << std::endl;
			count_Iter++;
			
			sf::sleep(sf::milliseconds(200));
		};
	//--------------
		
	}
	return 0;
}