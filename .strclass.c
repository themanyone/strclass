//usr/local/bin/anch -std=c99 -L. -keep -run "$0" "$@" ; exit
#include "strclass.h"

/* Dynamic strings with reference counting */
/* static, internal methods */

/* prepare a new line on the pad for writing */
/* todo: add list accessor functions */
static void prepare_line (hk_scratchpad *line_in) {
    hk_scratchpad new_line;
    TRY (new_line = malloc(sizeof(hk_scratchpad)));
    new_line->next = *line_in;
    *line_in = new_line;
}
/* get line from scratchpad */
/* so we can reallocate its mem */
static hk_scratchpad get_line (hk_scratchpad line_in, void *line) {
    hk_scratchpad tmp = line_in;
    while (tmp) {
        if (tmp->mem == line) {
            return tmp;
        } tmp = tmp->next;
    } return NULL;
}
/* external methods */
/* safer malloc */
void *hk_malloc (hk_scratchpad *line_in, size_t sz) {
    prepare_line (line_in);
    TRY ((*line_in)->mem = malloc (sz));
    return (*line_in)->mem;
}
/* safe reallocate with wrap mem */
void *hk_realloc (hk_scratchpad *line_in, void *line, size_t sz) {
    hk_scratchpad got_line = get_line (*line_in, line);
    if (got_line) {
        TRY (got_line->mem = realloc (line, sz));
        return got_line->mem;
    } else return hk_malloc (line_in, sz);
}
/* duplicate string */
char *hk_strdup (hk_scratchpad *line_in, char *in) {
    return strcpy (hk_malloc(line_in, strlen(in)+1), in);
}
/* duplicate string with length */
char *hk_strndup (hk_scratchpad *line_in,char *in, size_t len) {
    char *dest = strncpy (hk_malloc(line_in, len + 1), in, len);
    dest[len] = '\0';
    return dest;
}
/* strcat */
char *hk_strcat (hk_scratchpad *line_in, char *dest, char *source) {
    size_t len = strlen(source) + strlen(dest) + 1;
    dest = hk_realloc (line_in, dest, len);
    return strcat (dest, source);
}
/* strncat */
char *hk_strncat (hk_scratchpad *line_in, char *dest, char *source, size_t sz) {
    size_t len=strlen(source)+ sz + 1;
    dest = hk_realloc (line_in, dest, len);
    return strncat (dest, source, sz);
}
/* free memory used by our routines */
void hk_cleanup (hk_scratchpad *line_in) {
    hk_scratchpad x,tmp = *line_in;
    while ((x = tmp)) {
        if (x->mem) {
            free (x->mem);
            x->mem = NULL;
        } tmp = tmp->next;
        free (x);
        x = NULL;
}   }
/* print list, assuming it contains strings ;0) */
void hk_print (hk_scratchpad *line_in) {
    hk_scratchpad tmp = *line_in;
    while ((tmp)) {
        printf ("%s\n",(char*)tmp->mem);
        tmp = tmp->next;
}   } 