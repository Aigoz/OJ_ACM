 /************************************************************************
  Function:        ZOJ1004: http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1004
  History :        Create:2012年11月22日23:03:01 (Actually, it is, strictly, a completion time
  Owner:            Yang HaiTao( Dennis Young)
  Reflection:    There is a much easier way to make it(_2) using 回溯.
                 Maybe I don
 ************************************************************************/
 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 
 /*Bound*/
 #define kIOArraySize        51
 #define kWordsArraySize    50
 /*    state    */
 #define kStateCheckTrue        1
 #define kStateCheckFalse        0
 #define kStateNotFound        0
 #define kStateHasFound        1
 
 int searchTarstrFromSrcstr(char *srcStr, char *tarStr, int inOutSum);
 void outputTLArray(int TLArray[kIOArraySize]);
 void resetTLArray(int TLArray[kIOArraySize]);
 void resetTLArrayByStep(int TLArray[kIOArraySize]);
 
 /************************************************************************
 *                        Global Variable                                    *                                                         
 ************************************************************************/
 /* 0: exit    1: in        2: out
 index0: currentIndex         1-1000->in,out to print.
 */
 int printTempLineArray[kIOArraySize] = {0};
 char charTable[3] = {'p', 'i', 'o'};
 
 int main()
 {
     char sourceWords[kWordsArraySize], targetWords[kWordsArraySize];
     int state;
 
     while (scanf("%s %s", sourceWords, targetWords) != EOF)
     {
         printf("[\n");
         state = searchTarstrFromSrcstr(sourceWords, targetWords, 0);
         printf("]\n");
     }
 
     return 0;
 }
 
 int searchTarstrFromSrcstr(char *srcStr, char *tarStr, int inOutSum)
 {
     int srcStrLength = 0;
     int tarStrLength = 0;
     int foundFlag = kStateNotFound;
     int i = 0;
     int k = 0;
     int howToNameThisNum = 0;
     char newSrcStr[kWordsArraySize] = {0};
 
     srcStrLength = strlen(srcStr);
     tarStrLength = strlen(tarStr);
 
     /*    error return and end return*/
     /* End of the String*/
     if (0 == srcStrLength && 0 == tarStrLength)
     {
         outputTLArray(printTempLineArray);
         return kStateCheckTrue;
     }
     else if (srcStrLength != tarStrLength)
     {
         /* it can not do this with different string length*/
         resetTLArray(printTempLineArray);
         return kStateCheckFalse;
     }
 
     /*search the 1st char of target string from last char of the source string*/
     for (i=srcStrLength - 1; i>=0; i--)
     {
         if (srcStr[i] == tarStr[0])
         {
             foundFlag = kStateHasFound;
 
             /* howToNameThisNum is a temp number which is important to the next step*/
             howToNameThisNum = i + 1 - inOutSum;
             if (howToNameThisNum < 0)
             {
                 /*NOTE:  <0 means, you need to out more than one char to get the char that you want,
                     but the unnecessary char will make your target word Wrong.*/
                 /* !!!!Important one!!!!!   you need to reset last step when the function will return false*/
                 resetTLArrayByStep(printTempLineArray);
                 return kStateCheckFalse;
             }
             else
             {
                 /*insert "i" into the print Array*/
                 for (k = 1; k<= howToNameThisNum; k++)
                 {
                     printTempLineArray[(printTempLineArray[0]+k)] = 1;
                 }
                 /*inset "o" into the print Array*/
                 printTempLineArray[0] = 
                     printTempLineArray[0] + howToNameThisNum+ 1;
                 /*set the first flag number*/
                 printTempLineArray[printTempLineArray[0]] = 2;
                 
                 /*creat new source string
                 The way like this:            source:aabcd    target:b
                     1.new=""    ->    2.new="aa"    ->     3.new="aacd"    */
                 strcpy(newSrcStr,"");
                 strncpy(newSrcStr, srcStr, i+1-1);
                 newSrcStr[i] = '\0';
                 strcat(newSrcStr, srcStr+i+1);
 
                 /*find the next char of the target string from the new source string*/
                 if (kStateCheckFalse == searchTarstrFromSrcstr
                     (newSrcStr, tarStr+1, inOutSum + howToNameThisNum - 1))
                 {
                     /*resetTLArray(printTempLineArray);
                     //这里不用resetTLArray只需设置notfound*/
                     /* you need set the foundFlag back to NotFound, begin the child function return false.*/
                     foundFlag = kStateNotFound;
                 }
                 else
                 {
                     /*    This is IMPORTENT!!!!!!!*/
                     resetTLArrayByStep(printTempLineArray);
                 }
             }
         }
     }
 
     if (kStateNotFound == foundFlag)
     {
         resetTLArray(printTempLineArray);
         return kStateCheckFalse;
     }
     else
         return kStateCheckTrue;
 }
 
 void outputTLArray(int TLArray[kIOArraySize])
 {
     int i = 0;
 
     for (i = 1; i <= TLArray[0]; i++)
     {
         printf("%c ",charTable[TLArray[i]]);
     }
     printf("\n");
 }
 
 void resetTLArray(int TLArray[kIOArraySize])
 {
     int i = 0;
     for (i = 1; i <= TLArray[0]; i++)
     {
         TLArray[i] = 0;
     }
     TLArray[0] = 0;
 }
 
 void resetTLArrayByStep(int TLArray[kIOArraySize])
 {
     int i = 0;
     i = TLArray[0];
     do 
     {
         TLArray[i] = 0;
         i--;
         TLArray[0]--;
     } while(i>0 && TLArray[i] != 2);
 }