#include "../upstring/upstring.h"

const unsigned short vowels[] = {
                0x561 /*ա*/ ,
                0x565 /*ե (է)*/,
                0x568 /*ը*/,
                0x56B /*ի*/,
                0x578 /*ո(o)*/,
                0x582 /*ւ(ու)*/,
                //ձայնավոր հնչյուններ
                0x567 /*է*/,
                0x585 /*օ*/

};

// լ, մ, ն, ռ, ր, յ
const unsigned short deep[] = {
                0x56C /*լ*/ ,
                0x574 /*մ*/ ,
                0x576 /*ն*/ ,
                0x57C /*ռ*/ ,
                0x580 /*ր*/ ,
                0x575 /*յ*/
};


//եթե ձայնավոր է ։1։ հակարակ դեպքում ։0։
unsigned char is_vowel(unsigned short cr){
    int i;
    upLoop(i,0,8)
        if(vowels[i]==cr)
            return 1;
    return 0;
}


//գտնել ձայնորդները
unsigned char is_deep(unsigned short cr){
    int i;
    upLoop(i,0,8)
        if(deep[i]==cr)
            return 1;
    return 0;
}
