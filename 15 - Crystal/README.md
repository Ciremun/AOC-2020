# Day 15

## Dependencies

[Crystal](https://crystal-lang.org/)  

## Version [WSL]

    Crystal 0.35.1 [5999ae29b] (2020-06-19)

    LLVM: 8.0.0
    Default target: x86_64-unknown-linux-gnu

## Result

    pt.1: 232
    pt.2: 18929178

    $ time
    real    0m8.145s
    user    0m8.407s
    sys     0m0.193s

## Run

    crystal build 15.cr --release
    ./15 2,1,10,11,0,6