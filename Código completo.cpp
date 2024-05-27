/* IFPB CAMPUS JOÃO PESSOA - TRABALHO DE CONCLUSÃO DE CURSO TÉCNICO EM ELETRÔNICA INTEGRADO AO ENSINO MÉDIO - HIDROPONIA VERTICAL MICROCONTROLADA;
Autores: Ronaldo Urquiza Herculano Filho e Juliana Oliveira Galdino dos Santos;
Orientador: Hélder Cavalcante Nascimento.

Agradecimentos especiais à Ana Schenkel, Jonatas Souza e Igor Stephan.

ESSA PROGRAMAÇÃO FOI DESENVOLVIDA COM A INTENÇÃO DE INTEGRAR 3 SENSORES DIFERENTES COM UM DISPLAY LCD PARA O SENSORIAMENTO DE UMA TORRE AEROPÔNICA */

/*BIBLIOTECAS ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <OneWire.h> // Inclui a biblioteca "OneWire".
#include <DallasTemperature.h> // Inclui a biblioteca "DallasTemperature".
#include <EEPROM.h> // Inclui a biblioteca "EEPROM".
#include "GravityTDS.h" // Inclui a biblioteca "GravityTDS".
#include <LiquidCrystal.h> // Inclui a biblioteca "LiquidCrystal".
/*BIBLIOTECAS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*PORTAS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#define ONE_WIRE_BUS 6 // Porta em que o sensor de temperatura está (Arduin DB6).
#define TdsSensorPin A0 // Porta em que o sensor de condutividade está (Arduin A0).
#define leiturasensor A1 // Porta em que o sensor de pH está (Arduin A1).
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Identificação dos pinos do LCD no arduino.
/*PORTAS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*OPERAÇÃOES DAS BILIOTECAS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
OneWire oneWire(ONE_WIRE_BUS); // Configur a instância oneWire para comunicar com qualquer outro dispositivo OneWire (não apenas ICs de temperature da Maxim/Dallas).
DallasTemperature sensors(&oneWire); // Passa a referência oneWire para a Dallas Temperature.
GravityTDS gravityTds; // Operação da biblioteca GravityTDS.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Procedimento padrão da biblioteca LiquidCrystal para a identificação do  s pinos do LCD.
/*OPERAÇÃOES DAS BILIOTECAS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*FUNÇÕES --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
float TEMP(); // Criando função para o sensor de temperatura.
float TDS(); // Criando função para o sensor de condutividade.
float PH(); // Criando função para o sensor de acidez e basicidade.
float MediaTensaopH(); // Criando função para obter os valores da sonda de pH.
/*FUNÇÕES --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*VARIÁVEIS INDEPENDENTES --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/ 

/*Comentário: Declaramos várias variáveis e atribuimos o valor '0' a todas elas pois essa é uma forma de garantir que a variável irá inicializar limpa, sem nenhum valor, para assim ser utilizada sem nenhum problema*/

float tempC = 0; // Criando uma variável do tipo float com o nome  “tempC“ e atribuindo-a o valor 0.
float temperature = 25; // Criando uma variável do tipo float com o nome  “temperature“ e atribuindo-a o valor 25.
float tdsValue = 0; // Criando uma variável do float com o nome “tdsValue“.
float tdsC = 0; // Criando uma variável do tipo float com o nome “tdsC“ e atribuindo-a o valor 0.
int temp = 0; // Criando uma variável do tipo inteira com o nome “temp“.
float p = 0; // Criando uma variável do float com o nome “p“.

/* -> SUBTÓPICO DAS VARIÁVEIS INDEPENDENTES: VARIÁVEIS PARA A CALIBRAÇÃO DA SONDA PH */

int N = 29; // Criando uma variável do tipo inteira com o nome “N“ e atribuindo-a o valor 29.
float sensor = 0; // Criando uma variável do tipo float com o nome “sensor“ e atribuindo-a o valor 0.
float tensao = 0; // Criando uma variável do tipo float com o nome “tensao“ e atribuindo-a o valor 0.
float ph2 = 6.86; // Criando uma variável do float com o nome “ph2“ e atribuindo-a o valor 6.86.  // IMPORTANTE!!!! : ALTERE ESSE PRIMEIRO VALOR DE PH "6.86" PARA A CONCENTRAÇÃO DA SUA SOLUÇÃO DE CALIBRAÇÃO 1.
float ph1 = 4.01; // Criando uma variável do float com o nome “ph1“ e atribuindo-a o valor 4.01. // IMPORTANTE!!!! : ALTERE ESSE SEGUNDO VALOR DE PH "4.01" PARA A CONCENTRAÇÃO DA SUA SOLUÇÃO DE CALIBRAÇÃO 2.
float a = 0; // Criando uma variável do tipo float com o nome “a" e atribuindo-a o valor 0.
float b = 0; // Criando uma variável do tipo float com o nome “b“ e atribuindo-a o valor 0.
float v1 = 0; // Criando uma variável do tipo float com o nome “v1“ e atribuindo-a o valor 0.
float v2 = 0; // Criando uma variável do tipo float com o nome “v2“ e atribuindo-a o valor 0.
float MediaphC = 0; // Criando uma variável do tipo float com o nome “MediaphC“ e atribuindo-a o valor 0.
int i = 0; // Criando uma variável do tipo inteira com o nome “i“ e atribuindo-a o valor 0.
float phC = 0; // Criando uma variável do tipo float com o nome “phC“ e atribuindo-a o valor 0.
char switchCases = 'A'; // Criando uma variável do tipo char com o nome “switchCases“ e atribuindo-a o caractere 'A'.

