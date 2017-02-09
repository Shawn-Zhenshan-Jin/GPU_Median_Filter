# GPU_Median_Filter
*Super efficient median filter for GPU computing*

**Threads Organization on The Blocks**
![Alt text](https://cloud.githubusercontent.com/assets/14370804/22793865/bd5a38b8-eeb6-11e6-809f-ddb35557b30f.png "Threads Organization on The Blocks")
* T_total = samples * N // T_total: total number of threads  
* bdk = nthread/N        
* grd = samples/bdk + 1 


This median filter is based on the paper [link](http://ceur-ws.org/Vol-1543/p1.pdf "High Performance Median Filtering Algorithm Based on NVIDIA GPU Computing"). In the paper, Mr.Placido only implemented the median filter for odd number and this median filter is efficient for both even and odd situation
