#include <LiquidCrystal_I2C.h>
// Configuração do LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27, 16 colunas, 2 linhas
// Pinos
#define SENSOR_PIN 34     // Potenciômetro no GPIO34
#define IRRIGATION_PIN 2  // Pino do relé/LED no GPIO2
// Parâmetros de controle
const int UMIDADE_MINIMA = 30;  // Liga irrigação abaixo deste valor
const int UMIDADE_MAXIMA = 70;  // Desliga irrigação acima deste valor
const int INTERVALO = 1000;     // Intervalo entre leituras (1s)
// Variáveis
int umidade = 0;
bool irrigacaoLigada = false;
void setup() {
Serial.begin(115200);
// Configura pinos
pinMode(IRRIGATION_PIN, OUTPUT);
digitalWrite(IRRIGATION_PIN, LOW);
// Inicializa LCD
lcd.init();
lcd.backlight();
mostrarMensagemInicial();
}
void loop() {
// Lê e converte a umidade (0-100%)
umidade = map(analogRead(SENSOR_PIN), 0, 4095, 0, 100);
// Controle da irrigação
if (umidade < UMIDADE_MINIMA && !irrigacaoLigada) {
ligarIrrigacao();
} 
else if (umidade >= UMIDADE_MAXIMA && irrigacaoLigada) {
desligarIrrigacao();
}
// Atualiza display e serial
atualizarDisplay();
enviarParaSerial();
delay(INTERVALO);
}
void ligarIrrigacao() {
digitalWrite(IRRIGATION_PIN, HIGH);
irrigacaoLigada = true;
lcd.setCursor(0, 0);
lcd.print("IRRIGACAO LIGADA ");
Serial.println("Irrigação LIGADA");
}
void desligarIrrigacao() {
digitalWrite(IRRIGATION_PIN, LOW);
irrigacaoLigada = false;
lcd.setCursor(0, 0);
lcd.print("IRRIGACAO DESLIG.");
Serial.println("Irrigação DESLIGADA");
}
void atualizarDisplay() {
// Linha inferior: mostra umidade
lcd.setCursor(0, 1);
lcd.print("Umidade: ");
lcd.print(umidade);
lcd.print("%  ");
}
void enviarParaSerial() {
Serial.print("Umidade: ");
Serial.print(umidade);
Serial.print("% | Irrigação: ");
Serial.println(irrigacaoLigada ? "LIGADA" : "DESLIGADA");
}
void mostrarMensagemInicial() {
lcd.setCursor(0, 0);
lcd.print("Controle de");
lcd.setCursor(0, 1);
lcd.print("Irrigacao");
delay(2000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Status:");
lcd.setCursor(0, 1);
lcd.print("Umidade: ");
}