/* -> SUBTÓPICO DAS VARIÁVEIS INDEPENDENTES: VARIÁVEIS PARA A CALIBRAÇÃO DA SONDA PH*/

/*VARIÁVEIS INDEPENDENTE --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() // Função que inicializa diversas operações do código.
{
  pinMode(leiturasensor, INPUT); // Define a porta em que o sensor de pH está (Arduin A1) como INPUT, ou seja, entrada de dados.
  Serial.begin(9600); // Começando Serial na velocidade de 9600 bits por segundo.
  Serial.println("Para entrar no modo de calibracao da sonda pH digite 1 e pressione as tecla ctrl+enter e para entrar na calibracao do sensor de condutividade digite 'enter' e pressione as teclas ctrl+enter"); // Escreve a mensagem anterior no monitor serial.
  lcd.begin(16, 2); // Configura o número de colunas e linhas do LCD:
  sensors.begin(); // Inicialização da biblioteca do sensor de temperatura.
  gravityTds.setPin(TdsSensorPin); // Comando para "setar" o pino em que o sensor está conectado no Arduíno, a porta já foi identificada na parte superior da programação.
  gravityTds.setAref(5.0); // Tensão de refência em ADC, padrão 5V do Arduino UNO.
  gravityTds.setAdcRange(1024); // 1024 para 10bit ADC, 4096 para 12bit ADC.
  gravityTds.begin(); // Inicialização do sensor de condutividade.
}

void loop() // Iniciando a função de repetição do código, esse é a parte da programação que irá ser executada constantemente infinitas vezes.
 {
   
/* Comentário: É aqui onde todos valores lidos pelos sensores e manipulados pelas funções estão sendo utilizados, os valores de cada função são "puxados" por esse laço de repetição.
Dessa forma, é possível exibir visualmente no display LCD cada respota de cada sensor através da atribuição dos valores armazenados das suas funções à variáveis x, y e z */
  
  float x = TEMP(); // Atribuindo o valor que a função de Temperatura retorna à variável "x"
  float y = TDS(); // Atribuindo o valor que a função de Condutividade retorna à variável "y"
  float z = PH(); // Atribuindo o valor que a função de pH retorna à variável "z"
  lcd.setCursor(0,0); // Define o cursor do LCD na linha e na coluna inicial.
  lcd.print(" PH   TDS   TEMP"); // Escreve "PH    TDS   TEMP" no LCD.
    lcd.setCursor(0,1); // Define o cursor do LCD na coluna inicial e na linha de baixo.
    lcd.print(z,1); // Escreve o valor do pH com limite de 2 casas decimais.
  	lcd.setCursor(6,1); // Define o cursor do LCD na coluna 7 e na linha de baixo.
    lcd.print(y,0); // Escreve o valor da condutividade elétrica sem casas decimais.
  	lcd.setCursor(12,1); // Define o cursor do LCD na coluna 14 e na linha de baixo.  
    lcd.print(x,1); // Escreve o valor da temperatura com limite de 1 casa decimal.
    delay(500); // Espera 500 milissegundos para repetir o mesmo procedimento.
     
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

  } // Chave que fecha a estrutura do void loop.

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

float PH() // Criando função para o sensor de pH.
{
  p = (a * float(analogRead(leiturasensor)*0.00488) + b); // Equacionamento matemático baseado numa função afim "f=a*x+b" utilizando os valores das variáveis do menu de calibração e os valores que retornam da sonda pH para disponibilizar uma leitura constante do sensor em uma escala entendível que é a de acidificação e basicidade (0.00 - 14.00).
  //Serial.println(p); // Linha extra para teste da função, visualiza a varíavel 'p' após o equacionamento matemático.
  phC = p; // Atribui à variável "phC" o valor "p" que foi o resultado do equacionamento matemático para leitura do sensor de pH.
  return phC; // Retorna 'phC', resultado da função que será utilizado no void loop.
}
