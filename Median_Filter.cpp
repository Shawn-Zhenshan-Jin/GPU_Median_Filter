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
