#ifndef FILTERS_H
#define FILTERS_H

#include "../upstring/upstring.h"

char filter_list(char *addr, upstring *str);
unsigned int filter_ext(char *addr, upstring *str,char is_begin, char is_end,unsigned int *ret);
unsigned char is_vowel(unsigned short _char_);
unsigned char is_deep(unsigned short cr);


//ձայնավորներ
void filter_ev(upstring *str);
void filter_5_7(upstring *crt,upstring *prev);
void filter_34(upstring *str);
void filter_24_o(upstring *str);
unsigned char hidden_8(upstring *str);
int add_8(upstring *str,unsigned int start,unsigned int length);

//բաղաձայներ
void filter_2_26_35(upstring *str);
void filter_3_15_36(upstring *str);
void filter_4_9_31(upstring *str);
void filter_13_18(upstring *str);
void filter_14_17_33(upstring *str);
void filter_19_25_27(upstring *str);
void filter_21(upstring *str);
void filter_28_32__30_f__16(upstring *str);
#endif
