// #include <iostream>
// #include <list>
// #include <memory>
// #include <chrono>
// #include <cassert>
#include <bits/stdc++.h>
using namespace std;

string list_int_to_string(list<int> l){
    string res = "[";
    for (auto val : l){
        res += to_string(val) + ",";
    }
    res += "]";
    return res;
}
int prod_elems_in_list(list<int> &l){
    int res = 1;
    for(int elem : l){
        res *= elem;
    }
    return res;
}
list<int> make_list_from_arr(int *arr){
    list<int> res(arr, arr+sizeof(arr)/sizeof(int));
    return res;
}
class gen_arr{
	vector<int> shape;
	int ndim;
	unique_ptr<int[]> arr;
	
}