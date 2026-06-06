# Current Progress

The current implementation uses a basic Quicksort where the first element of the partition is chosen as the pivot, hence the file name `quicksort_first_element.cpp`.

```cpp
void quicksort(vector<long long>& nums,long long l,long long r){
    if(l>=r){
        return;
    }

    long long pivot=nums[l];
    long long p=l+1;
    long long q=r;

    while(true){
        while(p<=r && nums[p]<pivot){p++;}
        while(q>l && nums[q]>pivot){q--;}

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
}
```

## Benchmark Setup

* 1000 test cases
* Each test case contains 10,000 randomly generated integers
* The same input data is used for both Quicksort and `std::sort`
* Benchmarks were run under three compilation settings:

  * Default compilation
  * `-O2`
  * `-O3`

## Results

### Default Compilation

```
Time for quicksort in milliseconds and seconds for 1000 vectors is: 740 ms 0.740165 sec
Time for std::sort in milliseconds and seconds for 1000 vectors is: 1009 ms 1.00993 sec
```

### Compiled with `-O2`

```
Time for quicksort in milliseconds and seconds for 1000 vectors is: 195 ms 0.195319 sec
Time for std::sort in milliseconds and seconds for 1000 vectors is: 163 ms 0.163887 sec
```

### Compiled with `-O3`

```
Time for quicksort in milliseconds and seconds for 1000 vectors is: 191 ms 0.191849 sec
Time for std::sort in milliseconds and seconds for 1000 vectors is: 164 ms 0.16468 sec
```

## Observations

* Compiler optimizations dramatically improved performance for both algorithms.
* The difference between `-O2` and `-O3` was relatively small.
* On random input, the custom Quicksort implementation performs surprisingly close to `std::sort`.
* `std::sort` remains faster due to its highly optimized introsort implementation and years of engineering effort.
* Further experiments are planned using:

  * Randomized pivots
  * Median-of-three pivots
  * Sorted input
  * Reverse-sorted input
  * Duplicate-heavy input
  * Large-scale benchmarks
