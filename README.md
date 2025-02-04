# CEPEDI

## Semáforo

Este repositório contém implementações de temporização utilizando o Raspberry Pi Pico, organizadas em dois diretórios distintos dentro da pasta `semaforos`. Cada diretório possui um arquivo `semaforo.c`, porém os códigos são diferentes.

### Estrutura de Diretórios

- `TemporizadorDisparo/` - Implementação baseada em eventos de disparo controlados por um botão.
- `TemporizadorPeriodico/` - Implementação baseada em temporizadores periódicos.

### Como Navegar

Para acessar cada diretório, utilize os seguintes comandos:

```bash
cd semaforos/TemporizadorDisparo   # Para a versão de disparo
cd semaforos/TemporizadorPeriodico # Para a versão periódica
```

## Funcionalidades Implementadas

### **Temporizador de Disparo**
Este programa gerencia três LEDs, que são ativados ao pressionar um botão e desligados gradativamente com um atraso de 3 segundos entre cada mudança de estado.

#### **Especificações:**
1. **Acionamento por botão:** Pressionar o botão liga os três LEDs simultaneamente.
2. **Mudança de estado:** A cada 3 segundos, um LED é desligado até que todos estejam apagados.
3. **Uso de Callbacks:** A transição de estados é gerenciada por funções de call-back, como `turn_off_callback()`.
4. **Bloqueio de reativação:** O botão só pode ativar os LEDs novamente após a sequência completa de desligamento.
5. **Hardware:** Testado na ferramenta educacional **BitDogLab** com:
   - LED RGB – GPIOs **11, 12 e 13**
   - Botão A – GPIO **05**

### **Temporizador Periódico**
Este programa simula um **semáforo**, alternando os LEDs entre vermelho, amarelo e verde, com um intervalo de 3 segundos entre cada mudança de cor.

#### **Especificações:**
1. **Sequência do semáforo:**
   - Vermelho → Amarelo → Verde (com 3 segundos entre cada mudança).
2. **Uso de `add_repeating_timer_ms()`:**
   - Implementação de temporização periódica utilizando o **Pico SDK**.
3. **Mensagens na Serial:**
   - O programa imprime informações na porta serial a cada **1 segundo (1000 ms)**.

## **Pré-requisitos**

1. **Ambiente de Desenvolvimento**: VS Code (ou equivalente).
2. **Pico SDK** instalado.
3. **Simulador Wokwi** configurado.
4. **Compilador C (GCC ou equivalente).**

## **Como Usar**

1. **Clone o repositório:**

    ```bash
    git clone https://icarosg/semaforos.git
    ```

2. **Acesse a pasta desejada:**

    ```bash
    cd semaforos/TemporizadorDisparo   # Ou cd semaforos/TemporizadorPeriodico
    ```

3. **Faça o import do projeto por meio do Raspberry Pi Pico Project (Extensão do VSCODE)**

4. **Compile o código:**

    ```bash
    gcc semaforo.c -o main
    ```

5. **Execute o programa:**

    ```bash
    ./main
    ```

## **Demonstração**

Assista ao vídeo demonstrativo no seguinte link: [Vídeo da solução](https://www.dropbox.com/scl/fi/6eiwmkkqolcny44nv65jd/DemonstracaoTemporizadorPeriodicoTemporizadorDisparo.mkv?rlkey=7yxcub60lhnw4sazlmw9cti47&st=ncw5012q&dl=0).

