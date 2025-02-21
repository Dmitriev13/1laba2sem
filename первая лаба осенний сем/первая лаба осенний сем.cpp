#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

void findAns(int dp[20][101], int k, int s, int w[], vector<int>& result) {
    if (k == 0 || s == 0) return;
    if (dp[k][s] != dp[k - 1][s]) {
        result.push_back(k);
        findAns(dp, k - 1, s - w[k], w, result);
    }
    else {
        findAns(dp, k - 1, s, w, result);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Считываем данные из файла input.txt" << endl;
    ifstream inputFile("input.txt");
    int dp[15][101];
    int z, n;

    inputFile >> n >> z;

    int w[20] = { 0 }; // Веса предметов
    int t[20] = { 0 }; // Налоги

    for (int i = 1; i <= n; i++) {
        inputFile >> w[i]; // Считываем веса
    }
    for (int i = 1; i <= n; i++) {
        inputFile >> t[i]; // Считываем налоги
    }

    int maxi = 10000;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= 100; j++) { // Исправлено до 100
            dp[i][j] = maxi;
        }
    }
    dp[0][0] = 0;

    for (int k = 1; k <= n; k++) {
        for (int s = 0; s <= 100; s++) { // Исправлено до 100
            if (s >= w[k]) {
                dp[k][s] = min(dp[k - 1][s], dp[k - 1][s - w[k]] + t[k]);
            }
            else {
                dp[k][s] = dp[k - 1][s];
            }
        }
    }

    int minTax = maxi;
    for (int s = z + 1; s <= 100; s++) {
        minTax = min(minTax, dp[n][s]);
    }

    if (minTax == maxi) {
        cout << "Нет решения" << endl;
    }
    else {
        cout << "Минимальный налог" << endl;
        cout << minTax << endl;
        vector<int> result;

        int s = 0;
        for (int j = z + 1; j <= 100; j++) {
            if (dp[n][j] == minTax) {
                s = j;
                break;
            }
        }

        for (int k = n; k > 0; k--) {
            if (s >= w[k] and dp[k][s] != dp[k - 1][s]) {
                result.push_back(k); // Добавляем предмет
                s -= w[k]; // Уменьшаем вес
            }
        }
        cout << "Предметы которые надо взять:  ";

        for (int i = result.size() - 1; i >= 0; i--) {

            cout << result[i] << " ";
        }
        cout << endl;
    }

    inputFile.close();
    return 0;
}
