# 5327K's implementation of Pure Pursuit

## Requirements
This was made and tested on `Ubuntu 20.04` on `wsl2`, with `GCC-9.4.0` and `C++17`.

## Usage
**NOTE**: When developing, make sure `./include` contains all necessary PROS API files. To get the files for development, do the following:
1. Use the [`pros-cli`](https://pros.cs.purdue.edu/v5/getting-started/) to create a new temporary project (`pros conductor new-project tmp`), unless you already have a PROS project with the necessary files.
2. Copy and paste all files under `/include` into the folder where you downloaded this repository.
3. Delete the `tmp` folder if you want.

To run (while testing; if you are uploading to the robot, you should copy this into an actual PROS project and use the PROS cli instead), you can run this command (or something similar):
```bash
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
- [FRC Team 1712's Paper on Pure Pursuit](https://www.chiefdelphi.com/uploads/default/original/3X/b/e/be0e06de00e07db66f97686505c3f4dde2e332dc.pdf) (from [this forum post](https://www.chiefdelphi.com/t/paper-implementation-of-the-adaptive-pure-pursuit-controller/166552)), a copy of which can be found [in this repository](paper.pdf).
- [FRC Team 3256's implementation in Java (of the above paper)](https://github.com/Team3256/warriorlib/tree/master/src/main/java/frc/team3256/warriorlib/auto/purepursuit).
- [The PROS v5 API Documentation](https://pros.cs.purdue.edu/v5/index.html).
