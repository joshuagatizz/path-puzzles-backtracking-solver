// Solver algorithm for Path Puzzles
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
bool isFound = false;

int mx[] = {1, 0, 0, -1};
int my[] = {0, -1, 1, 0};
char dir[] = {'d', 'l', 'r', 'u'};

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

    A.resize(m, vector<char>(n, '0'));
}

void outputSolution() {
    timeStop = steady_clock::now();
    cout << "solution found!\n\n";

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    auto duration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << endl << "time taken: " << duration.count()/1000000.0 << "ms.";
}

bool isValidCell(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

void decrementEntry(int x, int y) {
    if (cr[x] != -1) {
        cr[x]--;
    }
    if (cc[y] != -1) {
        cc[y]--;
    }
}

void incrementEntry(int x, int y) {
    if (cr[x] != -1) {
        cr[x]++;
    }
    if (cc[y] != -1) {
        cc[y]++;
    }
}

bool isConstraintValid() {
    for (int i = 0; i < m; i++) {
        if (cr[i] != -1 && cr[i] != 0) {
            return false;
        }
    }
    for (int j = 0; j < n; j++) {
        if (cc[j] != -1 && cc[j] != 0) {
            return false;
        }
    }
    return true;
}

void traverseCell(pair<int, int> current) {
    pair<int, int> adj;
    pair<int, int> finZeroIdx = {finish.fi-1, finish.se-1};

    decrementEntry(current.fi, current.se);
    
    if (current != finZeroIdx) {
        for (int i = 0; i < 4; i++) {
            adj = {current.fi+mx[i], current.se+my[i]};
            if (isValidCell(adj.fi, adj.se) && A[adj.fi][adj.se] == '0' && cr[adj.fi] != 0 && cc[adj.se] != 0) {
                A[current.fi][current.se] = dir[i];

                traverseCell(adj);
                
                A[current.fi][current.se] = '0';
                
            }
        }
    } else {
        if (isConstraintValid()) {
            A[current.fi][current.se] = 'u';
            outputSolution();
            exit(0);
        }
    }
    
    incrementEntry(current.fi, current.se);
}

int main() {
    readInput();
    timeStart = steady_clock::now();

    traverseCell({start.fi-1, start.se-1});
    cout << "solution not found.";
    
    return 0;
}