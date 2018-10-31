#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

vector<int> prods(vector<int> shape){
	vector<int> prod_vec;
	int prod = 1;
	int dimns = shape.size();
	for (int i = 0; i < dimns; ++i)
	{
		prod *= shape[dimns-i-1];
		prod_vec.push_back(prod);
	}
	return prod_vec;
}



string str(int arr[], vector<int> shape){
	vector<int> prod_vec = prods(shape);
	int dimns = shape.size();
	string res = "";
	for (int i = 0; i < prod_vec[dimns-1]; ++i)
	{
		int count = 0;
		for (int j = 0; j < dimns; ++j)
		{
			if(i % prod_vec[j] == 0){
				count++;
			}
			else{
				break;
			}
		}
		if(count){
			for (int j = 0; j < dimns; ++j)
			{
				if(j >= dimns-count){
					res += "[";
				}
				else{
					res += " ";
				}
			}
		}
		res += to_string(arr[i]);
		count = 0;
		for (int j = 0; j < dimns; ++j)
		{
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


int main(){
	vector<int> dim;
	dim.push_back(3);
	dim.push_back(4);
	dim.push_back(5);
	dim.push_back(6);
	int len = dim[0]*dim[1]*dim[2]*dim[3];
	int arr[len] = {0};
	string res = str(arr, dim);
	cout<<res;
	// for (int i = 0; i < len; ++i)
	// {
	// 	int dimns = dim.size();
	// 	// for (int i = 0; i < count; ++i)
	// 	// {
	// 	// 	/* code */
	// 	// }
	// 	int prod = len;
	// 	int count = 0;
	// 	int tt = 0;
	// 	for (int j = 0; j < dimns; ++j)
	// 	{
	// 		if(i % prod == 0){
	// 			count++;
	// 			tt = 1;
	// 		}
	// 		// else cout<<" ";
	// 		prod = prod/dim[j];
	// 	}
	// 	if(tt == 1){		
	// 		for (int i = 0; i < dimns; ++i)
	// 		{
	// 			if(i >= (dimns-count)){
	// 				cout<<"]";
	// 			}
	// 			else cout<<" ";
	// 		}
	// 	}
	// 	cout<<arr[i];
	// 	prod = len;
	// 	int is = 0;
	// 	for (int j = 0; j < dimns; ++j)
	// 	{
	// 		if((i+1) % prod == 0){
	// 			cout<<"]";
	// 			is = 1;
	// 		}
	// 		prod = prod/dim[j];
	// 	}
	// 	if(is == 1){
	// 		cout<<endl;
	// 	}
	// 	else cout<<" ";
	// }
}