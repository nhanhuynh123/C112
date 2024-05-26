#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
struct coordinate {
    int col;
    int row;

    coordinate operator+ (coordinate other) {
        coordinate res;
        res.col = col + other.col;
        res.row = row + other.row;
        return res;
    }
    bool operator== (coordinate o) {
        return col == o.col && row == o.row;
    }
};
struct heu_data {
    coordinate coor;
    int heu;
};
struct compare {
    bool operator()(const heu_data& a, const heu_data& b) {
        return a.heu > b.heu;
    }
};
struct handle {
    int euclide_dis (coordinate pos, coordinate tar) {
        return sqrt(pow(abs(pos.col - tar.col), 2) + pow(abs(pos.row - tar.row), 2));
    }
    bool check(int n, int m, coordinate pos) {
        return ((0 <= pos.col && pos.col <= m - 1) && (0 <= pos.row && pos.row <= n - 1));
        // return ((0 <= pos.x <= n - 1) && (0 <= pos.y <= n - 1));
    }
    pair<int, int> get_index(coordinate pos, int m) {
        // return {m - 1 - pos.x, pos.y};
        return {m - 1 - pos.col, pos.row};
    }
    int calculate(vector<vector<int>> env, coordinate farmer, coordinate castle) {
        int m = env.size();
        int n = env[0].size();
        // cout << m <<" " << n << endl;
        vector<coordinate> movements = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
        priority_queue<heu_data, vector<heu_data>, compare> open;
        vector<vector<int>> num_of_move(m, vector<int>(n, -1));
        vector<vector<int>> visited(m, vector<int>(n, 0));
        pair<int, int> farmer_ind = get_index(farmer, m);
        // cout << farmer_ind.first << " " << farmer_ind.second << endl;
        num_of_move[farmer_ind.first][farmer_ind.second] = 0;
        open.push({farmer, 0});
        while (open.size()) {
            coordinate cur_coor = open.top().coor;
            open.pop();
            pair<int, int> index = get_index(cur_coor, m);
            int cost = num_of_move[index.first][index.second];
            visited[index.first][index.second] = 1;
            if (cur_coor == castle) {
                break;
            }
            for (auto movement : movements) {
                coordinate new_coor = cur_coor + movement;
                // cout << new_coor.x << " " << new_coor.y << " " << check(n, new_coor) << endl;

                pair<int, int> new_ind = get_index(new_coor, m);
                if (check(n, m, new_coor) == true && env[new_ind.first][new_ind.second] == 0 && visited[new_ind.first][new_ind.second] == 0 && num_of_move[new_ind.first][new_ind.second] == -1) {
                // cout << "heelo\n" ;
                    open.push({new_coor, cost});
                    num_of_move[new_ind.first][new_ind.second] = cost + 1;
                }
            }
        //     for (auto i:num_of_move) {
        //     for (int j:i) cout << j << " ";
        //     cout << endl;
        // }
        // cout << "---\n";
        }
        // for (auto i:num_of_move) {
        //     for (int j:i) cout << j << " ";
        //     cout << endl;
        // }
        pair<int, int>  castle_ind = get_index(castle, m);
        return num_of_move[castle_ind.first][castle_ind.second];
    }
};
int main() {
    handle h;
    int m, n;
    coordinate farmer;
    coordinate castle;
    cin >> m >> n >> farmer.col >> farmer.row >> castle.col >> castle.row;

    vector<vector<int>> map(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    cout << h.calculate(map, farmer, castle);
    return 0;
}