
#include "ILI9341.h"
#include "spi.h"
#include <stdio.h>
#include <stdlib.h>

#define ILI9341_CS_LOW    P15 = 0   // Chip Select low
#define ILI9341_CS_HIGH   P15 = 1   // Chip Select high
#define ILI9341_DC_LOW    P11 = 0   // Data/Command low for command
#define ILI9341_DC_HIGH   P11 = 1   // Data/Command high for data
#define ILI9341_RST_LOW   P12 = 0   // Reset low
#define ILI9341_RST_HIGH  P12 = 1   // Reset high

volatile uint32_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint32_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;


static void swap(uint16_t *a, uint16_t *b) {
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

static void delay(unsigned int count){
    unsigned int i;
    while (count--){
        for (i = 0; i < 1000; i++);
    }
}

void ILI9341_WriteCommand(uint8_t cmd){
	ILI9341_DC_LOW;    // Command mode
    ILI9341_CS_LOW;    // Select the display
    Spi_Write_Byte(cmd);
    ILI9341_CS_HIGH;   // Deselect the display
}

void ILI9341_WriteData(uint8_t dat){
	ILI9341_DC_HIGH;   // Data mode
    ILI9341_CS_LOW;    // Select the display
    Spi_Write_Byte(dat);
    ILI9341_CS_HIGH;   // Deselect the display
}


void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len){
	ILI9341_DC_HIGH;   // Data mode
    ILI9341_CS_LOW;    // Select the display
	Spi_Write_Buff(buffer,len);
    ILI9341_CS_HIGH;   // Deselect the display
}

void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	uint8_t buffer[4];
	buffer[0] = x1 >> 8;
	buffer[1] = x1;
	buffer[2] = x2 >> 8;
	buffer[3] = x2;

	ILI9341_WriteCommand(0x2A);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	buffer[0] = y1 >> 8;
	buffer[1] = y1;
	buffer[2] = y2 >> 8;
	buffer[3] = y2;

	ILI9341_WriteCommand(0x2B);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));
	ILI9341_WriteCommand(0x2C);
}

void ILI9341_Reset(void){
	ILI9341_RST_LOW;	//Disable
	delay(10);
	ILI9341_CS_LOW;		//Select
	delay(10);
	ILI9341_RST_HIGH;   //Enable
	ILI9341_CS_HIGH; 	//Deselect
}

void ILI9341_Enable(void){
	ILI9341_RST_HIGH;   //Enable
}

void ILI9341_Init(void){
	ILI9341_Enable();
	ILI9341_Reset();

	//SOFTWARE RESET
	ILI9341_WriteCommand(0x01);
	delay(10);

	//POWER CONTROL A
	ILI9341_WriteCommand(0xCB);
	ILI9341_WriteData(0x39);
	ILI9341_WriteData(0x2C);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x34);
	ILI9341_WriteData(0x02);

	//POWER CONTROL B
	ILI9341_WriteCommand(0xCF);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_WriteCommand(0xE8);
	ILI9341_WriteData(0x85);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_WriteCommand(0xEA);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_WriteCommand(0xED);
	ILI9341_WriteData(0x64);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x12);
	ILI9341_WriteData(0x81);

	//PUMP RATIO CONTROL
	ILI9341_WriteCommand(0xF7);
	ILI9341_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_WriteCommand(0xC0);
	ILI9341_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_WriteCommand(0xC1);
	ILI9341_WriteData(0x10);

	//VCM CONTROL
	ILI9341_WriteCommand(0xC5);
	ILI9341_WriteData(0x3E);
	ILI9341_WriteData(0x28);

	//VCM CONTROL 2
	ILI9341_WriteCommand(0xC7);
	ILI9341_WriteData(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_WriteCommand(0x36);
	ILI9341_WriteData(0x48);

	//PIXEL FORMAT
	ILI9341_WriteCommand(0x3A);
	ILI9341_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_WriteCommand(0xB1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_WriteCommand(0xB6);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x82);
	ILI9341_WriteData(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_WriteCommand(0xF2);
	ILI9341_WriteData(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_WriteCommand(0x26);
	ILI9341_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE0);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x2B);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x4E);
	ILI9341_WriteData(0xF1);
	ILI9341_WriteData(0x37);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x10);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x09);
	ILI9341_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x14);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x11);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x48);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x36);
	ILI9341_WriteData(0x0F);

	//EXIT SLEEP
	ILI9341_WriteCommand(0x11);
	delay(100);

	//TURN ON DISPLAY
	ILI9341_WriteCommand(0x29);

	//STARTING ROTATION
	ILI9341_SetRotation(SCREEN_VERTICAL_1);
}

