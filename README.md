# 5327K's implementation of Pure Pursuit

## Requirements
This was made and tested on `Ubuntu 20.04` on `wsl2`. 
- C++17

## Usage
**NOTE**: When developing, make sure ./include contains all necessary PROS API files.

To run (while testing; if you are uploading to the robot, you probably use the PROS cli instead), you can run this command (or something similar):
```bash
# cd ./src/gui
g++ *.cpp *.h -std=c++17 -O2 -I../include -o main
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
