# File2.H

simplay it convert any file to a .H header, it creat a const char* strinf contining all the data from the file that i use for shaders


### How to use it?
first comile it with
``` bash
gcc main.c -o f2h #try g++ if it dosnt work
```
and then you will have f2h good to go, and to use it

```bash 
f2g main.c main.h main_string #this creat a main.h with in a main_string string contine all the data of main.c as a string
```
if you want to save as a matrix, add -m to the end, and it will creat a char matrix for you;
