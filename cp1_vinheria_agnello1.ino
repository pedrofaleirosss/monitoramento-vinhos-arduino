// C++ Code
// CP1 - Edge Computing & Computer Sistems
// Pedro Faleiros 562523
// Luan Felix 565541
// João Lopes 565737
// Felipe Campos 562752
// Leandro Farias 566488

// Biblioteca para o display LCD
#include <LiquidCrystal.h>

// Pinos de controle do LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Pinos dos LEDs e buzzer
const int ldrPin = A0;
const int ledVerde = 8;
const int ledAmarelo = 7;
const int ledVermelho = 6;
const int buzzer = 13;

// Caracteres personalizados para o desenho no display LCD
byte image17[8] = {B01100, B01000, B10000, B00000, B00000, B00000, B00000, B00000};
byte image01[8] = {B00000, B00000, B00001, B00010, B00010, B00100, B00100, B00100};
byte image02[8] = {B00111, B11000, B00100, B00010, B00001, B00010, B00100, B00000};
byte image03[8] = {B00000, B11000, B00100, B00010, B00010, B00001, B00000, B00000};
byte image04[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B10000, B01000};
byte image20[8] = {B11000, B01000, B10000, B00000, B00000, B00000, B00000, B00000};
byte image19[8] = {B10101, B01010, B00000, B01111, B11000, B10000, B00000, B00000};
byte image18[8] = {B00100, B00011, B00000, B00000, B00000, B00001, B00001, B00001};

void desenhaLogo() {
  // Desenha a logo usando os caracteres personalizados
  lcd.setCursor(0, 1); lcd.write(byte(0));
  lcd.setCursor(0, 0); lcd.write(byte(1));
  lcd.setCursor(1, 0); lcd.write(byte(2));
  lcd.setCursor(2, 0); lcd.write(byte(3));
  lcd.setCursor(3, 0); lcd.write(byte(4));
  lcd.setCursor(3, 1); lcd.write(byte(5));
  lcd.setCursor(2, 1); lcd.write(byte(6));
  lcd.setCursor(1, 1); lcd.write(byte(7)); 
}

void setup()
{
  // Define os pinos dos LEDs e buzzer como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Registra os caracteres personalizados no LCD
  lcd.createChar(0, image17);
  lcd.createChar(1, image01);
  lcd.createChar(2, image02);
  lcd.createChar(3, image03);
  lcd.createChar(4, image04);
  lcd.createChar(5, image20);
  lcd.createChar(6, image19);
  lcd.createChar(7, image18);

  // Inicializa comunicação serial para debug
  Serial.begin(9600);
  
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16,2);
  lcd.clear();
  
  // Mostra o mascote no LCD
  desenhaLogo();
  
  // Mensagem ao lado do desenho
  lcd.setCursor(5, 0);
  lcd.print("DevZilla");
  lcd.setCursor(5, 1);
  lcd.print("Bem-vindo!");
}

void loop()
{
  // Garante que o LCD continue visível
  lcd.display(); 
  
  int leituraLDR = 0; // Variável que guarda o valor do ldr
  const int numMedicoes = 10; // Número de medições para fazer a média
  String status = ""; // Variável que guarda o status da vinheria
  
  // Faz 10 leituras e soma
  for (int i = 0; i < numMedicoes; i++) {
    leituraLDR += analogRead(ldrPin);
    delay(10); // Pequeno delay entre leituras para dar tempo de estabilizar
  }

  // Calcula a média
  leituraLDR = leituraLDR / numMedicoes;
  
  // Mapeia para porcentagem de 0 a 100%
  int luminosidadePercent = map(leituraLDR, 54, 974, 0, 100);

  // Exibe o valor da luminosidade no monitor serial
  Serial.print("Luminosidade: ");
  Serial.print(luminosidadePercent);
  Serial.println("%");

  // Reseta os sinais visuais e sonoros antes de avaliar a condição
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  noTone(buzzer);

  // Verifica em qual faixa a luminosidade está e aciona os sinais correspondentes
  if (luminosidadePercent <= 40) {
    // Ambiente ideal - Acende led verde
    status = "Ideal";
    digitalWrite(ledVerde, HIGH);
    delay(3000);
  } else if (luminosidadePercent <= 60) {
    // Alerta - Acende led amarelo e toca buzina 
    status = "Alerta";
    digitalWrite(ledAmarelo, HIGH);
    tone(buzzer, 150); // Frequência de 150 Hz
  	delay(3000); // Dura 3 segundos
  	noTone(buzzer); // Para o som
  } else {
    // Crítico - Acende led vermelho e toca buzina
    status = "Critico";
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 200); // Frequência de 200 Hz
  	delay(3000); // Dura 3 segundos
  	noTone(buzzer); // Para o som
  }
  
  // Limpa a tela do LCD
  lcd.clear();
  
  // Mostra o mascote no LCD
  desenhaLogo();
  
  // Mostra o valor da % de luminosidade no LCD
  lcd.setCursor(5, 0);
  lcd.print("Luz:");
  lcd.print(luminosidadePercent);
  lcd.print("%");
  
  // Mostra o status (Ideal, Alerta, Crítico) no LCD
  lcd.setCursor(5, 1);
  lcd.print(status);

  delay(1000); // Espera 1 segundo antes da próxima medição
}