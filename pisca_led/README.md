## Piscando LED utilizando contador/temporizador do ATMega 328p

Programa utiliza os registradores TCCR0A e TCCR0B.

Registradores que não estão setados, recebem o valor default, ou seja, 0. Não trabalhamos diretamente com o registrador TCCR0A que está atuando no modo normal, pois todos os valores estão como 0.

Setamos os valores de CS02 e CS00 para o prescaler (divisão de clock) de 1024.

Utilizamos também o registrador de interrupção TIMSK0, deixando TOIE0 como HIGH para habilitarmos a interrupção de estouro.

Calculamos em quanto tempo a interrupção é chamada através da fórmula:

![](https://imgur.com/a/GVkFn8K)
