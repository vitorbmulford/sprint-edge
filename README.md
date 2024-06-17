LCV Motors 
Nomes dos Integrantes
Milton Cezar Bacanieski (RM: 555206)
Vitor Bebiano Mulford (RM: 555026)
Lorenzo Mangini (RM: 554901)

Descrição
Este projeto tem como objetivo criar um sistema de controle para um carro de Fórmula E, com foco na gamificação e na visibilidade da competição. Utilizando um display LCD e botões de controle, o sistema permite ao usuário visualizar e ajustar a velocidade e a marcha do carro, além de fornecer informações adicionais, como o nível de bateria.
![image](https://github.com/vitorbmulford/sprint-edge/assets/142764430/2039e309-483d-4b53-b847-e9b320a238a2)

Componentes Utilizados
Arduino (ou qualquer microcontrolador compatível)
Display LCD 16x2
Botões de controle (para aceleração e frenagem)
Fios de conexão
Resistor pull-down para os botões
Funcionalidades
Controle de Velocidade:

O sistema permite aumentar ou diminuir a velocidade do carro através dos botões de aceleração e frenagem.
A velocidade é ajustada de acordo com a marcha selecionada, que varia conforme a velocidade atual do carro.
Marcha:

A marcha do carro é automaticamente ajustada com base na velocidade. As marchas são numeradas de 1 a 8, sendo a marcha 1 a mais baixa e a marcha 8 a mais alta.
Exibição no LCD:

O display LCD mostra a velocidade atual e a marcha selecionada.
Um "emoji" de bateria indica o nível da bateria, variando de 1 a 5.
Tela de Inicialização:

Uma tela de boas-vindas exibe o nome da equipe, "LCV Motors", seguida por um efeito de rotação do texto.
Esquema de Conexão
Display LCD:

Pino 12: RS
Pino 11: E
Pino 5: D4
Pino 4: D5
Pino 3: D6
Pino 2: D7
Botões:

Pino 9: Botão de Aceleração
Pino 8: Botão de Freio
Código
O código fonte está dividido em diversas partes:

Setup Inicial:

Configuração do display LCD e dos pinos dos botões.
Exibição da tela de boas-vindas.
Loop Principal:

Leitura dos estados dos botões.
Ajuste da velocidade e marcha com base nos estados dos botões e nos tempos definidos.
Funções Auxiliares:

increaseSpeed(): Incrementa a velocidade conforme a marcha.
decreaseSpeed(): Diminui a velocidade gradualmente.
brakeSpeed(): Reduz rapidamente a velocidade para simular a frenagem.
updateGear(): Atualiza a marcha com base na velocidade atual.
updateLCD(): Atualiza o display LCD com a velocidade, marcha e nível da bateria.
showStartupScreen(): Exibe a tela de inicialização com animação.
Como Usar
Configuração do Hardware:

Conecte os fios aos pinos apropriados conforme o esquema de conexão.
Certifique-se de que o display LCD está corretamente alimentado e configurado.
Carregamento do Código:

Abra o Arduino IDE e carregue o código no seu microcontrolador.
Funcionamento:

Pressione os botões de aceleração e freio para ajustar a velocidade do carro.
Observe a atualização da velocidade e da marcha no display LCD.
Utilize a frenagem rápida para simular paradas bruscas.
Contribuições
Este projeto foi desenvolvido com o intuito de aumentar a visibilidade da Fórmula E e tornar a experiência mais interativa e divertida

Links: 
Simulção TinkerCad - https://www.tinkercad.com/things/f3WpwgPvv1D-sprint-1/editel
Video Explicativo YouTube - 
