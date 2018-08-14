//#include <ctype.h>
//#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include "urldecode.h"

/* Function: urlDecode */
char *urlDecode(const char *str) {
  //int d = 0; /* whether or not the string is decoded */

  char *dStr = (char *) malloc(strlen(str) + 1);
  char eStr[] = "00"; /* for a hex code */

  strcpy(dStr, str);

  //while(!d) {
    //d = 1;
    int i; /* the counter for the string */

    for(i=0;i<strlen(dStr);++i) {

      if(dStr[i] == '%') {
        if(dStr[i+1] == 0)
          return dStr;

        if(isxdigit(dStr[i+1]) && isxdigit(dStr[i+2])) {

          //d = 0;

          /* combine the next to numbers into one */
          eStr[0] = dStr[i+1];
          eStr[1] = dStr[i+2];

          /* convert it to decimal */
          long int x = strtol(eStr, NULL, 16);

          /* remove the hex */
          memmove(&dStr[i+1], &dStr[i+3], strlen(&dStr[i+3])+1);

          dStr[i] = x;
        }
      }
      else if(dStr[i] == '+') { dStr[i] = ' '; }
    }
  //}

  return dStr;
}

int main(void) {
  printf("URL Decoder Test\n");
  printf("================\n\n");

  /* TEST 1 */
  printf("Test 1: Just a space\n");
  printf("--------------------\n");
  //printf("Input:    M+%60%21%40%23%24%25%5E%26*%28%29-_%2B%3D%7B%7D%5B%5D%3B%27%3A\"<>%2C.%2F%7C%5C+M\n");
  printf("\n");
  printf("Expected Output: M `!@#$%^&*()-_+={}[];':\"<>,./|\\ M\n");
  char *test1 = urlDecode("M+%60%21%40%23%24%25%5E%26*%28%29-_%2B%3D%7B%7D%5B%5D%3B%27%3A\"<>%2C.%2F%7C%5C+M");
  printf("Actual Output:   %s\n\n\n", test1);
  free(test1);


  /* TEST 2 */
  printf("Test 2: A string with a space\n");
  printf("-----------------------------\n");
  printf("Input:           M+M%%2BM+M%%2520M\n");
  printf("Expected Output: M M+M M%%20M\n");
  char *test2 = urlDecode("M+M%2BM+M%2520M\n");
  printf("Actual Output:   %s\n\n\n", test2);
  free(test2);


  /* TEST 3 */
  printf("Test 3: Just a %% symbol\n");
  printf("------------------------\n");
  printf("Input:           %%0+n\n");
  printf("Expected Output: %%0 n\n");
  char *test3 = urlDecode("%0+n");
  printf("Actual Output:   %s\n\n\n", test3);
  free(test3);


  /* TEST 4 */
  printf("Test 4: A string with all escaped characters\n");
  printf("--------------------------------------------\n");
  printf("Input:           %%20%%21%%22%%23%%24%%25%%26%%27%%28%%29\n");
  printf("Expected Output:  !\"#$&'()\n");
  char *test4 = urlDecode("%20%21%22%23%24%26%27%28%29");
  printf("Actual Output:   %s\n\n\n", test4);
  free(test4);


  /* TEST 5 */
  printf("Test 5: A string with doubly escaped characters\n");
  printf("-----------------------------------------------\n");
  printf("Input:           %%2520%%2524%%2523\n");
  printf("Expected Output:  $#\n");
  char *test5 = urlDecode("%2520%2524%2523");
  printf("Actual Output:   %s\n\n\n", test5);
  free(test5);


  /* TEST 6 */
  printf("Test 6: An empty string\n");
  printf("-----------------------\n");
  printf("Input:           \n");
  printf("Expected Output: \n");
  char *test6 = urlDecode("");
  printf("Actual Output:   %s\n\n\n", test6);
  free(test6);


  /* TEST 7 */
  printf("Test 7: A number of percent signs\n");
  printf("---------------------------------\n");
  printf("Input:           %%%%%%%%\n");
  printf("Expected Output: %%%%%%%%\n");
  char *test7 = urlDecode("%%%%");
  printf("Actual Output:   %s\n\n\n", test7);
  free(test7);


  /* TEST 8 */
  printf("Test 8: A number of percent signs followed by an encoded symbol\n");
  printf("---------------------------------------------------------------\n");
  printf("Input:           %%%%%%%%%%29\n");
  printf("Expected Output: %%%%%%%%)\n");
  char *test8 = urlDecode("%%%%%29");
  printf("Actual Output:   %s\n\n\n", test8);
  free(test8);


  /* TEST 9 */
  printf("Test 9: A mix of +'s for spaces(which don't get decoded)\n");
  printf("-------------------------------\n");
  printf("Input:           a%%20b+c+d%%20x\n");
  printf("Expected Output: a b c d x\n");
  char *test9 = urlDecode("a%20b+c+d%20x");
  printf("Actual Output:   %s\n\n\n", test9);
  free(test9);

  printf("Testing is complete!\n\n\n");

  return 0;
}