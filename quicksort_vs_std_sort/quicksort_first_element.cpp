#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;
void quicksort(vector<long long>& nums,long long l,long long r){
    if(l>=r){
        return;
    }
    long long pivot=nums[l];
    long long p=l+1;
    long long q=r;
    while(true){
        while(p<=r && nums[p]<pivot){p++;};
        while(q>l && nums[q]>pivot){q--;};

        if(p<q){
            swap(nums[p],nums[q]);
            p++;
            q--;
        }
        else{
            break;
        }
    }
    swap(nums[l],nums[q]);
    quicksort(nums,l,q-1);
    quicksort(nums,q+1,r);
    return;
}
int main(){
    long long n;
    cin>>n;
    vector<vector<long long>> cases(n);
    for(long long i=0;i<n;i++){
        long long m;
        cin>>m;
        vector<long long> curr(m);
        for(int j=0;j<m;j++){
            cin>>curr[j];
        }
        cases[i]=curr;
    }
    vector<vector<long long>> cases2=cases;
    auto start=chrono::steady_clock::now();
    for(auto &i:cases){
        quicksort(i,0,i.size()-1);
        
    }
    auto end=chrono::steady_clock::now();
    auto duration_ms_quick=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec_quick=end-start;
    start=chrono::steady_clock::now();
    for(auto &i :cases2){
        sort(i.begin(),i.end());
    }
    end=chrono::steady_clock::now();
    auto duration_ms_sort=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec_sort=end-start;
    cout<<"Time for quicksort in milliseconds and seconds for "<<n<<" vectors is:"<<duration_ms_quick.count()<<" "<<duration_sec_quick.count()<<endl;
    cout<<"Time for std::sort in miliseconds and seconds for "<<n<<" vectors is:"<<duration_ms_sort.count()<<" "<<duration_sec_sort.count()<<endl;
    return 0;
}