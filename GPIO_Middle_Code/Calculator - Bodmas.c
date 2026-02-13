#define _XTAL_FREQ 20000000
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned int i=0;
unsigned int j=0;
int num = 0;
int lastValue = 0;
char op = '+';   
int result = 0;
unsigned char s1[95];

void operations(unsigned char exp[])
{
    unsigned char hex_digits[16] = {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };

    
    
     while(1)
    {
        if(exp[i]>='0' && exp[i]<='9')
            num = num*10 + (exp[i]-'0');

        if(exp[i]=='+' || exp[i]=='-' || exp[i]=='*' || exp[i]=='/' || exp[i]=='\0')
        {
            switch(op)
            {
                case '+': result += lastValue; lastValue = num; break;
                case '-': result += lastValue; lastValue = -num; break;
                case '*': lastValue = lastValue * num; break;
                case '/': if(num!=0) lastValue = lastValue / num; break;
            }
            op = exp[i];
            num = 0;
        }

        if(exp[i]=='\0') break;
        i++;
    }

    result += lastValue;

   
    unsigned char hex[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    TRISC =0; TRISB=0;
    PORTC  = hex[result%10];
    PORTB = hex[(result/10)%10];
    
   
}




void arithmatic(unsigned char a)
{
     unsigned char hex_digits[16] = {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };
     TRISC=0x00;
     
    if(a =='=')
    {
        PORTC=0x86;
        s1[j]='\0';
        operations(s1);
     //operations(s1);
    }
    else if(a=='C')
    { PORTC=0xC0;
      PORTB=0xC0;
      i=0,j=0,num = 0,lastValue = 0,result = 0,op='+';
      for(int k = 0; k < 70; k++){
      s1[k] = 0;}
      return;
    }  
    else
    {
     if(a>='0' && a<='9'){
     PORTC=hex_digits[a-'0'];}
     else if (a =='*'){
     PORTC=0xAB;}
     else if(a=='+'){
     PORTC=0x8C;}
     else if(a== '-'){
     PORTC= 0x92;}
     else if(a== '/'){
     PORTC=0xA1;}
     
      s1[j]=a; 
      j++;
    }
    
}
void cal_boardmas(void)
{    unsigned int bit1=-1,bit2=-1;
     unsigned char keyboard[4][4] = 
     {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'C','0','=','+'}
     };
     while(1)
    { 
    while(1)
    {
        TRISD = 0xF0;
        PORTD = 0x0F;
       
            if((PORTD &(1<<4))!= 0){bit1=0;break;}    
            else if((PORTD &(1<<5))!=0){bit1=1; break;}
            else if((PORTD &(1<<6))!=0){  bit1=2; break;}
            else if((PORTD &(1<<7))!=0){bit1=3; break;}
            else{;}
    }
    while(1)
    {
         TRISD = 0x0F;
         PORTD = 0xF0;
            if((PORTD &(1<<0))!= 0){bit2=0; break;}         
            else if((PORTD &(1<<1))!=0){bit2=1; break;}
            else if((PORTD &(1<<2))!=0){bit2=2; break;}
            else if((PORTD &(1<<3))!=0){bit2=3; break;}
            else{;}  
    }
  arithmatic(keyboard[bit2][bit1]); 
}
void main(void)  
{
    while(1)
    {
        cal_boardmas();
    }
}
