# Node_ESP8266_Projects
Repository for my NODE projects

x---------------x--------------------x

NODE NA IDE ARDUINO:
ESP 8266

Entrar em: http://www.kevindarrah.com/wiki/index.php?title=TrigBoard
Procurar pelo link do Base Firmware.

Go to File>>Preferences and add this URL to to the "Additional Boards Manager URL". 
Paste this link: http://arduino.esp8266.com/stable/package_esp8266com_index.json

Go to Tools>>Board>>Boards Manager... Search for ESP8266, and go ahead and click install
Dai ele vai instalar suporte para a nova placa.

ir em TOOLS>>Boards  e escolher:
Node MCU 0.9 (ESP-12Module)

Para testar, seecione a porta certa e abra o Files>>Examples  e procure o ESP 8266 >> Blink
No meu so' programou se botar a plaquinha sobre os cabos, NAO PODE ENCOSTAR NA MESA!!!!

WARNING:
1) Quando instala a board,ele instala tambemas libraries do ESP
Mas ele so' mostra em files>>exemples se tiver selecionado a Borad MCU 0.9 (ESP-12Module), senao nao aparece!!!

2) CUIDADO!!! OS NUMEROS DO DEFINE SAO OS GPIO, nao os pinos do chip!!! Como na Raspberry
Placa 	GPIO (Nome que deve dar no Define)
d0		16
d1		5
d2		4
d3 		0
d4		2
d5		14
d6		12
d7		13
d8		15
A0		17

x-----------x------------x-----------x

HOW TO CONFIGURE OTA (Over The Air) PROGRAMMING

1) Program NODE with Examples >> ArduinoOTA >> Basic OTA

2) Turn on CelPhone WiFi network

3) Change Port (Arduino interface) to: esp8266-ip

4) Now you can reprogram NODE with blik to test
Obs.: It will say that your board is not connected...
      Then, No Answer....
      KEEP TRYING...
      Eventualy it conectes and programs...
      
5) VERY IMPORTANT >> Each time you reprogram via WiFi, You have to includ Basic OTA plus your software,other wise you wont be able to reprogram via wifi again!!

