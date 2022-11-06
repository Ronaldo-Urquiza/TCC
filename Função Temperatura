float TEMP() // Criando função para o sensor de temperatura.
{

/*Comentário: Aqui utiliza-se bastante das funções e seus processos já concebidos pela biblioteca da empresa que criou esse sensor de temperatura. Para maiores consultas e entendimento acesse a biblioteca "DallasTemperature" no google e estude suas funções! */
  
  sensors.requestTemperatures(); // Comando para obter a temperatura do sensor, esse comando é pré-fabricado da biblioteca do sensor de temperatura.
  float tempC = sensors.getTempCByIndex(0); // Recebe uma amostra do sensor e realiza o cálculo da biblioteca do sensor de temperatura para obtenção de um valor entendível e atribui à variável do tipo float, com nome 'tempC', o resultado desse cálculo.
  
    if (tempC != DEVICE_DISCONNECTED_C) // Se a temperatura foi realizada com sucesso...
    {
      //Serial.print("A temperatura é: "); // Escreve "A temperatura é: " no monitor serial.
      //Serial.println(tempC); // Escreve "tempC" no monitor serial.
    }
    else // Se a temperatura não foi realizada com sucesso...
    {
      //Serial.println("Ops! Nenhuma leitura de temperatura foi realizada");  // Escreve "Ops! Nenhuma leitura de temperatura foi realizada" no monitor serial.
    }
  
  return tempC; // Retorna 'tempC', resultado da função que será utilizado no void loop.
}
