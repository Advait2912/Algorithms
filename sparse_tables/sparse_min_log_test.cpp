#include<iostream>
#include<vector>
#include<cmath>
#include <chrono>

using namespace std;

vector<vector<long long>> build_table(vector<long long>& nums){
    vector<vector<long long>> lookup (nums.size(),vector<long long>(log2(nums.size())+1));
    //build for 2^0 length which is of 1 size 
    //for subarray of size one min is arr[i] itself
    for(long long i=0;i<nums.size();i++){
        lookup[i][0]=nums[i];
    }
    for(long long j=1;(1LL<<j)<=nums.size();j++){
        for(long long i=0;(i+(1LL<<j)-1)<nums.size();i++){
            lookup[i][j]=min(lookup[i][j-1],lookup[i+(1LL<<(j-1))][j-1]);
        }
    }
    return lookup;


}
long long query(vector<vector<long long>>&lookup,long long l,long long r){
    long long j=log2(r-l+1);
    return min(lookup[l][j],lookup[r-(1LL<<j)+1][j]);

}
long long smart_query(vector<long long>& logs,vector<vector<long long>>&lookup,long long l,long long r){
    long long j=logs[r-l+1];
    return min(lookup[l][j],lookup[r-(1LL<<j)+1][j]);

}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //Replaced answer stoarge with hash storing as takes too much space otherwise
    long long t;
    cin >> t;
    vector<vector<long long>> tests(t);
    vector<vector<pair<long long,long long>>> queries(t);

    cout << "Reading input...\n";
    for(long long i=0;i<t;i++){

        if(i % max(1LL,t/100) == 0){

            const int width = 40;
            double progress = (double)i / t;
            cout << "\rInput [";

            int pos = width * progress;
            for(int j=0;j<width;j++){
                if(j < pos) cout << "=";
                else if(j == pos) cout << ">";
                else cout << " ";
            }

            cout << "] "
                 << int(progress * 100)
                 << "%"
                 << flush;
        }

        long long n;
        cin >> n;
        vector<long long> temp(n);
        for(long long j=0;j<n;j++){
            cin >> temp[j];
        }

        long long q;
        cin >> q;
        vector<pair<long long,long long>> query_curr(q);

        for(long long j=0;j<q;j++){
            long long a,b;
            cin >> a >> b;
            query_curr[j] = {a,b};
        }
        tests[i] = move(temp);
        queries[i] = move(query_curr);
    }

    cout << "\rInput [========================================] 100%\n";
    cout << "Input processing complete.\n\n";
    // Sparse Table Query Benchmark
    cout << "Benchmarking Sparse Table...\n";

    auto start = chrono::steady_clock::now();
    unsigned long long hash_q = 0;

    for(long long i=0;i<t;i++){

        if(i % max(1LL,t/100) == 0){
            const int width = 40;
            double progress = (double)i / t;
            cout << "\rSparse Table [";
            int pos = width * progress;

            for(int j=0;j<width;j++){
                if(j < pos) cout << "=";
                else if(j == pos) cout << ">";
                else cout << " ";
            }

            cout << "] "
                 << int(progress * 100)
                 << "%"
                 << flush;
        }

        auto &test_vector = tests[i];
        auto &querys = queries[i];
        auto lookup = build_table(test_vector);
        for(const auto &q : querys){

            unsigned long long ans =
                query(
                    lookup,
                    q.first,
                    q.second
                );

            hash_q ^= (
                ans +
                0x9e3779b97f4a7c15ULL
            );
        }
    }
    auto end = chrono::steady_clock::now();

    cout << "\rSparse Table [========================================] 100%\n";

    auto duration_ms_q =
        chrono::duration_cast<chrono::milliseconds>(
            end - start
        );
    chrono::duration<double>
        duration_sec_q = end - start;

    // Sparse Table + Log Table Benchmark


    cout << "Benchmarking Sparse Table + Logs...\n";

    start = chrono::steady_clock::now();
    unsigned long long hash_sq = 0;

    for(long long i=0;i<t;i++){
        if(i % max(1LL,t/100) == 0){

            const int width = 40;
            double progress = (double)i / t;

            cout << "\rSparse+Logs [";
            int pos = width * progress;
            for(int j=0;j<width;j++){
                if(j < pos) cout << "=";
                else if(j == pos) cout << ">";
                else cout << " ";
            }

            cout << "] "
                 << int(progress * 100)
                 << "%"
                 << flush;
        }
        auto &test_vector = tests[i];
        auto &querys = queries[i];
        vector<long long> logs(
            test_vector.size() + 1
        );

        logs[1] = 0;
        for(long long k=2;
            k<=test_vector.size();
            k++)
        {
            logs[k] = logs[k/2] + 1;
        }
        auto lookup =
            build_table(test_vector);

        for(const auto &q : querys){

            unsigned long long ans =
                smart_query(
                    logs,
                    lookup,
                    q.first,
                    q.second
                );

            hash_sq ^= (
                ans +
                0x9e3779b97f4a7c15ULL
            );
        }
    }
    end = chrono::steady_clock::now();
    cout << "\rSparse+Logs [========================================] 100%\n";

    auto duration_ms_sq =
        chrono::duration_cast<chrono::milliseconds>(
            end - start
        );
    chrono::duration<double>
        duration_sec_sq = end - start;
    // Validation

    if(hash_q != hash_sq){

        cout << "\nVALIDATION FAILED\n";

        cout << "Hash Query      : "
            << hash_q
            << '\n';

        cout << "Hash SmartQuery : "
            << hash_sq
            << '\n';

        return 0;
    }

    cout << "\nValidation Passed\n";

    cout << "Result Hash     : "
        << hash_q
        << '\n';
    // Metrics

    long long total_elements = 0;
    long long total_queries = 0;

    for(long long i=0;i<t;i++){
        total_elements += tests[i].size();
        total_queries += queries[i].size();
    }

    cout << "\n===== BENCHMARK METRICS =====\n";

    cout << "Arrays Tested    : "
         << t << '\n';

    cout << "Total Elements   : "
         << total_elements << '\n';

    cout << "Total Queries    : "
         << total_queries << '\n';

    cout << '\n';

    cout << "Sparse Table Query Time:\n"
         << duration_ms_q.count()
         << " ms | "
         << duration_sec_q.count()
         << " sec\n\n";

    cout << "Sparse Table + Log Table Time:\n"
         << duration_ms_sq.count()
         << " ms | "
         << duration_sec_sq.count()
         << " sec\n";

    cout << "=============================\n";
    return 0;
}
