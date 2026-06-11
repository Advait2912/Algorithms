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
    fout.rdbuf()->pubsetbuf(new char[1 << 20], 1 << 20);
    const long long T = 5000;

    const long long N_MIN = 1000;
    const long long N_MAX = 100000;

    const long long Q_MIN = 1000;
    const long long Q_MAX = 100000;

    long long total_elements = 0;
    long long total_queries = 0;

    long long min_n_seen = 1e18;
    long long max_n_seen = 0;

    long long min_q_seen = 1e18;
    long long max_q_seen = 0;

    fout << T << '\n';

    for(long long tc = 0; tc < T; tc++) {
        if(tc % 100 == 0){

        const int width = 50;

        double progress =
            static_cast<double>(tc) / T;

        cout << "[";

        int pos = width * progress;

        for(int i=0;i<width;i++){
            if(i < pos) cout << "=";
            else if(i == pos) cout << ">";
            else cout << " ";
        }

        cout << "] "
            << int(progress * 100)
            << "%\r"
            << flush;
        }
        long long N =
            N_MIN + rng() % (N_MAX - N_MIN + 1);

        long long Q =
            Q_MIN + rng() % (Q_MAX - Q_MIN + 1);

        total_elements += N;
        total_queries += Q;

        min_n_seen = min(min_n_seen, N);
        max_n_seen = max(max_n_seen, N);

        min_q_seen = min(min_q_seen, Q);
        max_q_seen = max(max_q_seen, Q);

        fout << N << '\n';

        for(long long i = 0; i < N; i++) {

            long long x =
                rng() % 1000000000LL;

            fout << x;

            if(i + 1 < N)
                fout << ' ';
        }

        fout << '\n';

        fout << Q << '\n';

        for(long long i = 0; i < Q; i++) {

            long long l, r;

            switch(i % 5) {

                case 0:
                    // full-array style queries
                    l = rng() % max(1LL, N / 20);
                    r = N - 1 - (rng() % max(1LL, N / 20));
                    break;

                case 1:
                    // single element
                    l = rng() % N;
                    r = l;
                    break;

                case 2:
                    // tiny intervals
                    l = rng() % N;
                    r = min(
                        N - 1,
                        l + static_cast<long long>(rng() % 10)
                    );
                    break;

                case 3:
                    // medium intervals
                    l = rng() % N;
                    r = min(
                        N - 1,
                        l + static_cast<long long>(rng() % 1000)
                        );
                    break;

                default:
                    // random
                    l = rng() % N;
                    r = rng() % N;

                    if(l > r)
                        swap(l, r);
            }

            fout << l << ' ' << r << '\n';
        }
    }

    fout.close();

    cout << "\n===== TEST METRICS =====\n";

    cout << "Arrays Generated : "
         << T << '\n';

    cout << "Total Elements   : "
         << total_elements << '\n';

    cout << "Total Queries    : "
         << total_queries << '\n';

    cout << "Average N        : "
         << (double)total_elements / T
         << '\n';

    cout << "Average Q        : "
         << (double)total_queries / T
         << '\n';

    cout << "Min N            : "
         << min_n_seen << '\n';

    cout << "Max N            : "
         << max_n_seen << '\n';

    cout << "Min Q            : "
         << min_q_seen << '\n';

    cout << "Max Q            : "
         << max_q_seen << '\n';
        long double estimated_numbers =
        total_elements +
        2.0L * total_queries;

    cout << "Total Numbers Written : "
        << estimated_numbers
        << '\n';
    cout << "========================\n";

    return 0;
}