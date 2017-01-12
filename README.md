# utst
Simple unit test framework for Unix C programs.

## License

Copyright 2014, 2015 Steven Ford http://geeky-boy.com and licensed
"public domain" style under
[CC0](http://creativecommons.org/publicdomain/zero/1.0/): 
![CC0](https://licensebuttons.net/p/zero/1.0/88x31.png "CC0")

To the extent possible under law, the contributors to this project have
waived all copyright and related or neighboring rights to this work.
In other words, you can use this code for any purpose without any
restrictions.  This work is published from: United States.  The project home
is https://github.com/fordsfords/utst/tree/gh-pages

To contact me, Steve Ford, project owner, you can find my email address
at http://geeky-boy.com.  Can't see it?  Keep looking.

## Introduction

The utst package implements a very simple unit test framework for C programs.
I developed it because [goodletest](https://github.com/google/googletest)
is for C++ but writing C code is my hobby.  Also, googletest is rather
heavy-weight and takes some work to get it working.  Note that utst is
written for Unix-based projects.

Note that this framework assumes that you have source files with testable
units (modules) consisting primarily of callable C functions.  The source
files should *not* contain "main", since utst creates its own "main" to
drive the unit testing.

Also, it should be obvious that utst does not itself test your code.  You
have to write your own self-test code.  The utst framework is simply an
environment that makes it a little easier to write that code.

You can find utst at:

* https://github.com/fordsfords/utst/tree/gh-pages

## Quick Start

If you intend to modify the utst framework itself (fix problems, enhancements),
I suggest you clone the github repo https://github.com/fordsfords/utst

However, if you simply want to use it, you really only need one file: utst.sh

* Enter the commands:

        wget http://fordsfords.github.io/utst/utst.sh
        chmod +x utst.sh

* You can also get a sample module which contains a simple functions
and unit tests for that function.  At the present time, I consider
sample.c to be the "documentation" for the utst package.  If there is
demand for better doc, let me know.

        wget http://fordsfords.github.io/utst/sample.c
        ./utst.sh sample.c

Here's the output:

        INFO: utst, V=1.0
        INFO: Creating utst.h
        INFO: Creating sample.utst
        INFO: compiling sample.c
        INFO: Running sample
        utst: function_name=addtxt_err_tests, num_asserts=2
          PASS
        utst: function_name=addtxt_ok_tests, num_asserts=6
          FAIL: assert 4: UTST_ASSERT failed at sample.c:92 (strcmp(file2, "A.txt") == 0)

Note that there are two test functions, and the second one detects
a problem in the 4th assert.  For your enjoyment, sample.c has a bug
in it.  :-)

Also note that after detecting a failed assertion, the code
continues to execute.  I.e. the 4th assert failed, but it still
ran through 5-6.

## Release Notes

* 1.0 (12-Jan-2017)

    Initial release.
