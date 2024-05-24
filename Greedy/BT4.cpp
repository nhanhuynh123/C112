#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;


int main() {
    map<string, int> index;
    int v, e;
    cin >> v >> e;
    vector<vector<int>> graph(v, vector<int>(v, 0));
    while(v--) {
        string temp;
        cin >> temp;
        index[temp] = index.size();
    }
    while(e--) {
        string v1, v2;
        cin >> v1 >> v2;
        int i = index[v1];
        int j = index[v2];
        graph[i][j] = 1;
        graph[j][i] = 1;
    }
    for (int i = 0; i < graph.size(); i++) {
        int count = 0;
        for (int j = 0; j < graph.size(); j++) {
            if (graph[i][j] == 1) count++;
        }
        cout << count << " ";
    }
    return 0;
}