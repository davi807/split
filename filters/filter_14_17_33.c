/**
Ձ―Ծ―Ց
*/

#include "filters.h"

void filter_14_17_33(upstring *str){
    static char init = 0;
    static char addr[256];
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_14_17_33");
        init = 1;
    }
    filter_list(addr,str);
}
