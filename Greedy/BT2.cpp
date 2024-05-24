#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> get_vertice(map<string, map<string, int>> adl, string v) {
    vector<string> vertice;
    for (auto& outerPair : adl) {
        const string& outerKey = outerPair.first;
        vertice.push_back(outerKey);
    }
    auto it = find(vertice.begin(), vertice.end(), v);
    vertice.erase(it);
    return vertice;
}

// Hàm in nội dung của map
void printMap(const map<string, map<string, int>>& myMap) {
    // Duyệt qua từng phần tử của map ngoài cùng
    for (const auto& outerPair : myMap) {
        const string& outerKey = outerPair.first;          // Khóa của map ngoài
        const map<string, int>& innerMap = outerPair.second;  // Giá trị của map ngoài (là một map)
        
        // In khóa của map ngoài
        cout << outerKey << " : {" << endl;

        // Duyệt qua từng phần tử của map bên trong
        for (const auto& innerPair : innerMap) {
            const string& innerKey = innerPair.first;    // Khóa của map trong
            int value = innerPair.second;                // Giá trị của map trong
            
            // In cặp khóa-giá trị của map trong
            cout << "    " << innerKey << " : " << value << endl;
        }
        
        cout << "}" << endl;
    }
}
int main() {
    // Adjacncy list for storing edge
    map<string, map<string, int>> adjacency_list;

    int n;
    string v;
    cin >> n >> v;
    // Input section
    while(n-- ) {
        string s1, s2;
        int w;
        cin >> s1 >> s2 >> w;
        adjacency_list[s1][s2] = w;
    }
    printMap(adjacency_list);
    // Get available vertice
    vector<string> vertice = get_vertice(adjacency_list, v);
    vector<string> path;
    path.push_back(v);
    // Greedy section
    string current_vertex = v;
    while(vertice.size()) {
        int best_choice = 0;
        int min_w = adjacency_list[current_vertex][vertice[best_choice]];

        // Getting best_choice loop
        for (int i = 1; i < vertice.size(); i++) 
        {
            if (min_w > adjacency_list[current_vertex][vertice[i]]) 
            {
                best_choice = i;
                min_w = adjacency_list[current_vertex][vertice[i]];
            }
        }
        path.push_back(vertice[best_choice]);
        current_vertex = vertice[best_choice];
        vertice.erase(vertice.begin() + best_choice);
        // cout << "Path: ";
        // for (auto i : path) {
        //     cout << i << " ";
        // }
        // cout << endl;
    }
    // for (auto i : vertice) {
    //     cout << i << " ";
    // }
    // cout << endl;
    path.push_back(v);
    for (auto i : path) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

/*
cur = v
while(vertice.size()) {

best_choice = vertice[0]
min_w = adja[cur][bestchoice]

for (i: 1 -> vertice.size() {
    if (vertice[i] == cur){}
    else {
        if (min_w > adja[cur][vertice[[i]]) {
            best_choice = vertice[i];
            min_w = adja[cur][vertice[i]];
        }
    }
})
path.push_back(best_choice);
cur = best_choice;
vertice.erase(best_choice);
}
*/