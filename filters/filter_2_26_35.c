/**
Բ Պ Փ
*/

#include "filters.h"

void filter_2_26_35(upstring *str){
    static char init = 0;
    static char addr[256];
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_2_26_35");
        init = 1;
    }
    filter_list(addr,str);
}
