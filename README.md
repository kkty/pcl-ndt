```
$ docker build -f Dockerfile.old -t pcl-ndt-old .
$ docker run pcl-ndt-old
target_size = 112586, input_size = 112624
elapsed_init,elapsed_align,converged,score,iterations
0.006236,3.76182,1,0.290128,15
0.00502,3.82854,1,0.290128,15
0.004975,3.82671,1,0.290128,15
...
$ docker build -f Dockerfile.new -t pcl-ndt-new .
$ docker run pcl-ndt-new
target_size = 112586, input_size = 112624
elapsed_init,elapsed_align,converged,score,iterations
0.007026,1.28837,1,0.290128,15
0.006578,1.29485,1,0.290128,15
0.006377,1.29513,1,0.290128,15
...
```
