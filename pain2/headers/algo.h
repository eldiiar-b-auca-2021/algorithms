#ifndef ALGO_H
#define ALGO_H
#include "city.h"
#include "flight.h"
#include <vector>
#include <iostream>
#include "bits/stdc++.h"
using namespace std;
int nearestNode(vector<double> &shortDis, vector<bool> &visited)
{
    double min = INFINITY;
    int index = 0;
    for (int i = 1; i < shortDis.size(); i++)
    {
        if (!visited[i] && min > shortDis[i])
        {
            index = i;
            min = shortDis[i];
        }
    }
    return index;
}
void dijkstra(vector<vector<double>> &v, vector<double> &shortDis, vector<bool> &visited, map<int, int> &chain, int src)
{
    shortDis[src] = 1;
    for (int i = 1; i < v.size(); i++)
    {
        int nearestNodeIndex = nearestNode(shortDis, visited);
        visited[nearestNodeIndex] = true;
        for (int j = 1; j < v.size(); j++)
        {
            if (!visited[j] && v[nearestNodeIndex][j] != INFINITY
            && v[nearestNodeIndex][j] + shortDis[nearestNodeIndex] < shortDis[j])
            {
                shortDis[j] = v[nearestNodeIndex][j] + shortDis[nearestNodeIndex];
                chain[j] = nearestNodeIndex;
            }
        }

    }
}
std::vector<Flight> create(const std::vector<City> &c, double maxDistance, const City &origin,
                           const City &destination){
    auto fullRoute = std::vector<Flight>();
    map<pair<string,string>, double> distanceBetweenCities;
    map<string, pair<double, double>> mOfC;
    int uniqueIdent = 1;
    map<string, int> convertCityToNumber;
    map<int, string> convertIndexToCity;
    for (auto it : c)
    {
        convertCityToNumber[it.getName()] = uniqueIdent;
        convertIndexToCity[uniqueIdent] = it.getName();
        mOfC[it.getName()] = make_pair(it.getLatitude(), it.getLongitude());
        uniqueIdent++;
    }
    for (auto it : c){
        for (auto it2 : c)
        {
            double dis = calculateDistance(it, it2);
            if (it.getName() != it2.getName() && dis <= maxDistance)
            {
                distanceBetweenCities[make_pair(it.getName(), it2.getName())] = dis;
            }
        }
    }
    vector<vector<double>> v(33, vector<double>(33, INFINITY));
    for (auto it : distanceBetweenCities){
        v[convertCityToNumber[it.first.first]][convertCityToNumber[it.first.second]] = it.second;
    }

    vector<double> shortDis(v.size(), INFINITY);
    vector<bool> visited(v.size(), false);
    map<int, int> chain;
    dijkstra(v, shortDis, visited, chain, convertCityToNumber["Bishkek"]);
    int indexOfCityDes = convertCityToNumber[destination.getName()];
    vector<City> vec;
    vec.push_back(destination);

    bool isFirst = true;
    while(true)
    {
        int it;
        if (isFirst) {
            it = chain[indexOfCityDes];
            isFirst = false;
        }else {
            it = chain[it];
        }
        if (convertIndexToCity[it] == origin.getName()){
            auto it1 = convertIndexToCity[it];
            vec.push_back(*new City(it1,mOfC[it1].first,mOfC[it1].second));
//            fullRoute.push_back(
//                    *new Flight(vec[0], vec[1],
//                                distanceBetweenCities[make_pair(vec[0].getName(), vec[1].getName())]));
            break;
        }
        if (it == 0) {
            vec.clear();
            break;
        }
        cout << convertIndexToCity[it] << "\n";
        auto it1 = convertIndexToCity[it];
        vec.push_back(*new City(it1,mOfC[it1].first,mOfC[it1].second));
    }
    reverse(vec.begin(), vec.end());
    while(vec.size() >= 2)
    {
        fullRoute.push_back(
                    *new Flight(vec[0], vec[1],
                                distanceBetweenCities[make_pair(vec[0].getName(), vec[1].getName())]));
        vec.erase(vec.begin());
    }
    return fullRoute;

}
std::vector<Flight> findShortestRoute(const std::vector<City> &c, double maxDistance, const City &origin,
                                      const City &destination) {
    std::cout << "Creating a route between two cities." << std::endl;
    return create(c,maxDistance,origin,destination);
}

vector<Flight> init(const vector<City> &cities, double maxDistance){
    vector<Flight> list;
    for(int i = 0; i < cities.size(); i++){
        for(int j = 0; j < cities.size(); j++){
            if(i != j){
                double dist = calculateDistance(cities[i], cities[j]);
                if(dist <= maxDistance){
                    list.emplace_back(cities[i], cities[j], dist);
                }
            }
        }
    }
    return list;
}

int findRoot(map<int, int> &parent, int &node){
    if(parent[node] == node)
        return node;
    return findRoot(parent, parent[node]);
}

struct EdgeSort{
    bool operator()(const Flight &a, const Flight &b) const{
        return a.getDistance() < b.getDistance();
    }
};
vector<Flight> findBestRouteMap(const vector<City> &cities, double maxDistance) {
    cout << "Creating a route map between all the cities." << endl;

    vector<Flight> edges = init(cities, maxDistance);
    sort(edges.begin(), edges.end(), EdgeSort());

    map<int, int> parent;
    map<City, int> convert;
    for(int i = 0; i < cities.size(); i++) {
        parent[i] = i;
        convert[cities[i]] = i;
    }

    vector<Flight> fullMap;
    int count = 0;

        for (auto it = edges.begin(); it != edges.end(); it++) {
        int u = convert[it->getOrigin()];
        int v = convert[it->getDestination()];

        if (findRoot(parent, u) != findRoot(parent, v)) {
            fullMap.emplace_back(cities[u], cities[v], it->getDistance());

            int rootA = findRoot(parent, u);
            int rootB = findRoot(parent, v);
            parent[rootA] = rootB;

            count++;
            if (count == cities.size() - 1) break;
        }
    }
    return fullMap;
}
#endif //ALGO_H