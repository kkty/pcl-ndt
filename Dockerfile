FROM ubuntu:18.04
RUN apt-get update && apt-get install build-essential libboost-all-dev libeigen3-dev libflann-dev cmake git -y
RUN git clone https://github.com/kkty/pcl /pcl
RUN cd /pcl && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j && make install
RUN mkdir /work
COPY CMakeLists.txt main.cpp room_scan1.pcd room_scan2.pcd /work/
RUN cd /work && mkdir build && cd build && cmake .. && make
CMD /work/build/main /work/room_scan1.pcd /work/room_scan2.pcd
