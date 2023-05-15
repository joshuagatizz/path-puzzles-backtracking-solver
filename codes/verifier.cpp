// Verifier algorithm for Path Puzzles
// Author: Joshua E. S.

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using namespace std::chrono;

steady_clock::time_point timeStart, timeStop;

int m, n;
pair<int, int> start, finish;
vector<vector<char>> A;
vector<int> cr, cc;

void readInput() {
    cin >> m >> n;
    cin >> start.fi >> start.se;
    cin >> finish.fi >> finish.se;
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
    current = {start.fi-1, start.se-1};
    pair<int, int> staZeroIdx = {start.fi-1, start.se-1};
    pair<int, int> finZeroIdx = {finish.fi-1, finish.se-1};
    
    if (A[staZeroIdx.fi][staZeroIdx.se] == '0' || A[finZeroIdx.fi][finZeroIdx.se] != 'u') {
        return false;
    }

    while (current != finZeroIdx && visited[current.fi][current.se] != 1) {
        int ic = current.fi, jc = current.se;
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

    if (current != finZeroIdx || A[current.fi][current.se] != 'u') {
        return false;
    }
    visited[current.fi][current.se] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != '0' && visited[i][j] == 0) {
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

int main() {
    readInput();
    timeStart = steady_clock::now();

    if (verifyConnectivity() && verifyConstraint(cr, cc)) {
        cout << "valid solution!";
    } else {
        cout << "invalid!";
    }
    
    timeStop = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << endl << "time taken: " << duration.count()/1000000.0 << "ms.";

    return 0;
}