void ILI9341_SetRotation(uint8_t rotation){
	ILI9341_WriteCommand(0x36);
	delay(1);

	switch(rotation){
	case SCREEN_VERTICAL_1:
		ILI9341_WriteData(0x40|0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		ILI9341_WriteData(0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		ILI9341_WriteData(0x80|0x08);
		LCD_WIDTH  = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		ILI9341_WriteData(0x40|0x80|0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		break;
	}
}


void ILI9341_DrawColor(uint16_t color){
	uint8_t buffer[2];
buffer[0] = color>>8;
	buffer[1] = color;
	ILI9341_WriteBuffer(buffer, sizeof(buffer));
}

void ILI9341_DrawColorBurst(uint16_t color, uint32_t siz){
	uint32_t BufferSize = BURST_MAX_SIZE;
  uint8_t chifted;
	uint32_t SendingSize;
	uint32_t SendingInBlock;
	uint32_t RemainderFromBlock;
  uint32_t j;
	uint8_t BurstBuffer[BURST_MAX_SIZE];
	
	/*if((siz*2) < BURST_MAX_SIZE){
		BufferSize = siz;
	}
	else{
		BufferSize = BURST_MAX_SIZE;
	}
	*/

	ILI9341_DC_HIGH;
	ILI9341_CS_LOW;

	chifted = color>>8;
	

	for(j = 0; j < BufferSize; j+=2){
		BurstBuffer[j] = chifted;
		BurstBuffer[j+1] = color;
	}

	SendingSize = siz * 2;
	SendingInBlock = SendingSize / BufferSize;
	RemainderFromBlock = SendingSize % BufferSize;

	if(SendingInBlock != 0){
		for(j = 0; j < SendingInBlock; j++){
			Spi_Write_Buff(BurstBuffer,BufferSize);
		}
	}
  Spi_Write_Buff(BurstBuffer,RemainderFromBlock);
	ILI9341_CS_HIGH;
}

void ILI9341_FillScreen(uint16_t color){
	ILI9341_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT);
	ILI9341_DrawColorBurst(color, LCD_WIDTH*LCD_HEIGHT);
}

void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color){
	uint8_t bufferX[4];
	uint8_t bufferY[4];
	uint8_t bufferC[2];
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;
	
  bufferX[0] = x>>8;
	bufferX[1] = x;
	bufferX[2] = (x+1)>>8;
	bufferX[3] = (x+1);
	
	bufferY[0] = y>>8;
	bufferY[1] = y;
	bufferY[2] = (y+1)>>8;
	bufferY[3] = (y+1);

	bufferC[0] = color>>8;
	bufferC[1] = color;
	

	ILI9341_WriteCommand(0x2A);						//ADDRESS
	ILI9341_WriteBuffer(bufferX, sizeof(bufferX));	//XDATA

	ILI9341_WriteCommand(0x2B);						//ADDRESS
	ILI9341_WriteBuffer(bufferY, sizeof(bufferY));	//YDATA

	ILI9341_WriteCommand(0x2C);						//ADDRESS
	ILI9341_WriteBuffer(bufferC, sizeof(bufferC));	//COLOR
}

void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH){
		width=LCD_WIDTH-x;
	}

	if((y+height-1)>=LCD_HEIGHT){
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x+width-1, y+height-1);
	ILI9341_DrawColorBurst(color, height*width);
}


void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color){
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH){
		width=LCD_WIDTH-x;
	}

	ILI9341_SetAddress(x, y, x+width-1, y);
	ILI9341_DrawColorBurst(color, width);
}

