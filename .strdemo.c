//usr/local/bin/anch -std=c99 -L. -lstrclass  -keep -run "$0" "$@" ; exit 0
//make shared
/* strdemo.c * * * * * * * * * * * * * * * * * * * * * * * * * * *  * \
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
#include "strclass.h"
int main (int argc, char **argv) {
    hk_scratchpad pad1 = NULL, pad2 = NULL;
    printf ("Start test:\n\n");
    char *p1, *p2;
    p1 = hk_substr (&pad1,"Travis"+1, 3);
    printf ("hk_substr  \"Travis\"+1, 3 = \"%s\"\n",p1);
    p2 = hk_strncat (&pad1, p1, "e party eek.", 7);
    printf ("hk_strncat \"e party time\", 7 = \"%s\"\n",p2);
    p2 = hk_strdup (&pad1, "mojo football");
    printf ("\npad1: \n");
    hk_print (&pad1);
    p1 = hk_strndup (&pad2, p2, 7);
    printf ("hk_strndup s, 7 = \"%s\"\n",p1);
    
    /* free the memory for further use */
    hk_cleanup (&pad1);
    hk_cleanup (&pad2);
    return 0;
} 