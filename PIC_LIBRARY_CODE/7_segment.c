void delay_s(unsigned int x)
{
    OPTIONAL_REG=0x00;
    unsigned int count = 0;
    OPTIONAL_REG =0x87;
    STATUS=0X40;
    TMR0 = 0x00;
    INTCON&=~(1<<2);   
     
    while (count<(3*x))
    {
      if (INTCON & (1<<2))
        {
            INTCON &= ~(1 << 2);
            TMR0=0;
            count++;
        }
    }
}

void seven_segment(unsigned char a,port n)
{
volatile unsigned char *t,*p;
unsigned char hex_digits[16] = {
0xC0,0xF9,0xA4,0xB0,
0x99,0x92,0x82,0xF8,
0x80,0x90,0x88,0x83,
0xC6,0xA1,0x86,0x8E
};
       t = tris[n];
       p = port_s[n];
      *t=0x00;
    int i= a-'0';
    if(i>=0&& i<=9)
    {
    *p=hex_digits[i];
    }
    else if(i>17&&i<=23)
    {
        i=i-7;
        *p=hex_digits[i];
    } 
    return;
}

void seven_segment_1(unsigned char a)
{
unsigned char hex_digits[16] = {
0xC0,0xF9,0xA4,0xB0,
0x99,0x92,0x82,0xF8,
0x80,0x90,0x88,0x83,
0xC6,0xA1,0x86,0x8E
};
 
   TRISD=0x00;
    int i= a-'0';
    if(i>=0&& i<=9)
    {
    PORTD=hex_digits[i];
    }
    else if(i>17&&i<=23)
    {
        i=i-7;
        PORTD=hex_digits[i];
    } 
    return;
}

void upcounter(int a,port m)
{
        for(int i=a;i>=0;i--)
        {
            char n=(unsigned char)i+'0';
            seven_segment(n,m);
            delay_s(1);
        }
}

void downcounter(int a,port m)
{
        for(int i=0;i<a;i++)
        {
            char n=(unsigned char)i+'0';
            seven_segment(n,m);
            delay_s(1);
        }
}
void 4_digit_counter( int x,port n) // count using 2 ports
{
      volatile unsigned char *t,*p;
      unsigned int digit_1=0;
      unsigned int digit_2=0;
      unsigned int digit_3=0;
      unsigned int digit_4=0;
      
       t = tris[n];
       p = port_s[n];
       *t =0x00;
      
    for(unsigned int i=0;i<x;i++)
    {
        digit_1=i%10;
        digit_2=(i/10)%10;
        digit_3=(i/100)%10;
        digit_4=(i/1000)%10;
        
        *p=0x01;
     char m=(unsigned char)digit_1 +'0';
       seven_segment_1(m);
       delay_s(1);
       
        
         *p=0x02;
     char n=(unsigned char)digit_2+'0';
        seven_segment_1(n);
         delay_s(1);
         
           *p=0x03;
     char o=(unsigned char)digit_3+'0';
        seven_segment_1(o);
        delay_s(1);
        
          *p=0x0F;
     char p=(unsigned char)digit_4+'0';
        seven_segment_1(p);
          delay_s(1);
          
    }
}
   
