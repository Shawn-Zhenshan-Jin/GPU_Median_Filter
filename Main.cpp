//This main function is not complete, please adjust it based on customerized requirement
[...]
// data preparations for even/odd sequence median filter
int c;
int c_even;
if((N % 2) == 0){
	N = N/2;
	N = N/2 - 1;
} else {
	c = (N - 1)/2;
	c_even = 0;
}

int nthread = 1024; //the maximum number of threads per core in the GPU
int bkd=(nthread-(nthread % N)) / N;
int grd=((samples-(samples % bkd))/bkd)+1;
dim3 thdims(bkd, N, 1); // N: total number of elements in one target sub-sequence
dim3 bkdims(grd, 1, 1);
// call median filter with cuda extension
CMF<<<bkdims,thdims>>>(IN, OUT, c, c_even);
[...]
