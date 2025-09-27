#include<stdio.h>

int main(){
  int m,dm1,dm2,dm3,d,dg;
  
  dg=0;
  dm1=28;
  dm2=30;
  dm3=31;
  
  printf("vvedite mouth and day");
  scanf("%d%d",&m,&d);
  
  switch(m){
    case 1:
      dg=d;
      break;
    case 2:
      dg=dm3+d;
      break;
    case 3:
      dg=dm3+dm1+d;
      break;
    case 4:
      dg=dm1+dm3+dm3+d;
      break;
    case 5:
      dg=dm1+dm3*2+dm2+d;
      break;
    case 6:
      dg=dm1+dm3*3+dm2*2+d;
      break;
    case 7:
      dg=dm1+dm3*3+dm2*2+d;
      break;
    case 8:
      dg=dm1+dm3*4+dm2*2+d;
      break;
    case 9:
      dg=dm1+dm3*5+dm2*3+d;
      break;
    case 10:
      dg=dm1+dm3*5+dm2*4+d;
      break;
    case 11:
      dg=dm1+dm3*6+dm2*4+d;
      break;
    case 12:
      dg=dm1+dm3*6+dm2*4+d;    
      break;
  }
  printf(" dg=%7.2d",dg);
  return 0;
}
