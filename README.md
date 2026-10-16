# lspp

A feature-rich CLI tool for directory inspection, metadata analysis, and customizable output.

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
- Debian Linux x64 (WSL)
- Debian Linux ARM64
- Oxygen OS Android ARM64 (via Termux)

## Installation
No installation required.
Simply download the latest version of `lspp`, unzip it with any program you want and you're good to go! \
Don't forget to add the executable file to your PATH so that you can run it from anywhere.

## Usage Examples
### Show directory contents
Shows what is in directory. Doesn't measure directories' size.

```bash
$ lspp
 1 ] .git
 2 ] .lib
 3 ] .vs
 4 ] include
 5 ] out
 6 ] src
 7 ] tests
 8 . .gitignore                  10    B
 9 . CMakeLists.txt              612   B
10 . CMakePresets.json           1.40 KB
11 . LICENSE                     1.04 KB
12 . README.md                   4.18 KB
```

### Sorting by size
Measures recursively and sorts by total size.
```bash
$ lspp -Rs
 1 ] .vs                         4.47 GB
 2 ] out                         154  MB
 3 ] .git                        31.6 MB
 4 ] .lib                        2.34 MB
 5 ] src                         11.5 KB
 6 ] include                     11.2 KB
 7 ] tests                       1.27 KB
 8 . README.md                   4.18 KB
 9 . CMakePresets.json           1.40 KB
10 . LICENSE                     1.04 KB
11 . CMakeLists.txt              612   B
12 . .gitignore                  10    B
```
### Sorting by name
Case sensitive sorting by name.
```bash
$ lspp -c
1 ] A
2 ] B
3 ] b1
4 ] C
5 ] D
```
Case insensitive sorting by name (default).
```
$ lspp -i
1 ] A
2 ] B
3 ] C
4 ] D
5 ] b1
```
## Arguments

Long options use a double dash (`--`), while short options use a single dash (`-`). Short options can be combined into a single argument (e.g., `-rf` is equivalent to `-r -f`).

| Long option | Short option | Description |
|---|---|---|
| `--reversed` | `-r` | Reverse sorting order |
| `--by-name-cs` | `-c` | Sort entries by name (case-sensitive) |
| `--by-name-ci` | `-i` | Sort entries by name (case-insensitive) |
| `--by-size` | `-s` | Sort entries by file size |
| `--by-time` | `-t` | Sort entries by last modification time |
| `--no-measure` | `-m` | Disable size measurement |
| `--recursive` | `-R` | Measure directory sizes recursively |
| `--file-first` | `-f` | Show files before directories |
| `--dir-first` | `-d` | Show directories before files |
| `--no-priority` | `-p` | Do not prioritize files or directories |

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
