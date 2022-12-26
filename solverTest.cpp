// Solver algorithm for Path Puzzles
// Author: Joshua E. S.

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int m, n;
pair<int, int> start, finish;
vector<vector<char>> A;
vector<int> cr, cc;
bool isFound = false;

int mx[] = {-1, 0, 1, 0};
int my[] = {0, 1, 0, -1};
char dir[] = {'u', 'r', 'd', 'l'};
vector<vector<vector<char>>> solutions;

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

    A.resize(m, vector<char>(n, '0'));
}

void outputSolutions() {
    if (solutions.empty()) {
        cout << "no solutions found.\n";
    } else {
        int sum = solutions.size();
        cout << sum << " solution(s) found.";
        for (auto sol : solutions) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << sol[i][j] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }
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

bool verifyPath() {
    if (!verifyConnectivity() || !verifyConstraint(cr, cc)) {
        return false;
    }
    return true;
}

void traverseCell(pair<int, int> current) {
    pair<int, int> adj;
    pair<int, int> finZeroIdx = {finish.first-1, finish.second-1};
    
    if (current == finZeroIdx) {
        A[current.first][current.second] = 'u';
        
        if (verifyPath()) {
            isFound = true;
            solutions.push_back(A);
        }
        A[current.first][current.second] = '0';
        return;
    }
    for (int i = 0; i < 4 && !isFound; i++) {
        adj = {current.first+mx[i], current.second+my[i]};
        if (isValidCell(adj.first, adj.second)) {
            if (A[adj.first][adj.second] == '0') {
                A[current.first][current.second] = dir[i];
                traverseCell(adj);
                
                A[current.first][current.second] = '0';
            }
        }
    }
}

int main() {
    readInput();
    // debug();
    auto timeStart = high_resolution_clock::now();

    traverseCell({start.first-1, start.second-1});

    auto timeStop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(timeStop - timeStart);
    // outputSolutions();
    cout << "time taken: " << duration.count() << "ms.";
    
    return 0;
}