void ILI9341_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t color){
	uint16_t dx,dy;
  uint16_t err,ystep,xs,dlen;
  uint16_t steep;
  steep = abs(y1 - y0) > abs(x1 - x0);
  

  if (steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }

  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  dx = x1 - x0, dy = abs(y1 - y0);;

  err = dx >> 1, ystep = -1, xs = x0, dlen = 0;

  if (y0 < y1) ystep = 1;

  // Split into steep and not steep for FastH/V separation
  if (steep) {
    for (; x0 <= x1; x0++) {
      dlen++;
      err -= dy;
      if (err < 0) {
        if (dlen == 1) ILI9341_DrawPixel(y0, xs, color);
        else ILI9341_DrawVLine(y0, xs, dlen, color);
        dlen = 0;
        y0 += ystep; xs = x0 + 1;
        err += dx;
      }
    }
    if (dlen) ILI9341_DrawVLine(y0, xs, dlen, color);
  }
  else
  {
    for (; x0 <= x1; x0++) {
      dlen++;
      err -= dy;
      if (err < 0) {
        if (dlen == 1) ILI9341_DrawPixel(xs, y0, color);
        else ILI9341_DrawHLine(xs, y0, dlen, color);
        dlen = 0;
        y0 += ystep; xs = x0 + 1;
        err += dx;
      }
    }
    if (dlen) ILI9341_DrawHLine(xs, y0, dlen, color);
  }

}

void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color){
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((y+height-1)>=LCD_HEIGHT){
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x, y+height-1);
	ILI9341_DrawColorBurst(color, height);
}

void ILI9341_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color){
	int x = radius-1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y){
		ILI9341_DrawPixel(X + x, Y + y, color);
		ILI9341_DrawPixel(X + y, Y + x, color);
		ILI9341_DrawPixel(X - y, Y + x, color);
		ILI9341_DrawPixel(X - x, Y + y, color);
		ILI9341_DrawPixel(X - x, Y - y, color);
		ILI9341_DrawPixel(X - y, Y - x, color);
		ILI9341_DrawPixel(X + y, Y - x, color);
		ILI9341_DrawPixel(X + x, Y - y, color);

		if (err <= 0){
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0){
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}

void ILI9341_DrawFilledCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color){
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;
    int i;
	while (x >= y){
		for (i = X - x; i <= X + x; i++){
			ILI9341_DrawPixel(i, Y + y,color);
			ILI9341_DrawPixel(i, Y - y,color);
		}

		for (i = X - y; i <= X + y; i++){
			ILI9341_DrawPixel(i, Y + x,color);
			ILI9341_DrawPixel(i, Y - x,color);
		}

		y++;
		radiusError += yChange;
		yChange += 2;

		if (((radiusError << 1) + xChange) > 0){
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void ILI9341_DrawHollowRectangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color,uint8_t thickness){
	uint8_t i;
	uint16_t xLen = 0;
	uint16_t yLen = 0;
	uint8_t negX = 0;
	uint8_t negY = 0;
	float negCalc = 0;

	negCalc = X1 - X0;
	if(negCalc < 0) negX = 1;
	negCalc = 0;

	negCalc = Y1 - Y0;
	if(negCalc < 0) negY = 1;

	//DRAW HORIZONTAL!
	if(!negX){
		xLen = X1 - X0;
	}
	else{
		xLen = X0 - X1;
	}
	
  for(i=0;i<thickness;i++){
		ILI9341_DrawHLine(X0, Y0+i, xLen, color);
		ILI9341_DrawHLine(X0, Y1-i, xLen, color);
	}
	
	
	
	// ILI9341_DrawHLine(X0, Y0, xLen, color);
	// ILI9341_DrawHLine(X0, Y1, xLen, color);

	//DRAW VERTICAL!
	if(!negY){
		yLen = Y1 - Y0;
	}
	else{
		yLen = Y0 - Y1;
	}
	
   for(i=0;i<thickness;i++){
		ILI9341_DrawVLine(X0+i, Y0, yLen, color);
	  ILI9341_DrawVLine(X1-i, Y0, yLen, color);
	}    
	// ILI9341_DrawVLine(X0, Y0, yLen, color);
	// ILI9341_DrawVLine(X1, Y0, yLen, color);

	if((xLen > 0)||(yLen > 0)){
		ILI9341_DrawPixel(X1, Y1, color);
	}
}

void ILI9341_DrawFilledRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color){
	uint16_t xLen = 0;
	uint16_t yLen = 0;
	uint8_t negX = 0;
	uint8_t negY = 0;
	uint32_t negCalc = 0;
	uint16_t X0True = 0;
	uint16_t Y0True = 0;

	negCalc = X1 - X0;
	if(negCalc < 0) negX = 1;
	negCalc = 0;

	negCalc = Y1 - Y0;
	if(negCalc < 0) negY = 1;

	if(!negX){
		xLen = X1 - X0;
		X0True = X0;
	}
	else{
		xLen = X0 - X1;
		X0True = X1;
	}

	if(!negY){
		yLen = Y1 - Y0;
		Y0True = Y0;
	}
	else{
		yLen = Y0 - Y1;
		Y0True = Y1;
	}

	ILI9341_DrawRectangle(X0True, Y0True, xLen, yLen, color);
}

void ILI9341_DrawHollowEllipse(uint16_t x0,uint16_t y0,uint32_t rx,uint32_t ry,uint16_t color){
	uint32_t x,y;
    uint32_t rx2 = rx * rx;
    uint32_t ry2 = ry * ry;
    uint32_t fx2 = 4 * rx2;
    uint32_t fy2 = 4 * ry2;
    uint32_t s;
    
    if (rx<2) return;
    if (ry<2) return;

    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
    // These are ordered to minimise coordinate changes in x or y
    // drawPixel can then send fewer bounding box commands
    ILI9341_DrawPixel(x0 + x, y0 + y, color);
    ILI9341_DrawPixel(x0 - x, y0 + y, color);
    ILI9341_DrawPixel(x0 - x, y0 - y, color);
    ILI9341_DrawPixel(x0 + x, y0 - y, color);
    if (s >= 0) {
      s += fx2 * (1 - y);
      y--;
    }
    s += ry2 * ((4 * x) + 6);
   }

    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
    // These are ordered to minimise coordinate changes in x or y
    // drawPixel can then send fewer bounding box commands
    ILI9341_DrawPixel(x0 + x, y0 + y, color);
    ILI9341_DrawPixel(x0 - x, y0 + y, color);
    ILI9341_DrawPixel(x0 - x, y0 - y, color);
    ILI9341_DrawPixel(x0 + x, y0 - y, color);
    if (s >= 0){
      s += fy2 * (1 - x);
      x--;
    }
    s += rx2 * ((4 * y) + 6);
  }
}

