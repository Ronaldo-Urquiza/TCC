float MediaTensaopH(int pino) // Criando função para realizar a média de tensão da sonda de pH.
{
  /*Comentário: Aqui foi criado uma estrutura para obter 29 valores da sonda pH e realizar uma média de tensão capaz de assegurar uma maior segurança no aferimento da solução nutritiva */

  for(i=0; i<N; i++){ // Criando um laço de repetição com "for" que faz com que a variável "i" incialize com 0 e incremente +1 até 'N' vezes (29 vezes),
  sensor = float(analogRead(pino)); // Atribui à variável 'sensor' o valor da leitura analógica da sonda pH.
  tensao += sensor * (5.0 / 1023.0); // É realizado uma divisão entre (5.0 / 1023.0) e o resultado dessa operação é multiplicado com o valor atribuído à variável 'sensor' e o valor atribuído à variável 'tensao' será o valor atribuído à variável 'tensao' mais o resultado da operação descrita anteriormente.
  //Serial.println(tensao); // Linha extra para teste da função, visualiza a varíavel 'tensao', após o desenvolvimento da função.
  } i = 0; // Zera a varíavel "i" para o laço de repetição ser executado novamente sem complicações no futuro.
  tensao /= N; // 'tensao' será 'tensao' dividido por 'N' (29).
  MediaphC = tensao; // Atribui à variável 'MediaphC' o valor da variável 'tensao'.
  //Serial.print(tensao,4); // Linha extra para teste da função, visualiza a varíavel 'tensao', com um limite de 4 casas decimais, após o desenvolvimento da função.
  //Serial.println(MediaphC); // Linha extra para teste da função, visualiza a varíavel 'MediaphC' após o desenvolvimento da função.
  return MediaphC; // Retorna 'MediaphC', resultado da função que será utilizado na função do sensor de pH propriamente dito.
}
