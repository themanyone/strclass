//usr/bin/chmod -x "$0"; exit
/* strdemo.c * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
*                                                                      * 
* Copyright (C) 2016 by Henry Kroll III, www.thenerdshow.com           * 
*                                                                      * 
* This program is free software: you can redistribute it and/or modify * 
* it under the terms of the GNU General Public License as published by * 
* the Free Software Foundation, either version 3 of the License, or    * 
* (at your option) any later version.                                  * 
*                                                                      * 
* This program is distributed in the hope that it will be useful,      * 
* but WITHOUT ANY WARRANTY; without even the implied warranty of       * 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        * 
* GNU General Public License for more details.                         * 
*                                                                      * 
* You should have received a copy of the GNU General Public License    * 
* along with this program.  If not, see <http://www.gnu.org/licenses/>.* 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef _STRCLASS
#define STRCLASS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _STR(a) #a
#define STR(a) _STR(a)
#define TRY(a) if (!(a)){ \
    perror(__FILE__":"STR(__LINE__));exit(1);}
#define FREE(a) if(a){free(a);a=NULL;}
#define ERR(...) fprintf (stderr, __VA_ARGS__);exit (1)
#define DEBUG 0
#define debug(...) if(DEBUG)fprintf(stderr,__VA_ARGS__)
#define hk_substr hk_strndup
#if defined(_WIN32) || defined(_WIN64) // if windows
#define DLL_EXPORT __declspec(dllexport) // make DLL
#else
#define DLL_EXPORT
#endif
typedef struct line {
    void *mem;
    struct line *next;
} s_line, *hk_scratchpad;

void *_allok (size_t sz);
void *_reallok (void *ptr, size_t sz);
void *allok (hk_scratchpad *mem_store, size_t sz);
void *reallok (hk_scratchpad *mem_store, void *ptr, size_t sz);
char *hk_strdup (hk_scratchpad *mem_store, char *in);
char *hk_strndup (hk_scratchpad *mem_store,char *in, size_t len);
char *hk_strcat (hk_scratchpad *mem_store, char *dest, char *source);
char *hk_strncat (hk_scratchpad *mem_store, char *dest, char *source, size_t sz);
void hk_cleanup (hk_scratchpad *mem_store);
void hk_print (hk_scratchpad *mem_store);
#endif //_STRCLASS
