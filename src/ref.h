#pragma once

#include <regex.h>

#include "intset.h"

#define REF_SEARCH 1
#define REF_EXACT 2
#define REF_EXACT_SET 3
#define REF_RANGE 4
#define REF_RANGE_EXT 5

typedef struct ref {
    int type;
    unsigned int book;
    unsigned int chapter;
    unsigned int chapter_end;
    unsigned int verse;
    unsigned int verse_end;
    intset *verse_set;
    char *search_str;
    regex_t search;
} ref;

ref *
newref();

void
freeref(ref *ref);

int
parseref(ref *ref, const char *ref_str);
