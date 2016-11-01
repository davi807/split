/**
Գաղտնավանկի «ը»
*/

#include "filters.h"

upstring h8 = nls;

unsigned char hidden_8(upstring *str){
    static char addr[256];
    unsigned int count = 0,
                  part_start,
                  part_length,
                  ret=0;
    int i = 0,last=-1;

    if(!h8.length){
        h8 = tpString("ը");
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"word_8");
    }
    //հատուկ բառեր
    filter_ext(addr,str,1,1,&ret);

    upLoop(i,0,str->length){
        if(is_vowel(str->text[i])){
            //բաղաձայների կուտակում սկզբում
            if(last==-1){
                if(i>1){
                    part_start = 0;
                    part_length = i + 1;
                    add_8(str,part_start,part_length);
                }
            }
            else{
                //բաղաձայների կուտակում մեջտեղում
                if(i-last-1>2){
                    part_start = last;
                    part_length = i - last+1;
                    add_8(str,part_start,part_length);
                }
            }
            last = i;
        }
        else{
            if(i==str->length-1){
                //տառերի խմբում չկա ձայնավոր
                if(last==-1){
                    //բոլոր բաղաձայներից հետո ավելացնել «ը» տառը
                    for(i=1; i <= str->length; i+=2)
                        upInsert(h8,str,i,1);
                    break;
                }
                //բաղաձայների կուտակում վերջում
                if(i-last>1){
                    part_start = last;
                    part_length = i-last+1;
                    add_8(str,part_start,part_length);
                    break;
                }
            }
        }

    }
    return count;
}

// ավելացնել «ը»
int add_8(upstring *str,unsigned int start,unsigned int length){
    static char init = 0;
    static char addr[256];
    unsigned int  i,j,p=0,except = 0, ret = 1;
    char bgn = (start==0),
        end = (start+length==str->length);
    if(!init){
        strcpy(addr,getenv("list_dir"));
        strcat(addr,"list_8");
        init = 1;
    }
    upstring part = upCopy(*str,start,length);

    except = filter_ext(addr,&part,bgn,end,&ret);
    if(except>0){
        upReset(&part);
        return -1;
    }

    //բառի սկզբի բաղաձայների մեջտեղում գրել «ը», եթե 2֊րդ տառը «յ» չէ
    if(bgn && !(is_vowel(part.text[0]) || is_vowel(part.text[1])) && part.text[1]!=0x575){
        upInsert(h8,&part,1,1);
        p+=2;
    }


    upLoop(i,p,length){
        j = 0;
        if(
            is_vowel(part.text[i]) || //տառը ձայնավոր է
            ( ( i + (++j) < length) && is_vowel(part.text[i+1])) || //հաջորդ տառը ձայանվոր է
            ( ( i + (++j) < length) && is_vowel(part.text[i+2])) || //հաջորդի հաջորդ տառը ձայանվոր է
            ( ( i + (++j) < length) && part.text[i+j]==0x575 && is_vowel(part.text[i+j]) ) //«յ» + ձայնավոր
        ){
            i += j;
            continue;
        }


        if(is_deep(part.text[i])){
            if( ( i + 1 < length) && is_deep(part.text[i+1]) ){
                    upInsert(h8,&part,++i,1);
            }
        }else{
            if( ( i + 1 < length) && is_deep(part.text[i+1]) ){
                    upInsert(h8,&part,++i,1);
            } //անիմաստ կրկնություն
            /** ԻՆՉ֊ՈՐ ԲԱՆ ԿԻՍԱՏ Ա */
        }
    }

    if(part.length != length){
        upDelete(str,start,length);
        upInsert(part,str,start,part.length);
    }
    //printf(" >>");
    //upConsoleWrite(part);
    //printf(" %d : %d \n",bgn,end);

    upReset(&part);
    return 0;
}



