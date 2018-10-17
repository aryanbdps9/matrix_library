#include <iostream>
#include <list>
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
	generic_array* arr;
	int ga_length;
	int val;
	int ndim;
	list<int> shape;
	void init_helper(list<int>shape){
		this->shape = shape;
		this->ndim = shape.size();
		if (this->ndim == 0){
			this->ga_length = 0;
        }
		else{
			this->ga_length = shape.front();
			arr = new generic_array[this->ga_length];
		}
	}
	string str_helper(string append){
		if (this->ndim == 0){
			return to_string(this->val);
		}
		else if (this->ndim == 1){
			string res(this->ga_length*2+1, ',');
			res[0] = '[';
			for (int i = 0; i < this->ga_length; i++){
				res[2*i+1] = this->arr[i].str_helper("")[0];
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
				arr[i].init(shape);
			}
		}
	}
	void init(list<int> shape, int val){
		init_helper(shape);
		this->val = val;
		if (this->ndim != 0){
			shape.pop_front();
			for (int i = 0; i < this->ga_length; i++){
				arr[i].init(shape, val);
			}
		}
	}
	generic_array(){
		this->arr = NULL;
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
        // cout << "copy constructor called\n";
        this->ga_length = src.ga_length;
        this->ndim = src.ndim;
        this->val = src.val;
        this->shape = src.shape;
        if (this->ndim == 0){
            this->arr = NULL;
        }
        else{
            this->arr = new generic_array[this->ga_length];
            for (int i = 0; i < this->ga_length; i++){
                this->arr[i] = src.arr[i];
            }
        }
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
};

int main(){
    int shapearr[] = {4,5};
    list<int> shape(shapearr, shapearr+2);
    generic_array ga(shape, 2), gb(shape, 3);
    cout << "#############\n";
    generic_array gc(shape);
    gc = ga.add(gb);
    cout << ga.str() << endl << gb.str() << gc.str();
    return 0;
}