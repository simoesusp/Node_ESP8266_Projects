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

## Include Pin Definition:
// All Digital Pins have PWM, except D0   !!!!!!!!!!

// IO PINOUT Definition:

#define D0 16

#define D1 5

#define D2 4

#define D3 0

#define D4 2

#define D5 14

#define D6 12

#define D7 13

#define D8 15

#define A0 0    This need checking !!!

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
Then, you have to include function arduinoOTAHandle  in the LOOP, To listen to new programming attempts.

6) VERY, VERY IMPORTANT >> If you are using long delays (as in Blink) in the LOOP function, arduinoOTAHandle wont be called necessarily  when you press program button on the Arduino Interface. Since NODE will be probably stuck in the delay function. The longer the delay, the harder it is to reprogram (NOT CONNECTED error).
>> Proposed solution: create yourself a delay function, calling delay (10) and arduinoOTAHandle in a loop!! Then, NODE will be listenning to reprogram attempts while in delay!!

