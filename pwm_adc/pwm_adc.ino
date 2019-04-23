#include <avr/io.h>
#include <inttypes.h> //Definição de tipos

int main()
{
  // iniciamos zerando o valor do output do pwm de TCCR1A
  OCR1A = 0;

  // configuracao do PWM
  //FAST PWM 10 bits (Modo 7) sem inversão
  TCCR1A = _BV(COM1A1) // Essa configuração garante um FAST PWM não invertido
           | _BV(WGM10) | _BV(WGM11); //Definindo PWM com fase corrigida de 10 bits
  TCCR1B = _BV(CS11) | //Habilitando um prescaler de 8
           _BV(WGM12); //Definindo PWM com fase de 10 bits

  // PB1/OC1A como saída
  DDRB = _BV(PB1);

  // valor inicial da variável auxiliar
  uint16_t valorAD = 0;

  DDRB  &= 0b11111110;  //Pino PB0 como entrada
  DDRC &= 0b0;

  //Configuração do AD
  ADMUX  |= _BV(REFS0); //Utiliza VCC como referência e PC0 como entrada analog
  ADCSRA |= _BV(ADEN);  //Habilita o AD

  while (1)
  {
    if (PINB & 0x01)
    {
      ADCSRA |= _BV(ADSC);
      while (!(ADCSRA & 0x10));
      valorAD = ADC;
      OCR1A = valorAD;
    }
  }
}
