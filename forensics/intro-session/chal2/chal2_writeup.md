# chal2

## Problem

* The executable [code1](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/code1) has some problem and you are getting an error if you try running it. Can you fix the executable and capture the flag?

## Solution

Let us try running the executable and see what we get.
```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: ./code1
bash: ./code1: cannot execute binary file: Exec format error
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: ./code1
bash: ./code1: cannot execute binary file: Exec format error
```

It says, **Exec format error**. So, there is some problem with the file format.

### 0. What is a file format?

We come across various file formats everyday. For images, we see **png**, **jpeg**, **bmp**, For video files, we have **mp4**, **dat**, **mpeg** etc, object file formats - **COFF**, **ELF**, **Mach-O**.

What are these file formats?

First of all, a [file format](https://en.wikipedia.org/wiki/File_format) is a way to encode information in a particular manner.

Let us take 2 examples to understand it better.

#### a. PNG: Portable Network Graphics

[PNG](https://en.wikipedia.org/wiki/Portable_Network_Graphics) is a file format for images. It was designed mainly to transfer images on the internet. Let us take 
![index.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/index.png "index.png").

Let us inspect this file using the **file** command.
```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: file index.png 
index.png: PNG image data, 300 x 150, 8-bit colormap, non-interlaced
```

The following is how it looks when index.png is opened using vim.

![png-file.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/png-file.png "png-file.png")

It is a **binary** file format.

When some random file is given to you, how would you identify what file format it is? 
Every file format has what is known as a **signature**. That signature is unique for a file format. [Wikipedia's list of file signatures](https://en.wikipedia.org/wiki/List_of_file_signatures)

The following is the signature of a PNG file. The first 8 bytes **must** be the following: (Refer wikipedia's list of signatures)
```
89 50 4E 47 0D 0A 1A 0A
```
Open **any** valid png file. The first 8 bytes will be the above 8 bytes. These bytes are also called **magic bytes** or **magic numbers**.

Normal editors like vim are not helpful in editing these binary files. You can use **hexeditor** to do that. You may download it using the following command.
```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: sudo apt-get install ncurses-hexedit
```

This is how it looks like when you open a file with that hexeditor.

![hexeditor-index.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/hexeditor-index.png "hexeditor-index.png"). Observe the first 8 bytes.

### 1. Now, to the challenge

That was an informal introduction to file formats. Now, we'll use what we learnt to solve the challenge.

We know that the file **code1** is an executable, but we are getting a file format error. So, we'll see what the executable format looks like. We are looking at an executable which can be run on Linux.

The file format of executables for linux is the **Executable and Linkable Format** or **ELF**. This is the file format the system understands.

Let us verify this using the **file** command.

```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: file code1
code1: data
```

It just says **data**. For some reason, the **file** format is unable to detect that **code1** is an ELF file. 

Let us write a simple program and use **file** command on the new executable.

```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: cat hello.c
#include <stdio.h>
int main()
{
	printf("Hello World!\n");
	return 0;
}


adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: gcc hello.c -o hello

adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: ./hello
Hello World!

adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: file hello
hello: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, for GNU/Linux 2.6.32, BuildID[sha1]=aae5154ad5715205d8fa932fc65778877ecff942, not stripped
```

Look at the above output. The file command is able to detect that the new executable is **ELF 64-bit LSB executable, ....**.

Let us look at the ELF file's signature (refer to wikipedia's list of signatures).
![elf-magic.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/elf-magic.png "elf-magic.png")

Now, let us open up **code1** with hexeditor.

![code1-hexeditor.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/code1-hexeditor.png "code1-hexeditor.png")

The first 4 bytes here are **7F 62 4C 46**. But, it should be **7F 45 4C 46**. So, the second byte should be changed from **b** to **E** (or **0x62** to **0x45**). Let us change it and save it.

![code1-hexeditor-corrected.png](https://github.com/WebClub-NITK/CTF-League/tree/master/forensics/intro-session/chal2/code1-hexeditor-corrected.png "code1-hexeditor-corrected.png")

Now, let us use **file** command on **code1** again.
```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: file code1
code1: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, for GNU/Linux 2.6.32, BuildID[sha1]=74460a08880e9d93299944771e5b75bcdb6400ea, not stripped
```

Let us try running **code1**.
```
adwi@adwi:~/my_repos/CTF-League/forensics/intro-session/chal2: ./code1
Flag: CTFl{W3lc0m3_1o_f0r3n$ic$}
```

There you go!

## Flag: CTFl{W3lc0m3_1o_f0r3n$ic$}

-----------------------------------------------------

## PS

### 0. Another way to solve it

Look at the strings present in **code1**.

### 1. Executable and Linkable Format (ELF)

ELF is a beautiful file format for executables, libraries, object files for **UNIX-Like** systems. Linux, OpenBSD, FreeBSD ... can understand the ELF file format.

The header file **elf.h** present at ```/usr/include/elf.h``` has the complete specification of ELF. You can also use [this tutorial](https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/) to understand ELF better.
