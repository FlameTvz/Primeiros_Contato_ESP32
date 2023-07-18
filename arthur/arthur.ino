const int pot = 34;             // potenciomentro
const int led1 = 2;             // LEDs
const int led2 = 15;            // LEDs
const int led3 = 12;            // LEDs
const int bot1 = 13;            // Botão
const int bot2 = 22;            // Botão2
unsigned char Flag_Botao = 0;   // Flag do Botão
unsigned char Flag_Botao2 = 0;  // Flag do Botão2
unsigned char Flag_Botao3 = 0;
unsigned long intervalo = 50;

void controlleds(int potana);

void setup() {
  Serial.begin(9600);
  //Define quais as variaveis serao saidas e quais serao entradas
  // attachInterrupt(digitalPinToInterrupt(bot1),controlleds(potana),CHANGE);
  // attachInterrupt(digitalPinToInterrupt(bot1),test1,LOW);
  // attachInterrupt(digitalPinToInterrupt(bot2),flag_bt2,LOW);
  //attachInterrupt(digitalPinToInterrupt(bot2) && digitalPinToInterrupt(bot1),   ,LOW);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
}

void loop() {
  int potana = analogRead(pot);  // Potenciometro Analogico
  controlleds(potana);           // Funçao de Controlar os LEDs
  todas_flags();
}




void todas_flags() {
  if ((digitalRead(bot1) == HIGH || digitalRead(bot2) == HIGH)) {
    if ((digitalRead(bot1) == HIGH && digitalRead(bot2) == HIGH)) {
      if (Flag_Botao3 == 0) {
        delay(100);
        while (digitalRead(bot1) == HIGH || digitalRead(bot2) == HIGH)
          ;
        Flag_Botao3 = 1;
      }
     
      else {
        while (digitalRead(bot1) == HIGH || digitalRead(bot2) == HIGH)
          ;
        if (Flag_Botao3 == 1) {
          Flag_Botao3 = 0;  // Reiniciar a Flag_Botao3 para 0
        }
      }
    }

    else {

      if (digitalRead(bot1) == HIGH) {
        if (Flag_Botao == false) {
          delay(10);
          while (digitalRead(bot1) == HIGH)
            Flag_Botao = true;
        } else {
          if (Flag_Botao == true) {
            delay(10);
            while (digitalRead(bot1) == HIGH)
              Flag_Botao = false;
          }
        }
      }

      else {
        if (digitalRead(bot2) == HIGH) {
          if (Flag_Botao2 == false) {
            delay(10);
            while (digitalRead(bot2) == HIGH)
              Flag_Botao2 = true;
          }

          else {
            if (Flag_Botao2 == true) {
              delay(100);
              while (digitalRead(bot2) == HIGH)
                Flag_Botao2 = false;
            }
          }
        }
      }
    }
  }
}
  void desliga() {
    if (Flag_Botao3 == 1) {
      delay(intervalo);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      delay(intervalo);
    }
  }


  void controlleds(int potana) {
    int porcentagem = map(potana, 0, 4095, 0, 100);
    delay(50);



    if (Flag_Botao2 == 1) {

      if (!Flag_Botao) {
        digitalWrite(led1, porcentagem >= 25 && porcentagem < 50);
        digitalWrite(led2, porcentagem >= 50 && porcentagem < 75);
        digitalWrite(led3, porcentagem >= 75);
        desliga();
      } else {
        digitalWrite(led3, porcentagem >= 25 && porcentagem < 50);
        digitalWrite(led2, porcentagem >= 50 && porcentagem < 75);
        digitalWrite(led1, porcentagem >= 75);
        desliga();
      }
    } else {
      if (!Flag_Botao) {
        digitalWrite(led1, porcentagem >= 25);
        digitalWrite(led2, porcentagem >= 50);
        digitalWrite(led3, porcentagem >= 75);
        desliga();
      } else {
        digitalWrite(led1, porcentagem >= 75);
        digitalWrite(led2, porcentagem >= 50);
        digitalWrite(led3, porcentagem >= 25);
        desliga();
      }
    }
  }
