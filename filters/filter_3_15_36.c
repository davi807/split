/**
Գ Կ Ք
*/

#include "filters.h"

void filter_3_15_36(upstring *str){
    static char init = 0;
    static char addr[256];
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_3_15_36");
        init = 1;
    }
    filter_list(addr,str);
}
