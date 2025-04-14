#include "MS51_32K.H"
// #include "fonts.h"


#define ILI9341_SCREEN_HEIGHT 	240
#define ILI9341_SCREEN_WIDTH 	320

#define BURST_MAX_SIZE 			500

// Default color definitions
#define BLACK      				0x0000
#define NAVY        			0x000F
#define DARKGREEN   			0x03E0
#define DARKCYAN    			0x03EF
#define MAROON      			0x7800
#define PURPLE      			0x780F
#define OLIVE       			0x7BE0
#define LIGHTGREY   			0xC618
#define DARKGREY    			0x7BEF
#define BLUE        			0x001F
#define GREEN       			0x07E0
#define CYAN        			0x07FF
#define RED         			0xF800
#define MAGENTA     			0xF81F
#define YELLOW      			0xFFE0
#define WHITE       			0xFFFF
#define ORANGE      			0xFD20
#define GREENYELLOW 			0xAFE5
#define PINK        			0xF81F
#define BROWN                   0x9A60      
#define GOLD                    0xFEA0      
#define SILVER                  0xC618      
#define SKYBLUE                 0x867D      
#define VIOLET                  0x915C 
#define TRANSPARENT             0x0120 // This is actually a dark green

#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1

void ILI9341_WriteCommand(uint8_t cmd);
void ILI9341_WriteData(uint8_t dat);
void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len);
void ILI9341_Reset(void);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_SetRotation(uint8_t rotation);
void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ILI9341_DrawColor(uint16_t color);
void ILI9341_DrawColorBurst(uint16_t color, uint32_t siz);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color);
void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color);
void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color);
void ILI9341_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t color);



void ILI9341_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color);
void ILI9341_DrawFilledCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color);
void ILI9341_DrawHollowRectangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color,uint8_t thickness);
void ILI9341_DrawFilledRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color);
void ILI9341_DrawHollowEllipse(uint16_t x0,uint16_t y0,uint32_t rx,uint32_t ry,uint16_t color);
void ILI9341_DrawFilledEllipse(uint16_t x0, uint16_t y0, uint32_t rx, uint32_t ry, uint16_t color);
void ILI9341_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* image, uint8_t orientation);
void ILI9341_DrawBMP(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t* image,uint16_t color,uint16_t bg_color);
void ILI9341_DrawIcon(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t* buff,uint16_t siz);
