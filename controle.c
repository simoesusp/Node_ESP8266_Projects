/* Controle do robô via notebook
 * Mandando comandos via cURL
 *
 * Para compilar:
 * 	gcc controle.c -o controle -lcurl
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

#include <curl/curl.h>

#define IP "192.168.43.160"

//KBHIT FUNCTIONS
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int speed = 0;
int curva = 0;
int m_dir = 0, m_esq = 0;

int main() {
	int ch = 0;
	int quit = 0;

	char url[500] = {0};
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();

	init_keyboard();
	while(!quit) {
		printf("looping\n");
		//usleep(600000);
		usleep(1000);
		if(kbhit()) {
			ch = readch();

			switch(ch) {
			case 'w':
				if(!curva) {
					if(speed != 5)
						speed++;
				} else {
					curva = 0;
				}
				break;
			case 's':
				if(!curva) {
					if(speed != -5)
						speed--;
				} else {
					curva = 0;
				}
				break;
			case 'a':
				m_esq = 1;
				m_dir = 0;
				curva = 1;
				break;
			case 'd':
				m_esq = 0;
				m_dir = 1;
				curva = 1;
				break;
			//Antes de quitar, setar tudo para zero
			case 'q':
				quit = 1;
			case ' ':
				m_esq = 0;
				m_dir = 0;
				curva = 0;
				speed = 0;
				break;
			}
		}

		printf("Speed is %d\n", speed);
		printf("m_esq %d m_dir %d\n", m_esq, m_dir);
		printf("curva %d\n", curva);
		printf("\n");

		//Construir URL
		sprintf(url, "%s/motor?speed1=%d&speed2=%d&dir1=%d&dir2=%d", IP, speed, speed, m_esq, m_dir);

		printf("[%s]\n", url);

		//Mandar pro NodeMCU
		curl_easy_setopt(curl, CURLOPT_URL, url);
		res = curl_easy_perform(curl);
	}

	curl_easy_cleanup(curl);
	close_keyboard();
	exit(0);
}

//KBHIT
static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard() {
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard() {
	tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit() {
	char ch;
	int nread;

	if(peek_character != -1)
		return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);

	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}

int readch() {
	char ch;

	if(peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0, &ch, 1);
	return ch;
}
//FIM DO KBHIT
