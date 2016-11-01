#ifndef MKRAT_H
#define MKRAT_H

#include "upstring/upstring.h"
#include "filters/filters.h"

typedef struct word word;
struct word{
    upstring word;
    upstring *syllables;
    unsigned int start;
    unsigned int length;
    unsigned char countSyllebles;
    unsigned char space;
    unsigned char Intonation;
};


void toLowerCase(upstring *);
void cleanText(upstring *);
unsigned int getWord(upstring source, unsigned int start, unsigned int *wordStart);
char filter(upstring *str,upstring *prev);
char has_letter(upstring *str, unsigned short a, unsigned short b, unsigned short c);
upstring *split(upstring str,unsigned int *n);
#endif
