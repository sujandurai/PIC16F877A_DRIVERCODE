#include "gpio.h"

unsigned int n=0;
unsigned int sum=0;
unsigned int set=0,s=0;
unsigned int m=0,mul=1,div=1;
unsigned int sign=0;

void cal_sequential(unsigned char a)
{
    
    
    unsigned char hex_digits[16] = {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };
   
    TRISC = 0x00;
    TRISB = 0x00;
    PORTB =0xC0;
    if(a >= '0' && a <= '9'){
            n= n*10 + a-'0';
            PORTC = hex_digits[a - '0'];
            //set=1;
    }  
    
    else if(a=='+')
    {
         if(sign==1){sum=sum+n;}
        else if(sign==2){sum=sum-n;}
        else if(sign==3){sum=mul*n*sum;}
        else if(sign==4){sum=(div*sum)/n;}
        else {
            sum=sum+n;}
            n=0;
            set=1;
            m=1,s=1;
            op=1;
            sign=1;
    }
  
    else if(a=='-')
    {
        if(sign==1){sum=sum+n;}
        else if(sign==2){sum=sum-n;}
        else if(sign==3){sum=mul*n*sum;}
        else if(sign==4){sum=(sum*div)/n;}
        else{
           if(m<=0)
           sum=n-sum;
           else{
           sum=sum-n;}
           }
           n=0;
           m=1,s=1;
           set=2;
           sign=2;
    }
    else if(a=='*')
     {
        if(sign==1){sum=sum+n;}
        else if(sign==2){sum=sum-n;}
        else if(sign==3){sum=mul*n*sum;}
        else if(sign==4){sum=(sum*div)/n;}
        else{
          sum=mul*n;}
          set=3,n=0,m=1;s=1;
          sign=3;
          
     }
    else if(a=='/')
    {
         if(sign==1){sum=sum+n;}
        else if(sign==2){sum=sum-n;}
        else if(sign==3){sum=mul*n*sum;}
        else if(sign==4){sum=(div*sum)/n;}
        else{
        if(s<=0)
        sum=n/div;
        else
        sum=(sum*div)/1;
        }
        set=4,n=0,s=1,m=1;
        sign=4;
    }
        
    
     else if(a=='=')
    {
        if(set==1||set==0){
        sum=sum+n;}
        else if(set==2){
        sum=sum-n;}
        else if(set==3)
        {
            if(sum>0)
            sum=mul*n*sum;
            else
            sum=mul*n;
        }
        else if(set==4)
        sum=(div*sum)/n;
     
        if(sum>9)
        {PORTC=hex_digits[sum%10];
        PORTB=hex_digits[sum/10];
         
        sum=0,m=0,set=0,s=0,div=1,sign=0,mul=1;;
         
        }
        else{
        PORTC= hex_digits[sum];
        PORTB=0xC0;
        
        sum=0,m=0,set=0,s=0,div=1,sign=0,mul=1;
        }
     }    
    else if(a=='C')
    {
       sum=0;
       PORTC=0xC0;
       PORTB=0xC0;
       n=0;
       mul=1;
       div=1;
       s=0;
       sign=0;
    }
      
}

void keypad_scan(void)
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
   
    cal_sequential(keyboard[bit2][bit1]); 
   
   }
}
