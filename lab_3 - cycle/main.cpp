#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool dfs(int& i, int parent, vector<bool>& visited, vector<string>& matrix) {
    visited[i] = true;

    for(int v=0; v<matrix[i].size(); v++) {
        if(matrix[i][v] == '1') {
            if(!visited[v]) {
                if (dfs(v, i, visited, matrix)) 
                    return true;
            }
            else if( v != parent) {
                return true;
            }
        }
    }
    return false;
}

int isCycle(vector<string>& matrix) {
    size_t n = matrix.size();
    vector<bool> visited(n, false);
    for(int i = 0; i<n; i++) {
        if(!visited[i]) {
            if(dfs(i, -1, visited, matrix)) 
                return 1;
        }
    }
    return 0;
}

bool isConnected(vector<string>& matrix) {
    size_t n = matrix.size();
    vector<bool> visited(n, false);
    int count = 0;
    for(int i = 0; i<n; i++) {
        if(!visited[i]) {
            dfs(i, -1, visited, matrix);
            count++;
        }
    }
    return count == 1;
}

bool isSymmetric(vector<string>& matrix) {
    for(size_t m=0;m<matrix.size(); m++) {
        for(size_t j=0; j<matrix[m].size(); j++) {
            if(matrix[m][j] != matrix[j][m])
                return false;
        }
    }
    return true;
}

void printMatrix(vector<string>& matrix) {
    for(size_t i=0;i<matrix.size(); i++) {
        for(size_t j=0; j<matrix[i].size(); j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int main() {
    int n, length, num;
    string input, tempString;
    cin >> n;

    for(size_t i = 0; i < n ; i++) {
        vector<string> matrix;
        cin >> length;
        cin >> input;
        for(size_t n = 0; n < input.size(); n++) {
            if((n+1) % length == 0) {
                tempString += input[n];
                matrix.push_back(tempString);
                tempString = "";
            } else {
                tempString += input[n];
            }
        }
    
        cout << (isCycle(matrix) && isConnected(matrix) && isSymmetric(matrix)) << endl;
    }
    return 0;
}