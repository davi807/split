/**
Դ֊Տ֊Թ մի քանի բառ մի քանի վերջածանց
*/

#include "filters.h"

void filter_4_9_31(upstring *str){
    static char init = 0;
    static char addr[256];
    static upstring wrd;
    static upstring urd;
    static upstring rord;
    static upstring erord;
    unsigned int i;
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_4_9_31");
        wrd = tpString("որդ");
        urd = tpString("ուրդ");
        rord = tpString("րորդ");
        erord = tpString("երորդ");
        init = 1;
    }
    filter_list(addr,str);

    //մի շարք վերջածանցներում «դ»֊ն լսվում է «թ»
    if(
        ( ((i=upPos(erord,*str))>0) && (i+erord.length > str->length-4)) ||
        ( ((i=upPos(rord,*str))>0) && (i+rord.length > str->length-4)) ||
        ( ((i=upPos(urd,*str))>0) && (i+urd.length > str->length-4)) ||
        ( ((i=upPos(wrd,*str))>0) && (i+wrd.length > str->length-4))
    ){
        do{++i;}while(str->text[i]!=0x564);
        str->text[i]=0x569;
    }
}
