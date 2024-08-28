# Lab 5

## student name
Logan Tucker
## grader name
Henry Kim

Recall the [Assignment](https://www.cs.dartmouth.edu/~tjp/cs50/labs/lab5/).

**Total: 61/100 points**

## (10) Overall

5/10 points:

* -3 failed SUBMIT5 branch check
* Tip: include a .gitignore for common so that you don't accidentally commit executables or object files
* -2 failed check for executables and object files

## (10) Makefiles

10/10 points:

* 

## (10) Documentation

2/10 points:

* -1 should describe how `indexBuild` was implemented
* -1 should describe how most of the index.c methods were implemented as wrappers for the hashtable module
* -1 should describe how `index_load` was implemented
* -1 should describe the new methods in `pagedir.c`
* -1 should describe the new methods in `word.c`
* -1 failed top-level README username check
* -2 failed indexer testing.sh and testing.out

## (10) Testing

8/10 points:

* -2 does not test with wikipedia or toscrape
* Use constants for repeated values and paths

## (20) Coding Style

18/20 points:

* -2 excessively nested code: use a helper function if you go more than 3 or 4 levels of indentation
* Combine nested `if` statements onto one line using `&&` to reduce overall indentation levels. Also consider using `continue` to reduce indentation
```c
    if (strlen(newWord) > 2){    
        // code here
    }
```

```c
    if (strlen(newWord) < 3){    
        continue
    }
    // code here
```

## (30) Functionality

10/30 points:

* -20 indexes do not produce the correct output

## (10) Memory leaks, according to valgrind

8/10 points:
* -2 still reachable memory
```
==1985879== Command: ./indexer /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-5 index.txt
==1985879== 
==1985879== 
==1985879== HEAP SUMMARY:
==1985879==     in use at exit: 4,720 bytes in 10 blocks
==1985879==   total heap usage: 2,384 allocs, 2,374 frees, 337,912 bytes allocated
==1985879== 
==1985879== 472 bytes in 1 blocks are still reachable in loss record 1 of 2
==1985879==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1985879==    by 0x490B6CD: __fopen_internal (iofopen.c:65)
==1985879==    by 0x490B6CD: fopen@@GLIBC_2.2.5 (iofopen.c:86)
==1985879==    by 0x10A4F8: parseArgs (indexer.c:44)
==1985879==    by 0x10A418: main (indexer.c:25)
==1985879== 
==1985879== 4,248 bytes in 9 blocks are still reachable in loss record 2 of 2
==1985879==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1985879==    by 0x490B6CD: __fopen_internal (iofopen.c:65)
==1985879==    by 0x490B6CD: fopen@@GLIBC_2.2.5 (iofopen.c:86)
==1985879==    by 0x10AC5E: pagedir_load (pagedir.c:66)
==1985879==    by 0x10A5BC: indexBuild (indexer.c:61)
==1985879==    by 0x10A424: main (indexer.c:26)
==1985879== 
==1985879== LEAK SUMMARY:
==1985879==    definitely lost: 0 bytes in 0 blocks
==1985879==    indirectly lost: 0 bytes in 0 blocks
==1985879==      possibly lost: 0 bytes in 0 blocks
==1985879==    still reachable: 4,720 bytes in 10 blocks
==1985879==         suppressed: 0 bytes in 0 blocks
==1985879== 
==1985879== For lists of detected and suppressed errors, rerun with: -s
==1985879== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


## Late penalties

