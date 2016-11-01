#include "mkrat.h"

int main()
{
    setenv("list_dir","/home/davit/Desktop/split/list/",1);

    upstring s = upString("նախադասություն");
    unsigned int n,m;
    upstring *arr;

    filter(&s,0);
    arr = split(s,&n);
    //printf("  %d  ",n);
    upConsoleWriteln(s);

    upLoop(m,0,n)
        upConsoleWriteln(arr[m]);

    return 0;
}
