/**
վ ֊ֆ
ռ ֊ ր
//մ ֊ ն
հ
*/

#include "filters.h"


/* վ ֊ ֆ + ռ ֊ ր + հ*/
void filter_28_32__30_f__16(upstring *str){
    static char init = 0;
    static char addr[256];
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"f_28_32__30_f__16");
        init = 1;
    }
    filter_list(addr,str);
}
