#include <LiquidCrystal.h> // Biblioteca para controlar o LCD

// Configuração dos pinos do display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pinos para botões
const int accelButtonPin = 9; // Pino onde o botão de aceleração está conectado
const int brakeButtonPin = 8; // Pino onde o botão de freio está conectado
int accelButtonState = 0; // Variável para armazenar o estado do botão de aceleração
int brakeButtonState = 0; // Variável para armazenar o estado do botão de freio
int lastAccelButtonState = 0; // Variável para armazenar o último estado do botão de aceleração
int speed = 0; // Velocidade inicial
int gear = 1; // Marcha inicial
const int maxSpeed = 300; // Velocidade máxima
unsigned long lastUpdateTime = 0; // Tempo da última atualização
const unsigned long interval = 100; // Intervalo para aumentar a velocidade
const unsigned long decInterval = 200; // Intervalo para diminuir a velocidade
const unsigned long brakeInterval = 50; // Intervalo para frear
int batteryLevel = 5; // Nível inicial da bateria (1 a 5)

// Definição do "emoji" de bateria
byte battery[8] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110
};

void setup() {
  lcd.begin(16, 2); // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.createChar(0, battery); // Cria o caractere personalizado da bateria
  pinMode(accelButtonPin, INPUT); // Configura o pino do botão de aceleração como entrada
  pinMode(brakeButtonPin, INPUT); // Configura o pino do botão de freio como entrada
  
  // Apresentação inicial
  showStartupScreen(); // Chama a função para mostrar a tela de inicialização

  lcd.print("Velocidade:"); // Exibe "Velocidade:" no LCD
  updateLCD(); // Atualiza o LCD com a velocidade e marcha iniciais
}

void loop() {
  accelButtonState = digitalRead(accelButtonPin); // Lê o estado do botão de aceleração
  brakeButtonState = digitalRead(brakeButtonPin); // Lê o estado do botão de freio
  unsigned long currentTime = millis(); // Obtém o tempo atual

  if (accelButtonState == HIGH) {
    if (currentTime - lastUpdateTime >= interval) {
      increaseSpeed(); // Aumenta a velocidade
      lastUpdateTime = currentTime; // Atualiza o tempo da última atualização
    }
  } else if (brakeButtonState == HIGH) {
    if (currentTime - lastUpdateTime >= brakeInterval) {
      brakeSpeed(); // Diminui a velocidade rapidamente
      lastUpdateTime = currentTime; // Atualiza o tempo da última atualização
    }
  } else {
    if (currentTime - lastUpdateTime >= decInterval) {
      decreaseSpeed(); // Diminui a velocidade gradualmente
      lastUpdateTime = currentTime; // Atualiza o tempo da última atualização
    }
  }

  if (accelButtonState != lastAccelButtonState) {
    if (accelButtonState == LOW) {
      lastUpdateTime = millis(); // Reseta o tempo quando o botão é solto
    }
    delay(50); // Debounce delay
  }

  lastAccelButtonState = accelButtonState; // Atualiza o último estado do botão de aceleração
}

void increaseSpeed() {
  int increment = 0;

  // Determina o incremento de velocidade com base na marcha atual
  switch (gear) {
    case 1:
      increment = 20; // Primeira marcha: incrementa rapidamente
      break;
    case 2:
      increment = 15; // Segunda marcha: incrementa rapidamente
      break;
    case 3:
      increment = 12; // Terceira marcha: incrementa de forma moderada
      break;
    case 4:
      increment = 10; // Quarta marcha: incrementa de forma mais lenta
      break;
    case 5:
      increment = 8;  // Quinta marcha: incrementa ainda mais lentamente
      break;
    case 6:
      increment = 6;  // Sexta marcha: incrementa ainda mais lentamente
      break;
    case 7:
      increment = 4;  // Sétima marcha: incrementa suavemente
      break;
    case 8:
      increment = 2;  // Oitava marcha: incrementa suavemente
      break;
  }

  if (speed + increment <= maxSpeed) {
    speed += increment; // Incrementa a velocidade

    // Atualiza a marcha de acordo com a velocidade
    updateGear();
    updateLCD(); // Atualiza o LCD com a nova velocidade e marcha
  } else {
    speed = maxSpeed; // Garante que a velocidade não ultrapasse o máximo
    updateLCD(); // Atualiza o LCD com a velocidade máxima
  }
}

