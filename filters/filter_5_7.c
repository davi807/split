/**
«է» հնչյունը գրել «ե» տառով
բառամիջի «ե» կարդալ «յէ(յե)» եթե նախոռդ տառը ձայնավոր է
բառի սկզբում գրված «ե» դարձնել «յէ(յե)»
ստուգել օժանդակ բայերի հնչողությունը կախված նախորդ բառից
*/

#include "filters.h"


void filter_5_7(upstring *crt,upstring *prev){
    static unsigned char init = 0;
    static upstring em;
    static upstring es;
    static upstring enq;
    static upstring eq;
    static upstring en;
    /** Դերբայներ **/
    static upstring um;
    static upstring el;
    static upstring al;
    static upstring is;
    static upstring ox;
    static upstring ac;
    static upstring elu;
    static upstring alu;
    //յ
    static upstring y;
    upstring s;
    unsigned int i;

    if(!init){
        em = tpString("եմ");
        es = tpString("ես");
        enq = tpString("ենք");
        eq = tpString("եք");
        en = tpString("են");
        //***********//
        um = tpString("ում");
        el = tpString("ել");
        al = tpString("ալ");
        is = tpString("իս");
        ox = tpString("ող");
        ac = tpString("ած");
        elu = tpString("ելու");
        alu = tpString("ալու");
        //***********//
        y = tpString("յ");
        init=1;
    }

    if(!upLength(*crt))
        return;
    //Ստուգել օժանդակ բայերը
    if(upLength(*crt)<4){
        if( upComp(*crt,em) ||
            upComp(*crt,eq) ||
            upComp(*crt,en) ||
            upComp(*crt,enq)   )
            return;
        if(upComp(*crt,es) && prev && prev->length>3){
            //*Ես* գրում եմ
            //Դու գրում *ես*
            s = upCopy(*prev,prev->length-4,4);
            if( (prev->length>2) &&
                (
                  upPos(el,s)==s.length-2||
                  upPos(al,s)==s.length-2||
                  upPos(is,s)==s.length-2||
                  upPos(ox,s)==s.length-2||
                  upPos(ac,s)==s.length-2||
                  upPos(um,s)==s.length-3||
                  upPos(elu,s)==s.length-4||
                  upPos(alu,s)==s.length-4
                )
              ){upReset(&s); return;}
            upReset(&s);
        }
    }
    //բառի սկզբի «ե»֊ն փոխել «յէ(յե)»֊ի
    if(crt->text[0]==0x565)
        upInsert(y,crt,0,1);
    //եթե «ե»֊ից առաջ կա ձայնավոր
    upLoop(i,3,crt->length)
        if(crt->text[i]==0x565){
            if(is_vowel(crt->text[i-1]))
                upInsert(y,crt,i,1);
        }
        else if(crt->text[i]==0x567)
            crt->text[i] = 0x565;
    upLoop(i,0,crt->length){
        if(i>2) break;
        if(crt->text[i]==0x567)
            crt->text[i] = 0x565;
    }
}
