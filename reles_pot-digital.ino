//Acionamento de reles e potenciometro digital via Bluetooth
int valor = 0;  // Valor inicial
int valordoblue = -1;
int entrada = 0;
// Pinos dos reles 1-4
#define rele1 10 //definido a pinagem
#define rele2 2  //definido a pinagem
#define rele3 3  //definido a pinagem
#define rele4 4  //definido a pinagem

// Pinos do potenciômetro digital X9C103
#define INC_PIN  5      // Pino de incremento (INC)
#define UD_PIN   6      // Pino de direção (U/D)
#define CS_PIN   7      // Pino de seleção de chip (CS)

void setup()
{
  // Iniciar a Serial
  Serial.begin(9600); //Início da serial do bluetooth

  // Pinos dos reles 1-4
  pinMode(rele1, OUTPUT); //Ligando a saída dos reles
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  digitalWrite(rele1, HIGH); //Garantir que os reles estejam desligados antes do comando
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);

  // Pinos do potenciômetro digital X9C103
  pinMode(INC_PIN, OUTPUT);
  pinMode(UD_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(UD_PIN, HIGH);
  digitalWrite(CS_PIN, LOW);

  // Incrementar o valor inicial
  for (int i = 0; i < valor; i++) {
    digitalWrite(INC_PIN, HIGH);
    delay(10);
    digitalWrite(INC_PIN, LOW);
    delay(10);
  }
  // Deselecionar o chip
  digitalWrite(CS_PIN, HIGH);
}

void loop() {
  // Funcionamento dos reles
  if (Serial.available() > 0) {
    valordoblue = Serial.read();
  }

  // Funcionamento do X9C103
  if (Serial.available()) {
    entrada = Serial.read();
    if (entrada == 'i' || entrada == 'I') {
      incrementar();
    } else if (entrada == 's' || entrada == 'S') {
      decrementar();
    }
  }

  // Funcionamento dos reles
  if (valordoblue == 'A' || valordoblue == 'a') {
    digitalWrite(rele1, valordoblue == 'A' ? HIGH : LOW);
  }

  if (valordoblue == 'B' || valordoblue == 'b') {
    digitalWrite(rele2, valordoblue == 'B' ? HIGH : LOW);
  }

  if (valordoblue == 'C' || valordoblue == 'c') {
    digitalWrite(rele3, valordoblue == 'C' ? HIGH : LOW);
  }

  if (valordoblue == 'D' || valordoblue == 'd') {
    digitalWrite(rele4, valordoblue == 'D' ? HIGH : LOW);
  }
}

// Funcionamento do X9C103
void incrementar() {
  digitalWrite(UD_PIN, HIGH);  // Configurar para incremento

  // Selecionar o chip
  digitalWrite(CS_PIN, LOW);

  // Incrementar o valor
  digitalWrite(INC_PIN, HIGH);
  delay(10);
  digitalWrite(INC_PIN, LOW);
  delay(10);

  // Deselecionar o chip
  digitalWrite(CS_PIN, HIGH);

  valor += 100;  // Atualizar o valor
}

void decrementar() {
  digitalWrite(UD_PIN, LOW);  // Configurar para decremento

  // Selecionar o chip
  digitalWrite(CS_PIN, LOW);

  // Decrementar o valor
  digitalWrite(INC_PIN, HIGH);
  delay(10);
  digitalWrite(INC_PIN, LOW);
  delay(10);

  // Deselecionar o chip
  digitalWrite(CS_PIN, HIGH);

  valor -= 100;  // Atualizar o valor
}
