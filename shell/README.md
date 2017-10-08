# Shell Lab

The purpose of this lab is to create a shell that uses my tokenizer and the
system calls fork(), execve(), and wait() to create child processes and run
commands. If the absolute path is not specified, the shell will use the
PATH environment to find it. If the path of the command is not found, the shell will print "Command not found.", or it will print the exit code number if the command fails. This shell successfully performs pipes, cd, and simple commands. I was not able to implement the background tasks without causing the entire shell to crash, so I left out the implementation of that requirement.

This directory contains the following files:
* test.c - This file contains main() and uses fork(), execve(), and wait().
* mytoc.c- This file contains my tokenizer.
* mytoc.h - This is the header file for mytoc.c.
* helpFuncts.c - This file contains helper functions for test.c and a few string functions.
* helpFuncts.h - This is the header file for helpFuncts.h.

To compile:
~~~
$ make test
~~~
To run:
~~~
$ ./test
~~~
To exit program:
~~~
$ exit
~~~
To delete binaries:
~~~
$ make clean
~~~

## Help I Recieved:
* For my isExit() function, I received help from the strcmp() function example in
page 106 of the K&R textbook, but I modified it so that it only compares to check
if "exit" is the input.
* For my getString() function, I used most of the code from the gets_n() function
that I put in my Arch1 binary search tree lab from Fall 2016.
* I used the same format of if-statements that is shown in Figure 5.3 in Chapter 5 of Three Easy
Pieces to create processes and differentiate between the child and parent process.
* For the write() system call, I received help and I used the same if-statement
format from the following URL: www.codewiki.wikidot.com/c:system-calls:write
* For the wait() system call, I received some help on how to get the exit code using wait() from the following URL: www.geeksforgeeks.org/wait-system-call-c/
* I used a few of the shell demos labs that were given to us as a guide to using pipe(), dup(), and dup2().