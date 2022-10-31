float PH() // Criando função para o sensor de pH.
{
  p = (a * float(analogRead(leiturasensor)*0.00488) + b); // Equacionamento matemático baseado numa função afim "f=a*x+b" utilizando os valores das variáveis do menu de calibração e os valores que retornam da sonda pH para disponibilizar uma leitura constante do sensor em uma escala entendível que é a de acidificação e basicidade (0.00 - 14.00).
  //Serial.println(p); // Linha extra para teste da função, visualiza a varíavel 'p' após o equacionamento matemático.
  phC = p; // Atribui à variável "phC" o valor "p" que foi o resultado do equacionamento matemático para leitura do sensor de pH.
  return phC; // Retorna 'phC', resultado da função que será utilizado no void loop.
}
