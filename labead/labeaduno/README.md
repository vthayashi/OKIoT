# Osciloscópio e Gerador de Funções com Arduino Uno

![Geral](https://github.com/vthayashi/OKIoT/blob/master/labead/img/geral.png)

Procedimento inicial para bancada de eletrônica open source com Arduino Uno, funcionalidades de osciloscópio, gerador de funções (ondas triangular, senoidal e quadrada), fonte de tensão, voltímetro, entradas e saídas digitais. Adicionalmente, controle de relés e servo motor.

**Pré-requisitos**: Computador com Windows, Arduino Uno e componentes.

## Cópia local
Gerar cópia local a partir do Github, pasta [labeaduno](https://github.com/vthayashi/OKIoT/tree/master/labead/labeaduno)

## Setup Arduino e Python 3
Descrição da configuração do Arduino IDE para carga de programa no Arduino Uno, bibliotecas python pyserial para comunicação serial, e flask para aplicação web para interface de bancada acessível localmente por meio de navegador.

### Lista de Materiais
1x Arduino Uno

1x Cabo USB para Arduino Uno

### Arduino IDE
- Caso não possua Arduino IDE instalado no computador, obter no [Site do Arduino](https://arduino.cc/en/Main/Software)

- Realizar a carga do [programa](https://github.com/vthayashi/OKIoT/tree/master/labead/labeaduno/LabEadUno3_2005020a) no Arduino Uno.

### Python 3 e bibliotecas pyserial, flask
- Caso não possua python 3 instalado, obter Python 3 a partir do instalador para Windows, habilitar a opção “Add python to environment variable” na instalação, obter em: https://www.python.org/downloads/release/python-382/ (selecionar o arquivo Windows x86-64 executable installer)

- Adicionar as bibliotecas pyserial (https://pypi.org/project/pyserial/) e flask (https://flask.palletsprojects.com/en/1.1.x/quickstart/#quickstart) a partir do comando pip do python

- A partir da pasta onde está a cópia local do [app.py](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/app.py), digitar “cmd” na barra de endereços

- No prompt de comando, digitar “set FLASK_APP=app.py”

- **Atenção**: alterar a configuração da porta serial COM correta no [app.py](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/app.py). Ou seja, substituir o "COM8" pela COM onde o Arduino está conectado (pode ser visualizada no Arduino IDE)

- Executar o programa [app.py](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/app.py) com duplo clique

- Acessar http://127.0.0.1:5000/ para visualizar a interface web da bancada (há um [arquivo de atalho](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/LabEad.url))

- Se precisar reiniciar o servidor, basta fechar a janela do Python (onde o log do servidor pode ser visualizado) e executar o [app.py](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/app.py) novamente.

**Atenção**: ao reiniciar o servidor, fechar as janelas do navegador que estão acessando o endereço da página.

## Shields PWM e Gerador de Funções
Montagem do shield de conversão de PWM para CC (Corrente Contínua), e shield de Gerador de Funções para CA (Corrente Alternada).
O gerador de funções foi construído a partir da montagem VCO (Voltage Controlled Oscillator).

### Lista de Materiais

#### Geral

1x Arduino Uno

1x Cabo USB para Arduino Uno

1x Fonte 9V regulada

#### Shield CC

1x Placa Padrão ilhada 44x80 mm

1x CI LM324

4x resistor de carbono 10kOhm 1/4W

4x capacitor eletrolítico 22uF 16V

1x barra de pinos macho 1x40 vias 11,5 mm 180o (35/40 pinos utilizados)

1x barra de pino 1x40 femea 180o (26/40 pinos utilizados)

#### Shield CA

1x Placa Padrão ilhada 46x62 mm

1x CI LM324

2x transistor BC548

3x diodo 1N4148

2x capacitor eletrolítico 22uF 16V

1x capacitor poliéster 47nF

5x resistor de carbono 10kOhm

1x resistor de carbono 3K3Ohm

1x resistor carbono 4K7Ohm

1x resistor carbono 22kOhm

1x resistor carbono 33kOhm

3x resistor carbono 47kOhm

3x resistor carbono 100kOhm

1x resistor carbono 180kOhm

1x resistor carbono 330kOhm

1x barra de pinos macho 1x40 vias 11,5 mm 180o (24/40 pinos utilizados)

1x barra de pino 1x40 femea 180o (21/40 pinos utilizados)

### Esquemático e PCB
- Realizar a montagem conforme [Esquemático e projeto do PCB](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/LabEadUno3_200521.fzz) (placas Gerador e D/A) desenvolvidos no [Fritzing](https://fritzing.org/home/)

**Atenção**: caso as frequências da interface necessitem de calibração, é possível realizar ajustes na [página em HTML](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/templates/scope.html), através de editor [Notepad++](https://notepad-plus-plus.org/).

![Esquemático](https://github.com/vthayashi/OKIoT/blob/master/labead/img/esquematico.png)

![PCB](https://github.com/vthayashi/OKIoT/blob/master/labead/img/pcb.png)
