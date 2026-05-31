


#include"UART.H"

void main(void) 
{
    //TRISC= 0B10000000;
    init_tx();
    //txstr("(EmbeTronicX): Enter the letters in keyboard\n\r\r");
    while(1) {
        TXREG='A';
       
    }   
}
