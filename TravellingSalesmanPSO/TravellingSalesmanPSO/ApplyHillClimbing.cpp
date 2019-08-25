#include<iostream>
#include<vector>
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
vector<pair<int, int>> ApplyHillClimbing(vector<pair<int, int>> city_coordinates, float recorded_distance) {
	vector<pair<int, int>> temp;
	vector<pair<int, int>> best_city_coordinates = city_coordinates;
	float current_distance = 20000.0f;//a very high value, that's it
	int numCities = city_coordinates.size();
	temp = city_coordinates;
	cout << "Received distance: " << recorded_distance << endl;
	for (int i = 0;i < numCities - 1;i++) {
		for (int j = i + 1;j < numCities;j++) {
			pair<int, int> temp_pair = temp[i];
			temp[i] = temp[j];
			temp[j] = temp_pair;
			current_distance = calcDistance(temp);
			cout << "currently calculated: " << current_distance << endl;
			if (current_distance < recorded_distance) {
				cout << "Changed distance: " << current_distance;
				recorded_distance = current_distance;
				best_city_coordinates = temp;
			}
			temp = city_coordinates;
		}
	}
	return best_city_coordinates;
}