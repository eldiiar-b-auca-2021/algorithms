
#ifndef IO_H
#define IO_H

#include <fstream>
#include <sstream>
#include "city.h"
#include "flight.h"
std::vector<City> parseCitiesFromCSV(const std::string &filename) {

    //The file is expected to be in the following format:
    //City Name, Latitude, Longitude, ...
    std::vector<City> cities;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return cities;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        std::string latitude;
        std::string longitude;

        if (
                std::getline(iss, name, ',') && // Read until the first comma (the name)
                std::getline(iss, latitude, ',') && // Read until the second comma (the latitude)
                std::getline(iss, longitude, ',') // Read until the third comma (the longitude)
                )
            cities.emplace_back(name, std::stod(latitude), std::stod(longitude));
        else
            std::cerr << "Error parsing line: " << line << std::endl;
    }

    return cities;
}

void printRoutesInWKTFormat(const std::vector<Flight> &routes) {
    std::cout << "Printing the routes in WKT format." << std::endl;
    std::ofstream out("output.csv");
    out << "Name, WKT" << std::endl;
    for (auto& route : routes) {
        out << route.getOrigin().getName()<<"-"<<route.getDestination().getName() // Name of the route
            <<"," // Comma separator
            <<"\"" // Opening quote for the WKT
            << "LINESTRING(" // WKT for a line
            << route.getOrigin().getLongitude() << " " << route.getOrigin().getLatitude() << ", " //Origin (x, y)
            << route.getDestination().getLongitude() << " " << route.getDestination().getLatitude() << ")" //Destination (x, y)
            << "\"" //Closing quote for the WKT
            << std::endl;
    }
}

#endif //IO_H