#include <bits/stdc++.h>
using namespace std;

vector<char> letters;
bool occupied[10];
unordered_map<char, int> assigned;

// Function to convert word -> number based on current assignment
int sum(const string &s) {
    int summ = 0;
    for (char c : s) {
        if (assigned.find(c) == assigned.end()) return -1; // not yet assigned
        summ = summ * 10 + assigned[c];
    }
    return summ;
}

// Backtracking solver
bool cryptArithmetic(int ind, const string &in1, const string &in2, const string &result) {
    if (ind == (int)letters.size()) {
        int left = sum(in1) + sum(in2);
        int right = sum(result);

        if (left == right) {
            // Print solution
            cout << in1 << ":";
            for (char c : in1) cout << assigned[c];
            cout << "\n";

            cout << in2 << ":";
            for (char c : in2) cout << assigned[c];
            cout << "\n";

            cout << result << ":";
            for (char c : result) cout << assigned[c];
            cout << "\n";

            return true;
        }
        return false;
    }

    char l = letters[ind];

    for (int i = 0; i < 10; i++) {
        // Leading digit cannot be zero
        if ((in1[0] == l && i == 0) ||
            (in2[0] == l && i == 0) ||
            (result[0] == l && i == 0)) continue;

        if (!occupied[i]) {
            assigned[l] = i;
            occupied[i] = true;

            if (cryptArithmetic(ind + 1, in1, in2, result)) return true;

            assigned.erase(l);
            occupied[i] = false;
        }
    }
    return false;
}

int main() {
    string in1, in2, result;
    cout << "Enter first input string:" << endl;
    cin >> in1;
    cout << "Enter second input string:" << endl;
    cin >> in2;
    cout << "Enter result string:" << endl;
    cin >> result;

    vector<bool> visited(26, false);

    for (char c : in1) {
        if (!visited[c - 'A']) {
            letters.push_back(c);
            visited[c - 'A'] = true;
        }
    }
    for (char c : in2) {
        if (!visited[c - 'A']) {
            letters.push_back(c);
            visited[c - 'A'] = true;
        }
    }
    for (char c : result) {
        if (!visited[c - 'A']) {
            letters.push_back(c);
            visited[c - 'A'] = true;
        }
    }

    if (!cryptArithmetic(0, in1, in2, result)) {
        cout << "No solution" << endl;
    }

    return 0;
}

