#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    mt19937 rng(
        chrono::steady_clock::now()
        .time_since_epoch()
        .count()
    );

    ofstream fout("input.txt");

    int T = 1000;
    fout << T << '\n';

    for(int tc = 0; tc < T; tc++) {

        int n = 10000; 

        fout << n << '\n';

        for(int i = 0; i < n; i++) {

            // many duplicates are good for testing quicksort
            int x = rng() % 20;

            fout << x;

            if(i + 1 < n)
                fout << ' ';
        }

        fout << '\n';
    }

    fout.close();

    cout << "Generated input.txt with "
         << T
         << " test cases\n";
}