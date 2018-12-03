# Multithreaded Matrix multiplication library

numpy_style_main.cpp is the single threaded library.
to compile it, use the following command:
`g++ numpy_multi_thr.cpp -std=c++11 -O4 -march=native`
It might complain about the pthread library, in that case, add `-lpthread` at the end.

## Relevant Programs:
- numpy_multi_thr.cpp multithreaded lib


## The list of functions that NEED to be implemented are:
### Single threaded:
- Elementwise
	- [X] Add
	- [X] Subtract
	- [X] Multiply
	- [X] Divide
	- [X] Fn
	- [ ] conjugate (can be done using fn, or directly)
- [X] reshape
- [X] matmul
- [X] FFT
- [X] transpose
- [X] convolution
- [ ] (optional (what an irony)) padding with some number n
- [X] trace
- [X] sum
- [X] mean
- [X] minimum
- [X] maximum

### Multi threaded:
- Elementwise
	- [X] Add
	- [X] Subtract
	- [X] Multiply
	- [X] Divide
	- [X] Fn
	- [ ] conjugate (can be done using fn, or directly)
- [X] matmul
- [X] FFT
- [X] transpose
- [ ] convolution
- [ ] (optional (what an irony)) padding with some number n
- [X] trace
- [X] sum
- [X] mean
- [X] minimum
- [X] maximum
