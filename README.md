
# https://oeis.org/A344202

## https://mathoverflow.net/questions/296729/solve-this-diophantine-equation-2x-13y-1-2z2

```bash
$ sudo apt install build-essential git cmake libgmp-dev

$ git clone https://github.com/bluescarni/mppp

$ cd mppp

$ mkdir build

$ cd build

$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

$ make -j9

$ sudo cmake  --build . --target install

$ cd

$ git clone https://github.com/SofiaSL/ord23

$ cd ord23

$ mkdir build

$ cd build

$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

$ make -j9

$ ./tests

$ ./ord23
```