void decreaseSpeed() {
  int decrement = 5; // Definindo uma diminuição gradual

  if (speed - decrement >= 0) {
    speed -= decrement; // Diminui a velocidade

    // Atualiza a marcha de acordo com a velocidade
    updateGear();
    updateLCD(); // Atualiza o LCD com a nova velocidade e marcha
  } else {
    speed = 0; // Garante que a velocidade não seja negativa
    updateLCD(); // Atualiza o LCD com velocidade zero
  }
}

void brakeSpeed() {
  int decrement = 15; // Definindo uma diminuição rápida para frenagem

  if (speed - decrement >= 0) {
    speed -= decrement; // Diminui a velocidade rapidamente

    // Atualiza a marcha de acordo com a velocidade
    updateGear();
    updateLCD(); // Atualiza o LCD com a nova velocidade e marcha
  } else {
    speed = 0; // Garante que a velocidade não seja negativa
    updateLCD(); // Atualiza o LCD com velocidade zero
  }
}

void updateGear() {
  // Atualiza a marcha de acordo com a velocidade
  if (speed < 60) {
    gear = 1;
  } else if (speed < 100) {
    gear = 2;
  } else if (speed < 140) {
    gear = 3;
  } else if (speed < 180) {
    gear = 4;
  } else if (speed < 220) {
    gear = 5;
  } else if (speed < 260) {
    gear = 6;
  } else if (speed < 280) {
    gear = 7;
  } else {
    gear = 8;
  }
}

void updateLCD() {
  lcd.clear(); // Limpa o display LCD
  lcd.setCursor(0, 0); // Move o cursor para a primeira linha
  lcd.print("Velocidade:"); // Exibe o texto "Velocidade:"
  lcd.setCursor(12, 0); // Move o cursor para a posição da velocidade
  lcd.print(speed); // Exibe a velocidade
  lcd.setCursor(0, 1); // Move o cursor para a segunda linha
  lcd.print("Marcha:"); // Exibe o texto "Marcha:"
  lcd.setCursor(8, 1); // Move o cursor para a posição da marcha
  lcd.print(gear); // Exibe a marcha
  lcd.setCursor(12, 1); // Move o cursor para a posição do emoji da bateria
  for (int i = 0; i < batteryLevel; i++) {
    lcd.write(byte(0)); // Exibe o "emoji" da bateria
  }
}

void showStartupScreen() {
  lcd.clear(); // Limpa o display LCD
  lcd.setCursor(0, 0); // Move o cursor para a primeira linha
  lcd.print("Bem-vindo a"); // Exibe o texto "Bem-vindo a"
  lcd.setCursor(0, 1); // Move o cursor para a segunda linha
  lcd.print("LCV Motors!"); // Exibe o texto "LCV Motors!"
  delay(2000); // Espera 2 segundos

  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft(); // Rola o display para a esquerda
    delay(200); // Espera 200 milissegundos
  }

  lcd.clear(); // Limpa o display LCD
  lcd.setCursor(0, 0); // Move o cursor para a primeira linha
  lcd.print("LCV"); // Exibe o texto "LCV"
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(4, 0); // Move o cursor para a posição 4 da primeira linha
    lcd.print(" "); // Exibe um espaço
    delay(300); // Espera 300 milissegundos
    lcd.setCursor(4, 0); // Move o cursor para a posição 4 da primeira linha
    lcd.print("."); // Exibe um ponto
    delay(300); // Espera 300 milissegundos
    lcd.setCursor(5, 0); // Move o cursor para a posição 5 da primeira linha
    lcd.print(" "); // Exibe um espaço
    delay(300); // Espera 300 milissegundos
    lcd.setCursor(5, 0); // Move o cursor para a posição 5 da primeira linha
    lcd.print("."); // Exibe um ponto
    delay(300); // Espera 300 milissegundos
    lcd.setCursor(6, 0); // Move o cursor para a posição 6 da primeira linha
    lcd.print(" "); // Exibe um espaço
    delay(300); // Espera 300 milissegundos
    lcd.setCursor(6, 0); // Move o cursor para a posição 6 da primeira linha
    lcd.print("."); // Exibe um ponto
    delay(300); // Espera 300 milissegundos
  }
  delay(1000); // Espera 1 segundo
  lcd.clear(); // Limpa o display LCD
}
