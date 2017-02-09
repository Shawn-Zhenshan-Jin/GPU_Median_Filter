__global__ 
void CMF(int* in, int* out, int c, int c_even, int N) {
	// k = input array index
	int k = c+blockDim.x*blockIdx.x+threadIdx.x;
	int M[N] = {0}; //major array
	int e[N] = {0}; //equal array
	int m[N] = {0}; //minor array
	//window index
	int i = k-c+threadIdx.y;
	for (int j=k-c; j<k-c+N; j++) {
		if (in[j]>in[i]) M[threadIdx.y]+=1;
		else if (in[j]<in[i]) m[threadIdx.y]+=1;
		else e[threadIdx.y]+=1;
	}

	for (int j = 0; j<N; j++) {
		// Even number case
		if (N%2 == 0) {
			if (M == c || M == c_even ||m == c ||m == c_even|| e >= c){
				if(e + gpuMin(M, m) == N/2.0){
					out[k] += in[k-c+j]/(2.0 * e); // In case median equal to multiple numbers
				}else{
					out[k] += in[k-c+j]/e;
				}
			}
		// Odd number case
		} else {
			if (M[j]==c || m[j]==c || e[j]>=c) {
				out[k] = in[k-c+j];
				return;
			}
		}
	}
}

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
