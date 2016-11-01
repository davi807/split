#include "mkrat.h"

//*****Convers to lowercase
void toLowerCase(upstring *str){
    unsigned int i, length = upLength(*str);
    sint current;
    upLoop(i,0,length){
        current = str->text[i];
        if(current>0x530 && current<0x557){ //Aremenian
            str->text[i] = current+48;
        }
        else if(current>0x40 && current<0x5B){ //Latin
            str->text[i] = current+32;
        }
        else if(current>0x409 && current<0x430){ //Cyrillic
            str->text[i] = current+32;
        }
    }
}

//*****Remove non-armenian letters
void cleanText(upstring *str){
    unsigned int i;
    upLoop(i,0,str->length){
        if(str->text[i]<0x561 || str->text[i]>0x587){
            upDelete(str,i,1);
            --i;
        }
    }
}

//*****Read word from stream
unsigned int getWord(upstring source, unsigned int start, unsigned int *wordStart){
    unsigned int i,l;

    //getting start possition
    upLoop(i,start,source.length)
        if( source.text[i]<128 &&
            (
             source.text[i]==32 ||
             source.text[i]=='\n'
            )
          );
        else
            break;
    *wordStart = i;
    //getting end position and length
    l=0;
    upLoop(i,*wordStart,source.length)
        if( source.text[i]<128 &&
            (
             source.text[i]==32 ||
             source.text[i]=='\n'
            )
          )
            break;
         else
            ++l;

    return l;
}

char has_letter(upstring *str, unsigned short a, unsigned short b, unsigned short c){
    short i;

    if(c)
        upLoop(i,0,str->length){
            if(a==str->text[i] || b==str->text[i] || c==str->text[i])
                return 1;
        }
    else if(b)
        upLoop(i,0,str->length){
            if(a==str->text[i] || b==str->text[i])
                return 1;
        }
    else
        upLoop(i,0,str->length){
            if(a==str->text[i])
                return 1;
        }

    return 0;
}

//*****վանկատել
upstring *split(upstring str,unsigned int *n){
    unsigned int i,j,close_until=0,state=0;
    upstring tmp = nls;
    upstring *syl_arr;
    *n = 0;

    if(str.length==0)
        return;

    upLoop(i,0,str.length){
        if(is_vowel(str.text[i]))
            ++(*n);
    }
    syl_arr = upNew(*n,upstring);
    upLoop(i,0,str.length){
        if(is_vowel(str.text[i])){
            syl_arr[state] = upCopy(str,close_until,i-close_until+1);
            upLoop(j,i+1,str.length){
                if(is_vowel(str.text[j])){
                    if(j-i-1>1){
                        /*ստուգել յ տառը ինչ որ բան անել*/
                        tmp = upCopy(str,i+1,j-i-2);
                        upAppend(syl_arr+state,tmp);
                        close_until = j-1;
                    }
                    else
                        close_until = i+1;
                    break;
                }

            }
            if(j==str.length){
                tmp = upCopy(str,i+1,str.length);
                upAppend(syl_arr+state,tmp);
                break;
            }
            i = j-1;
            ++state;
        }
    }
    return syl_arr;
}
