# 🍷 Sistema de Monitoramento de Luminosidade - Vinheria Agnello

Projeto desenvolvido em Arduino para monitorar as condições de **luminosidade** em ambientes de armazenamento de vinhos. A qualidade do vinho é diretamente afetada pela luz, e esse sistema auxilia na manutenção do ambiente ideal.
Esse projeto foi desenvolvido como avaliação da aula de Edge Computing & Computer Sistems da FIAP.

## Link para Visualização 🔗

Você pode visualizar o projeto no Tinkercad pelo link abaixo:

👉 [Visualizar Projeto no Tinkercad](https://www.tinkercad.com/things/jV5w3iEgfAq-cp1-vinheria-agnello?sharecode=q0mPI88NLpmLmgYG8AyLep92nI3L8V3z_jZAmbArU0s)

## 🙋‍♂️ Integrantes

- [Pedro Faleiros](https://github.com/pedrofaleirosss)
- [Luan Felix](https://github.com/luansfff)
- [João Lopes](https://github.com/Joaolopes1311)
- [Felipe Campos](https://github.com/camp0s0s)
- [Leandro Farias](https://github.com/leofkin)

## 🔧 Funcionalidades

- Captura da intensidade luminosa com sensor LDR
- Cálculo do percentual de luminosidade (0 a 100%) com `map()`
- Sistema de alarme visual com LEDs:
  - 🟢 LED verde → ambiente ideal
  - 🟡 LED amarelo → alerta
  - 🔴 LED vermelho → crítico
- Alarme sonoro com buzzer nos níveis de alerta e crítico
- Exibição de mensagens em LCD 16x2
- Logo animada da DevZilla no display

## 📸 Imagem do Circuito

![image](https://github.com/user-attachments/assets/698576e6-440c-45fd-ae5f-f71bb5559219)
![image](https://github.com/user-attachments/assets/df155879-0874-4429-b073-c200e6193618)
![image](https://github.com/user-attachments/assets/75fd7cfa-8b16-4804-b421-bad39c52ebd0)
![image](https://github.com/user-attachments/assets/e0771108-588b-4301-abfc-45674bc8ac0e)

## 🧪 Componentes Utilizados

| Quantidade | Componente             |
|------------|------------------------|
| 1          | Arduino Uno R3         |
| 1          | Sensor LDR             |
| 1          | Resistor 10kΩ (pull-down para o LDR) |
| 3          | LEDs (verde, amarelo, vermelho) |
| 3          | Resistores 220Ω (para LEDs) |
| 1          | Buzzer                 |
| 1          | LCD 16x2 com interface paralela |
| 1          | Protoboard             |
| Diversos   | Cabos jumpers          |  

## 📦 Como usar

1. Abra o código `.ino` no Arduino IDE.
2. Conecte os componentes conforme o esquema.
3. Faça o upload para o Arduino.
4. Ajuste os limites de alerta se necessário no código:
   ```cpp
   if (luminosidadePercent <= 40) {
     // Ambiente ideal
   }
