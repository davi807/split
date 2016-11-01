/**
Ջ―Ճ―Չ մի քանի բառ
*/

#include "filters.h"

void filter_19_25_27(upstring *str){
    static char init = 0;
    static char addr[256];
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_19_25_27");
        init = 1;
    }
    filter_list(addr,str);
}
