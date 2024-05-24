// #include <iostream>
// #include <map>
// #include <string>
// #include <vector>
// #include <set>
// #include <algorithm>
// #include <queue>
// using namespace std;
// struct c_data {
//     string vertex;
//     int weight;
//     vector<string> path;

//     c_data( string ch, int num, vector<string> cl)
//         : vertex(ch), weight(num), path(cl) {}
// };
// struct compare {
//     bool operator() (const c_data& a,const c_data&b) {
//         return a.weight > b.weight;
//     }
// };
// struct handle {
//     void dijkstra(map<string, map<string, int>> ad_list, string v1, string v2, map<string, int> index, vector<string> vertice) {
//         priority_queue<c_data, vector<c_data>, compare> open;
//         open.push(c_data(v1, 0, {}));
//         int flag = 0;
//         set<string> count;
//         while (open.size()) {
//             c_data top = open.top();
//             open.pop();
//             string cur_v = top.vertex;
//             int cost = top.weight;
//             vector<string> path = top.path;
//             // Count open-vertice
//             count.insert(cur_v);
            
//             if (cur_v == v2) {
//                 flag = 1;
//                 path.push_back(cur_v);
//                 for(auto i : path) cout << i << " ";
//                 cout << endl;
//                 cout << count.size() << " " << cost << endl;
//                 break;
//             } else {
//                 for (auto i:ad_list[cur_v]) {
//                     vector<string> temp_path = path;
//                     temp_path.push_back(cur_v);
//                     open.push(c_data(i.first, cost + ad_list[cur_v][i.first], temp_path));
//                 }
//             }
//         }
//         if (flag == 0) cout << "-unreachable-\n1 0\n";
//     }
// };
// int main() {
//     handle h;
//     int v, ac;
//     cin >> v >> ac;
//     int temp = v;
//     map<string, int> index;
//     map<string, map<string, int>> ad_list;
//     vector<string> vertice;
//     while(temp--) {
//         string vertex;
//         cin >> vertex;
//         index[vertex] = index.size();
//         vertice.push_back(vertex);
//     }
//     for (int i = 0; i < v; i++)
//         for (int j = 0; j < v; j++)
//         {
//             int w;
//             cin >> w;
//             if(w != 0) 
//                 ad_list[vertice[i]][vertice[j]] = w;
//         }
//     // for (auto Outterpair : ad_list) {
//     //     auto innerPair = Outterpair.second;
//     //     cout << Outterpair.first << "{\n";
//     //     for (auto i:innerPair) {
//     //         cout << "key: " << i.first << " value: " << i.second << endl;
//     //     }
//     //     cout << "}\n";
//     // }
//     // for (int i = 0; i < v; i++)
//     // { 
//     //     for (int j = 0; j < v; j++)
//     //     {
//     //         cout << graph[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }
//     while(ac--) {
//         string v1, v2;
//         cin >> v1 >> v2;

//         h.dijkstra(ad_list, v1, v2, index, vertice);
//     }
//     return 0;
// }


#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

// Cấu trúc để lưu thông tin đỉnh và trọng số cho thuật toán Dijkstra
struct Edge {
    int vertex;
    int weight;
};

struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        if (a.weight != b.weight) 
            return a.weight > b.weight;
        else 
            return a.vertex < b.vertex;
    }
};

struct handle {
    pair<vector<string>, pair<int, int>> dijkstra(string start, string end, vector<vector<int>> graph, int n, unordered_map<string, int> vertex_index, vector<string> vertice) {
        vector<int> distance(n, numeric_limits<int>::max());
        vector<int> parent(n, -1);
        vector<int> visited(n, 0);
        priority_queue<Edge, vector<Edge>, Compare> open;
        int end_ind = vertex_index[end];
        int start_ind = vertex_index[start];
        open.push({start_ind, 0});

        while (open.size()) {

            int cur_vertex = open.top().vertex;
            int weight = open.top().weight;
            open.pop();
            visited[cur_vertex] = 1;
            if (cur_vertex == end_ind) {
                break;
            }

            for (int i = 0; i < n; i++) {
                if (graph[cur_vertex][i] != 0 && visited[i] == 0 && distance[i] > weight + graph[cur_vertex][i]) {
                    distance[i] = weight + graph[cur_vertex][i];
                    parent[i] = cur_vertex;
                    open.push({i, distance[i]});
                }
            }
        }
        int num_visited = 0;
        for (int i : visited) {
            if (i == 1) num_visited++;
        }
        if (distance[end_ind] == numeric_limits<int>::max()) 
            return {{"-unreachable-"}, {num_visited, 0}};

        vector<string> path;
        for (int v = end_ind; v != -1; v = parent[v]) {
            path.push_back(vertice[v]);
        }
        reverse(path.begin(), path.end());

        return {path, {num_visited, distance[end_ind]}};
    }

};

int main() {
    handle h;
    int v, n;
    cin >> v >> n;
    
    vector<string> vertices(v);
    unordered_map<string, int> vertex_index;
    
    for (int i = 0; i < v; ++i) {
        cin >> vertices[i];
        vertex_index[vertices[i]] = i;
    }

    vector<vector<int>> adjacency_matrix(v, vector<int>(v));

    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            cin >> adjacency_matrix[i][j];
        }
    }

    vector<pair<string, string>> queries(n);

    for (int i = 0; i < n; ++i) {
        cin >> queries[i].first >> queries[i].second;
    }

    for (const auto& query : queries) {
        auto result = h.dijkstra(query.first, query.second, adjacency_matrix, v, vertex_index, vertices);
        const auto& path = result.first;
        int distance = result.second.second;
        int visited = result.second.first;

        if (path[0] == "-unreachable-") {
            cout << "-unreachable-" << endl;
            cout << visited << " " << 0 << endl;
        } else {
            for (const auto& vertex : path) {
                cout << vertex << " ";
            }
            cout << endl;
            cout << visited << " " << distance << endl;
        }
    }

    return 0;
}
