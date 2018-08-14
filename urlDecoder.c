#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
void process_responce(const char *);
char * extract_between(const char *, const char *, const char *);
char *urlDecode(const char *);
char * ssid = "";
char * pwd = "";

int main() 
{
	char* res = "GET /file:///C:/192.168.10.1/?ssid=Swaraj+78+%2520D+%2B+%2F%5C+%26&pwd=M+%60%21%40%23%24%25%5E%26*%28%29-_%2B%3D%7B%7D%5B%5D%3B%27%3A%5C%22%3C%3E%2C.%2F%7C%5C%5C+M HTTP2.0";
	process_responce(res);
	printf("SSid= %s, Pwd= %s", ssid, pwd);
	return 0;
}

void process_responce(const char *res)
{
	res = strcat(extract_between(res, "/?", " "), " ");
	ssid = urlDecode(extract_between(res, "ssid=", "&"));
	pwd = urlDecode(extract_between(res, "&pwd=", " "));
}

char * extract_between(const char *str, const char *p1, const char *p2)
{
  const char *i1 = strstr(str, p1);
  if(i1 != NULL)
  {
    const size_t pl1 = strlen(p1);
    const char *i2 = strstr(i1 + pl1, p2);
    if(p2 != NULL)
    {
     /* Found both markers, extract text. */
     const size_t mlen = i2 - (i1 + pl1);
     char *ret = (char *)malloc(mlen + 1);
     if(ret != NULL)
     {
       memcpy(ret, i1 + pl1, mlen);
       ret[mlen] = '\0';
       return ret;
     }
    }
  }
}

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
