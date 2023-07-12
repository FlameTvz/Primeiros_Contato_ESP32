const int pot = 34;                 // potenciomentro
const int led1 = 2;                 // LEDs
const int led2 = 15;                // LEDs
const int led3 = 12;                // LEDs
const int bot1 = 13;                // Botão
const int bot2 = 22;                // Botão2
unsigned char invertordem = false;  // Variável para controlar a inversão da ordem dos LEDs
unsigned char invertordem2 = false;  // Variável para controlar a inversão da ordem dos LEDs 2
unsigned char Trata_Botao = 0;      // Tratamento do Botão
unsigned char Trata_Botao2 = 0;      // Tratamento do Botão2
unsigned char Flag_Botao = 0;       // Flag do Botão
unsigned char Flag_Botao2 = 0;      // Flag do Botão2



void setup() {
  Serial.begin(9600);
  //Define quais as variaveis serao saidas e quais serao entradas
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
}

void loop() {
  delay(10);
  int potana = analogRead(pot);         // Potenciometro Analogico
  int estadobotao = digitalRead(bot1);  //
  // outro_modo(potana);                   // Novo modo de acender os LEDs
  controlleds(potana);                  // Funçao de Controlar os LEDs


  //o Botao esta como PULLDOWN, por isso começar com HIGH
  if (digitalRead(bot1) == HIGH) {
    if (Flag_Botao == false) {
      delay(100);  // Aguarda um curto período para evitar leituras falsas
      if(digitalRead(bot1) == HIGH)
      Flag_Botao = true;  //
    }

  } else {
    if (Flag_Botao == true) {
      delay(100);
      if (digitalRead(bot1) == HIGH)
      Flag_Botao = false;
    }
    // delay(100);
  }

  if (Flag_Botao) {
    if (Trata_Botao) {
      if (invertordem)
        invertordem = 0;
      else
        invertordem = 1;
      Trata_Botao = 0;
    }

  } else {
    Trata_Botao = 1;
  }


  if (digitalRead(bot2) == HIGH) {
    if (Flag_Botao2 == false) {
      delay(100);  // Aguarda um curto período para evitar leituras falsas
      if (digitalRead(bot2) == HIGH)
        Flag_Botao2 = true;  //
    }

  } else {
    if (Flag_Botao == true) {
      delay(100);
      if (digitalRead(bot2) == HIGH)
        Flag_Botao2 = false;
    }
    // delay(100);
  }

  if (Flag_Botao2) {
    if (Trata_Botao2) {
      if (invertordem2)
        invertordem2 = 0;
      else
        invertordem2 = 1;
      Trata_Botao2 = 0;
    }

  } else {
    Trata_Botao2 = 1;
  }

  delay(100);
}


void controlleds(int potana) {
  int porcentagem = map(potana, 0, 4095, 0, 100);
  delay(50);
  if (Flag_Botao2 == 1){
  if (!Flag_Botao) {
    digitalWrite(led1, porcentagem >= 25 && porcentagem < 50);
    digitalWrite(led2, porcentagem >= 50 && porcentagem < 75);
    digitalWrite(led3, porcentagem >= 75);
  } else {
    digitalWrite(led3, porcentagem >= 10 && porcentagem < 80);
    digitalWrite(led2, porcentagem >= 80 && porcentagem < 90);
    digitalWrite(led1, porcentagem >= 90);
  }
  }
  else{
    if(!Flag_Botao)
    {
      digitalWrite(led1, porcentagem >= 25);
      digitalWrite(led2, porcentagem >= 50);
      digitalWrite(led3, porcentagem >= 75);
  }
  else{
      digitalWrite(led1, porcentagem >= 75);
      digitalWrite(led2, porcentagem >= 50);
      digitalWrite(led3, porcentagem >= 25);
  }
  }
}
