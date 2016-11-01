/**
Եթե «և» տառից առաջ գրված է ձայնավոր
կարդացվում է «յէվ»,
բաղաձայնի դեպքում «էվ»։
*/

#include "filters.h"

void filter_ev(upstring *str){
    static unsigned char init = 0;
    static upstring EV;
    static upstring _EV;
    static upstring ev;
    static upstring yev;
    unsigned int i;

    if(!init){
        EV =  tpString("և");
        _EV = tpString("եւ");
        ev =  tpString("եվ");
        yev = tpString("յեվ");
        init = 1;
    }

    while((i = upPos(_EV,*str))!=-1){
        upDelete(str,i,2);
        if( i==0 || is_vowel(str->text[i-1]) )
            upInsert(yev,str,i,3);
        else
            upInsert(ev,str,i,2);
    }

    while((i = upPos(EV,*str))!=-1){
        upDelete(str,i,1);
        if( i==0 || is_vowel(str->text[i-1]) )
            upInsert(yev,str,i,3);
        else
            upInsert(ev,str,i,2);
    }
}
