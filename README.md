# lspp

lspp is a CLI tool for viewing directory contents and analyzing file sizes 

## Features
- Cross-platform
- Standalone & portable
- Lightweight
- Flexible sorting
- Recursive file size analysis

## Supported on...
- ✅ Windows x64
- ✅ Windows x32
- ✅ Linux x64
- ✅ Linux ARM64
- ✅ Android ARM64

(if your system isn't listed here, you can try [building yourself](#self-build))

## Tested on...
- Windows 10 x64
- Windows 11 x64
- Debian Linux x64
- Debian Linux ARM64
- Oxygen OS Android ARM64 (via Termux)

## Installation
No installation required.
Simply download the latest version of `lspp`, unzip it with any program you want and you're good to go!

## Usage Examples
### Sorting by size

Measures recursively and sorts by total size:
```bash
$ lspp -Rs
] .vs                           16/08/2026      346 MB
] out                           23/12/2025      76.5 MB
] .git                          16/08/2026      158 KB
] src                           19/06/2026      8.01 KB
] include                       05/03/2026      5.97 KB
] media                         16/08/2026      1.90 KB
. CMakePresets.json             31/07/2026      1.40 KB
. README.md                     25/03/2026      991 B
. CMakeLists.txt                31/07/2026      556 B
. .gitignore                    23/12/2025      10.0 B

423 MB total by 10 entries.
```
### Sorting by name
Case sensitive sorting by name:
```bash
$ lspp -c
] A                             16/08/2026      0 B
] B                             16/08/2026      0 B
] b1                            16/08/2026      0 B
] C                             16/08/2026      0 B
] D                             16/08/2026      0 B
```
Case insensitive sorting by name (default):
```
$ lspp -i
] A                             16/08/2026      0 B
] B                             16/08/2026      0 B
] C                             16/08/2026      0 B
] D                             16/08/2026      0 B
] b1                            16/08/2026      0 B
```

## Arguments
Long options use a double dash (`--`), while short options use a single dash (`-`). Shortened versions can be combined into a single argument (e.g., `-rf` is equivalent to `-r -f`).

Reverse sorting order  
`-r` \
`--reversed`

Sort entries by name (case-sensitive)  
`-c` \
`--by-name-cs`

Sort entries by name (case-insensitive)  
`-i` \
`--by-name-ci`

Sort entries by file size  
`-s` \
`--by-size`

Disable size measurement  
`-m` \
`--no-measure` 

Measure directory sizes recursively  
`-R` \
`--recursive`

Show files before directories  
`-f` \
`--file-first`

Show directories before files  
`-d` \
`--dir-first`

Do not prioritize files or directories  
`-p` \
`--no-priority`

# Self Build
`lspp` relies only on standard C++ features, `CMake`, and `utf8proc` making it buildable on virtually any environment with a modern C++ compiler. If your OS isn't listed in `Supported on...`, you can try building `lspp` yourself.
All you need is: 
- CMake 3.20 or higher
- A C++ compiler (clang, MSVC, etc.)

## Steps to build
1. Clone the repository
2. Configure with CMake
`cmake -B build -DCMAKE_BUILD_TYPE=Release`
3. Build the binary
`cmake --build build --config Release`

You're done! 
