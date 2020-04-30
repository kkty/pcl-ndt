FROM ubuntu:18.04
RUN apt-get update && apt-get install build-essential libboost-all-dev libeigen3-dev libflann-dev cmake git -y
RUN git clone https://github.com/kkty/pcl /pcl && cd /pcl && git checkout 661487b5587d00c443d26defbe361b783e0f3d83
RUN cd /pcl && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j4 && make install
RUN mkdir /work
COPY CMakeLists.txt main.cpp room_scan1.pcd room_scan2.pcd /work/
RUN cd /work && mkdir build && cd build && cmake .. && make
CMD /work/build/main
