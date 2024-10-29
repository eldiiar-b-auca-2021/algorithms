#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <limits>

#include "headers/city.h"
#include "headers/flight.h"
#include "headers/io.h"
#include "headers/algo.h"
#include "headers/util.h"

const int SHORTEST_ROUTE = 1;
const int ROUTE_MAP = 2;
const int EXIT = 3;

int request_option() {
    std::cout << "Now, tell me what do you want to accomplish?\n"
              << SHORTEST_ROUTE << ". Create a route between two cities.\n"
              << ROUTE_MAP << ". Create a route map between all the cities.\n"
              << EXIT << ". Exit." << std::endl;
    int option;
    std::cin >> option;
    return option;
}

City request_city(std::vector<City> &cities) {
    std::string cityName;
    while (true) {
        try {
            std::cin >> cityName;
            City city = findCityByName(cities, cityName);
            return city;
        } catch (const std::invalid_argument &e) {
            std::cout << "City not found. Please try again." << std::endl;
        }
    }
}

std::pair<City, City> requestOriginAndDestination(std::vector<City> &cities) {
    std::cout << "Please, enter the origin city." << std::endl;
    City origin = request_city(cities);
    std::cout << "Please, enter the destination city." << std::endl;
    City destination = request_city(cities);
    return std::make_pair(origin, destination);
}


std::vector<Flight> createRoutes(std::vector<City> &cities, double maxDistance) {
    int option = request_option();
    while (true) {
        switch (option) {
            case SHORTEST_ROUTE: {
                std::pair origin_and_destination = requestOriginAndDestination(cities);
                return findShortestRoute(cities, maxDistance, origin_and_destination.first,
                                         origin_and_destination.second);
            }
            case ROUTE_MAP:
                return findBestRouteMap(cities, maxDistance);
            case EXIT:
                throw exit_exception();
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}

double requestMaxDistance() {
    double maxDistance;

    while (true) {
        std::cout << "Please, enter the maximum positive distance between a plane can fly: ";
        if (std::cin >> maxDistance && maxDistance > 0) {
            return maxDistance;
        } else {
            // Check if cin is in a fail state (e.g. when a letter is entered)
            if (std::cin.fail()){
                // Clear the fail state and discard the invalid input.
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Invalid distance. Please try again" << std::endl;
        }
    }
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }


    City d = *new City("Naryn",41.1306,72.0806);
    City c = *new City("Orlovka", 42.4451,75.3518);
    std::cout << calculateDistance(c,d);
    std::vector<City> cities = parseCitiesFromCSV(argv[1]);
   // findShortestRoute(cities,400, c, d);
    if (cities.empty()) {
        std::cout << "No valid city data was found in the file." << std::endl;
        return EXIT_FAILURE;
    }
    try {
        double maxDistance = requestMaxDistance();
        auto routes = createRoutes(cities, maxDistance);
        printRoutesInWKTFormat(routes);
    } catch (const exit_exception &e) {
        std::cout << e.what() << std::endl;
    } catch (const impossible_route_exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
