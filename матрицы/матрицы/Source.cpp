#include <iostream> 
#include <vector> 
#include <thread> 

using namespace std;

void thread_Myltiplicatio_Matrix(vector<vector <long long>>& m, vector<vector <long long>>& m1, 
                                 vector<vector<long long>> &result , int n, int begin) {
    
    for (int i = begin; i < m.size(); i+=n) {
        int sum = 0;
        for (int j = 0; j < m[0].size(); j++) {
            for (int k = 0; k < m[0].size(); k++) {
                sum += m[i][k] * m1[k][j];
            }
            result[i][j] = sum;
            sum = 0;
        }
    }

}

void Hello(vector <vector <long long>>& m, vector <vector <long long>>& m1
    , vector <vector<long long>>& result, int n, int begin) {
    cout << "hello world";
}

int main() {
    long long row, column;
    long long row_, column_;

    int n;

    cout << "Enter quantity threads";

    cin >> n;


    cout << "Enter the number of rows of the first matrix: ";
    cin >> row;
    cout << "Enter the number of columns of the first matrix: ";
    cin >> column;

    cout << "Enter the number of rows of the second matrix: ";
    cin >> row_;
    cout << "Enter the number of columns of the second matrix: ";
    cin >> column_;

    if (column != row_) {
        cout << "Matrix multiplication is not possible";
        return 0;
    }

    vector <vector <long long>> firstMatrix(row, vector <long long>(column));
    vector <vector <long long>> secondMatrix(row_, vector <long long>(column_));

    cout << "Fill in the first matrix\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> firstMatrix[i][j];
        }
    }

    cout << "Fill in the second matrix\n";
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < column_; j++) {
            cin >> secondMatrix[i][j];
        }
    }

    vector <vector <long long>> resultMatrix(row, vector <long long>(column_));
    int begin = 0;

    vector <thread> threads;

    if (n > column) {
        n = column;
    }
    
    for (int i = 0; i < n; i++) {

        threads.push_back(thread(thread_Myltiplicatio_Matrix, ref(firstMatrix), ref(secondMatrix), ref(resultMatrix),n,begin));

        begin++;
    }

    for (auto& i : threads) {
        i.join();
    }

    for (auto& i : resultMatrix) {
        for (auto& j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}