void ILI9341_DrawFilledEllipse(uint16_t x0, uint16_t y0, uint32_t rx, uint32_t ry, uint16_t color){
  uint32_t x, y;
  uint32_t rx2 = rx * rx;
  uint32_t ry2 = ry * ry;
  uint32_t fx2 = 4 * rx2;
  uint32_t fy2 = 4 * ry2;
  uint32_t s;

  if (rx<2) return;
  if (ry<2) return;

  for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
    ILI9341_DrawHLine(x0 - x, y0 - y, x + x + 1, color);
    ILI9341_DrawHLine(x0 - x, y0 + y, x + x + 1, color);

    if (s >= 0) {
      s += fx2 * (1 - y);
      y--;
    }
    s += ry2 * ((4 * x) + 6);
  }

  for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
    ILI9341_DrawHLine(x0 - x, y0 - y, x + x + 1, color);
    ILI9341_DrawHLine(x0 - x, y0 + y, x + x + 1, color);

    if (s >= 0) {
      s += fy2 * (1 - x);
      x--;
    }
    s += rx2 * ((4 * y) + 6);
  }

}





void ILI9341_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor){
	uint8_t fOffset, fWidth, fHeight, fBPL;
	uint8_t *tempChar;
	int j;
	int i;
	uint8_t z,b;

	if ((ch < 31) || (ch > 127)) return;

	fOffset = font[0];
	fWidth = font[1];
	fHeight = font[2];
	fBPL = font[3];

	tempChar = (uint8_t*)&font[((ch - 0x20) * fOffset) + 4]; /* Current Character = Meta + (Character Index * Offset) */

	/* Clear background first */
	ILI9341_DrawRectangle(X, Y, fWidth, fHeight, bgcolor);

	for (j=0; j < fHeight; j++)
	{
		for (i=0; i < fWidth; i++)
		{
			z =  tempChar[fBPL * i + ((j & 0xF8) >> 3) + 1]; /* (j & 0xF8) >> 3, increase one by 8-bits */
			b = 1 << (j & 0x07);
			if (( z & b ) != 0x00)
			{
				ILI9341_DrawPixel(X+i, Y+j, color);
			}
		}
	}
}

