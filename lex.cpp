#include <stdio.h>
#include "lex.h"
static Token lookahead = UNKNOWN;
static char buffer[MAXLEN];

