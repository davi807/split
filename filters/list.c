#include "filters.h"

char filter_list(char *addr, upstring *str){
    char brk = 0;
    unsigned int line = 0;
    long i;

    upstring row;
    upstring separator = upString("=>");
    upstring hjk;
    upstring rps;

    FILE *f = fopen(addr,"r");

    if(!f){
        fprintf(stderr,"Listfile '%s' not found\n",addr);
        return -1;
    }

    if(!str)
        return -2;

    while(1){
        row = upReadC(f,'\n');
        if(!row.length)
            break;
        ++line;
        if(row.text[0]=='%'){
            upReset(&row);
            continue;
        }

        i = upPos(separator,row);
        if(i<1){
            upReset(&row);
            fprintf(stderr,"List error in file '%s' on line '%d'\n",addr,line);
            continue;
        }

        if(i+2>row.length-1){
            fprintf(stderr,"Replace error in file '%s' on line '%d'\n",addr,line);
            upReset(&row);
            continue;
        }

        hjk = upCopy(row,0,i);
        rps = upCopy(row,i+2,row.length-i);

        //Replace
        while((i=upPos(hjk,*str))!=-1){
            upDelete(str,i,hjk.length);
            upInsert(rps,str,i,rps.length);
            //Allow break?
            if( 100.0 * rps.length / str->length > 44)
                brk = 1;
        }

        //Clear heap
        upReset(&rps);
        upReset(&hjk);
        upReset(&row);

        //End while loop
        if(brk) break;
    }
    fclose(f);
    return 0;
}


/*Filter extend... copy-paste
v = ձայնավոր հատվածից առաջ/հետո
c = բաղաձայն հատվածից առաջ/հետո
V = ձայնավորը առաջին/վերջին տառն է
C = բաղաձայնը առաջին/վերջին տառն է
* = հատվածը սկզբում/վերջում է
*/
unsigned int filter_ext(char *addr, upstring *str,char is_begin, char is_end,unsigned int *ret){
    char brk=0,begin,end,allw;
    unsigned int line = 0;
    long i;

    upstring row;
    upstring separator = upString("=>");
    upstring hjk;
    upstring rps;

    FILE *f = fopen(addr,"r");

    if(!f){
        fprintf(stderr,"Listfile '%s' not found\n",addr);
        return -1;
    }

    if(!str)
        return -2;

    while(1){
        begin = 0;
        end = 0;
        allw = 0;
        row = upReadC(f,'\n');
        if(!row.length)
            break;
        ++line;
        if(row.text[0]=='%'){
            upReset(&row);
            continue;
        }

        i = upPos(separator,row);

        if(i<1){
            upReset(&row);
            fprintf(stderr,"List error in file '%s' on line '%d'\n",addr,line);
            continue;
        }

        if(i+2>row.length-1){
            fprintf(stderr,"Replace error in file '%s' on line '%d'\n",addr,line);
            upReset(&row);
            continue;
        }

        hjk = upCopy(row,0,i);
        rps = upCopy(row,i+2,row.length-i);

        if(hjk.text[0]=='v' ||
            hjk.text[0]=='c' ||
            hjk.text[0]=='V' ||
            hjk.text[0]=='C' ||
            hjk.text[0]=='*'){

            begin = hjk.text[0];
            upDelete(&hjk,0,1);
        }


        if(hjk.text[hjk.length-1]=='v' ||
            hjk.text[hjk.length-1]=='c' ||
            hjk.text[hjk.length-1]=='V' ||
            hjk.text[hjk.length-1]=='C' ||
            hjk.text[hjk.length-1]=='*'){

            end = hjk.text[hjk.length-1];
            upDelete(&hjk,hjk.length-1,1);
        }



        //Replace
        while((i=upPos(hjk,*str))!=-1){
            switch(begin){
                case 0: allw =1; break;
                case '*': if(is_begin && i==0) allw =1; break;
                case 'V': if(is_begin && is_vowel(str->text[0]) && i==1) allw =1; break;
                case 'v': if(i>0 && is_vowel(str->text[i-1])) allw =1; break;
                case 'C': if(is_begin && !is_vowel(str->text[0]) && i==1) allw =1; break;
                case 'c': if(i>0 && !is_vowel(str->text[i-1])) allw =1; break;
            }
            if(!allw) break;

            if(end) allw = 0;

            switch(end){
                case 0: allw =1; break;
                case '*': if(is_end && i+hjk.length == str->length) allw =1; break;
                case 'V': if(i+hjk.length == str->length-1 && is_end && is_vowel(str->text[str->length-1])) allw =1; break;
                case 'v': if(i+hjk.length < str->length && is_vowel(str->text[i+hjk.length])) allw =1; break;
                case 'C': if(i+hjk.length == str->length-1 && is_end && !is_vowel(str->text[str->length-1])) allw =1; break;
                case 'c': if(i+hjk.length < str->length && !is_vowel(str->text[i+hjk.length])) allw =1; break;
            }
            if(!allw) break;

            if(*ret){
                *ret = hjk.length;

                //Clear heap
                upReset(&rps);
                upReset(&hjk);
                upReset(&row);

                return i;
            }

            upDelete(str,i,hjk.length);
            upInsert(rps,str,i,rps.length);
            //Allow break?
            if( 100.0 * rps.length / str->length > 44)
                brk = 1;
            if(rps.length-hjk.length > 0)
                break;
        }

        //Clear heap
        upReset(&rps);
        upReset(&hjk);
        upReset(&row);

        //End while loop
        if(brk) break;
    }
    fclose(f);
    return 0;
}

