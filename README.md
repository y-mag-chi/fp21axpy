FP21SAXPY
====

FP21SAXPY provides an example to use FP21, a custom data type, in OpenACC.

## Description
FP21 data type is our proposed floating-point number format, which is composed of 1-bit sign bit, 8-bits exponent part, and 12-bits fraction part. FP21 has the advantage of the same dynamic range as FP32 and a better accuracy than FP16.

3 × FP21 numbers are stored into 1 × 64-bit element, so it is suitable for 3-D simulations.

For memory bandwidth bound computations, 1.5-fold speedup can be expected by using FP21 data types compared to the standard FP32 data types.

## Requirement
* NVIDIA GPU
* PGI compiler (The default makefile has been written for PGI and tested with PGI 18.10.)

## Usage
### Compile
```
$ make
```  

### Run
You can run the program by simply  `./saxpy.exe`.  
If all goes well, you can get standard output as below:  
```
N = 20000000
OpenACC FP32 SAXPY
  results:  [  OK  ]
  time(ms)= 0.889600
  BW(GB/s)= 809.352518
OpenACC FP21 SAXPY
  results:  [  OK  ]
  time(ms)= 0.586000
  BW(GB/s)= 819.112628
```  

## Publication
Takuma Yamaguchi, Kohei Fujita, Tsuyoshi Ichimura, Akira Naruse, Muneo Hori, and Maddegedara Lalith, “GPU Implementation of a Sophisticated Implicit Low-Order Finite Element Solver with FP21-32-64 Computation Using OpenACC,” In Proceedings of Sixth Workshop on Accelerator Programming Using Directives (WACCPD), IEEE, 2019. (accepted)

## Licence
FP21SAXPY, version 1.0.0　(c) 2019 Takuma Yamaguchi  
FP21SAXPY is freely distributable under the terms of an MIT-style license.
