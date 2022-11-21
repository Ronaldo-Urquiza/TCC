/*Comentário: É aqui onde incia-se o nosso menu de calibração para a sonda de pH através do monitor serial, totalmente construido do 0 através da estrutura "switchCase" */

 char switchCases = 'A'; // Se certifica e força a varíavel do tipo char de nome "switchCases" a inicializar com o caractere 'A', tal atribuição foi feita para resolver um problema em que o menu de calibração da sonda pH não incializava com nenhum caractere descrito no switchcase no montitor serial.
 switchCases = Serial.read(); // Lê dados recebidos na porta serial e atribui à variável 'switchCases'.
 switch (switchCases) { // Inicia a estrutura do switchCase (menu de calibração) baseado na variável switchCases.

  case '1': // Esse caso introduz o usuário a como usar o menu de calibração de pH
   Serial.println(); // Pula uma linha no monitor serial.
   Serial.println("Entrando no modo de calibracao da sonda pH..."); // Escreve a mensagem "Entrando no modo de calibracao da sonda pH..." no monitor serial.
   Serial.println("Para calibrar o sensor coloque-o na solucao de calibracao 1 (6.86pH) e digite 2, depois coloque-o na solucao de calibracao 2 (4.01pH) e digite 3"); // Escreve a mensagem "Para calibrar o sensor coloque-o na solucao basica e digite 2, depois coloque-o na solucao acida e digite 3" no monitor serial.
  break; // Finaliza o caso 1 (procedimento padrão da estrutura switchCase).

  case '2': // Esse caso atribui à variável 'v2' a tensão da solução de pH 6.86;
   v2 = MediaTensaopH(leiturasensor); // Atribui à variável 'v2' o valor da função 'MediaTensaopH' que proveu valores retificados da leitura da porta análogica em que o sensor de pH está conectado.
   Serial.println(); // Pula uma linha no monitor serial.
   Serial.println("Voce colocou o sensor na solucao neutra e o valor foi armazenado."); // Escreve a mensagem "Voce colocou o sensor na solucao neutra e o valor foi armazenado." no monitor serial.
  break; // Finaliza o caso 2 (procedimento padrão da estrutura switchCase).

  case '3': // Esse caso é o mais importante da calibração, além de atribuir a tensão da solução de pH 4.011 à variável 'v1' ele, de fato, realiiza a calibração da sonda pH através das formulações matemáticas que tem os seus resultados atribuidos às variáveis 'a' e 'b'.
    v1 = MediaTensaopH(leiturasensor); // Atribui à variável 'v1' o valor da função 'MediaTensaopH' que proveu valores retificados da leitura da porta análogica em que o sensor de pH está conectado.
    Serial.println(); // Pula uma linha no monitor serial.
    Serial.println("Voce colocou o sensor na solucao acida e o valor foi armazenado."); // Escreve a mensagem "Voce colocou o sensor na solucao acida e o valor foi armazenado." no monitor serial.
    ///Serial.println(v2); // Linha teste para escrever o valor atribuido à variável 'v2' no monitor serial.  
    ///Serial.println(v1); // Linha teste para escrever o valor atribuido à variável 'v1' no monitor serial.  
    a = ((ph2-ph1)/(v2-v1)); // Atribui à variável 'a' o resultado do equacionamento matemático "((ph2-ph1)/(v2-v1));"
    b = ph2-a*v2; // Atribui à variável 'b' o resultado do equacionamento matemático "ph2-a*v2"
    //Serial.println(a); // Linha teste para escrever o valor atribuido à variável 'a' no monitor serial.
    //Serial.println(b); // Linha teste para escrever o valor atribuido à variável 'b' no monitor serial.  
    Serial.println("Sensor calibrado com sucesso! Digite '4' caso queira ver as tensoes das respectivas solucoes ou '5' caso queira ver a formulacao da calibracao."); // Escreve a mensagem "Sensor calibrado com sucesso! Digite '4' caso queira ver as tensoes das respectivas solucoes ou '5' caso queira ver a formulacao da calibracao." no monitor serial.
  break; // Finaliza o caso 3 (procedimento padrão da estrutura switchCase).

  case '4': // Esse caso é de exemplificação, ele irá mostrar os valores atribuídos às variáveis 'v1' e 'v2', que são as tensões lidas das respectivas soluções.
    Serial.println(); // Pula uma linha no monitor serial.
    Serial.println("Tensoes das solucoes passadas:"); // Escreve a mensagem "Tensoes das solucoes passadas:" no monitor serial.
    Serial.println(v1); // Escreve o valor atribuido à variável 'v1' no monitor serial.
    Serial.println(v2); // Escreve o valor atribuido à variável 'v2' no monitor serial.
  break; // Finaliza o caso 4 (procedimento padrão da estrutura switchCase).

  case '5': // Esse caso irá mostrar a formulação matemática escrita e detalhada da calibração da sonda pH.
  
  // Fórmula padrão para a calibração da sonda pH: y = ax + b. // y = "ph1" // a = "a" // x = "v1".

    Serial.println(); // Pula uma linha no monitor serial.
    Serial.println("Formulacao:"); // Escreve a mensagem "Formulacao:" no monitor serial.
    Serial.print("y="); // Escreve a mensagem "y=" no monitor serial.
    Serial.print(a); // Escreve o valor atribuido à variável 'a' no monitor serial.
    Serial.print("*x"); // Escreve a mensagem "*x" no monitor serial.
    Serial.print("+"); // Escreve a mensagem "+" no monitor serial.
    Serial.println(b); // Escreve o valor atribuido à variável 'b' no monitor serial.  
  break; // Finaliza o caso 5 (procedimento padrão da estrutura switchCase).

 } // Chave que fecha a estrutura do switch case.
