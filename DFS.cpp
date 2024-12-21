#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;
bool dfs(int startX, int startY, int endX, int endY, int maxX, int maxY) {
    stack<pair<int, int>> s;
    map<pair<int, int>, bool> visited;
    s.push({startX, startY});
    visited[{startX, startY}] = true;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!s.empty()) {
        pair<int, int> current = s.top(); 
        s.pop();
        int x = current.first;
        int y = current.second;
        if (x == endX && y == endY) {
            cout << "Da tim thay duong di den (" << endX << ", " << endY << ")\n";
            return true;
        }
        for (auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Kiểm tra nếu tọa độ mới hợp lệ và chưa thăm
            if (newX >= 0 && newY >= 0 && newX < maxX && newY < maxY && !visited[{newX, newY}]) {
                visited[{newX, newY}] = true;
                s.push({newX, newY});
            }
        }
    }

    cout << "Khong tim thay duong di den ("<< endX << ", " << endY <<")\n";
    return false;
}

int main() {
    int startX = 0, startY = 0; 
    int endX = 4, endY =4;     
    int maxX = 5, maxY = 5;      
    dfs(startX, startY, endX, endY, maxX, maxY);

    return 0;
}
