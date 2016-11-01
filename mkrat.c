#include "mkrat.h"

//*****Filter string
char filter(upstring *str,upstring *prev){
    static upstring ev,u=nls;
    if(u.length==0){
        ev = tpString("եւ");
        u  = tpString("ու");
    }
    //ջնջել ավելորդ տառը, իսկ մնացածը դարձնել փոքրատառ
    toLowerCase(str);
    cleanText(str);
    if(str->length==0)
        return -1;

    //«և»
    if(has_letter(str,0x587,0,0) || upPos(ev,*str))
        filter_ev(str);

    //«բ֊պ֊փ»
    if(has_letter(str,0x562,0x57A,0x583))
        filter_2_26_35(str);

    //«գ֊կ֊ք»
    if(has_letter(str,0x563,0x56F,0x584))
        filter_3_15_36(str);

    //«դ֊տ֊թ»
    if(has_letter(str,0x564,0x57F,0x569))
        filter_4_9_31(str);

    //«ձ֊ծ֊ց»
    if(has_letter(str,0x571,0x56E,0x581))
        filter_14_17_33(str);

    //«ջ֊ճ֊չ»
    if(has_letter(str,0x57B,0x573,0x579))
        filter_19_25_27(str);

    //«յ»
    if(has_letter(str,0x575,0,0))
        filter_21(str);

    //«ղ֊խ»
    if(has_letter(str,0x572,0x56D,0))
        filter_13_18(str);

    //«հ», «ռ֊ր», «վ֊ֆ»
    if(has_letter(str,0x580,0x570,0x7C) || has_letter(str,0x57E,0,0))
        filter_28_32__30_f__16(str);

    /**Ձայնավորներ*/
    //«է֊ե»
    if(has_letter(str,0x565,0x567,0))
        filter_5_7(str,prev);

    //«ու»
    if(upPos(u,*str)!=-1)
        filter_34(str);

    //«օ֊ո»
    if(has_letter(str,0x578,0x585,0))
        filter_24_o(str);

    hidden_8(str); /* գաղտնավանկի «ը» */

    return 0;
}

/*
int mkrat(upstring *text){

}
*/

