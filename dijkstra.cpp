#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class Graph
{
public:
    unordered_map<string, vector<pair<string, int>>> adjList;

    void addStation(const string &station)
    {
        adjList[station]; // Create a new entry for the station
    }

    void addConnection(const string &station1, const string &station2, int fare)
    {
        adjList[station1].push_back(make_pair(station2, fare));
        adjList[station2].push_back(make_pair(station1, fare)); // For undirected graph
    }

    void dijkstra(const string &start, const string &destination)
    {
        unordered_map<string, int> minFare;
        unordered_map<string, string> parent;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        for (const auto &pair : adjList)
        {
            minFare[pair.first] = numeric_limits<int>::max(); // Initialize to infinity
        }

        minFare[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty())
        {
            auto [currentFare, currentStation] = pq.top();
            pq.pop();

            if (currentStation == destination)
            {
                break; // Shortest path found
            }

            for (const auto &[neighbor, fare] : adjList[currentStation])
            {
                if (currentFare + fare < minFare[neighbor])
                {
                    minFare[neighbor] = currentFare + fare;
                    parent[neighbor] = currentStation;
                    pq.push(make_pair(minFare[neighbor], neighbor));
                }
            }
        }

        // Output the minimum fare and path
        if (minFare[destination] == numeric_limits<int>::max())
        {
            cout << "No path found from " << start << " to " << destination << "." << endl;
        }
        else
        {
            cout << "Minimum fare from " << start << " to " << destination << " is: " << minFare[destination] << endl;
            cout << "Path: ";

            // Backtrack to find the path
            vector<string> path;
            string station = destination;
            while (station != start)
            {
                path.push_back(station);
                station = parent[station];
            }
            path.push_back(start);
            reverse(path.begin(), path.end()); // Reverse the path for correct order

            for (const string &s : path)
            {
                cout << s << (s != destination ? " -> " : "");
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph journeyPlanner;

    // Add stations and connections (example data)
    journeyPlanner.addStation("A");
    journeyPlanner.addStation("B");
    journeyPlanner.addStation("C");
    journeyPlanner.addStation("D");
    journeyPlanner.addConnection("A", "B", 5);  // Connection A-B with fare/distance 5
    journeyPlanner.addConnection("A", "C", 10); // Connection A-C with fare/distance 10
    journeyPlanner.addConnection("B", "C", 3);  // Connection B-C with fare/distance 3
    journeyPlanner.addConnection("B", "D", 1);  // Connection B-D with fare/distance 1
    journeyPlanner.addConnection("C", "D", 2);  // Connection C-D with fare/distance 2

    // User input for starting and destination stations
    string start, destination;
    cout << "Enter starting station: ";
    cin >> start;
    cout << "Enter destination station: ";
    cin >> destination;

    // Perform Dijkstra's algorithm to find the shortest path
    journeyPlanner.dijkstra(start, destination);

    return 0;
}
