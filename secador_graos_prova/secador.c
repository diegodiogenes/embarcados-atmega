volatile int16_t umidade;
volatile int16_t temperatura;

ISR(TIMER0_OVF_vect)
{
  //quando acontece o estouro, é feito a leitura da conversão AD
  ADCSRA |= _BV(ADSC); //Inicia a conversão AD
  while (!(ADCSRA & 0b00010000)); //Aguarda a conversão AD terminar, como foi setado inicialmente no ADMUX, a primeira conversão é de PC0, configurado para o sensor de temperatura
  temperatura = ADC;
  //Como o ADC devolve um valor de 10 bits (de 0 a 1024), e a temperatura vai de 0 a 200 precisamos converter da seguinte maneira:
  temperatura = ADC * (255 / 1024);
  //Setando o valor do ADMUX para conversão do sensor de umidade
  ADMUX |= BV(MUX0); //Recebendo do PC1, fazendo leitura do sensor de umidade
  ADCSRA |= _BV(ADSC); //Inicia a conversão AD
  while (!(ADCSRA & 0b00010000)); //Aguarda a conversão AD terminar
  umidade = (100 * ADC) / 1024; // A umidade pode variar de 0 a 100%
  //Voltando o ADMUX para a configuração inicial
  ADMUX &= 0b0;
}

int main() {
  //Inicialmente setamos os valores dos registradores que serão entrada e saída

  //Colocando os pinos PB1 e PB2 como sendo de saída para o PWM, OC1A e OC1B. PB3,PB4,PB5 como sendo as saídas parada o L1,L2 e L3 e PB0 como sendo a entrada de CH1
  DDRB |= 0b00111110;
  //Setando os registradores PC0 e PC1 como sendo os valores de entrada para ADC0 e ADC1 respectivamente
  DDRC &= 0b00000000;
  /* Configurando o PWM */
  //Definindo os registradores TCCR0A para fast PWM 10 bits não invertido
  TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | BV(WGM10);
  //Setando o prescaler para 1024, o que nos dá 7.8khz
  TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10);
  /* Configurando o contador */
  //O contador TCCR0A não é mexido, mantendo tudo 0, para atuar no modo normal
  //Setamos o prescaler no TCCR0B com 64, nos dando uma interrupção a cada 2ms
  TCCR0B = _BV(CS01) | _BV(CS00);
  //Habilitando interrupção de TC0
  TIMSK0 = _BV(TOIE0);
  //Iniciando nossa configuração da conversão AD
  ADMUX |= _BV(REFS0); // Utilizao VCC como referência, ou seja, 5V; Recebe o sinal na pota PC0 (ADC0)
  //Configurando o ADCSRA
  ADCSRA |= _BV(ADEN) | //Habilita o AD
            0b00000111; //Seta o Prescaler como 128, me dando um limite máximo de 15 kSPS na conversão

  while (1) {
    // Verifica se a chava está como HIGH
    if (PINB & 0b00000001) {
      if (temperatura < 20) {
        PORTB |= _BV(PORTB1);
      } else if (temperatura > 120) {
        PORTB |= _BV(PORTB2);
      } else if {
      PORTB &= 0b0;
      PORTB |= _BV(PORTB3);

        if (umidade == 100) {
          //setando OCR1A como sendo 100%
          OCR1A = 1023;
          //setando OCR1B como sendo 25%
          OCR1B = 0.25 * 1023;
        } else if ( umidade >= 50 && umidade < 100) {
          OCR1A = 0.5 * 1023;
          OCR1B = 0.5 * 1023;
        } else if ( umidade >= 25 && umidade < 50) {
          OCR1A = 0.25 * 1023;
          OCR1B = 1023;
        } else if ( umidade >= 25 && umidade < 50) {
          OCR1A = 0;
          OCR1B = 0;
          PORTB &= 0b0;
        }

      }
    // Caso a chave esteja como LOW tudo estará desligado
    } else {
      PORTB &= 0b0;
    }
  }

}
