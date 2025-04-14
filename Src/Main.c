#include "common.h"
#include "MS51_32K.H"
#include "ILI9341.h"
#include "spi.h"
#include "icons.h"
#include "fonts.h"

void delay(unsigned int count){
    unsigned int i;
    while (count--){
        for (i = 0; i < 1000; i++);
    }
}

void SPI_Init(){
    P15_QUASI_MODE;                                  // P15 (SS) Quasi mode
    P10_QUASI_MODE;                                  // P10 (SPCLK) Quasi mode
    P00_QUASI_MODE;                                  // P00 (MOSI) Quasi mode
    P01_QUASI_MODE;                                  // P01 (MISO) Quasi mode
        
    set_SPSR_DISMODF;                                // SS General purpose I/O ( No Mode Fault ) 
    clr_SPCR_SSOE;
    
    clr_SPCR_LSBFE;                                  // MSB first

    clr_SPCR_CPOL;                                   // The SPI clock is low in idle mode
    clr_SPCR_CPHA;                                   // The dat is sample on the second edge of SPI clock 
        
    set_SPCR_MSTR;                                   // SPI in Master mode 
    SPICLK_FSYS_DIV16;                                    // Select SPI clock 
    set_SPCR_SPIEN;                                  // Enable SPI function 
    clr_SPSR_SPIF;  
}


void main(){
	FsysSelect(FSYS_HIRC); // Select HIRC (High Internal RC Oscillator)
    MODIFY_HIRC(HIRC_24);  // Set HIRC to 24 MHz

	SPI_Init();
	ILI9341_Init();
	ILI9341_SetRotation(SCREEN_HORIZONTAL_1);
	ILI9341_FillScreen(BLACK);
	 
    ILI9341_DrawBMP(4,5,72,110,rect,ORANGE,BLACK);
	ILI9341_DrawBMP(4,125,72,110,rect ,ORANGE,BLACK);
	ILI9341_DrawBMP(84,125,72,110,rect,ORANGE,BLACK);
	ILI9341_DrawBMP(164,125,72,110,rect,ORANGE,BLACK);
	ILI9341_DrawBMP(244,125,72,110,rect,ORANGE,BLACK);
	ILI9341_DrawBMP(244,5,72,110,rect,ORANGE,BLACK);
	//ILI9341_DrawHollowRectangle(4,5,76,115,CYAN,3);
	//ILI9341_DrawHollowRectangle(4,125,76,235,CYAN,4);
	//ILI9341_DrawHollowRectangle(84,125,156,235,CYAN,4);
	//ILI9341_DrawHollowRectangle(164,125,236,235,CYAN,4);
	//ILI9341_DrawHollowRectangle(244,125,316,235,CYAN,4);
	//ILI9341_DrawHollowRectangle(244,5,316,115,CYAN,4);
	 
	ILI9341_DrawBMP(20,20,40,40,fry_pan,ORANGE,BLACK);
	ILI9341_DrawBMP(22,143,40,40,fan40,ORANGE,BLACK);
	ILI9341_DrawBMP(94,139,48,48,fan3_48,ORANGE,BLACK);
	ILI9341_DrawBMP(185,146,32,32,power_icon,ORANGE,BLACK);
	ILI9341_DrawBMP(260,142,40,40,lightbulb_off,ORANGE,BLACK);
	ILI9341_DrawBMP(260,20,40,40,chimney,ORANGE,BLACK);
	
	
	 
    ILI9341_DrawText("Fried",FONT4,18,84,ORANGE,BLACK);
    ILI9341_DrawText("Up",FONT4,30,204,ORANGE,BLACK);
    ILI9341_DrawText("Down",FONT4,98,204,ORANGE,BLACK);
    ILI9341_DrawText("Power",FONT4,174,204,ORANGE,BLACK);
    ILI9341_DrawText("Light",FONT4,262,204,ORANGE,BLACK);
    ILI9341_DrawText("Deoil",FONT4,260,84,ORANGE,BLACK);
	 
	 
    // ILI9341_DrawText("10:10", FONT7,103,40, WHITE,BLACK);
    delay(1000);
    
	
    while (1){
    }
}

