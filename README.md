# strclass
Dynamic strings with reference counting

Requires: Anchor `https://github.com/themanyone/anch`

##Build:
`make shared`

##Test:
`./strdemo`

##Usage:

Initialize new pad. To save memory, this may be done at the start of a loop.

`hk_scratchpad pad_ptr = NULL;`

hk_ functions

Functions in this library start with `hk_` prefix. See `strclass.def` for a full list of exported functions. The convention is to pass a reference to `pad_ptr` as the first argument.
Example:

`char * hk_substr(&pad_ptr, char* string, int start, int length);`

Return value: Most hk_ functions return a `char*` from `malloc()`. This string would ordinarily need to be `free()`'d, but the `pad_ptr` reference counter keeps track of every memory allocation. Running `hk_cleanup (&pad_ptr)` cleans up all the strings allocated to that pad.

```
char *p1 = hk_substr (&pad_ptr,"Travis"+1, 3); // p1 = "rav"
char *p2 = hk_strncat (&pad_ptr, p1, "e party week.", 7); // p2 = "rave party"
```

It is OK to reassign pointers; `pad_ptr` hasn't forgotten the old memory.

`char *p2 = hk_strdup (&pad_ptr, "This is a test"); // p2 = "This is a test"`

Use `hk_print(&pad_ptr);` to debug or print out contents of pad.

`hk_print (&pad_ptr); // Prints "rave party" and "This is a test".`

`hk_cleanup (&pad_ptr); // Free up this pad.`

To save memory, `hk_cleanup()` may be run at the end of a loop to clear the pad for each iteration.
