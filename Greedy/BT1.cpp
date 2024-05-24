#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    set<string> buffer;
    set<string> erased_buffer;
    while (n--) {
        string s1, s2;
        cin >> s1 >> s2;

        if  (buffer.find(s2 + s1) != buffer.end()) { 
            buffer.erase(s2 + s1);
            erased_buffer.insert(s2 + s1);
            erased_buffer.insert(s1 + s2);
        } else {
            if (erased_buffer.find(s1 + s2) == erased_buffer.end() && erased_buffer.find(s2 + s1) == erased_buffer.end()) // Chua nam trong tap xoa
                buffer.insert(s1 + s2); // Them vao tap hien thoi
        }
        // cout << buffer.size();
    }
    if (buffer.size() == 0) cout << "TRUE";
    else cout << "FALSE";

    return 0;
}