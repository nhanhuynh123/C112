#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// struct data {
//     string vertex;
//     int weight;
//     vector<char> path;

//     // Constructor
//     data(const string& ch, int num, const vector<char>& cl)
//         : vertex(ch), weight(num), path(cl) {}
// };

struct cus_data {
    std::string vertex;
    int weight;
    std::vector<string> path;
     
    // Constructor
    cus_data( string ch, int num, vector<string> cl)
        : vertex(ch), weight(num), path(cl) {}
};

// Hàm so sánh để sử dụng trong priority_queue
struct compare {
    bool operator() (const cus_data& a,const cus_data&b) {
        return a.weight > b.weight;
    }
};

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
// void printMap(const map<string, map<string, int>>& myMap) {
//     // Duyệt qua từng phần tử của map ngoài cùng
//     for (const auto& outerPair : myMap) {
//         const string& outerKey = outerPair.first;          // Khóa của map ngoài
//         const map<string, int>& innerMap = outerPair.second;  // Giá trị của map ngoài (là một map)
        
//         // In khóa của map ngoài
//         cout << outerKey << " : {" << endl;

//         // Duyệt qua từng phần tử của map bên trong
//         for (const auto& innerPair : innerMap) {
//             const string& innerKey = innerPair.first;    // Khóa của map trong
//             int value = innerPair.second;                // Giá trị của map trong
            
//             // In cặp khóa-giá trị của map trong
//             cout << "    " << innerKey << " : " << value << endl;
//         }
        
//         cout << "}" << endl;
//     }
// }

int main() {
    // Adjacncy list for storing edge
    map<string, map<string, int>> ad_list;
    int n;
    string s_v;
    cin >> n >> s_v;
    // Input section
    while(n-- ) {
        string s1, s2;
        int w;
        cin >> s1 >> s2 >> w;
        ad_list[s1][s2] = w;
    }
    // printMap(adjacency_list);
    // Get available vertice
    priority_queue<cus_data, vector<cus_data>, compare> open;
    vector<string> result;

    open.push(cus_data(s_v, 0, {}));
    while (true) {
        cus_data top = open.top();
        open.pop();
        string cur_v = top.vertex;
        int cost = top.weight;
        vector<string> path = top.path;
        cout << "Cur_v: " << cur_v << endl;
        if (cur_v == s_v && path.size() == ad_list.size()) {
            path.push_back(s_v);
            result = path;
            break;
        }
        if (path.size() + 1 == ad_list.size()) {
            path.push_back(cur_v);
            open.push(cus_data(s_v, cost + ad_list[cur_v][s_v], path));
        } else {
            for (auto& inner : ad_list[cur_v]) {
                const string& next_v = inner.first;
                if (find(path.begin(), path.end(), next_v) == path.end()) {
                    vector<string> new_path = path;
                    new_path.push_back(cur_v);
                    cout << next_v<< " Push " << cost + ad_list[cur_v][next_v] << " path:";
                    for (auto i : path) cout << i << " ";
                    cout << endl;
                    open.push(cus_data(next_v, cost + ad_list[cur_v][next_v], new_path));
                }
            }
        }
    }
    for (auto i:result) {
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