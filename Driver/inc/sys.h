
#define  FSYS_HXT   0
#define  FSYS_LXT   1
#define  FSYS_HIRC  2
#define  FSYS_LIRC  3
#define  FSYS_OSCIN_P30  4
#define  FSYS_HXTIN_P00  5
#define  HIRC_24        6
#define  HIRC_16        7
#define  HIRC_166       8
#define  FSYS_ECLK_P30	9
#define  FSYS_ECLK_P00  10


extern bit BIT_TMP;
extern unsigned char data  TA_REG_TMP,BYTE_TMP;

void FsysSelect(unsigned char u8FsysMode);
void ClockEnable(unsigned char u8FsysMode);
void ClockDisable(unsigned char u8FsysMode);
void ClockSwitch(unsigned char u8FsysMode);
void MODIFY_HIRC(unsigned char u8HIRCSEL);


