#include <Servo.h> 

const byte LINHAS = 4;
const byte COLUNAS = 4;

byte pinosLinhas[LINHAS] = {6, 7, 8, 9};
byte pinosColunas[COLUNAS] = {2, 3, 4, 5};

char matrizTeclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 

char senhaCorreta[5] = "123A"; 
char senhaDigitada[5];   
byte indice = 0;               

Servo meuMotor; 

// --- COMPONENTES VISUAIS ---
const byte PINO_VERDE = 11;
const byte PINO_VERMELHO = 12;

void setup() {
  Serial.begin(9600); 
  Serial.println("Tranca Digital Pronta. Aguardando senha...");
 
  for(int i = 0; i < LINHAS; i++){
    pinMode(pinosLinhas[i], OUTPUT); 
    digitalWrite(pinosLinhas[i], HIGH);
  }

  for(int i = 0; i < COLUNAS; i++){
    pinMode(pinosColunas[i], INPUT_PULLUP); 
  }
  
  meuMotor.attach(10); 
  meuMotor.write(0);   

  // Configura os pinos dos LEDs como saída de energia
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_VERMELHO, OUTPUT);
}

char lerTeclado() {
  for (int l = 0; l < LINHAS; l++){
    digitalWrite(pinosLinhas[l], LOW); 

    for (int c = 0; c < COLUNAS; c++){
      if (digitalRead(pinosColunas[c]) == LOW){ 
        delay(200); // Mantém o delay para evitar leitura dupla (debounce)
        digitalWrite(pinosLinhas[l], HIGH); 
        return matrizTeclas[l][c]; 
      }
    }
    digitalWrite(pinosLinhas[l], HIGH);
  }
  return '\0'; 
}

void loop() {
  char teclaPressionada = lerTeclado(); 

  if (teclaPressionada != '\0'){
    Serial.print("Tecla detectada: ");
    Serial.println(teclaPressionada);
    
    senhaDigitada[indice] = teclaPressionada;
    indice++;

    if (indice == 4) {
      senhaDigitada[4] = '\0';

      if (strcmp(senhaDigitada, senhaCorreta) == 0) {
        Serial.println("ACESSO LIBERADO!");
        
        // --- SUCESSO: Luz verde e abre a porta ---
        digitalWrite(PINO_VERDE, HIGH); 
        meuMotor.write(90); 
        delay(3000);        
        meuMotor.write(0);  
        digitalWrite(PINO_VERDE, LOW);  
        
      } else {
        Serial.println("SENHA INCORRETA!");
        
        // --- FALHA: Luz vermelha ---
        digitalWrite(PINO_VERMELHO, HIGH); 
        delay(1000); 
        digitalWrite(PINO_VERMELHO, LOW);  
      }
      
      indice = 0;
    }
  }
}
