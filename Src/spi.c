#include "MS51_32K.H"
#include "spi.h"
/****************************************************************/
void Spi_Write_Byte(unsigned char u8SpiWB)
{
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    clr_SPSR_SPIF;
}
/****************************************************************/
unsigned char Spi_Read_Byte(unsigned char u8SpiWB)
{
    unsigned char u8SpiRB;
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    u8SpiRB = SPDR;
    clr_SPSR_SPIF;
    return u8SpiRB;
}

void Spi_Write_Buff(uint8_t *buff,uint16_t len){
	unsigned int i;
	for(i =0;i<len;i++){
		SPDR = buff[i];
        while(!(SPSR&0x80));
        clr_SPSR_SPIF;
	}
}