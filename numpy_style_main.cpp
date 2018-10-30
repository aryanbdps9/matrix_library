// #include <iostream>
// #include <list>
// #include <memory>
// #include <chrono>
// #include <cassert>
#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct array_deleter{
	void operator()(T const *p)
	{
		delete[] p;
	}
};
template <class T>
string list_to_string(list<T> l){
    string res = "[";
    for (auto val : l){
        res += to_string(val) + ",";
    }
    res += "]";
    return res;
}
template <class T>
string vec_to_string(vector<T> v){
	string res = "[";
	for (auto val : v){
		res += to_string(val) + ",";
	}
	res += "]";
	return res;
}
template <class T>
T prod_elems_in_list(list<T> &l){
    T res = 1;
    for(int elem : l){
        res *= elem;
    }
    return res;
}
template <class T>
T prod_elems_in_vector(vector<T> &v){
	T res = 1;
	for (auto elem:v){
		res *= elem;
	}
	return res;
}
template <class T>
T validate_vec(vector<T> &v){
	for(auto elem:v){
		if (elem <= 0){
			return false;
		}
	}
	return true;
}
template <class T>
list<T> make_list_from_arr(T *arr){
    list<T> res(arr, arr+sizeof(arr)/sizeof(T));
    return res;
}
class gen_arr{
	vector<unsigned int> shape;
	vector<unsigned long long int> cumulative_shape;
	int ndim;
	shared_ptr<int> arr;
	int arr_len;
	int offset;
	// string str_helper_old(string append){
	// 	if (this->ndim == 0){
	// 		return to_string(this->val);
	// 	}
	// 	else if (this->ndim == 1){
	// 		string res = "";
	// 		res += "[";
	// 		for (int i = 0; i < this->ga_length; i++){
	// 			res += this->arr[i].str_helper("");
    //             res += ",";
	// 		}
	// 		res[res.length()-1] = ']';
	// 		return append+res;
	// 	}
	// 	else{
	// 		string res = append + "[\n";
	// 		string child_append = append + "\t";
	// 		for (int i = 0; i < this->ga_length; i++){
	// 			res += this->arr[i].str_helper(child_append)+";\n";
	// 		}
	// 		res += append+"]";
	// 		return res;
	// 	}
	// }
	vector<unsigned long long int> ret_cum_shape(vector<unsigned int> & shape){
		vector<unsigned long long int> res(1, shape.size());
		for (int i = shape.size()-2; i>= 0; i--){
			res[i] = res[i+1]*(shape[i]);
		}
		return res;
	}
	string string_helper(string append, int ind, int off){
		string res = append + "[";
		int ulim = shape[ndim - 1] + off;
		if (ind == ndim - 1){
			for (int i = off; i < ulim; i++){
				int ival = (((int*)(arr.get()))[i]);
				res += to_string(ival);
			}
		}
		return res;
	}
public:
	gen_arr(){
		this->arr.reset();
		this->ndim = 0;
		this->arr_len = 0;
		this->offset = 0;
	}
	void init(vector<unsigned int> shape){
		this->shape = shape;
		this->cumulative_shape = ret_cum_shape(this->shape);
		this->ndim = shape.size();
		this->arr = shared_ptr<int>(new int[arr_len], std::default_delete<int[]>());
		this->arr_len = prod_elems_in_vector(shape);
		this->offset = 0;
	}
	gen_arr(vector<unsigned int> shape){
		init(shape);
	}
	gen_arr(vector<unsigned int> shape, int init_val){
		// assert(validate_vec(shape));
		init(shape);
		memset(arr.get(), init_val, sizeof(int)*arr_len);
	}
	gen_arr add(gen_arr const &rhs){
		assert(this->shape == rhs.shape);
		gen_arr res(this->shape);
		for (int i = 0; i < this->arr_len; i++){
			res.arr.get()[i] = this->arr.get()[i] + rhs.arr.get()[i];
		}
		return res;
	}
	gen_arr  operator+(gen_arr const &rhs){
        return this->add(rhs);
    }
	gen_arr & operator=(gen_arr const & rhs){
		this->shape = rhs.shape;
		this->cumulative_shape = rhs.cumulative_shape;
		this->ndim = rhs.ndim;
		this->arr_len = rhs.arr_len;
		this->arr = shared_ptr<int>(new int[arr_len], std::default_delete<int>());
		memcpy(this->arr.get(), rhs.arr.get(), this->arr_len * sizeof(int));
		this->offset = 0;
	}
	string dummy_dump(){
		string res = "[";
		for (int i = 0; i < this->arr_len; i++){
			res += to_string(i) + ",";
		}
		res[res.size()-1] = ']';
		return res;
	}
};

int main(){
	int shapearr[2] = {4,1};
	vector<unsigned int> shape;
	shape.push_back(4);shape.push_back(1);
	// vector<unsigned int> shape(shapearr, shapearr+sizeof(shapearr)/sizeof(shapearr[0]));
	gen_arr a(shape, 2), b(shape, 3);
	// gen_arr c = a + b;
	return 0;
}