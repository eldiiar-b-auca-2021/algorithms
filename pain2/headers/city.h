
#ifndef CITY_H
#define CITY_H
#include "bits/stdc++.h"

struct City {
public:
    City(std::string name, double latitude, double longitude)
            : name(std::move(name)), latitude(latitude), longitude(longitude) {}

    std::string getName() const { return name; }

    double getLatitude() const { return latitude; }

    double getLongitude() const { return longitude; }
    bool operator<(const City &other) const{
        return latitude + longitude < other.longitude + other.latitude;
    }
private:
    std::string name;
    double latitude;
    double longitude;
};
double deg2rad(double deg) {
    return (deg * M_PI / 180);
}

double calculateDistance(const City &origin, const City &destination) {
    double dLat = (origin.getLatitude() - destination.getLatitude()) * M_PI / 180.0;
    double dLon = (origin.getLongitude() - destination.getLongitude()) * M_PI / 180.0;

    // convert to radians
    double latOrigin = origin.getLatitude() * M_PI / 180.0;
    double latDestination = destination.getLongitude() * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(latOrigin) * cos(latDestination);
    double radius = 6371;
    double c = 2 * asin(sqrt(a));

    return radius * c;
    //TODO: Implement this function
    return 0;
}

#endif //CITY_H