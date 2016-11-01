/**
բառի սկզբի «ո» գրել «վո» բացի «ով»֊ից
ձայնավորից հետո «ո» գրել «վո»
«օ» հնչյունը գրել «ո» տառով
*/

#include "filters.h"

void filter_24_o(upstring *str){
    static char init = 0;
    //«ով֊ովքեր»
    static upstring ov;
    static upstring ovqer;
    static upstring oveve;
    static upstring ovevice;
    static upstring v;
    unsigned int i;

    if(!init){
        ov = upString("ով");
        ovqer = upString("ովքեր");

        //«և» ու «է ե» ֆունկցիաները արդեն աշխատել են
        //գրքում գրած էր դրա համար էլ ավելացնում էս երկու բառը ։Ճ
        oveve = upString("ովեվե");
        ovevice = upString("ովեվիցե");

        v = upString("վ");
        init = 1;
    }
    //«ով»֊ը ու մնացածը թողնել նույնը
    if(
       upComp(*str,ov) ||
       upComp(*str,ovqer) ||
       upComp(*str,oveve) ||
       upComp(*str,ovevice)
      )
        return;

    //բառի սկզբում «ո» գրել «վո»
    if(str->text[0]==0x578)
        upInsert(v,str,0,1);

    //ձայնավորից («ա»֊ից) հետո «ո» գրել «վո», «օ-ն» գրել «ո» տառով
    //բայց բառի սկզբի «ո»֊երը անտեսել
    upLoop(i,3,str->length){
        if(str->text[i]==0x578){
            if(str->text[i-1]==0x561){
                upInsert(v,str,i,1);
                ++i;
            }
        }
        else if(str->text[i]==0x585)
            str->text[i] = 0x578;
    }
    upLoop(i,0,str->length){
        if(i>2) break;
        if(str->text[i]==0x585)
            str->text[i] = 0x578;
    }
}
