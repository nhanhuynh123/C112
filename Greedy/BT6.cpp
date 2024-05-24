#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct vertex {
    int name;
    int color;

    // constructor
    vertex() : name(0), color(0) {}
    vertex(int name, int color) {
        this->name = name;
        this->color = color;
    }
};
struct handle {
    int get_color(vector<int> num) {
        for (int i = 0; i < num.size(); i++) {
            if (num[i] != i) {
                return i;
            }
        }
        return num.size();
    }
    void check(vertex& tar, vector<int> ad_list_of_tar, map<string, vertex> index) {
        // Get color of vertice next by target
        set<int> colors_nextby_tar;
        // Get color in use
        set<int> color_in_use;
        vector<int> vector_c_iu;
        // 
        for(const auto& i:index) {
            if (ad_list_of_tar[i.second.name] == 1) {
                colors_nextby_tar.insert(i.second.color);
            }
            if(i.second.color != -1)
                color_in_use.insert(i.second.color);
        }
        // for (int i:color_in_use) cout << i << " ";
        // cout <<endl;
        int tar_color = tar.color;
        if (tar_color == -1 || colors_nextby_tar.find(tar_color) != colors_nextby_tar.end()) {
            set<int>::iterator it;
            int tar_newcolor;
            for (it = color_in_use.begin(); it != color_in_use.end(); ++it) {
                tar_newcolor = *it;
                vector_c_iu.push_back(*it);
                if (colors_nextby_tar.find(tar_newcolor) != colors_nextby_tar.end()){}
                else {
                    break;
                }
            }
            
            if (it == color_in_use.end()) {
                tar_newcolor = get_color(vector_c_iu);
            }
            tar.color = tar_newcolor;
            // cout << tar_newcolor << endl;
        }
    }
};
int main() {
    // Declare h type handle
    handle h;
    // Map that store index, color of string name 
    map<string, vertex> index;
    // Storing order vector
    vector<string> vertice;
    // Input parameter
    int v, e;
    cin >> v >> e;
    
    int temp_v = v;
    // Initialize a 2d vector which represent the connection of vertice
    vector<vector<int>> graph(v, vector<int>(v, 0));
    // Input vertice Ex: a b c
    while(temp_v--) {
        string temp;
        cin >> temp;
        index[temp] = vertex(index.size(), -1);
        vertice.push_back(temp);
    }
    // Input edge Ex: a b, b c
    while(e--) {
        string v1, v2;
        cin >> v1 >> v2;
        int i = index[v1].name;
        int j = index[v2].name;
        graph[i][j] = 1;
        graph[j][i] = 1;
    }
    index[vertice[0]].color = 0;
    for (int i = 1; i < vertice.size(); i++) {
        h.check(index[vertice[i]], graph[index[vertice[i]].name], index);
    }
    for (string v_name:vertice) {
        cout << index[v_name].color << " ";
    }
    cout << endl;

    return 0;
}