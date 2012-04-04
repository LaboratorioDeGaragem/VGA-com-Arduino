#define NOP asm("nop")
#define PRETO    PORTB = B00000000;
#define AZUL     PORTB = B00000001;
#define VERDE    PORTB = B00000010;
#define CIANO    PORTB = B00000011;
#define VERMELHO PORTB = B00000100;
#define MAGENTA  PORTB = B00000101;
#define AMARELO  PORTB = B00000110;
#define BRANCO   PORTB = B00000111;

unsigned int contalinhas = 1;

void setup()
{
  //Seta pinos 5, 6 e 7 como saidas
  // 7 - HSYNC
  // 6 - VSYNC
  // 5 - RGB  
  DDRD |= B11100000;
  DDRB |= B11100111;
  PORTD |= B11000000;

  //set timer  
  TCCR2A = 0x02;                        // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  TCCR2B |= (1 << CS20);                // 
  TCCR2B |= (1 << CS21);                // Seta prescaler
  TCCR2B &= ~(1 << CS22);               //
  
  TCNT2 = 0;                            // limpa contador
  //OCR2A = 0x03;                         // seta contador para comaracao

  TIMSK2 &= ~(1<<OCIE2A);                // seta interrupcao por comparacao  
  TIMSK2 |= (1<<TOIE2);                // seta interrupcao por overflow  
}

void loop()
{
  noInterrupts();
  do{
    PRETO;
    if (TCNT2 > 0x0f){

      delayMicroseconds(1); 
      NOP;NOP;NOP;NOP;
      
      TCNT2 = 0x00;

    
                        
      //pequeno ajuste de tempo, pode ser necessario ou nao dependendo da placa
      // #### HSYNC ###
      PORTD &= ~(1 << 7);      
      if (++contalinhas >= 525){ //525 linhas
        contalinhas = 1;
      }      
      PORTD |= (1 << 7);



      // ### VSYNC ###
      if ((contalinhas == 1)||(contalinhas == 2)){ //492 e 493
        PORTD &= ~(1 << 6);      
      } else {
        PORTD |= (1 << 6);
        

        NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
        NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
        NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
        NOP;NOP;NOP;NOP;NOP;
        
        if ((contalinhas >= 9) && (contalinhas <= 489)){ // 2 e 482
          
                BRANCO;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                PRETO;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                AZUL;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                VERDE;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                CIANO;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                VERMELHO;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                MAGENTA;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                AMARELO;
                delayMicroseconds(3);NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;
                PRETO;
                NOP;NOP;NOP;NOP;
        }
            
      }


}


}while(1);

}
