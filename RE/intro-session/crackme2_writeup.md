# crackme2

**NOTE**: This was not meant to be a intro-level challenge.

## Problem

Given the executable [crackme2](https://github.com/WebClub-NITK/CTF-League/blob/master/RE/intro-session/crackme2), find the flag.

## Solution

Let us run the executable.
```
adwi@adwi:~/ALL/CTF-League/CTF-League/RE/intro-session: ./crackme2
Enter the password: owihfowiehfowiehf
Try again!
adwi@adwi:~/ALL/CTF-League/CTF-League/RE/intro-session: ./crackme2
Enter the password: weoifhwoeifhwef
Try again!
adwi@adwi:~/ALL/CTF-League/CTF-League/RE/intro-session: ./crackme2
Enter the password: adwaithismyname
Try again!
```

Simple. We need to get that password!

### 0. Strings

Let us get the strings inside **crackme2** and go through them, see if we get any clue.
```
/lib64/ld-linux-x86-64.so.2
libc.so.6
__isoc99_scanf
puts
__stack_chk_fail
printf
__libc_start_main
__gmon_start__
GLIBC_2.7
GLIBC_2.4
GLIBC_2.2.5
UH-P
AWAVA
AUATL
[]A\A]A^A_
Enter the password:
You got access!
Try again!
;*3$"
GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010
```
* These are interesting.
```
Enter the password:
You got access!
Try again!
```
* But they don't tell anything about the password.

At this point, we need to level up our analysis.

### 1. Assembly code

When a C/C++ program is compiled, it is first converted into what is called as **Assembly code**. This code is specific to the underlying processor architecture. There are various architectures - x86(intel 32-bit), x64(intel 64-bit), arm, arm64 etc.,

This Assembly code is then converted to machine code(**0**s & **1**s). So, the executables (in our case **crackme2**) has the machine code of the C program.

We can get back assembly code from the underlying machine code. To do this, we'll use a tool called **objdump**.
```
adwi@adwi:~/CTF-League/RE/intro-session: objdump -Mintel -d crackme2 | grep "<main>" -A36
0000000000400646 <main>:
  400646:	55                   	push   rbp
  400647:	48 89 e5             	mov    rbp,rsp
  40064a:	48 83 ec 10          	sub    rsp,0x10
  40064e:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
  400655:	00 00 
  400657:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
  40065b:	31 c0                	xor    eax,eax
  40065d:	c7 45 f4 ef be ad de 	mov    DWORD PTR [rbp-0xc],0xdeadbeef
  400664:	bf 54 07 40 00       	mov    edi,0x400754
  400669:	b8 00 00 00 00       	mov    eax,0x0
  40066e:	e8 9d fe ff ff       	call   400510 <printf@plt>
  400673:	48 8d 45 f0          	lea    rax,[rbp-0x10]
  400677:	48 89 c6             	mov    rsi,rax
  40067a:	bf 69 07 40 00       	mov    edi,0x400769
  40067f:	b8 00 00 00 00       	mov    eax,0x0
  400684:	e8 a7 fe ff ff       	call   400530 <__isoc99_scanf@plt>
  400689:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
  40068c:	3b 45 f4             	cmp    eax,DWORD PTR [rbp-0xc]
  40068f:	75 0c                	jne    40069d <main+0x57>
  400691:	bf 6c 07 40 00       	mov    edi,0x40076c
  400696:	e8 55 fe ff ff       	call   4004f0 <puts@plt>
  40069b:	eb 0a                	jmp    4006a7 <main+0x61>
  40069d:	bf 7c 07 40 00       	mov    edi,0x40077c
  4006a2:	e8 49 fe ff ff       	call   4004f0 <puts@plt>
  4006a7:	b8 00 00 00 00       	mov    eax,0x0
  4006ac:	48 8b 55 f8          	mov    rdx,QWORD PTR [rbp-0x8]
  4006b0:	64 48 33 14 25 28 00 	xor    rdx,QWORD PTR fs:0x28
  4006b7:	00 00 
  4006b9:	74 05                	je     4006c0 <main+0x7a>
  4006bb:	e8 40 fe ff ff       	call   400500 <__stack_chk_fail@plt>
  4006c0:	c9                   	leave  
  4006c1:	c3                   	ret    
  4006c2:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  4006c9:	00 00 00 
  4006cc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

```

Don't get scared :P. Looking at assembly code for the first time might be overwhelming, but once we start understanding it, it'll be easy.

Again, let us do our first line of analysis. Let us see if there are any peculiar strings, numbers used inside the **main** function - which can be the password. There are so many numbers there. Let us list a few of them.
```
0x10
0xdeadbeef
0x400754
0x400769
0x40076c
0x40077c
```

* The second number looks very interesting. Note that it is a hexadecimal number, but it also looks like the string **deadbeef**. Let us try these numbers as passwords. These are in hexadecimal form. Let us convert to decimal and try. When it comes to tasks like these, **python** is the best.
```python
adwi@adwi:~/CTF-League/RE/intro-session: python3
Python 3.5.2 (default, Oct  8 2019, 13:06:37) 
[GCC 5.4.0 20160609] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 0x10
16
>>> 
>>> 0xdeadbeef
3735928559
>>> 
>>> 0x400754
4196180
>>> 
>>> 0x400769
4196201
>>> 
>>> 0x40076c
4196204
>>> 
>>> 0x40077c
4196220
>>> 
```

Now, let us run the crackme with these numbers as inputs.
```
adwi@adwi:~/CTF-League/RE/intro-session: ./crackme2
Enter the password: 16
Try again!
adwi@adwi:~/CTF-League/RE/intro-session: ./crackme2
Enter the password: 3735928559
You got access!
```

And you got it!

## Flag: 0xdeadbeef

--------------------------------------------------

## A few interesting things

### 1. Assembly

We looked at assembly code in this challenge. Understanding Assembly code is a very essential skill for Reverse Engineering. 

You can get started with Intel's assembly programming from [here](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html) & [here](https://www.pwnthebox.net/reverse/engineering/and/binary/exploitation/series/2018/08/12/introduction-to-x86-assembly-programming.html).