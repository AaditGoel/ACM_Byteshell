# ACM_Byteshell 
![image](https://github.com/AaditGoel/ACM_Byteshell/assets/101339161/21fc40d3-8e1e-44c2-b6b8-e787010267b0)


The project aims to build a simple shell using C language.In this project I have used VS code to write my code by connecting it WSL and used the GCC to compile and run it.You can connect it by installing the WSL extension in your VS code.

## What I learned in this project

* **Basic C language**
* **Using WSL and ubuntu via VS code**
* **Working of a shell which includes: Reading,Parsing and its execution**
* **Various builtin commands that can be launched in the shell like history,cd etc**

## Function and System calls

* ```chdir``` (man 2 chdir)
* ```exit``` (man 3 exit)
* ```fork``` (man 2 fork)
* ```free``` (man 3 free)
* ```getline``` (man 3 getline)
* ```malloc``` (man 3 malloc)
* ```realloc```
* ```perror``` (man 3 perror)
* ```strtok``` (man 3 strtok)
* ```waitpid``` (man 2 waitpid)
*  ```atoi```
## Builtin Commands I implemented

* ```cd``` : Function used to navigate and change the working directory
* ```help``` : Function used to get information regarding a built-in shell command 
* ```exit``` : terminates your script
* ```env``` : Function used to display the environment variables

## References
* ACM's session ppt
* [https://brennan.io/2015/01/16/write-a-shell-in-c/](https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html)
