// Configurações dos cômodos e luzes
const int numComodos = 4;
String comodos[numComodos] = {"Sala", "Quarto", "Cozinha", "Banheiro"};
bool luzes[numComodos] = {false, false, false, false}; // Todas começam desligadas
int comodoLigar;
int comodoDesligar;
// Função para exibir o status das luzes
void exibirStatus() {
    Serial.println("\nStatus das luzes:");
    for (int i = 0; i < numComodos; i++) {
        Serial.print(comodos[i] + ": ");
        Serial.println(luzes[i] ? "Ligado" : "Desligado");
    }
    Serial.println();
}

// Função para alterar o status das luzes
void alterarStatus(int index, bool status) {
    luzes[index] = status;
    Serial.print("A luz do(a) ");
    Serial.print(comodos[index]);
    Serial.println(status ? " foi ligada." : " foi desligada.");
}

void setup() {
    // Inicializa a comunicação serial
    Serial.begin(9600);
    Serial.println("--- Menu Casa Inteligente ---");
    Serial.println("1. Ligar luz");
    Serial.println("2. Desligar luz");
    Serial.println("3. Exibir status das luzes");
    Serial.println("0. Sair");
    Serial.println("Escolha uma opção digitando o número e pressionando Enter.");
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n'); // Lê a entrada do usuário
        int opcao = input.toInt();                  // Converte a entrada para inteiro

        switch (opcao) {
            case 1:
                Serial.println("Escolha um cômodo para ligar a luz:");
                for (int i = 0; i < numComodos; i++) {
                    Serial.print(i + 1);
                    Serial.println(". " + comodos[i]);
                }
                while (Serial.available() == 0);
                comodoLigar = Serial.readStringUntil('\n').toInt();
                if (comodoLigar > 0 && comodoLigar <= numComodos) {
                    alterarStatus(comodoLigar - 1, true);
                } else {
                    Serial.println("Cômodo inválido!");
                }
                break;

            case 2:
                Serial.println("Escolha um cômodo para desligar a luz:");
                for (int i = 0; i < numComodos; i++) {
                    Serial.print(i + 1);
                    Serial.println(". " + comodos[i]);
                }
                while (Serial.available() == 0);
                comodoDesligar = Serial.readStringUntil('\n').toInt();
                if (comodoDesligar > 0 && comodoDesligar <= numComodos) {
                    alterarStatus(comodoDesligar - 1, false);
                } else {
                    Serial.println("Cômodo inválido!");
                }
                break;

            case 3:
                exibirStatus();
                break;

            case 0:
                Serial.println("Encerrando o programa.");
                while (true); // Encerra o programa
                break;

            default:
                Serial.println("Opção inválida!");
        }

        // Reexibe o menu após cada interação
        Serial.println("\n--- Menu Casa Inteligente ---");
        Serial.println("1. Ligar luz");
        Serial.println("2. Desligar luz");
        Serial.println("3. Exibir status das luzes");
        Serial.println("0. Sair");
        Serial.println("Escolha uma opção digitando o número e pressionando Enter.");
    }
}
