#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// Configuração do display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7

Servo myServo;  // cria objeto servo

const String senhaCorreta = "1234";  // senha correta
String senhaInserida = "";  // string para armazenar senha digitada

// Configuração do teclado numérico
const byte ROWS = 4; // quatro linhas
const byte COLS = 4; // quatro colunas
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // pinos de conexão das linhas
byte colPins[COLS] = {A3, A2, A1, A0}; // pinos de conexão das colunas

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  myServo.attach(10);  // conecta o servo ao pino 10
  myServo.write(0);  // inicializa o servo fechado (porta trancada)
  
  Serial.begin(9600);  // inicializa a comunicação serial

  lcd.begin(16, 2);  // inicializa o LCD com 16 colunas e 2 linhas
  lcd.print("Insira a senha:");
  delay(2000);  // tempo para ler a mensagem
  lcd.clear();  // limpa o display
}

void loop() {
  char key = keypad.getKey();

  if (key) {  // se uma tecla foi pressionada
    if (key == '#') {  // '#' para confirmar a senha
      if (senhaInserida == senhaCorreta) {
        lcd.clear();
        lcd.print("Senha correta!");
        Serial.println("Senha correta! Abrindo a porta...");
        myServo.write(90);  // abre a porta
        delay(5000);  // mantém a porta aberta por 5 segundos
        myServo.write(0);  // fecha a porta
        lcd.clear();
        lcd.print("Porta fechada.");
        delay(2000);
      } else {
        lcd.clear();
        lcd.print("Senha incorreta!");
        Serial.println("Senha incorreta.");
        delay(2000);  // tempo para ler a mensagem
      }
      senhaInserida = "";  // reseta a senha inserida
      lcd.clear();
      lcd.print("Insira a senha:");

  } else if (key == '*') {  // '*' para apagar a senha
      senhaInserida = "";
      lcd.clear();
      lcd.print("Senha apagada.");
      Serial.println("Senha apagada.");
      delay(2000);
      lcd.clear();
      lcd.print("Insira a senha:");

  } else {
      senhaInserida += key;  // adiciona o número pressionado à senha
      lcd.clear();
      lcd.print("Senha: ");
      lcd.print(senhaInserida);  // exibe a senha inserida
      Serial.print("Senha inserida: ");
      Serial.println(senhaInserida);
    }
  }
}
