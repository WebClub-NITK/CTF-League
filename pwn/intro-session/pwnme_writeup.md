# pwnme

## Problem

Given a program [pwnme.c](https://github.com/WebClub-NITK/CTF-League/tree/master/pwn/intro-session/pwnme.c) and it's executables ([32-bit](https://github.com/WebClub-NITK/CTF-League/tree/master/pwn/intro-session/pwnme_32) & [64-bit](https://github.com/WebClub-NITK/CTF-League/tree/master/pwn/intro-session/pwnme_64)), we need to get a shell by exploiting a vulnerability present in the program.

## Solution

If these executables are not working for some reason, you can compile [pwnme.c](https://github.com/WebClub-NITK/CTF-League/tree/master/
pwn/intro-session/pwnme.c) to get them.
```
$ gcc pwnme.c -o pwnme
```

### 0. Understanding the program well

We have the sourcecode of the program with us. Let us go through it and get a clear picture of what the program is doing.
```c
adwi@adwi:~/CTF-League/pwn/intro-session: cat pwnme.c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sigsegv_handler(int sig)
{
	printf("You got a shell!!\n");
	fflush(stdout);

	system("/bin/sh");
}

void vuln()
{
	char buf[16];
	printf("Enter any string you want!");
	fflush(stdout);

	gets(buf);
	fflush(stdin);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegv_handler);

	vuln();

	return 0;
}
```

**1.** Let us start with **main** function. It goes like this.
```c
int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegv_handler);

	vuln();

	return 0;
}
```
* It calls some wierd function **signal** with 2 arguments. At this point, we don't have to worry about this.

* Then it calls the function **vuln()**.

**2.** Understanding **vuln** function.
```c
void vuln()
{
	char buf[16];
	printf("Enter any string you want!");
	fflush(stdout);

	gets(buf);
	fflush(stdin);
}
```
* It initializes a **buffer** of length 16 bytes.
* It prints a string **Enter any string you want!**.
* Then it executes a ```gets(buf)```. Let us see what the function **gets** does.
```
adwi@adwi:~/CTF-League/pwn/intro-session: man gets
GETS(3)                    Linux Programmer's Manual                   GETS(3)

NAME
       gets - get a string from standard input (DEPRECATED)

SYNOPSIS
       #include <stdio.h>

       char *gets(char *s);

DESCRIPTION
       Never use this function.

       gets()  reads  a  line from stdin into the buffer pointed to by s until
       either a terminating newline or EOF, which it replaces with a null byte
       ('\0').  No check for buffer overrun is performed (see BUGS below).

```
* It is used to get a string from standard input, your terminal by default.
* In the description, the first thing we read is **Never use this function.**. This means, there is something problematic with this function, but the author of this program has used it.

* Let us read through the manual page. Look what I found in the **BUGS** section.
```
BUGS
       Never use gets().  Because it is impossible to tell without knowing the
       data  in  advance  how  many  characters  gets() will read, and because
       gets() will continue to store characters past the end of the buffer, it
       is  extremely  dangerous  to  use.   It has been used to break computer
       security.  Use fgets() instead.
```

* And I think we have our culprit. 
* The buffer is **16** bytes in size. Ideally, the input taken from the user should not be more than 16 bytes. Even if the input is more than 16 bytes, it should be cut short to 16 bytes and taken in.
* But **gets** never does any check on the input length. It simply takes whatever you input, irrespective of the length.

### 1. Running the program

I am running a 64-bit Linux OS. So, I'll be running **pwnme_64**. 
```
adwi@adwi:~/CTF-League/pwn/intro-session: ./pwnme_64
Enter any string you want!aodifhwoeif

adwi@adwi:~/CTF-League/pwn/intro-session: ./pwnme_64
Enter any string you want!12345678

adwi@adwi:~/CTF-League/pwn/intro-session: ./pwnme_64
Enter any string you want!lsdifhowiefhwoiefhowiehfowiehfowiefhoweihf
You got a shell!!
$ 
```
* The third input was too long to handle, you got the shell!

### But.. What exactly happened?

At this point, you might have a lot of questions like "What if the input is too long? How does it make the program vulnerable?" etc.,

The vulnerability we just exploited is known as the **Buffer Overflow Vulnerability**. The name suggests what it is. There is a buffer (**buf[16]**). When we gave an input longer than the buffer (or **overflown the buffer**), we ended up getting a shell.

When something like this happens, the program is **killed** by the OS and it is called a **Segmentation fault**. You might have seen this often **Segmentation fault(core dumped)**. 

So, if any error occurs while you are running the program, and the program doesn't know how to handle that error, the OS kills it.

In this challenge, we have written a function **sigsegv_handler** which handles the segmentation fault. That is why the program doesn't crash.
```
void sigsegv_handler(int sig)
{
	printf("You got a shell!!\n");
	fflush(stdout);

	system("/bin/sh");
}
```

This program was a made-up example for you to get a feel of BOF. In reality, there is no handler. The program will just crash. No handler will give a shell automatically.

As the series progresses, we'll discuss BOF in detail, we'll understand what exactly happens and how we can exploit to get a shell (even without such handlers).

We'll also learn about other such deadly vulnerabilities, how they can be exploited to get a shell.












