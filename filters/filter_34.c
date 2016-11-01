/**
«ու» հնչյունը գրել «ւ» տառով
*/

#include "filters.h"

void filter_34(upstring *str){
    static char init = 0;
    static upstring u;
    unsigned int i;

    if(!init){
        u = tpString("ու");
        init = 1;
    }

    while((i = upPos(u,*str))!=-1)
        upDelete(str,i,1);
}
