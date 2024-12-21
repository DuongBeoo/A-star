#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    int parentX, parentY;

    Node(int x, int y, int g, int h, int parentX = -1, int parentY = -1)
        : x(x), y(y), g(g), h(h), parentX(parentX), parentY(parentY) {
        f = g + h; 
    }
    bool operator>(const Node& other) const {
        return f > other.f; 
    }
};
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
vector<pair<int, int>> a_star(int startX, int startY, int endX, int endY, int maxX, int maxY) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    map<pair<int, int>, bool> closedSet;
    map<pair<int, int>, pair<int, int>> cameFrom;
    openSet.push(Node(startX, startY, 0, heuristic(startX, startY, endX, endY)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        if (current.x == endX && current.y == endY) {
            vector<pair<int, int>> path;
            pair<int, int> currentPos = {current.x, current.y};
            while (cameFrom.find(currentPos) != cameFrom.end()) {
                path.push_back(currentPos);
                currentPos = cameFrom[currentPos];
            }
            path.push_back({startX, startY});
            reverse(path.begin(), path.end()); 
            return path;
        }
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;
            if (newX < 0 || newY < 0 || newX >= maxX || newY >= maxY) {
                continue;
            }
            if (!closedSet[{newX, newY}]) {
                int newG = current.g + 1;
                int newH = heuristic(newX, newY, endX, endY);
                openSet.push(Node(newX, newY, newG, newH, current.x, current.y));
                cameFrom[{newX, newY}] = {current.x, current.y};
            }
        }
        closedSet[{current.x, current.y}] = true;
    }

    return {};
}

int main() {
    int startX = 0, startY = 0;
    int endX = 5, endY = 5;
    int maxX = 6, maxY = 6;
    
    vector<pair<int, int>> path = a_star(startX, startY, endX, endY, maxX, maxY);
    if (!path.empty()) {
        cout << "Duong di tu (" << startX << ", " << startY << ") den (" << endX << ", " << endY << "):\n";
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "Khong tim thay duong di!" << endl;
    }

    return 0;
}
