// #include <iostream>
// #include <list>
// #include <memory>
// #include <chrono>
// #include <cassert>
#include <bits/stdc++.h>
using namespace std;
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
    T res = T(1);
    for(auto elem : l){
        res *= elem;
    }
    return res;
}
template <class T>
T prod_elems_in_vector(vector<T> &v){
	T res = T(1);
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
vector<unsigned long long int> prods(vector<unsigned int> shape){
	vector<unsigned long long int> prod_vec;
	unsigned long long int prod = 1;
	unsigned int dimns = shape.size();
	for (int i = 0; i < dimns; ++i)
	{
		prod *= shape[dimns-i-1];
		prod_vec.push_back(prod);
	}
	return prod_vec;
}


vector<unsigned long long int> ret_cum_shape(vector<unsigned int> & shape){
	vector<unsigned long long int> res(shape.size(), 1);
	for (int i = shape.size()-2; i>= 0; i--){
		res[i] = res[i+1]*(shape[i+1]);
	}
	return res;
}

vector<unsigned long long int> ret_cum_shape2(vector<unsigned int> & shape){
	vector<unsigned long long int> res(shape.size(), 1);
	for (int i = shape.size()-2; i>= 0; i--){
		res[i] = res[i+1]*(shape[i]);
	}
	return res;
}

template<class T>
class gen_arr{
	vector<unsigned int> shape;
	vector<unsigned long long int> cumulative_shape;
	int ndim;
	shared_ptr<T> arr;
	int arr_len;
	int offset;
public:
	gen_arr(){
		this->arr.reset();
		this->ndim = 0;
		this->arr_len = 0;
		this->offset = 0;
	}
	void init(vector<unsigned int> shape, bool alloc=true){
		this->shape = shape;
		this->cumulative_shape = ret_cum_shape(this->shape);
		this->ndim = shape.size();
		this->arr_len = prod_elems_in_vector(shape);
		if (alloc){
			this->arr = shared_ptr<T>(new T[arr_len], std::default_delete<T[]>());
		}
		this->offset = 0;
	}
	gen_arr(vector<unsigned int> shape, T init_val, bool do_init=true, bool alloc=true){
		if (! alloc){
			printf("non alloc constructor called\n");
		}
		init(shape, alloc);
		if (do_init && alloc){
			fill_n(arr.get(), this->arr_len, init_val);
		}
	}
	// gen_arr(vector<unsigned int> shape, T init_val){
	// 	// assert(validate_vec(shape));
	// 	init(shape, true);
	// 	fill_n(arr.get(), this->arr_len, init_val);
	// 	cout << endl;
	// }
	gen_arr(vector<unsigned int> shape){
		init(shape);
	}
	string print_stats(){
		string res = "";
		res = res + "shape:\t" + vec_to_string(this->shape)+";\t";
		res = res + "ndim:\t" + to_string(this->ndim)+";\t";
		res = res + "arr_len:\t" + to_string(this->arr_len)+";\t";
		res = res + "offset:\t" + to_string(this->offset)+";\t";
		return res;
	}
	gen_arr add(gen_arr<T> const &rhs){
		assert(this->shape == rhs.shape);
		gen_arr<T> res(this->shape);
		int ilhs = 0, irhs0 = this->offset, irhs1 = rhs.offset;
		T *ptrlhs = res.arr.get(), *ptrrhs0 = this->arr.get(), *ptrrhs1 = rhs.arr.get();
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
		this->arr = shared_ptr<T>(new T[arr_len], std::default_delete<T>());
		memcpy(this->arr.get(), rhs.arr.get(), this->arr_len * sizeof(T));
		this->offset = 0;
	}
	gen_arr operator[](int index){
		assert(index >= 0);
        if (this->ndim > 0){
			vector<unsigned int> new_shape(this->shape.begin()+1, this->shape.end());
			T temp;
			gen_arr<T> res(new_shape, temp, false, false);
			res.arr = this->arr;
			int new_offset = this->offset + this->cumulative_shape[0]*index;
			res.offset = new_offset;
			return res;
		}
		else{
			printf("this->ndim should be a positive int\n");
			assert(this->ndim > 0);
		}
    }
	// int operator[](int index){
	// 	assert(index >= 0);
	// 	assert(this->ndim == 1)
	// 	return this->arr.get()[this->offset+index];
	// }
	gen_arr matmul(gen_arr<T> & rhs){
		assert(this->ndim == 2 && rhs.ndim == 2);
		int m1 = this->shape[0], n1 = this->shape[1];
		int m2 = rhs.shape[0], n2 = rhs.shape[1];
		assert(n1 == m2);
		vector<unsigned int> new_shape;
		new_shape.push_back(m1); new_shape.push_back(n2);
		gen_arr<T> res(new_shape, 0, false, true);
		printf("matmul: res defined\n");
		int sum;
		int rhs0off = this->offset, rhs1off = rhs.offset;
		int rhs0sh0 = this->cumulative_shape[0], rhs1sh0 = rhs.cumulative_shape[0];
		// cout << "rhs.cumulative_shape = " << vec_to_string(rhs.cumulative_shape) << endl;
		// cout << "rhs.shape = " << vec_to_string(rhs.shape) << endl;
		T *ptrlhs = res.arr.get(), *ptrrhs0 = this->arr.get(), *ptrrhs1 = rhs.arr.get();
		ptrlhs = ptrlhs + res.offset;
		for (int ii = 0; ii < m1; ii++){
			for(int jj = 0; jj < m1; jj++){
				T sum = 0;
				for (int kk = 0; kk < n1; kk++){
					sum += ptrrhs0[rhs0off+ii*rhs0sh0+kk]*ptrrhs1[rhs1off+kk*rhs1sh0+jj];
				}
				*ptrlhs = sum;
				// cout << "ii = " << ii << ";\tjj = " << jj << ";\tsum = " << sum << endl;
				ptrlhs++;
			}
		}
		return res;
	}

	gen_arr conv(gen_arr<T> & rhs){
		int rhs0_ndim = this->ndim;
		int rhs1_ndim = rhs.ndim;
		assert(rhs0_ndim == rhs1_ndim);
		vector<unsigned int> new_shape;
		vector<unsigned int> rhs0_shape = this->shape;
		vector<unsigned int> rhs1_shape = rhs.shape;
		for (int i = 0; i < rhs0_ndim; ++i)
		{
			new_shape.push_back(rhs0_shape[i] + rhs1_shape[i] - 1);
		}
		gen_arr<T> res(new_shape, 0, true, true);
		printf("conv: res defined\n");
		// int sum;
		int rhs0off = this->offset, rhs1off = rhs.offset;
		vector<unsigned long long int> rhs0_cush = this->cumulative_shape, rhs1_cush = rhs.cumulative_shape, lhs_cush = res.cumulative_shape;
		// cout << "rhs.cumulative_shape = " << vec_to_string(rhs.cumulative_shape) << endl;
		// cout << "rhs.shape = " << vec_to_string(rhs.shape) << endl;
		T *ptrlhs = res.arr.get(), *ptrrhs0 = this->arr.get(), *ptrrhs1 = rhs.arr.get();
		// ptrlhs = ptrlhs + res.offset;
		int rhs1_len = rhs.arr_len;
		int rhs0_len = this->arr_len;
		for (int rhs1_indx = 0; rhs1_indx < rhs1_len; ++rhs1_indx)
		{
			// int temp1 = *(ptrrhs1+rhs1off+rhs1_indx);
			for (int rhs0_indx = 0; rhs0_indx < rhs0_len; ++rhs0_indx)
			{
				// int temp2 = *(ptrrhs0+rhs0off+rhs0_indx);
				// int temp3 = temp1*temp2;
				int offset = 0;
				int rhs0_j = rhs0_indx;
				int rhs1_j = rhs1_indx;
				for (int k = 0; k < rhs0_ndim; ++k)
				{
					int rhs0_i = rhs0_j/rhs0_cush[k];
					int rhs1_i = rhs1_j/rhs1_cush[k];
					rhs0_j = rhs0_j % rhs0_cush[k];
					rhs1_j = rhs1_j % rhs1_cush[k];
					int lhs_i = (rhs1_shape[k] - rhs1_i - 1) + rhs0_i;
					offset += lhs_i*lhs_cush[k];
				}
				*(ptrlhs+offset) += ptrrhs1[rhs1off+rhs1_indx]*ptrrhs0[rhs0off+rhs0_indx];
			}
		}
		return res;
	}

	string str(){
		cout << "str entered\n";
		auto prod_vec = prods(shape);
		// vector<unsigned long long int> prod_vec = ret_cum_shape(shape);
		// reverse(prod_vec.begin(), prod_vec.end());
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
	vector<unsigned int> get_shape(){
		return this->shape;
	}
};

int main(){
	int shapearr[2] = {4,1};
	vector<vector<unsigned int> > shapes;
	shapes.push_back(vector<unsigned int> ());
	shapes[0].push_back(1000);shapes[0].push_back(1000);
	// shapes[0].push_back(1000);shapes[0].push_back(10000);
	// vector<unsigned int> shape(shapearr, shapearr+sizeof(shapearr)/sizeof(shapearr[0]));
	// auto t_stamp11 = chrono::high_resolution_clock::now();
	// gen_arr a(shapes[0], 212000), b(shapes[0], 321112);
	// auto t_stamp12 = chrono::high_resolution_clock::now();
	// gen_arr c = a + b;
    // auto t_stamp13 = chrono::high_resolution_clock::now();
	// auto alloc_time121 = chrono::duration_cast<chrono::duration<double>>(t_stamp12 - t_stamp11).count();
	// auto alloc_time132 = chrono::duration_cast<chrono::duration<double>>(t_stamp13 - t_stamp12).count();

	// cout << "c.shape" << vec_to_string(c.get_shape()) << endl;
	// printf("Time(in seconds): Alloc:%f;\tComputation:%f;\n", alloc_time121, alloc_time132);

	shapes.push_back(vector<unsigned int> ());
	shapes[1].push_back(1000);shapes[1].push_back(1000);
	// shapes[1].push_back(10000);shapes[1].push_back(1000);

	auto t_stamp21 = chrono::high_resolution_clock::now();
	gen_arr<int> a2(shapes[0], 3), b2(shapes[1], 7);
	// printf("a2, b2 allocated\n");
	auto t_stamp22 = chrono::high_resolution_clock::now();
	auto c2 = a2.matmul(b2);
	// printf("c2 calculated\n");
    auto t_stamp23 = chrono::high_resolution_clock::now();
	auto alloc_time221 = chrono::duration_cast<chrono::duration<double>>(t_stamp22 - t_stamp21).count();
	auto alloc_time232 = chrono::duration_cast<chrono::duration<double>>(t_stamp23 - t_stamp22).count();
	cout << "fooo\n";
	cout << "c2.shape" << vec_to_string(c2.get_shape()) << endl;
	printf("Time(in seconds): Alloc:%f;\tComputation:%f;\n", alloc_time221, alloc_time232);

	// cout << "a's shape " << vec_to_string(a2.get_shape()) << endl;
	// cout << "a's dump: \n" << a2.str() << endl; // a2.dummy_dump()
	// cout << "b's dump: \n" << b2.str() << endl;
	// cout << "c's dump: \n" << c2.str() << endl;
	return 0;
}