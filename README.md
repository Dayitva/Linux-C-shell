# C Shell
It's a basic shell written in C.

# File description
1. cd.c : Implements the `cd` function
2. cmdhandle.c : Handles comparison of input string with the functions
3. cwd.c : Implements the `pwd` function
4. echo.c : Implements the `echo` function
5. ls.c : Implements the `ls` function
6. main.c : Wraps all the components together and contains shell loop
7. parse.c : Tokenizes the input string
8. pinfo.c : Implements the `pinfo` function
8. prompt.c : Prepares and asks for the prompt

# Steps to run the shell:
1. Type `make`.
2. Then type `./dash` to run the shell.
3. Type `exit` or `quit` to exit the shell. You can also press Ctrl + C to quit the shell.