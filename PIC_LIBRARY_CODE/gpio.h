#define  SETIN(n,port)  (port|=1<<(n))
#define  SETOUT(n,port) (port&=~(1<<(n)))
typedef enum
{
    OUTPUT = 0,
    INPUT  = 1
} pinmode_t;
typedef enum
{
    HIGH = 1,
    LOW = 0
}pinstate;
#define  SETHIGH(n,port) (port|=1<<(n))
#define  SETLOW(n,port)  (port&=~(1<<(n)))

#ifndef PORT
#define PORTA (*(volatile unsigned char *)0X05)
#define TRISA (*(volatile unsigned char *)0X85 )  //PORT A//
#define ADCON1 (*(volatile unsigned char*)0x9f)

#define PORTB (*(volatile unsigned char * )0X06)
#define TRISB (*(volatile unsigned char *)0X86 )  //PORT B//

#define PORTC (*(volatile unsigned char * ) 0X07)
#define TRISC (*(volatile unsigned char * )0X87)  //PORT C//

#define PORTD (*(volatile unsigned char * )0X08)
#define TRISD (*(volatile unsigned char *)0X88 )  //PORT D//

#define PORTE (*(volatile unsigned char *)0X09)
#define TRISE (*(volatile unsigned char *)0x89)   //PORT E//
#endif

void GPIO_pinmode(int a,pinmode_t b)
    {
        if(a>=33&&a<=40)        //PORTB
        {   if(b==0) 
            SETOUT(a-33,TRISB);
            else
            SETIN(a-33,TRISB);
        }
       else if(a>=2 && a<=7) //PORTA//
        {
            ADCON1 = 0x06;
            if(b==0)
                SETOUT(a-2,TRISA);
            else
                SETIN(a-2,TRISA);
               
        }
        else if(((a>14)&&(a<19))||((a>22)&&(a<27))) // PORTC
       { 
        if(a<19)
            a=a-15;
        else
            a=a-19;
        if(b==0)
                SETOUT(a,TRISC);
            else
                SETIN(a,TRISC);
               
       }
      else if(((a > 18) && (a < 23)) || ((a > 26) && (a < 31))) // PORTD
       {
        if(a<23)
        a=a-19;
        else
        a=a-23;
         if(b==0)
            SETOUT(a,TRISD);
         else
            SETIN(a,TRISD);
       }
       else if((a>7)&&(a<11)) //PORTE
       {
        ADCON1 = 0x06;
        if(b==0)
             SETOUT(a-8,TRISE);
         else
            SETIN(a-8,TRISE);
       }
       else
        {//serial.printf("invalid") ;
         return;  
        } 
       
    }
void GPIO_pinwrite(int a,pinstate b)
    {
        if(a>=33&&a<=40)
        {   if(b==0) 
            SETLOW(a-33,PORTB);
            else
            SETHIGH(a-33,PORTB);
        }
         else if(((a>=2)&&(a<=7)))
        {
            if(b==0)
                SETLOW(a-2,PORTA);
            else
                SETHIGH(a-2,PORTA);
               
        }
       else if(((a > 14) && (a < 19)) || ((a > 22) && (a < 27))) // PORTC
        {
        if(a<19)
            a=a-15;
        else
            a=a-19;
            if(b==0)
                SETLOW(a,PORTC);
            else
                SETHIGH(a,PORTC);
               
        }
        else if(((a>18)&&(a<23))||((a>26)&&(a<31)))
       {
        if(a<23)
        a=a-19;
        else
        a=a-23;
         if(b==0)
            SETLOW(a,PORTD);
         else
            SETHIGH(a,PORTD);
       }
         else if((a>7)&&(a<11))
       {
        if(b==0)
             SETLOW(a-8,PORTE);
         else
            SETHIGH(a-8,PORTE);
       }
      
    }
