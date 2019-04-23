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

  //Atribui o pino PC0 (pin A0) como sendo input para a entrada analógica, PC0 também é o ADC0
  DDRC = 0b0;

  //Configuração do AD
  ADMUX  |= _BV(REFS0); //Utiliza VCC como referência (5V) e PC0 como entrada analog
  ADCSRA |= _BV(ADEN) | //Habilita o AD
            0b00000111; //Seta o Prescaler como 128, me dando um limite máximo de 15 kSPS na conversão

  while (1)
  {
    ADCSRA |= _BV(ADSC); //Inicia a conversão AD
    while (!(ADCSRA & 0b00010000)); //Aguarda a conversão AD terminar, checando o bit ADIF
    valorAD = ADC;
    //Atribui o valor da conversão a saída
    OCR1A = valorAD;
  }
}
