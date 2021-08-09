## to_ASCII-converter

### Introduction
This is a **.bmp** to **.txt** (ascii art) format converter, written on C programming language. 

---

Here is an example, of how does it work.
Source **eagle.bmp** image:

![Alt text](_readme/eagle.jpg "Optional title")

And coverted to ascii result:

![Alt text](_readme/ascii.png "Optional title")

Image, that will converted to ascii should
has a small size, because of it will be a lot of chars in document.

### Installation (Windows)

- #### Step 1 - clone repository
First of all you need to clone repository. The following command to do it:

    git clone https://github.com/Nikita-bunikido/to_ASCII-converter.git

- #### Step 2 - open .exe file
In repository you need to find file "toascii.exe",  and run it.

If you have a **32-digits OS** you should to
compile it. Following command to compile in
terminal:

    gcc toascii.c -o "C:\Windows\System32\toascii"

**Why compiling to System32?**
If you compile it into ```System32``` folder, you can run program in any directory.

If you haven't ```gcc``` compiler you can download installer [here](http://www.equation.com/servlet/equation.cmd?fa=fortran).

### Usage
```
usage: toascii [file] [width] [heigth] [path to save]
```

Path to save is not important if you need
to see result in command line.

---

Anyway you need to try some bitmaps
to convert in folder **examples**, and some results
of converting in folder **results**.