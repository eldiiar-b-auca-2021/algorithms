#ifndef ROUTE_H
#define ROUTE_H

#include <optional>
#include "city.h"
struct Flight {

public:
    Flight(const City& origin, const City& destination, const std::optional<double> param)
            : origin(origin), destination(destination) {
        distance = param.has_value() ? param.value() : calculateDistance(origin, destination);
    }

    City getOrigin() const { return origin; }

    City getDestination() const { return destination; }

    double getDistance() const { return distance; }
private:
    City origin;
    City destination;
    double distance;
};
#endif //ROUTE_H