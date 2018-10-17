#include <iostream>
#include <list>
// #include "myMat.cpp"

using namespace std;

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
	string str(){
		return str_helper("");
	}
};

int main(){
    int shapearr[] = {4,5, 6};
    list<int> shape(shapearr, shapearr+3);
    generic_array ga(shape, 2);
    cout << ga.str() << endl;
    return 0;
}