void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor){
	uint8_t charWidth;			/* Width of character */
	uint8_t fOffset = font[0];	/* Offset of character */
	uint8_t fWidth = font[1];	/* Width of font */
    uint8_t *tempChar;

	while (*str)
	{
		ILI9341_DrawChar(*str, font, X, Y, color, bgcolor);

		/* Check character width and calculate proper position */
		tempChar = (uint8_t*)&font[((*str - 0x20) * fOffset) + 4];
		charWidth = tempChar[0];
        
		if(charWidth + 2 < fWidth)
		{
			/* If character width is smaller than font width */
			X += (charWidth + 2);
		}
		else
		{
			X += fWidth;
		}

		str++;
	}
}

void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* image, uint8_t orientation){
	uint32_t counter = 0;
	uint32_t i;
	if(orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_SetRotation(SCREEN_HORIZONTAL_1);
		ILI9341_SetAddress(x,y,x+width-1,y+height-1);
	}
	else if(orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);
	}
	else if(orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_SetRotation(SCREEN_VERTICAL_2);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
	}
	else if(orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_SetRotation(SCREEN_VERTICAL_1);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
	}

	
	for(i = 0; i < width*height*2/BURST_MAX_SIZE; i++)
	{
		ILI9341_WriteBuffer((uint8_t*)(image + counter), BURST_MAX_SIZE);
		counter += BURST_MAX_SIZE;

		/* DMA Tx is too fast, It needs some delay */
		delay(1);
	}
}

void ILI9341_DrawBMP(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t* image,uint16_t color,uint16_t bg_color){
	uint16_t i,j;
	uint8_t k;
	uint8_t byte;
	uint8_t bit_bmp;
	uint8_t buff1[2];
	uint8_t buff2[2];
	buff1[0] = color>>8;
	buff1[1] = color;
	buff2[0] = bg_color>>8;
  buff2[1] = bg_color;
	ILI9341_SetAddress(x, y, x+width-1, y+height-1);
	ILI9341_DC_HIGH;
	ILI9341_CS_LOW;

	for(i=0;i<height;i++){
      for(j=0;j<(width/8);j++){
        byte = image[(width/8)*i+j];
        for(k =0;k<8;k++){
        	bit_bmp = byte>>(7-k) & 1;
        	if(bit_bmp == 1){
        		Spi_Write_Buff(buff1,2);
        	}
        	else{
        		Spi_Write_Buff(buff2,2);
        	}
        }

      }
	}
	ILI9341_CS_HIGH;
}
void ILI9341_DrawIcon(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t* buff,uint16_t siz){
	uint32_t BufferSize = BURST_MAX_SIZE;
	uint32_t SendingSize;
	uint32_t SendingInBlock;
	uint32_t RemainderFromBlock;
  uint32_t i,j;
	uint8_t BurstBuffer[BURST_MAX_SIZE];

	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH){
		width=LCD_WIDTH-x;
	}

	if((y+height-1)>=LCD_HEIGHT){
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x+width-1, y+height-1);

	ILI9341_DC_HIGH;
	ILI9341_CS_LOW;
	SendingSize = siz * 2;
	SendingInBlock = SendingSize / BufferSize;
	RemainderFromBlock = SendingSize % BufferSize;
  
  for(i=0;i<SendingInBlock;i++){
     for(j=0;j<250;j++){
     	BurstBuffer[2 * j] = buff[250*i+j]>>8;
     	BurstBuffer[2 * j + 1] = buff[250*i+j];
     }
     Spi_Write_Buff(BurstBuffer,BufferSize);
  }

  for(j=0;j<(RemainderFromBlock/2);j++){
  	BurstBuffer[2 * j] = buff[250*SendingInBlock+j]>>8;
    BurstBuffer[2 * j + 1] = buff[250*SendingInBlock+j];
  }
  Spi_Write_Buff(BurstBuffer,RemainderFromBlock);
	ILI9341_CS_HIGH;
}