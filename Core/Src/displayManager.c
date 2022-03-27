/*
 * displayMannager.c
 *
 *      Author: Maksym
 */

#include <displayManager.h>
#include "GFX.h"


#define NUMBER_OF_CHAR_ON_DISPLAY 18
char str[NUMBER_OF_CHAR_ON_DISPLAY];
char* prefix="wynik: ";
char display[NUMBER_OF_CHAR_ON_DISPLAY];

/**
 * @brief displayMeas
 * Funkcja wyswietlajaca na ekranie wynik
 * 
 * @param meas 
 * zmienna trzymajaca wartosc wyniku
 */
void displayMeas(uint32_t meas){
		snprintf(str, sizeof str, "%lu", (unsigned long)meas);
		//strcat(display,str);

			  GFX_draw_fill_rect(1,1,120,15,BLACK);// wyczyszczenie polowy ekranu

			  GFX_draw_string(5, 1,(unsigned char*)prefix, WHITE, BLACK, 1, 1);
			  GFX_draw_string(60, 1,(unsigned char*)str, WHITE, BLACK, 1, 1);
			  SSD1306_display_repaint();

}
/**
 * @brief fukncja usuwajaca znaczek "P" na ekranie
 * 
 */
void removePause(){
	 GFX_draw_fill_rect(110,20,10,10,BLACK);// usuniecie pauzy
	 SSD1306_display_repaint();
}
/**
 * @brief 
 * fukncja wyswietlajaca znaczek "P" na ekranie
 */
void displayPause()
{
	GFX_draw_string(110, 20,(unsigned char*)"P", WHITE, BLACK, 1, 1);
	SSD1306_display_repaint();

}
/**
 * @brief funkcja wyswietlajaca ekran powitalny
 * 
 */
void displayWelcome(){
	GFX_draw_string(5, 20,(unsigned char*)"Magnetometr", WHITE, BLACK, 1, 1);

	GFX_draw_string(5, 1,(unsigned char*)"Press to Start", WHITE, BLACK, 1, 1);
				  SSD1306_display_repaint();
}


