// Verifier algorithm for Path Puzzles
// Author: Joshua E. S.

#include <bits/stdc++.h>
using namespace std;

int m, n;
pair<int, int> start, finish;
vector<vector<char>> A;
vector<int> cr, cc;

void readInput() {
    cin >> m >> n;
    cin >> start.first >> start.second;
    cin >> finish.first >> finish.second;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        cr.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cc.push_back(x);
    }

    A.resize(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            A[i].push_back(c);
        }
    }
}

bool isValidCell(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

bool verifyConnectivity() {
    vector<vector<int>> visited;
    visited.resize(m, vector<int>(n, 0));
    pair<int, int> current;
    current = {start.first-1, start.second-1};
    pair<int, int> finZeroIdx = {finish.first-1, finish.second-1};

    while (current != finZeroIdx && visited[current.first][current.second] != 1) {
        int ic = current.first, jc = current.second;
        visited[ic][jc] = 1;
        if (A[ic][jc] == 'l' && isValidCell(ic, jc-1)) {
            current = {ic, jc-1};
        } else if (A[ic][jc] == 'r' && isValidCell(ic, jc+1)) {
            current = {ic, jc+1};
        } else if (A[ic][jc] == 'u' && isValidCell(ic-1, jc)) {
            current = {ic-1, jc};
        } else if (A[ic][jc] == 'd' && isValidCell(ic+1, jc)) {
            current = {ic+1, jc};
        } else {
            return false;
        }
    }

    if (current != finZeroIdx || A[current.first][current.second] == 0) {
        return false;
    }
    visited[current.first][current.second] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == '0' && visited[i][j] != 0) {
                return false;
            }
        }
    }
    
    return true;
}

bool verifyConstraint(vector<int> crow, vector<int> ccol) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != '0') {
                crow[i]--;
                ccol[j]--;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (cr[i] != -1 && crow[i] != 0) {
            return false;
        }
    }
    for (int j = 0; j < n; j++) {
        if (cc[j] != -1 && ccol[j] != 0) {
            return false;
        }
    }
    
    return true;
}

void debug() {
    cout << "m and n: " << m << " " << n << endl;
    cout << "start: " << start.first << " " << start.second << endl;
    cout << "finish: " << finish.first << " " << finish.second << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    readInput();
    // debug();

    if (verifyConnectivity() && verifyConstraint(cr, cc)) {
        cout << "correct solution!";
    } else {
        cout << "incorrect solution!";
    }

    return 0;
}