
# https://oeis.org/A344202

## https://mathoverflow.net/questions/296729/solve-this-diophantine-equation-2x-13y-1-2z2

```bash
$ sudo apt install build-essential git cmake libgmp-dev

$ git clone https://github.com/SofiaSL/ord23

$ cd ord23

$ mkdir build

$ cd build

$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

$ make -j9

$ ./tests

$ ./ord23
```

I ran a version of this program for 216 hours, giving this output:

```
108390409
149817457
2000634731
666591179.
4562284561............
14764460089.......
24040333283..................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
2506025630791........................................................................................
```

And

```
cat out.txt | grep "\." -o | wc -l
2590
```
so we know these entries are the only ones up to the 2590\*10^9.
