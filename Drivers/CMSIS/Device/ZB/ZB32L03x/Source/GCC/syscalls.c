/*********************************************************************
----------------------------------------------------------------------
File    : syscalls.c
Purpose : Reentrant functions for newlib to enable printf.
          printf will write to the SWO Stimulus port 0
          on Cortex-M3/4 targets.
Notes   : SWO Output should work on every Cortex-M. In case of errors
          check the defines for the debug unit.
          __heap_start__ and __heap_end__ have to be defined
          in the linker file.
          printf via Newlib needs about 30KB extra memory space.
--------- END-OF-HEADER --------------------------------------------*/

#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>


/*********************************************************************
* _write_r()
* Purpose
*   Reentrant write function. Outputs the data to Stimulus port 0.
*/
_ssize_t _write_r (struct _reent *r, int file, const void *ptr, size_t len)
{
    return 0;
}

/*********************************************************************
* _sbrk_r()
* Purpose
*   Allocates memory on the heap.
*/
void *_sbrk_r(struct _reent *_s_r, ptrdiff_t nbytes)
{
    return 0;
}

/*********************************************************************
*
*       Function dummies.
*       Return a default value.
*
*/
_ssize_t _read_r(struct _reent *r, int file, void *ptr, size_t len)
{
    return 0;
}

int _close_r(struct _reent *r, int file)
{
    return -1;
}

_off_t _lseek_r(struct _reent *r, int file, _off_t ptr, int dir)
{
    return (_off_t)0;
}

int _fstat_r(struct _reent *r, int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int isatty(int file);
int isatty(int file)
{
    return 1;
}

void _exit (int a)
{
    while(1) {};
}

int _kill (int a, int b)
{
    return 0;
}

int _getpid(int a)
{
    return 0;
}

int _isatty(int file)
{
    return 0;
}

void __attribute__((weak)) _init(void) {}
void __attribute__((weak)) _fini(void) {}

