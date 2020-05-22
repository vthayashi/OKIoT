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

- Se precisar reiniciar o servidor, basta fechar a janela do Python (onde o log do servidor pode ser visualizado) e executar o [app.py](https://github.com/vthayashi/OKIoT/blob/master/labead/labeaduno/app.py) novamente.

## Shields PWM e Gerador de Funções
Introdução PWM para CC, e Gerador de Funções para CA

### Lista de Materiais
1x Arduino Uno

1x Cabo USB para Arduino Uno

1x Fonte 9V regulada

### Esquemático e PCB
Descrição e menção ao Fritzing

![Esquemático](https://github.com/vthayashi/OKIoT/blob/master/labead/img/esquematico.png)

![PCB](https://github.com/vthayashi/OKIoT/blob/master/labead/img/pcb.png)

**Atenção**: ajuste no HTML (tbm poderia ser por potenciômetros no shield)

**Atenção**: alerta flask warmup
