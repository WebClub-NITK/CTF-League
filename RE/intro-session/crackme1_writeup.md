# crackme1

## Problem

Given the executable [crackme1](https://github.com/WebClub-NITK/CTF-League/blob/master/RE/intro-session/crackme1), find the flag.

## Solution

Let us run the executable and see what it does.
```
adwi@adwi:~/CTF-League/RE/intro-session: ./crackme1
Enter the password: qwerty1234oehrgouerg
Try again!
```

So, it is expecting some sort of password. I think **qwerty1234oehrgouerg** is the wrong password, that is why it asked us to try again.

While solving such *crackme*s, there are various lines of analysis. First line of analysis is the basic analysis, where you see what **strings** are present in the executable, what **functions** are used by the crackme.

Let us go ahead and get the list of all the strings in **crackme1** and put it into a file.
```
adwi@adwi:~/CTF-League/RE/intro-session: strings crackme1 > crackme1.str
```

Let us look into the strings now. The following are the first few strings.
```
/lib64/ld-linux-x86-64.so.2
HW d
libc.so.6
puts
__stack_chk_fail
stdin
printf
fgets
strlen
strcmp
__libc_start_main
__gmon_start__
GLIBC_2.4
GLIBC_2.2.5
UH-`
AWAVA
AUATL
[]A\A]A^A_
CTF{HI_THERE!}
Enter the password:
You win!
Try again!
;*3$"
GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010
crtstuff.c
__JCR_LIST__
deregister_tm_clones
__do_global_dtors_aux
completed.7596
__do_global_dtors_aux_fini_array_entry
frame_dummy
__frame_dummy_init_array_entry
crackme1.c
__FRAME_END__
__JCR_END__
__init_array_end
_DYNAMIC
__init_array_start
__GNU_EH_FRAME_HDR
_GLOBAL_OFFSET_TABLE_
__libc_csu_fini
.
.
.
```

It has a lot of wierd-named strings, whose meaning we don't know yet. Go through the strings and see if you find anything interesting, like the flag :P
```
/lib64/ld-linux-x86-64.so.2
HW d
libc.so.6
puts
__stack_chk_fail
stdin
printf
fgets
strlen
strcmp
__libc_start_main
__gmon_start__
GLIBC_2.4
GLIBC_2.2.5
UH-`
AWAVA
AUATL
[]A\A]A^A_
CTF{HI_THERE!}
```

Look at that, that looks like a flag - **CTF{HI_THERE!}**.

This is a potential flag we have found. Let us run crackme1, input this and see.
```
adwi@adwi:~/CTF-League/RE/intro-session: ./crackme1
Enter the password: CTF{HI_THERE!}
You win!
```

You got it!

This was a simple crackme which had the flag in plaintext form.

## Flag: CTF{HI_THERE!}

----------------------------------------------------
## A few interesting things

### 1. Strings

Strings inside the executable can give a lot of information about the executable - the functions it uses, the libraries it uses and more. So, let us go through **crackme1**'s strings and see what information we can extract.

Let us go through the first set of strings.
```
/lib64/ld-linux-x86-64.so.2
HW d
libc.so.6
puts
__stack_chk_fail
stdin
printf
fgets
strlen
strcmp
__libc_start_main
__gmon_start__
GLIBC_2.4
GLIBC_2.2.5
```

**1.** **/lib64/ld-linux-x86-64.so.2**
	* This is a very interesting piece of software. It is called the **Dynamic Linker**. It helps in running the program. It helps in loading all the libraries(eg: C library, C++ library) necessary for the program to run, prepare the program to run and then run it.
	* To know more about the dynamic linker, you can read it's manual page - ```man ld.so```.

**2.** **libc.so.6**: The C library is named as ```libc```. 


**3.** Next, we have a bunch of strings we know.

```
puts
__stack_chk_fail
stdin
printf
fgets
strlen
strcmp
```

* This lists the functions crackme1 is using - **puts**, **printf**, **fgets**, **strlen**, **strcmp**.

**4.** The strings ```GLIBC_2.4, GLIBC_2.2.5``` mostly depict the compatible C libarary versions. GLibc stands for **GNU C Library**. GNU  is an organization that writes compilers, libraries and more. If you have ever wondered what **gcc** stands for, it stands for **GNU C Compiler**.

**5.** The next set of strings are the ones we encountered while running the program.
```
CTF{HI_THERE!}
Enter the password:
You win!
Try again!
``` 

**6.** The following is an interesting string.
```
GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010
```
* It tells the version of GCC which was used to make the **crackme1** executable. Let us verify it.
```
adwi@adwi:~/ALL/CTF-League/CTF-League/RE/intro-session: gcc --version
gcc (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

After this, there are lot of strings which we can't make sense right now.

Google is an amazing friend. Search for these strings, learn what they are. As we move ahead in the series, we'll understand each of them in good detail.

### 2. Another way to crack this challenge

There might be multiple ways to crack a given challenge. The easiest and straight forward way is the following. We'll use a tool called **ltrace** (or **library call trace**) to get the flag.

In case you don't have ltrace with you, you can install it in the following manner.
```
$ sudo apt-get install ltrace
```

First, let us see what ltrace is, how it can help us.

```
adwi@adwi:~/CTF-League/RE/intro-session: man ltrace
LTRACE(1)                        User Commands                       LTRACE(1)

NAME
       ltrace - A library call tracer
.
.
.
DESCRIPTION
       ltrace is a program that simply runs the  specified  command  until  it
       exits.   It  intercepts and records the dynamic library calls which are
       called by the executed process and the signals which  are  received  by
       that  process.   It  can also intercept and print the system calls exe‐
       cuted by the program.
.
.
```

Let us use it on our program.
```
adwi@adwi:~/CTF-League/RE/intro-session: ltrace ./crackme1
__libc_start_main(0x4006f6, 1, 0x7ffd635c4208, 0x4007a0 <unfinished ...>
printf("Enter the password: ")                   = 20
fgets(Enter the password: woehwoiefh
"woehwoiefh\n", 99, 0x7f36bc75c8e0)        = 0x7ffd635c40b0
strlen("woehwoiefh\n")                           = 11
strcmp("woehwoiefh", "CTF{HI_THERE!}")           = 52
puts("Try again!"Try again!
)                               = 11
+++ exited (status 0) +++
```

Go through the series of C libarary calls made. You can see that **strcmp** function - this is a **string compare** function.
```
strcmp("woehwoiefh", "CTF{HI_THERE!}")           = 52
```
* I entered some string. It is being compared with another string **CTF{HI_THERE!}**. 

Now, let us input this string and see what happens.
```
adwi@adwi:~/CTF-League/RE/intro-session: ltrace ./crackme1
__libc_start_main(0x4006f6, 1, 0x7ffc51135758, 0x4007a0 <unfinished ...>
printf("Enter the password: ")                   = 20
fgets(Enter the password: CTF{HI_THERE!}
"CTF{HI_THERE!}\n", 99, 0x7f8b15e0d8e0)    = 0x7ffc51135600
strlen("CTF{HI_THERE!}\n")                       = 15
strcmp("CTF{HI_THERE!}", "CTF{HI_THERE!}")       = 0
puts("You win!"You win!
)                                 = 9
+++ exited (status 0) +++
```
There you go!