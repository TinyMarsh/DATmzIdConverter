# DATmzIdConverter
Calling on Mascot's export_dat_2.pl script. Specific to PC lab directory structure.

Compilation tested on gcc version 6.2.0 (x86_64-posix-seh-rev1, Built by MinGW-W64 project);

`> g++ converter.cpp -o converter.exe -m64 -lcomdlg32 -static-libstdc++ -static-libgcc -static -lpthread`

Execultable can be run anywhere since paths to necessary perl scripts are absolute. Paths to DAT files are fetched through window dialogue. mzid files will be output in the same directory as executable.
