Exemplo mandando comandos para o NodeMCU via programa em C.

Necessário instalar biblioteca [libcurl](https://curl.haxx.se/libcurl/).

Para compilar, não esquecer de -lcurl:
ex:
	gcc send.c -o send -lcurl

Usar junto com exemplo OTA_WebServer_LED_Motor!
