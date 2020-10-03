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
9. prompt.c : Prepares and asks for the prompt
10. bg.c : Implements the `bg` function
11. fg.c : Implements the `fg` function
12. env.c : Implements the `setenv` and `unsetenv` function
13. jobs.c : Implements the `jobs` function
14. kjob.c : Implements the `kjob` function
15. list.c : Contains the structs for Nodes and Processes
16. overkill.c : Implements the `overkill` function
17. sighandle.c : Contains code for signal handling

# Additional features
1. Supports background processes
2. Supports Ctrl + C and Ctrl + D functionality

# Steps to run the shell:
1. Type `make`.
2. Then type `./dash` to run the shell.
3. Type `quit` to exit the shell. You can also press Ctrl + D to quit the shell.