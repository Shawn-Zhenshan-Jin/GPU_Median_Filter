# GPU_Median_Filter
Super efficient median filter for GPU computing

![Alt text](https://cloud.githubusercontent.com/assets/14370804/22793865/bd5a38b8-eeb6-11e6-809f-ddb35557b30f.png "Threads Organization on The Blocks")
* T_total = samples * N    (1)
* bdk = nthread/N          (2)
* grd = samples/bdk + 1    (3)

This median filter is based on the paper [link](http://ceur-ws.org/Vol-1543/p1.pdf "High Performance Median Filtering Algorithm Based on NVIDIA GPU Computing"). In the paper, Mr.Placido only implement the odd number median filter and my median filter can is suitable for both even and odd situation
