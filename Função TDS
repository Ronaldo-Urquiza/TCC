float TDS() // Criando função para o sensor de condutividade.
{
  
/*Comentário: Aqui utiliza-se bastante das funções e seus processos já concebidos pela biblioteca da empresa que criou esse sensor de condutividade. Para maiores consultas e entendimento acesse a biblioteca "GravityTDS" no google e estude suas funções! */

  gravityTds.setTemperature(temperature);  // Define a temperatura e executa a compensação de temperatura.
  gravityTds.update();  // Recebe uma amostra do sensor e realiza o cálculo da biblioteca do sensor de condutividade para obtenção de um valor entendível.
  tdsC = gravityTds.getTdsValue();  // Atribui à variável, com o nome 'tdsC', o resultado do cáculo anterior.
  
  //Serial.println(tdsC); // Linha extra para teste da função, escreve o valor que foi atribuido à variável 'tdsC' no monitor serial.
  //Serial.println("ppm"); // Linha extra para teste da função, escreve "ppm" no monitor serial.
  
  return tdsC; // Retorna 'tdsC', resultado da função que será utilizado no void loop.
}
