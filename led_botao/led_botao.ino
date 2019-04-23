/*
  Projeto Arduino acendendo e apagando o led com botão.
  Por Diego Diógenes
*/


//Função main
int main() {

  //Declaração de inputs e outputs, onde PB0 é definido como output e PB1 é input
  DDRB = 0b00000001;

  //Laço infinito
  while (1) {
    //Se PB1 tiver HIGH, então acende o LED
    if (PINB & 0b00000010) {
      //Acende o LED em PB0
      PORTB |= 0b00000001;
    } else {
      //Apaga o LED em PB0
      PORTB |= 0b00000000;
    }
  }

}
