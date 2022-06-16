# 5327K's implementation of Pure Pursuit

## Requirements
This was made and tested on `Ubuntu 20.04` on `wsl2`. 
- C++20 support, specifically [support for `constexpr std::vector`s](https://en.cppreference.com/w/cpp/compiler_support) (scroll down to `constexpr std::vector`). We used GNU GCC v12 for this.
  - As of the time this was written, `g++12` is not available on Ubuntu. To install it, you can follow [this tutorial](https://www.youtube.com/watch?v=TCcUa1FPU80). Note that building takes *a long time*.
- Python header files (for [`matplotlib-cpp`](https://github.com/lava/matplotlib-cpp)) - we used Python 3.8.
  - To install these, you can use the `python3.8-dev` package on Ubuntu (`sudo apt install python3.8-dev`).
  - Note that this is only for testing and for viewing paths on matplotlib.

## Usage

To run (while testing; if you are uploading to the robot, you probably use the PROS cli instead), you can run this command (or something similar):
```bash
# cd ./src
/path/to/gcc-12/installation/bin/g++ *.cpp *.h -std=c++20 -O2 -I/usr/include/python3.8 -lpython3.8 -I../include -o main
./main
```

I personally used Visual Studio Code's extension, [Code Runner](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner), with this in `settings.json`:
```json
{
  "code-runner.executorMap": {
    "cpp": "cd $dir && ~/gcc-12/bin/g++ *.cpp *.h -std=c++20 -O2 -o main -lsfml-graphics -lsfml-window -lsfml-system && ./main; echo",
  },
}
```


## Resources Used
- [FRC Team 1712's Paper on Pure Pursuit](https://www.chiefdelphi.com/uploads/default/original/3X/b/e/be0e06de00e07db66f97686505c3f4dde2e332dc.pdf) (from [this forum post](https://www.chiefdelphi.com/t/paper-implementation-of-the-adaptive-pure-pursuit-controller/166552))
- [FRC Team 3256's implementation in Java (of the above paper)](https://github.com/Team3256/warriorlib/tree/master/src/main/java/frc/team3256/warriorlib/auto/purepursuit)
