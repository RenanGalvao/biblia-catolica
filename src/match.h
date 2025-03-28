#pragma once

#include "config.h"
#include "ref.h"

typedef struct {
    int start;
    int end;
} range;

typedef struct {
    int current;
    int next_match;
    range matches[2];
} next_data;

int
next_verse(const ref *ref, const config *config, next_data *next);
