#include<stdio.h>
#include <stdlib.h>
void printc(int endl,const char* fmt){
int i=0;
while (fmt[i]!='\0') {
  putchar(fmt[i]);
  ++i;
}
  if(endl==1){putchar(10);};
}
int main(int argc,char** argv){
if(argc>3 || argc<3){printc(1,"not args or enough.");}
printc(atoi(argv[1]),argv[2]);
}
