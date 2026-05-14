# 🔒 Tranca Digital com Arduino (MVP)

## 📖 Descrição do Projeto
Este projeto é um Produto Mínimo Viável (MVP) de um sistema de controle de acesso desenvolvido em C++ para microcontroladores AVR (Arduino UNO). O sistema utiliza uma matriz de contatos para entrada de dados (senha), processa a lógica de validação através de uma máquina de estados simples e aciona um atuador mecânico (Micro Servo Motor) em caso de credenciais válidas, além de fornecer feedback visual (IHM) ao operador via LEDs.

## 🛠️ Hardware Utilizado e Pinagem

* **Microcontrolador:** Arduino UNO
* **Interface de Entrada:** Teclado Matricial 4x4 (Membrana)
* **Atuador:** Micro Servo Motor (SG90)
* **Sinalização (IHM):** LEDs (Verde e Vermelho)

**Mapa de Conexões (Wiring):**
* **Pinos 6, 7, 8, 9:** Linhas do Teclado Matricial
* **Pinos 2, 3, 4, 5:** Colunas do Teclado Matricial
* **Pino 10 (PWM):** Controle de posição do Servo Motor
* **Pino 11:** LED Verde (Acesso Liberado)
* **Pino 12:** LED Vermelho (Acesso Negado)

## ⚙️ Lógica de Software
O firmware foi estruturado para evitar o travamento do microcontrolador e otimizar o uso da memória RAM:
1. **Varredura Matricial:** Uso das resistências internas de *pull-up* (`INPUT_PULLUP`) para leitura segura das teclas.
2. **Buffer de Memória:** Armazenamento sequencial dos caracteres digitados em um vetor `char`.
3. **Validação:** Uso da função `strcmp` para comparar a string digitada com a senha mestre na memória flash.
4. **Acionamento:** Controle de ângulo do servo motor (0º a 90º) para destrancar, com delay de retenção e retorno automático (posição segura).

## 🚀 Próximos Passos (Roadmap)
- [ ] Integração de Módulo RFID para acesso híbrido (Aproximação + Senha).
- [ ] Implementação de "Modo de Configuração" para troca de senha via teclado.

---
*Desenvolvido como projeto prático de integração mecatrônica e sistemas embarcados.*