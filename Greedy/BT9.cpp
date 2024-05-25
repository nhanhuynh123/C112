#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;
struct Edge {
    int vertex;
    int wei_heu;

    // bool operator<(const Edge& other) {
    //     return wei_heu < other.wei_heu;
    // }
    // bool operator== (const Edge& other) {
    //     return wei_heu == other.wei_heu && vertex == other.vertex;
    // }
};
struct compare {
    bool operator()(const Edge& a, const Edge& b) {
        if (a.wei_heu != b.wei_heu) return a.wei_heu < b.wei_heu;
        else return a.vertex < b.vertex;
    }
};
struct Priority_queue {
    vector<Edge> pq;
    compare comp;

    void push(const Edge& edge) {
        pq.insert(upper_bound(pq.begin(), pq.end(), edge, comp), edge);
    };
    Edge top() {
        if (pq.size()) return pq[0];
        else throw runtime_error("PriorityQueue is empty");
    };
    void pop(int i = 0) {
        if (pq.size()) pq.erase(pq.begin() + i);
    };
    int size() {
        return pq.size();
    };
    std::vector<Edge>::iterator find(int vertex) {
        return std::find_if(pq.begin(), pq.end(), [vertex](const Edge& e) {
            return e.vertex == vertex;
        });
    }
};
struct handle {
    pair<vector<string>, pair<int, int>> A_star(int start, int end, int v, vector<string> vertice,vector<vector<int>> graph, vector<int> h_n, map<string, int> index) {
        Priority_queue open;
        vector<int> close(v, 0);
        vector<int> distance(v, numeric_limits<int>::max());
        vector<int> parent(v, -1);

        distance[start] = 0;
        open.push({start, 0});
        while (open.size()) {
            Edge top = open.top();
            open.pop();
            close[top.vertex] = 1;
            if (top.vertex == end) {
                break;
            } else {
                for (int i = 0; i < v; i++) {
                    // if (vertice[top.vertex] == "S") {
                    //     cout << "Distance S"<< distance[top.vertex] << endl;
                    //     cout << "Distance BA" << distance[ind] << endl;
                    // }
                    int weight = graph[top.vertex][i];
                    if (distance[i] > weight + distance[top.vertex] && weight != 0) {
                        if (open.find(i) == open.pq.end() && close[i] == 0) {
                            distance[i] = weight + distance[top.vertex];
                            parent[i] = top.vertex;
                            open.push({i, distance[i] + h_n[i]});
                        }
                        else if (close[i] != 0) {
                            close[i] = 0;
                            int amount_decrease = distance[i] - weight - distance[top.vertex];
                            distance[i] = weight + distance[top.vertex];
                            parent[i] = top.vertex;
                            open.push({i, distance[i] + h_n[i]});
                            for (int j = 0; j < v; j++) {
                                if (parent[j] == i) {
                                    distance[j] -= amount_decrease;
                                }
                            }
                        }
                        else if (open.find(i) != open.pq.end()) {
                            distance[i] = weight + distance[top.vertex];
                            parent[i] = top.vertex;
                            open.pop(open.find(i) - open.pq.begin());
                            open.push({i, distance[i] + h_n[i]});
                        }
                    }
                }
            }
        }
    int count_close = 0;
    for (int i : close) {
        if (i == 1) count_close++;
    }
    // for (int i = 0; i < v; i++) {
    //     cout << vertice[i] << " " << close[i] << endl;
    // }
    // Do not reach end
    if (distance[end] == numeric_limits<int>::max()) 
        return {{"-unreachable-"}, {count_close, 0}};
    // Reach end
    vector<string> path;
    for (int cur = end; cur != -1; cur = parent[cur]) {
        path.push_back(vertice[cur]);
    }
    reverse(path.begin(), path.end());
    return {path, {count_close, distance[end]}};
    }
};
int main() {
    int v, e;
    cin >> v >> e;
    string start, end;
    cin >> start >> end;
    int temp = v;
    map<string, int> index;
    vector<string> vertice(v, "");
    for (int i = 0; i < v; i++) {
        cin >> vertice[i];
        index[vertice[i]] = i;
    }
    vector<int> h_n(v, -1);
    for (int i = 0; i < v; i++) {
        cin >> h_n[i];
    }
    vector<vector<int>> graph(v, vector<int>(v, 0));
    while (e--) {
        string v1, v2;
        cin >> v1 >> v2;
        cin >> graph[index[v1]][index[v2]];
    }
    // for (auto Outterpair : ad_list) {
    //     auto innerPair = Outterpair.second;
    //     cout << Outterpair.first << "{\n";
    //     for (auto i:innerPair) {
    //         cout << "key: " << i.first << " value: " << i.second << endl;
    //     }
    //     cout << "}\n";
    // }
    handle h;
    auto res = h.A_star(index[start], index[end], v, vertice, graph, h_n, index);
    vector<string> path = res.first;
    auto PAIR = res.second;
    if (path[0] == "-unreachable-") {
        cout << path[0] << endl;
        cout << PAIR.first << " " << PAIR.second << endl;
    } else {
        for (string it : path) cout << it << " ";
        cout << endl << PAIR.first << " " << PAIR.second << endl;
    }
    // for (int i = 0; i < v; i++)
    // { 
    //     for (int j = 0; j < v; j++)
    //     {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}