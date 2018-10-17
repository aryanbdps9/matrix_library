#include <iostream>
#include <list>
#include <memory>
// #include "myMat.cpp"

using namespace std;

string list_int_to_string(list<int> l){
    string res = "[";
    for (auto val : l){
        res += to_string(val) + ",";
    }
    res += "]";
    return res;
}

class generic_array{
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
	string str(){
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

};

int main(){
    int shapearr[] = {2, 2};
    list<int> shape(shapearr, shapearr+2);
    generic_array ga(shape, 43), gb(shape, 3);
    cout << "#############\n";
    generic_array gc(shape);
    gc = ga + -gb;
    ga += gc;
    cout << ga.str() << endl << gb.str() << gc.str();
    return 0;
}
