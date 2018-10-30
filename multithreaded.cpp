// #include <iostream>
// #include <list>
// #include <memory>
// #include <chrono>
// #include <cassert>
#include <thread>
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
class generic_array{
private:
	unique_ptr<generic_array[]> arr;
	int ga_length;
	int val;
	int ndim;
	list<int> shape;
	void init_helper(list<int>shape){
		this->shape = shape;
		this->ndim = shape.size();
		if (this->ndim == 0){
			this->ga_length = 0;
            this->arr.reset();
        }
		else{
			this->ga_length = shape.front();
			this->arr = unique_ptr<generic_array[]>(new generic_array[this->ga_length]);
		}
	}
	string str_helper(string append){
		if (this->ndim == 0){
			return to_string(this->val);
		}
		else if (this->ndim == 1){
			string res = "";
			res += "[";
			for (int i = 0; i < this->ga_length; i++){
				res += this->arr[i].str_helper("");
                res += ",";
			}
			res[res.length()-1] = ']';
			return append+res;
		}
		else{
			string res = append + "[\n";
			string child_append = append + "\t";
			for (int i = 0; i < this->ga_length; i++){
				res += this->arr[i].str_helper(child_append)+";\n";
			}
			res += append+"]";
			return res;
		}
	}
public:
	void init(list<int>shape){
		init_helper(shape);
		this->val = 0;
		if (this->ndim != 0){
			shape.pop_front();
			for (int i = 0; i < this->ga_length; i++){
				this->arr[i].init(shape);
			}
		}
	}
	void init(list<int> shape, int val){
		init_helper(shape);
		this->val = val;
		if (this->ndim != 0){
			shape.pop_front();
			for (int i = 0; i < this->ga_length; i++){
				this->arr[i].init(shape, val);
			}
		}
	}
    void init(list<int> shape, int* flat_arr){
        init_helper(shape);
        if (this->ndim == 0){
            this->ga_length = 0;
            this->arr.reset();
            this->val = flat_arr[0];
        }
        else{
            shape.pop_front();
            this->val = 0;
            int num_elem_in_submats = prod_elems_in_list(shape);
            for(int i = 0; i < this->ga_length; i++){
                this->arr[i].init(shape, &(flat_arr[num_elem_in_submats*i]));
            }
        }
    }
	generic_array(){
		this->arr.reset();
		this->val = 0;
		this->ndim = 0;
		this->ga_length = 0;
	}
	generic_array(list<int> shape){
		init(shape);
	}
	generic_array(list<int> shape, int init_val){
		init(shape, init_val);
	}
    generic_array(list<int>shape, int* flat_arr){
        init(shape, flat_arr);
    }
    generic_array(const generic_array &src){
        // cout << "copy constructor called. shape = " << list_int_to_string(src.shape) << "\n";
        this->ga_length = src.ga_length;
        this->ndim = src.ndim;
        this->val = src.val;
        this->shape = src.shape;
        if (this->ndim == 0){
            this->arr.reset();
        }
        else{
			this->arr = unique_ptr<generic_array[]>(new generic_array[this->ga_length]);
            for (int i = 0; i < this->ga_length; i++){
                this->arr[i] = src.arr[i];
            }
        }
    }
    ~generic_array(){
        this->arr.reset();
    }
public:
    int get_val(){ // Extracts val of the array
        return this->val;
    }
	string str(){ // Returns string representation of the array
		return str_helper("");
	}
    list<int> get_shape(){
        return this->shape;
    }
    generic_array add(generic_array const &rhs){
        generic_array res = *this;
        if (rhs.shape == this->shape){
            res.val += rhs.val;
            if (this->ndim != 0){
                for (int i = 0; i < this->ga_length; i++){
                    res.arr[i] = this->arr[i].add(rhs.arr[i]);
                }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return res;
    }
	// void add_range(generic_array const & rhs, generic_array& res, int l, int r){
	void add_range(generic_array const & rhs, generic_array* const res, int l, int r){
		// r is exclusive
		res->val = rhs.val + this->val;
		// if (res.ndim!= 0){}
		for (int i = l; i < r; i++){
			res->arr[i] = this->arr[i].add(rhs.arr[i]);
		}
	}
	generic_array multithreaded_add(generic_array const &rhs, int num_thr){
		generic_array res = *this;
		int block_size = ga_length / num_thr;
		if (rhs.shape == this->shape){
            res.val += rhs.val;
            if (this->ndim != 0){
				thread mythreads[num_thr];
				for (int i = 0; i < num_thr; i++){
					mythreads[i] = thread(&generic_array::add_range, this, rhs, &res, i*block_size, min((i+1)*block_size, ga_length));
					// mythreads[i] = thread(&generic_array::add_range, this, rhs, res, i*block_size, min((i+1)*block_size, ga_length));
				}
				for (int i = 0; i < num_thr; i++){
					mythreads[i].join();
				}
                // for (int i = 0; i < this->ga_length; i++){
                //     res.arr[i] = this->arr[i].add(rhs.arr[i]);
                // }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return res;
	}
    generic_array sub(generic_array const &rhs){
        generic_array res = *this;
        if (rhs.shape == this->shape){
            res.val -= rhs.val;
            if (this->ndim != 0){
                for (int i = 0; i < this->ga_length; i++){
                    res.arr[i] = this->arr[i].sub(rhs.arr[i]);
                }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return res;
    }
    generic_array elem_mul(generic_array const & rhs){
        generic_array res = *this;
        if (rhs.shape == this->shape){
            res.val *= rhs.val;
            if (this->ndim != 0){
                for (int i = 0; i < this->ga_length; i++){
                    res.arr[i] = this->arr[i].elem_mul(rhs.arr[i]);
                }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return res;
    }
    generic_array elem_div(generic_array const & rhs){
        generic_array res = *this;
        if (rhs.shape == this->shape){
            res.val /= rhs.val;
            if (this->ndim != 0){
                for (int i = 0; i < this->ga_length; i++){
                    res.arr[i] = this->arr[i].elem_div(rhs.arr[i]);
                }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return res;
    }
    generic_array & operator=(generic_array const &rhs){
        this->ga_length = rhs.ga_length;
        this->ndim = rhs.ndim;
        this->val = rhs.val;
        this->shape = rhs.shape;
        if (this->ndim == 0){
            this->arr.reset();
        }
        else{
			this->arr = unique_ptr<generic_array[]>(new generic_array[this->ga_length]);
            for (int i = 0; i < this->ga_length; i++){
                this->arr[i] = rhs.arr[i];
            }
        }
        return *this;
    }
    generic_array & operator=(int rhs){
        this->val = rhs;
        // return *this;
        if (this->ndim == 0){
            return *this;
        }
        else{
            for (int i = 0; i < this->ga_length; i++){
                this->arr[i] = rhs;
            }
        }
        return *this;
    }
    generic_array & operator+=(generic_array const &rhs){
        if (rhs.shape == this->shape){
            this->val += rhs.val;
            if (this->ndim != 0){
                for (int i = 0; i < this->ga_length; i++){
                    this->arr.get()[i] += rhs.arr.get()[i];
                }
            }
        }
        else{
            cout << "Incompatible shapes\n";
        }
        return *this;
    }
    generic_array operator+(generic_array const &rhs){
        return this->add(rhs);
    }
    generic_array operator-(generic_array const &rhs){
        return this->sub(rhs);
    }
    generic_array operator*(generic_array const &rhs){
        return this->elem_mul(rhs);
    }
    generic_array operator/(generic_array const & rhs){
        return this->elem_div(rhs);
    }
    generic_array & operator+(){
        return *this;
    }
    generic_array operator-(){
        generic_array res = *this;
        res.val = -(this->val);
        if (this->ndim != 0){
            for (int i = 0; i < this->ga_length; i++){
                res.arr.get()[i] = -(this->arr.get()[i]);
            }
        }

        return res;
    }
    generic_array & operator[](int index){
        assert(this->ndim > 0);
        assert(index >= 0 && index < this->ga_length);
        // TODO: throw exceptions
        return this->arr[index];
    }

public:
    generic_array matmul(generic_array & rhs){
        assert(this->ndim == 2 && rhs.ndim == 2);
        int m1 = this->shape.front(), n1 = this->shape.back();
        int m2 = rhs.shape.front(), n2 = rhs.shape.back();
        assert(n1 == m2);
        int newshapearr[] = {m1, n2};
        list <int> newshape = make_list_from_arr(newshapearr);
        generic_array res(newshape); // There are faster ways than this, but this will make multithreading stightly easier
        int sum;
        for(int ii = 0; ii < m1; ii++){ // row of 1st mat
            generic_array &row = this->arr[ii];
            for(int jj = 0; jj < n2; jj++){ // col of 2nd mat
                sum = 0;
                for(int kk = 0; kk < n1; kk++){
                    sum += row[kk].get_val() * rhs[kk][jj].get_val();
                }
                res[ii][jj] = sum;
            }
        }
        return res;
    }
};

// stop is exclusive
generic_array arange(list<int> &shape, int start, int stop, int step){
    if ((start - stop > 0 && step > 0) || (stop - start > 0 && step < 0) || start - stop == 0){
        return generic_array(shape);
    }
    int num_elems = (stop+1-start) / step;
    num_elems = num_elems > 0 ? num_elems : -num_elems;

    unique_ptr<int[]> buf(new int[num_elems]);
    for (int i = 0; i < num_elems; i++){
        buf[i] = start + step * i;
    }
    return generic_array(shape, buf.get());
}

generic_array arange(list<int> &shape, int stop){
    return arange(shape, 0, stop, stop > 0 ? 1 : -1);
}

generic_array arange(list<int> &shape, int start, int stop){
    return arange(shape, start, stop, stop > start ? 1 : -1);
}

int main(){
    int shapearr[] = {4, 4}, shapearr4x5[] = {4,5}, shapearr5x4[] = {5,4};
    int valarr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    list<int> shape = make_list_from_arr(shapearr);
    // list<int> shape(shapearr, shapearr+2);
    generic_array ga(shape, 43), gb(shape, 3);
    ga = 100;
    cout << "#############\n";
    generic_array gc(shape), ge(shape), gf(shape);
    gc = ga + -gb;
    generic_array gd = ga - gc;
    ge = ga * gb;
    gf = ga / gb;
    cout << ga.str() << endl << gb.str() << endl << gc.str() << endl << gd.str() << endl << ge.str() << endl << gf.str() << endl;
    generic_array gg(shape, valarr);
    gg = arange(shape, 1, 100);
    cout << gg.str() << endl;
    list<int> shape4x5 = make_list_from_arr(shapearr4x5), shape5x4 = make_list_from_arr(shapearr5x4);
    generic_array a = arange(shape4x5, 1, 20), b = arange(shape5x4, 1, 20);
    generic_array c = a.matmul(b);
    cout << "a = " << a.str() << endl << " b = " << b.str() << "c = " << c.str() << endl;
	int mm, nn;
	cout << "enter mm:\t" << endl;
	cin >> mm;
	cout << "enter nn:\t\n";
	cin >> nn;
	int large_shapearr[] = {mm, nn};
	// int large_shapearr[] = {10, 10};
	list<int> large_shape = make_list_from_arr(large_shapearr);
    auto t_stamp1 = chrono::high_resolution_clock::now();
    generic_array aa(large_shape, 1), bb(large_shape, 2), cc(large_shape);
    auto t_stamp2 = chrono::high_resolution_clock::now();
    cc = aa.multithreaded_add(bb, 2);
	// cc = aa + bb;
    auto t_stamp3 = chrono::high_resolution_clock::now();
    auto alloc_time21 = chrono::duration_cast<chrono::duration<double>>(t_stamp2 - t_stamp1) .count();
    auto alloc_time32 = chrono::duration_cast<chrono::duration<double>>(t_stamp3 - t_stamp2) .count();
    printf("Time(in seconds): Alloc:%f;\tComputation:%f;\n", alloc_time21, alloc_time32);
	// cout << "cc " << cc.str() << endl;
	cout << "cc " << list_int_to_string(cc.get_shape()) << endl;
	return 0;
}
