#include <avr/io.h>
#include <avr/interrupt.h>
/* Limite de interrupções em 61, pois queremos que o LED pisque a cada 1s. 61 * 16,384ms = 1s */
volatile uint16_t limite_interrupcoes_contagem = 61;
// variável auxiliar
volatile uint16_t contagem = 0;

//----------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect) //interrupção do TC0
{
  //soma o auxiliar a cada estouro
  contagem++;
  //verifica se possui os 61 estouros
  if (contagem >= limite_interrupcoes_contagem) {
    //se o led estiver aceso, apaga
    if (PORTB & 0b00000001) {
      PORTB &= 0b0;
    //caso contrário acende
    } else {
      PORTB |= _BV(PORTB0);
    }
    contagem = 0;
  }

}
//----------------------------------------------------------------------------------
int main()
{
  DDRB = 0b00000001; //somente pino do LED como saída (PB0)
  //Definimos o prescaler no TCCR0B, TC0 com prescaler de 1024 a 16MHz (default arduino)
  // gera uma interrupção a cada 16,384ms
  TCCR0B = _BV(CS02) | _BV(CS00);
  TIMSK0 = _BV(TOIE0); //habilita a interrupção do TC0
  sei(); //habilita a chave de interrupção global
  while (1)
  {
    /*Aqui vai o código, a cada estouro do TC0 o programa desvia para
      ISR(TIMER0_OVF_vect)*/
  }
}
