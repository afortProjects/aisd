#include <iostream>
#include <vector>
#include <string>

using namespace std;

int hasClaw(vector<string> matrix) {
    int n = matrix.size();
    if(n<4) return 1;
    for(int i=0;i<n;i++) {
        for(int j= 0;j<n; j++) {
            if(matrix[i][j] == '1' ) {
                for(int k=j+1; k<n; k++) {
                    if(matrix[i][k] == '1' && matrix[j][k] == '0') {
                        for(int l=k+1; l<n; l++) {
                            if(matrix[i][l] == '1' && matrix[j][l] == '0' && matrix[k][l] == '0' )
                                return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    int n, length, num;
    string input, tempString;
    //Number of matrixes
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
        cout << hasClaw(matrix) << endl;
    }
    return 0;
}