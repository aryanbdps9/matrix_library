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

vector<unsigned long long int> ret_cum_shape(vector<unsigned int> & shape){
	vector<unsigned long long int> res(shape.size(), 1);
	for (int i = shape.size()-2; i>= 0; i--){
		res[i] = res[i+1]*(shape[i]);
	}
	return res;
}
class gen_arr{
	vector<unsigned int> shape;
	vector<unsigned long long int> cumulative_shape;
	int ndim;
	shared_ptr<int> arr;
	int arr_len;
	int offset;
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
		this->arr_len = prod_elems_in_vector(shape);
		this->arr = shared_ptr<int>(new int[arr_len], std::default_delete<int[]>());
		this->offset = 0;
	}
	gen_arr(vector<unsigned int> shape){
		init(shape);
	}
	gen_arr(vector<unsigned int> shape, int init_val){
		// assert(validate_vec(shape));
		init(shape);
		fill_n(arr.get(), this->arr_len, init_val);
		cout << endl;
	}
	string print_stats(){
		string res = "";
		res = res + "shape:\t" + vec_to_string(this->shape)+";\t";
		res = res + "ndim:\t" + to_string(this->ndim)+";\t";
		res = res + "arr_len:\t" + to_string(this->arr_len)+";\t";
		res = res + "offset:\t" + to_string(this->offset)+";\t";
		return res;
	}
	gen_arr add(gen_arr const &rhs){
		assert(this->shape == rhs.shape);
		gen_arr res(this->shape);
		int ilhs = 0, irhs0 = this->offset, irhs1 = rhs.offset;
		int *ptrlhs = res.arr.get(), *ptrrhs0 = this->arr.get(), *ptrrhs1 = rhs.arr.get();
		for (; ilhs < this->arr_len; ilhs++, irhs0++, irhs1++){
			ptrlhs[ilhs] = ptrrhs0[irhs0] + ptrrhs1[irhs1];
			// res.arr.get()[ilhs] = this->arr.get()[irhs0] + rhs.arr.get()[irhs1];
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
	string str(){
		cout << "str entered\n";
		vector<unsigned long long int> prod_vec = ret_cum_shape(shape);
		reverse(prod_vec.begin(), prod_vec.end());
		int dimns = shape.size();
		string res = "";
		for (int i = 0; i < prod_vec[dimns-1]; ++i){
			int count = 0;
			for (int j = 0; j < dimns; ++j){
				if(i % prod_vec[j] == 0){
					count++;
				}
				else{
					break;
				}
			}
			if(count){
				for (int j = 0; j < dimns; ++j){
					if(j >= dimns-count){
						res += "[";
					}
					else{
						res += " ";
					}
				}
			}
			res += to_string(this->arr.get()[i]);
			count = 0;
			for (int j = 0; j < dimns; ++j){
				if((i+1) % prod_vec[j] == 0){
					count++;
					res += "]";
				}
				else{
					break;
				}
			}
			if(count){
				res += "\n";
			}
			else{
				res+= " ";
			}
		}
		return res;
	}
	string dummy_dump(){
		string res = "[";
		int ulim = this->offset + this->arr_len;
		int* ptrarr = this->arr.get();
		for (int i = this->offset; i < ulim; i++){
			res += to_string(ptrarr[i]) + ",";
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
	gen_arr a(shape, 212000), b(shape, 321112);
	gen_arr c = a + b;
	cout << "a's dump: \n" << a.str() << endl;
	cout << "b's dump: \n" << b.str() << endl;
	cout << "c's dump: \n" << c.str() << endl;
	return 0;
}