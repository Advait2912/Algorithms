#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

int main() {

    mt19937_64 rng(
        chrono::steady_clock::now()
        .time_since_epoch()
        .count()
    );

    ofstream fout("input.txt");

    const long long N = 100000;
    const long long Q = 1000000;

    fout << N << '\n';

    for(long long i = 0; i < N; i++){
        fout << (rng() % 1000000000);

        if(i + 1 < N)
            fout << ' ';
    }

    fout << '\n';

    fout << Q << '\n';

    for(long long i = 0; i < Q; i++){

        long long l = rng() % N;
        long long r = rng() % N;

        if(l > r)
            swap(l,r);

        fout << l << ' ' << r << '\n';
    }

    cout << "Generated input.txt\n";
}