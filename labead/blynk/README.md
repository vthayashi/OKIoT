# Setup Blynk

Este procedimento prático integra a familiarização com plataforma de Internet das Coisas Blynk.

## Instalação do aplicativo mobile

No celular, instale o aplicativo Blynk. O Blynk está disponível para download na Google Store ou na App Store.

Inicialmente, após abrir o aplicativo do Blynk no celular pela primeira vez, será necessário criar uma conta. Para tal, clique na opção Create New Account. Em seguida, indique um email e uma senha, e clique em Sign Up para finalizar o processo de criação da conta.

## Criação de um projeto

Após a criação da conta com login e senha no aplicativo, será necessário criar um projeto no Blynk. Selecione a opção New Project. Uma tela será apresentada onde é necessário escolher o nome do projeto, o dispositivo e o tipo de conexão. O nome do projeto aqui é arbitrário (por exemplo, Oficina LabEAD). O dispositivo deverá ser necessariamente o WeMos D1 mini e o tipo de conexão como Wi-Fi. 
 
![Criação de um projeto no Blynk](https://github.com/vthayashi/OKIoT/blob/master/labead/blynk/criacao.png)

Após a criação do projeto, um token de autenticação é gerado e enviado para o email cadastrado. Guarde o email ou anote o token de autenticação.

## Inclusão do Terminal Virtual no projeto Blynk

Vamos modificar o projeto do Blynk para incluir somente o widget Terminal. Assim, inicialmente garanta que o projeto está desativado. Para isto é necessário clicar no botão Stop no Blynk. 
Um Terminal pode ser acrescentado ao projeto do Blynk buscando o widget na seção Displays.

Após adicionar o Terminal ao projeto, será necessário mapear esse terminal em um pino virtual. Para tal, clique nele e, em seguida, clique no PIN e selecione o pino virtual V0. É importante que o pino selecionado seja necessariamente o V0, pois o sketch executando na máquina remota (computador da bancada) e no ESP8266 foi configurado desta forma.

Feito isso, pode-se voltar para a tela do projeto, clicando na seta ⇐ no canto superior esquerdo.

Com o projeto pronto no aplicativo, é possível ativá-lo clicando no botão Play localizado no canto superior esquerdo.

![Configuração do projeto para conexão com a bancada remota](https://github.com/vthayashi/OKIoT/blob/master/labead/blynk/terminal.png)
