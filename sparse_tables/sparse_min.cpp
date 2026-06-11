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
    for(long long j=1;(1<<j)<=nums.size();j++){
        for(long long i=0;(i+(1<<j)-1)<nums.size();i++){
            lookup[i][j]=min(lookup[i][j-1],lookup[i+(1<<(j-1))][j-1]);
        }
    }
    return lookup;


}
long long naive_query(vector<long long>& nums,long long l,long long r){
    long long ans = nums[l];

    for(long long i=l+1;i<=r;i++){
        ans = min(ans, nums[i]);
    }

    return ans;
}
long long query(vector<vector<long long>>&lookup,long long l,long long r){
    long long j=log2(r-l+1);
    return min(lookup[l][j],lookup[r-(1<<j)+1][j]);

}
long long smart_query(vector<long long>& logs,vector<vector<long long>>&lookup,long long l,long long r){
    long long j=logs[r-l+1];
    return min(lookup[l][j],lookup[r-(1<<j)+1][j]);

}
int main(){
    //read test_vector
    long long t;
    cin>>t;
    vector<long long> test_vector(t);
    for(long long i=0;i<t;i++){
        cin>>test_vector[i];
    }
    //read test queries;
    long long n;
    cin>>n;
    vector<vector<long long>> queries(n,vector<long long>(2));
    for(long long i=0;i<n;i++){
        vector<long long> temp(2);
        cin>>temp[0]>>temp[1];
        queries[i]=temp;
    }
    //stress test naive algorithm
    auto start=chrono::steady_clock::now();
    vector<long long> ans_naive;
    for(const auto &q:queries){
        ans_naive.push_back(naive_query(test_vector,q[0],q[1]));
    }
    //compute time
    auto end=chrono::steady_clock::now();
    auto duration_ms_naive=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec_naive=end-start;

    //stress test normal query using sparse table
    start=chrono::steady_clock::now();
    vector<vector<long long>> lookup=build_table(test_vector);
    vector<long long> ans_q;
    for(const auto &q:queries){
        ans_q.push_back(query(lookup,q[0],q[1]));
    }
    end=chrono::steady_clock::now();
    auto duration_ms_q=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec_q=end-start;

    //stress test smart query
    //build log table
    start=chrono::steady_clock::now();
    vector<long long> logs(t+1);
    logs[1]=0;
    for(long long i=2;i<=t;i++){
        logs[i]=logs[i/2]+1;
    }
    vector<vector<long long>> lookup2=build_table(test_vector);
    vector<long long> ans_sq;
    for(const auto & q:queries){
        ans_sq.push_back(smart_query(logs,lookup2,q[0],q[1]));
    }
    end=chrono::steady_clock::now();
    auto duration_ms_sq=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec_sq=end-start;

    if(ans_naive != ans_q){
    cout << "Sparse Table Query FAILED\n";
    return 0;
    }
    if(ans_naive != ans_sq){
        cout << "Smart Query FAILED\n";
        return 0;
    }
    cout << "Validation Passed\n\n";

    cout<< "Naive Query Time:\n"<< duration_ms_naive.count()<< " ms | "<< duration_sec_naive.count()<< " sec\n\n";
    cout<< "Sparse Table Query Time:\n"<< duration_ms_q.count()<< " ms | "<< duration_sec_q.count()<< " sec\n\n";
    cout<< "Sparse Table + Log Table Time:\n"<< duration_ms_sq.count()<< " ms | "<< duration_sec_sq.count()<< " sec\n";

    return 0;
}