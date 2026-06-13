# File2.H

simplay it convert any file to a .H header, it creat a static const char* string contining all the data from the file that i use for shaders


### How to Compile it?
first comile it with
``` bash
make
```
and then you will have f2h good to go, and to use it

if you in linux / macos / BSD and you want to install to your /bin/, run
``` bash
make install
```
### How to use it?
```bash 
f2h main.c main.h main_string #this creat a main.h with in a main_string string contine all the data of main.c as a string
```
so the layout is
``` bash
f2h [tragetFile] [HaderFile(the one that the data will save to)] [MatrixName] -option1 -option2 ...
```
if you want to save as a matrix, add -m  (or --matrix )to the end, and it will creat a char matrix for you;

if you want to use a exsist header file and appen the matrix to it add -a (or --append) to the end.
