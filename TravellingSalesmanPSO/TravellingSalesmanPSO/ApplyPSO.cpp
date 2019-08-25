//we will approximate f(x,y) = x^2+y^2+1 using PSO
#include<iostream>
#include<vector>
#include<time.h>

using namespace std;
float calcDistance(vector<pair<int, int>> city_coordinates) {
	float current_distance = 0.0f;
	int numCities = city_coordinates.size();

	int first_x = city_coordinates[0].first;
	int first_y = city_coordinates[0].second;
	for (int i = 1;i < numCities;i++) {
		current_distance += sqrt((first_x - city_coordinates[i].first) * (first_x - city_coordinates[i].first) + (first_y - city_coordinates[i].second) * (first_y - city_coordinates[i].second));
		first_x = city_coordinates[i].first;
		first_y = city_coordinates[i].second;
	}

	return current_distance;
}
float fitness(float val, float target) {
	return target-val;
}
float random_between_two_int(float min, float max) {
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}
vector<pair<int, int>> ApplyPSO(vector<pair<int, int>> city_coordinates, float recorded_distance) {
	std::srand(time(0));
	int numParticles = 100;
	vector<pair<float, float> >present_co_ordinates;
	vector<float> present;

	vector<pair<float, float> >pBest_co_ordinates;
	pair<float, float> gBest_co_ordinate;

	vector<float> pBest;
	float gBest;
	vector<float> velocity;
	vector<float> velocity_x;
	vector<float> velocity_y;


	//float target = 5;
	//float target_error = 0.000001;

	float c1 = 0.5;
	float c2 = 0.9;



	for (int i = 0;i < numParticles;i++) {
		float x = random_between_two_int(10, 50);
		float y = random_between_two_int(10, 50);
		present_co_ordinates.push_back(pair<float, float>(x, y));

		float f = pow(present_co_ordinates[i].first, 2) + pow(present_co_ordinates[i].second, 2) + 1.0;
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
	while (count_Iter < numIter) {
		//initializing each particle with its personal fitness value
		for (int i = 0;i < numIter;i++) {

			if (fitness(pBest[i], target) > fitness(present[i], target)) {
				pBest[i] = present[i];
				pBest_co_ordinates[i] = pair<float, float>(present_co_ordinates[i].first, present_co_ordinates[i].second);
			}
		}
		//now we will start estimating the global minimum
		//start with the particle which has the best fitness value and assign it as the global best(gBest)
		gBest = INT_MAX;
		for (int i = 0;i < numParticles;i++) {
			if (fitness(gBest, target) > fitness(pBest[i], target)) {
				gBest = pBest[i];
				gBest_co_ordinate = pair<float, float>(pBest_co_ordinates[i].first, pBest_co_ordinates[i].second);
			}
		}

		if (abs(gBest - target) < target_error)
			break;

		for (int i = 0;i < numParticles;i++) {
			//approximating the solution
			float randVal1 = random_between_two_int(-1, 1);//[0,1]
			float randVal2 = random_between_two_int(-1, 1);
			//cout<<randVal1<<" "<<randVal2<<endl;
//			velocity[i] = velocity[i] + c1*randVal1*(pBest[i] - present[i]) + c2*randVal2*(gBest - present[i]);
//			present[i] = present[i] + velocity[i];

			//approximating the particle position
			velocity_x[i] = velocity_x[i] + c1 * randVal1 * (pBest_co_ordinates[i].first - present_co_ordinates[i].first) + c1 * randVal1 * (gBest_co_ordinate.first - present_co_ordinates[i].first);
			velocity_y[i] = velocity_y[i] + c1 * randVal1 * (pBest_co_ordinates[i].second - present_co_ordinates[i].second) + c1 * randVal1 * (gBest_co_ordinate.second - present_co_ordinates[i].second);

			present_co_ordinates[i].first = pBest_co_ordinates[i].first + velocity_x[i];
			present_co_ordinates[i].second = pBest_co_ordinates[i].second + velocity_y[i];

			present[i] = pow(present_co_ordinates[i].first, 2) + pow(present_co_ordinates[i].second, 2) + 1;
		}
		cout << gBest << endl;
		cout << gBest_co_ordinate.first << " " << gBest_co_ordinate.second << endl;
		count_Iter++;
	}

	for (int i = 0;i < numParticles;i++) {
		if (present_co_ordinates[i].first == gBest_co_ordinate.first) {
			cout << "----------" << endl;
			cout << "(" << present_co_ordinates[i].first << "," << present_co_ordinates[i].second << "), ";
			cout << "----------" << endl;
		}
		else
			cout << "(" << present_co_ordinates[i].first << "," << present_co_ordinates[i].second << "), ";
	}
	count_Iter++;



}