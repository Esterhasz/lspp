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

## Tested on...
- Windows 10 x64
- Windows 11 x64
- Debian Linux x64
- Debian Linux ARM64
- Android ARM64 (via Termux)

## Installation
No installation required.
Simply download the latest version of `lspp`, unzip it with any program you want and you're good to go!

## Usage Examples
### Sorting by size
```bash
$ lspp -rc -sz
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
```bash
$ lspp -cs
] A                             16/08/2026      0 B
] B                             16/08/2026      0 B
] b1                            16/08/2026      0 B
] C                             16/08/2026      0 B
] D                             16/08/2026      0 B

$ lspp -ci
] A                             16/08/2026      0 B
] B                             16/08/2026      0 B
] C                             16/08/2026      0 B
] D                             16/08/2026      0 B
] b1                            16/08/2026      0 B
```

## Arguments
lspp supports various command-line arguments. Most options also have a short form.

Reverse sorting order  
`-rv` \
`-reversed`

Sort entries by name (case-sensitive)  
`-cs` \
`--by-name-cs`

Sort entries by name (case-insensitive)  
`-ci` \
`--by-name-ci`

Sort entries by file size  
`-sz` \
`--by-size`

Disable size measurement  
`-nm` \
`--no-measure` 

Measure directory sizes recursively  
`-rc` \
`-recursive`

Show files before directories  
`-ff` \
`--file-first`

Show directories before files  
`-df` \
`--dir-first`

Do not prioritize files or directories  
`-np` \
`--no-priority`
