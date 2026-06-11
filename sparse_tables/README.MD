# The Need:

* To perform range queries in O(1) time

* given a range and range queries about min/max we answer it in O(1) time by doing some precomputation and storing it

* Uses a lookup table [i][j] which stores precomputed min/max of length 2^j starting at index i

* build table from bottom up for lookup[i][j], that is for an interval of length 2^j we can use two intervals of length 2^(j-1) to compute it

### For normal g++ compilation

```
>> g++ sparse_min.cpp -o <filename>
>> <filename> < input.txt 
```

* generate input using test_generator.cpp

```
Validation Passed

Naive Query Time:
56979 ms | 56.9791 sec

Sparse Table Query Time:
139 ms | 0.139129 sec

Sparse Table + Log Table Time:
137 ms | 0.137771 sec
```

## massive improvement (410x nearly), and this isnt even compiler optimized time

### For -O2 g++ compilation

```
>> g++ -O2 sparse_min.cpp -o <filename>
>> <filename> < input.txt 
```

```
Validation Passed

Naive Query Time:
15109 ms | 15.1099 sec

Sparse Table Query Time:
54 ms | 0.0542459 sec

Sparse Table + Log Table Time:
42 ms | 0.0422366 sec
```

## improvement is still massive (280x), difference between without log table and with log table became noticeable here (1.28x)

### For -O3 g++ compilation

```
>> g++ -O3 sparse_min.cpp -o <filename>
>> <filename> < input.txt 
```

```
Validation Passed

Naive Query Time:
15618 ms | 15.6183 sec

Sparse Table Query Time:
46 ms | 0.0467545 sec

Sparse Table + Log Table Time:
36 ms | 0.0366326 sec
```

## improvement is still massive (340x nearly), difference between without log table and with log table is noticeable here as well (1.28x)



# Stress test log table vs without log table approach

# Warning  only run test_generator_log.cpp if you have space, it will generate a input.txt in GBs
- there is progress bar in both test_generator_log and sparse_min_log_test as they take time to process input
- to run do:
``` 
>>g++ -O2 sparse_min_log.cpp -o <filename>
>>g++ -O2 test_generator_log.cpp -o test
>>./test (this generates input.txt in same directory)
>><filename> <input.txt
``` 
## Your os might kill this process as memory usage can go up to several GBs 

## Output Observed
```
Reading input...
Input [========================================] 100%
Input processing complete.

Benchmarking Sparse Table...
Sparse Table [========================================] 100%
Benchmarking Sparse Table + Logs...
Sparse+Logs [========================================] 100%

Validation Passed
Result Hash     : 11400714818687164346

===== BENCHMARK METRICS =====
Arrays Tested    : 5000
Total Elements   : 250873117
Total Queries    : 256015899

Sparse Table Query Time:
26431 ms | 26.4314 sec

Sparse Table + Log Table Time:
26449 ms | 26.4495 sec
=============================

```
- barely any difference for both, construction of build sparse table dominates 
- the cost of computing log2() vs using a precomputed log table becomes negligible at this scale
- program during runtime crossed 6.7k MBs on task manager
