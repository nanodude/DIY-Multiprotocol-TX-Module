/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Multiprotocol is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Multiprotocol.  If not, see <http://www.gnu.org/licenses/>.
 */
 

//******************
// Protocols
//******************
enum PROTOCOLS
{
	MODE_SERIAL = 0,		// Serial commands
	MODE_FLYSKY = 1,		// =>A7105
	MODE_HUBSAN = 2,		// =>A7105
	MODE_FRSKYD = 3,		// =>CC2500
	MODE_HISKY  = 4,	    // =>NRF24L01
	MODE_V2X2   = 5,		// =>NRF24L01
	MODE_DSM   = 6,		// =>CYRF6936
	MODE_DEVO   = 7,		// =>CYRF6936
	MODE_YD717  = 8,		// =>NRF24L01
	MODE_KN     = 9,		// =>NRF24L01
	MODE_SYMAX  = 10,		// =>NRF24L01
	MODE_SLT    = 11,		// =>NRF24L01
	MODE_CX10   = 12,		// =>NRF24L01
	MODE_CG023  = 13,		// =>NRF24L01
	MODE_BAYANG = 14,		// =>NRF24L01
	MODE_FRSKYX = 15,		// =>CC2500
	MODE_ESKY   = 16,		// =>NRF24L01
	MODE_MT99XX = 17,		// =>NRF24L01
	MODE_MJXQ   = 18,		// =>NRF24L01
	MODE_SHENQI = 19,		// =>NRF24L01
	MODE_FY326  = 20,		// =>NRF24L01
	MODE_SFHSS  = 21,		// =>CC2500
	MODE_J6PRO  = 22,		// =>CYRF6936
	MODE_FQ777  = 23,		// =>NRF24L01
	MODE_ASSAN  = 24,		// =>NRF24L01
	MODE_FRSKYV = 25,	        // =>CC2500
	MODE_HONTAI = 26,	        // =>NRF24L01
	MODE_OPENLRS= 27	        // =>OpenLRS hardware
};

enum Flysky
{
	Flysky= 0,
	V9X9  = 1,
	V6X6  = 2,
	V912  = 3
};
enum Hisky
{
	Hisky = 0,
	HK310 = 1
};
enum DSM{
	DSM2_22	= 0,
	DSM2_11	= 1,
	DSMX_22	= 2,
	DSMX_11	= 3,
	DSM_AUTO = 4
};
enum YD717
{       			
	YD717   = 0,
	SKYWLKR = 1,
	SYMAX4  = 2,
	XINXUN  = 3,
	NIHUI   = 4
};
enum KN
{
	WLTOYS= 0,
	FEILUN= 1
};
enum SYMAX
{
	SYMAX   = 0,
	SYMAX5C = 1
};
enum CX10
{
    CX10_GREEN = 0,
    CX10_BLUE  = 1,		// also compatible with CX10-A, CX12
    DM007      = 2,
	Q282       = 3,
	JC3015_1   = 4,
	JC3015_2   = 5,
	MK33041    = 6,
	Q242       = 7
};
enum CG023
{
    CG023 = 0,
    YD829 = 1,
    H8_3D = 2
};
enum MT99XX
{
	MT99	= 0,
	H7		= 1,
	YZ		= 2,
	LS              = 3
};
enum MJXQ
{
	WLH08	= 0,
	X600	= 1,
	X800	= 2,
	H26D	= 3,
	E010	= 4
};

enum FRSKYX
{
	CH_16	= 0,
	CH_8	= 1,
};

enum HONTAI
{
	FORMAT_HONTAI	= 0,
	FORMAT_JJRCX1	= 1,
	FORMAT_X5C1	= 2
};

#define NONE 		0
#define P_HIGH		1
#define P_LOW		0
#define AUTOBIND	1
#define NO_AUTOBIND	0

struct PPM_Parameters
{
	uint8_t protocol : 5;
	uint8_t sub_proto : 3;
	uint8_t rx_num : 4;
	uint8_t power : 1;
	uint8_t autobind : 1;
	uint8_t option;
};

//*******************
//***   Pinouts   ***
//*******************

#if defined STM32_board

#define OCR1A TIMER2_BASE->CCR1
#define TCNT1 TIMER2_BASE->CNT
#define UDR0 USART2_BASE->DR
#define TIFR1 TIMER2_BASE->SR
#define OCF1A_bm TIMER_SR_CC1IF
#define UCSR0B USART2_BASE->CR1
#define RXCIE0 USART_CR1_RXNEIE_BIT
#define TXCIE0 USART_CR1_TXEIE_BIT
//#define TIFR1 TIMER2_BASE->SR
//********************
#define BIND_pin PA0
#define LED_pin  PA1						
//
#define PPM_pin PA8	//PPM  5V tolerant													
//
#define S1_pin PA4	//dial switch pins	
#define S2_pin PA5							
#define S3_pin PA6
#define S4_pin PA7	
//
#define CTRL1 PB4	//PE1						
#define CTRL2 PB5  //PE2
//CS pins
#define CC25_CSN_pin PB6//CC2500
#define NRF_CSN_pin  PB7//NRF24L01
#define CYRF_RST_pin PB8//CYRF RESET
#define A7105_CSN_pin PB9//A7105
#define CYRF_CSN_pin PB12//CYRF CSN
//SPI pins	
#define SCK_pin PB13//SCK
#define SDO_pin PB14//MISO	
#define SDI_pin PB15//MOSI							
//
#define TX_INV_pin PB3
#define RX_INV_pin PB1
//
#define PE1_on  digitalWrite(CTRL1,HIGH)
#define PE1_off digitalWrite(CTRL1,LOW)
//
#define PE2_on  digitalWrite(CTRL2,HIGH)
#define PE2_off digitalWrite(CTRL2,LOW)

#define RS_HI digitalWrite(CYRF_RST_pin,HIGH)				//reset pin cyrf 
#define RS_LO digitalWrite(CYRF_RST_pin,LOW)


#define  A7105_CSN_on digitalWrite(A7105_CSN_pin,HIGH)			
#define  A7105_CSN_off digitalWrite(A7105_CSN_pin,LOW)		

#define NRF_CE_on
#define NRF_CE_off

#define  SCK_on digitalWrite(SCK_pin,HIGH)			
#define  SCK_off digitalWrite(SCK_pin,LOW)		

#define  SDI_on digitalWrite(SDI_pin,HIGH)			
#define  SDI_off digitalWrite(SDI_pin,LOW)		

#define  SDI_1 (digitalRead(SDI_pin)==HIGH)	
#define  SDI_0 (digitalRead(SDI_pin)==LOW)			

#define CC25_CSN_on digitalWrite(CC25_CSN_pin,HIGH)		
#define CC25_CSN_off digitalWrite(CC25_CSN_pin,LOW)	

#define NRF_CSN_on digitalWrite(NRF_CSN_pin,HIGH)		
#define NRF_CSN_off digitalWrite(NRF_CSN_pin,LOW)	

#define CYRF_CSN_on digitalWrite(CYRF_CSN_pin,HIGH)		
#define CYRF_CSN_off digitalWrite(CYRF_CSN_pin,LOW)

#define CYRF_RST_HI digitalWrite(CYRF_RST_pin,HIGH)	//reset cyrf 
#define CYRF_RST_LO digitalWrite(CYRF_RST_pin,LOW)	//

#define  SDO_1 (digitalRead(SDO_pin)==HIGH)		
#define  SDO_0 (digitalRead(SDO_pin)==LOW)	

#define TX_INV_on digitalWrite(TX_INV_pin,HIGH)		
#define TX_INV_off digitalWrite(TX_INV_pin,LOW)

#define RX_INV_on digitalWrite(RX_INV_pin,HIGH)		
#define RX_INV_off digitalWrite(RX_INV_pin,LOW)

#define LED_on  digitalWrite(LED_pin,HIGH)
#define LED_off  digitalWrite(LED_pin,LOW)
#define LED_toggle  digitalWrite(LED_pin ,!digitalRead(LED_pin))
#define LED_SET_OUTPUT pinMode(LED_pin,OUTPUT)
#define IS_LED_on  ( digitalRead(LED_pin)==HIGH)

#define cli() noInterrupts()
#define sei() interrupts()
#define _delay_us(x) delayMicroseconds(x)
#define delayMilliseconds(x) delay(x)
//
#endif



// Macros
#define NOP() __asm__ __volatile__("nop")
#define BV(bit) (1 << bit)

//Serial flags definition
#define RX_FLAG_on			protocol_flags |= _BV(0)
#define RX_FLAG_off			protocol_flags &= ~_BV(0)
#define IS_RX_FLAG_on		( ( protocol_flags & _BV(0) ) !=0 )
//
#define CHANGE_PROTOCOL_FLAG_on		protocol_flags |= _BV(1)
#define CHANGE_PROTOCOL_FLAG_off		protocol_flags &= ~_BV(1)
#define IS_CHANGE_PROTOCOL_FLAG_on	( ( protocol_flags & _BV(1) ) !=0 )
//
#define POWER_FLAG_on		protocol_flags |= _BV(2)
#define POWER_FLAG_off		protocol_flags &= ~_BV(2)
#define IS_POWER_FLAG_on	( ( protocol_flags & _BV(2) ) !=0 )
//
#define RANGE_FLAG_on		protocol_flags |= _BV(3)
#define RANGE_FLAG_off		protocol_flags &= ~_BV(3)
#define IS_RANGE_FLAG_on	( ( protocol_flags & _BV(3) ) !=0 )
//
#define AUTOBIND_FLAG_on	protocol_flags |= _BV(4)
#define AUTOBIND_FLAG_off	protocol_flags &= ~_BV(4)
#define IS_AUTOBIND_FLAG_on	( ( protocol_flags & _BV(4) ) !=0 )
//
#define BIND_BUTTON_FLAG_on		protocol_flags |= _BV(5)
#define BIND_BUTTON_FLAG_off	protocol_flags &= ~_BV(5)
#define IS_BIND_BUTTON_FLAG_on	( ( protocol_flags & _BV(5) ) !=0 )

//PPM RX OK
#define PPM_FLAG_off			protocol_flags &= ~_BV(6)
#define PPM_FLAG_on			protocol_flags |= _BV(6)
#define IS_PPM_FLAG_on		( ( protocol_flags & _BV(6) ) !=0 )

//Bind flag for blinking
#define BIND_IN_PROGRESS	protocol_flags &= ~_BV(7)
#define BIND_DONE			protocol_flags |= _BV(7)
#define IS_BIND_DONE_on		( ( protocol_flags & _BV(7) ) !=0 )

#define BAD_PROTO_off		protocol_flags2 &= ~_BV(0)
#define BAD_PROTO_on		protocol_flags2 |= _BV(0)
#define IS_BAD_PROTO_on		( ( protocol_flags2 & _BV(0) ) !=0 )

#define RX_DONOTUPDTAE_off	protocol_flags2 &= ~_BV(1)
#define RX_DONOTUPDTAE_on	protocol_flags2 |= _BV(1)
#define IS_RX_DONOTUPDTAE_on	( ( protocol_flags2 & _BV(1) ) !=0 )

#define RX_MISSED_BUFF_off	protocol_flags2 &= ~_BV(2)
#define RX_MISSED_BUFF_on	protocol_flags2 |= _BV(2)
#define IS_RX_MISSED_BUFF_on	( ( protocol_flags2 & _BV(2) ) !=0 )

#define TX_MAIN_PAUSE_off		protocol_flags2 &= ~_BV(3)
#define TX_MAIN_PAUSE_on			protocol_flags2 |= _BV(3)
#define IS_TX_MAIN_PAUSE_on		( ( protocol_flags2 & _BV(3) ) !=0 )

#define TX_RX_PAUSE_off		protocol_flags2 &= ~_BV(4)
#define TX_RX_PAUSE_on			protocol_flags2 |= _BV(4)
#define IS_TX_RX_PAUSE_on		( ( protocol_flags2 & _BV(4) ) !=0 )

#define IS_TX_PAUSE_on		( ( protocol_flags2 & (_BV(4)|_BV(3)) ) !=0 )


#define IS_BIND_BUTTON_on	(digitalRead(BIND_pin)==LOW)

#define BIND_SET_INPUT		pinMode(BIND_pin,INPUT)
#define BIND_SET_PULLUP	        digitalWrite(BIND_pin,HIGH)	
#define BIND_SET_OUTPUT	        pinMode(BIND_pin,OUTPUT)

#define BLINK_BIND_TIME	100
#define BLINK_SERIAL_TIME	500
#define BLINK_BAD_PROTO_TIME_LOW	1000
#define BLINK_BAD_PROTO_TIME_HIGH	50

//AUX flags definition
#define Servo_AUX1	Servo_AUX & _BV(0)
#define Servo_AUX2	Servo_AUX & _BV(1)
#define Servo_AUX3	Servo_AUX & _BV(2)
#define Servo_AUX4	Servo_AUX & _BV(3)
#define Servo_AUX5	Servo_AUX & _BV(4)
#define Servo_AUX6	Servo_AUX & _BV(5)
#define Servo_AUX7	Servo_AUX & _BV(6)
#define Servo_AUX8	Servo_AUX & _BV(7)

#define GET_FLAG(ch, mask) ( ch ? mask : 0)

//************************
//***  Power settings  ***
//************************
enum {
	TXPOWER_100uW,
	TXPOWER_300uW,
	TXPOWER_1mW,
	TXPOWER_3mW,
	TXPOWER_10mW,
	TXPOWER_30mW,
	TXPOWER_100mW,
	TXPOWER_150mW
};

// A7105 power
//	Power amp is ~+16dBm so:
enum A7105_POWER
{
	A7105_POWER_0 = 0x00<<3 | 0x00,	// TXPOWER_100uW  = -23dBm == PAC=0 TBG=0
	A7105_POWER_1 = 0x00<<3 | 0x01,	// TXPOWER_300uW  = -20dBm == PAC=0 TBG=1
	A7105_POWER_2 = 0x00<<3 | 0x02,	// TXPOWER_1mW    = -16dBm == PAC=0 TBG=2
	A7105_POWER_3 = 0x00<<3 | 0x04,	// TXPOWER_3mW    = -11dBm == PAC=0 TBG=4
	A7105_POWER_4 = 0x01<<3 | 0x05,	// TXPOWER_10mW   =  -6dBm == PAC=1 TBG=5
	A7105_POWER_5 = 0x02<<3 | 0x07,	// TXPOWER_30mW   =   0dBm == PAC=2 TBG=7
	A7105_POWER_6 = 0x03<<3 | 0x07,	// TXPOWER_100mW  =   1dBm == PAC=3 TBG=7
	A7105_POWER_7 = 0x03<<3 | 0x07	// TXPOWER_150mW  =   1dBm == PAC=3 TBG=7
};
#define A7105_HIGH_POWER	A7105_POWER_7
#define	A7105_LOW_POWER		A7105_POWER_3
#define	A7105_RANGE_POWER	A7105_POWER_0
#define	A7105_BIND_POWER	A7105_POWER_0

// NRF Power
// Power setting is 0..3 for nRF24L01
// Claimed power amp for nRF24L01 from eBay is 20dBm. 
enum NRF_POWER
{						//      Raw            w 20dBm PA
	NRF_POWER_0 = 0x00,	// 0 : -18dBm  (16uW)   2dBm (1.6mW)
	NRF_POWER_1 = 0x01,	// 1 : -12dBm  (60uW)   8dBm   (6mW)
	NRF_POWER_2 = 0x02,	// 2 :  -6dBm (250uW)  14dBm  (25mW)
	NRF_POWER_3 = 0x03	// 3 :   0dBm   (1mW)  20dBm (100mW)
};
#define NRF_HIGH_POWER		NRF_POWER_2
#define	NRF_LOW_POWER		NRF_POWER_1
#define	NRF_RANGE_POWER		NRF_POWER_0
#define	NRF_BIND_POWER		NRF_POWER_0

// CC2500 power output from the chip itself
// The numbers do not take into account any outside amplifier
enum CC2500_POWER
{
	CC2500_POWER_0  = 0x00,	// –55dbm or less
	CC2500_POWER_1  = 0x50,	// -30dbm
	CC2500_POWER_2  = 0x44, // –28dbm
	CC2500_POWER_3  = 0xC0, // –26dbm
	CC2500_POWER_4  = 0x84, // –24dbm
	CC2500_POWER_5  = 0x81, // –22dbm
	CC2500_POWER_6  = 0x46, // –20dbm
	CC2500_POWER_7  = 0x93, // –18dbm
	CC2500_POWER_8  = 0x55, // –16dbm
	CC2500_POWER_9  = 0x8D, // –14dbm
	CC2500_POWER_10 = 0xC6,	// -12dbm
	CC2500_POWER_11 = 0x97,	// -10dbm
	CC2500_POWER_12 = 0x6E,	//  -8dbm
	CC2500_POWER_13 = 0x7F,	//  -6dbm
	CC2500_POWER_14 = 0xA9,	//  -4dbm
	CC2500_POWER_15 = 0xBB,	//  -2dbm
	CC2500_POWER_16 = 0xFE,	//   0dbm
	CC2500_POWER_17 = 0xFF	//  +1dbm
};
#define CC2500_HIGH_POWER	CC2500_POWER_16
#define CC2500_LOW_POWER	CC2500_POWER_13
#define CC2500_RANGE_POWER	CC2500_POWER_1
#define CC2500_BIND_POWER	CC2500_POWER_1

// CYRF power
enum CYRF_POWER
{
	CYRF_POWER_0 = 0x00,	// -35dbm
	CYRF_POWER_1 = 0x01,	// -30dbm
	CYRF_POWER_2 = 0x02,	// -24dbm
	CYRF_POWER_3 = 0x03,	// -18dbm
	CYRF_POWER_4 = 0x04,	// -13dbm
	CYRF_POWER_5 = 0x05,	//  -5dbm
	CYRF_POWER_6 = 0x06,	//   0dbm
	CYRF_POWER_7 = 0x07		//  +4dbm
};
#define CYRF_HIGH_POWER		CYRF_POWER_7
#define	CYRF_LOW_POWER		CYRF_POWER_3
#define	CYRF_RANGE_POWER	CYRF_POWER_1	// 1/30 of the full power distance
#define	CYRF_BIND_POWER		CYRF_POWER_0

enum TXRX_State {
	TXRX_OFF,
	TX_EN,
	RX_EN
};

// Packet ack status values
enum {
	PKT_PENDING = 0,
	PKT_ACKED,
	PKT_TIMEOUT
};
// baudrate defines for serial
#define SPEED_100K	0
#define SPEED_9600	1
#define SPEED_57600	2
#define SPEED_125K	3


//****************************************
//*** MULTI protocol serial definition ***
//****************************************
/*
**************************
16 channels serial protocol
**************************
Serial: 100000 Baud 8e2      _ xxxx xxxx p --
  Total of 26 bytes
  Stream[0]   = 0x55	sub_protocol values are 0..31
  Stream[0]   = 0x54	sub_protocol values are 32..63
   header
  Stream[1]   = sub_protocol|BindBit|RangeCheckBit|AutoBindBit;
   sub_protocol is 0..31 (bits 0..4), value should be added with 32 if Stream[0] = 0x54
   =>	Reserved	0
					Flysky		1
					Hubsan		2
					FrskyD		3
					Hisky		4
					V2x2		5
					DSM			6
					Devo		7
					YD717		8
					KN			9
					SymaX		10
					SLT			11
					CX10		12
					CG023		13
					Bayang		14
					FrskyX		15
					ESky		16
					MT99XX		17
					MJXQ		18
					SHENQI		19
					FY326		20
					SFHSS		21
					J6PRO		22
					FQ777		23
					ASSAN		24
					FrskyV		25
					HONTAI		26
					OpenLRS		27
   BindBit=>		0x80	1=Bind/0=No
   AutoBindBit=>	0x40	1=Yes /0=No
   RangeCheck=>		0x20	1=Yes /0=No
  Stream[2]   = RxNum | Power | Type;
   RxNum value is 0..15 (bits 0..3)
   Type is 0..7 <<4     (bit 4..6)
		sub_protocol==Flysky
			Flysky		0
			V9x9		1
			V6x6		2
			V912		3
		sub_protocol==Hisky
			Hisky		0
			HK310		1
		sub_protocol==DSM
			DSM2_22 	0
			DSM2_11 	1
			DSMX_22 	2
			DSMX_11 	3
		sub_protocol==YD717
			YD717		0
			SKYWLKR		1
			SYMAX4		2
			XINXUN		3
			NIHUI		4
		sub_protocol==KN
			WLTOYS		0
			FEILUN		1
		sub_protocol==SYMAX
			SYMAX		0
			SYMAX5C		1
		sub_protocol==CX10
			CX10_GREEN	0
			CX10_BLUE	1	// also compatible with CX10-A, CX12
			DM007		2
			Q282		3
			JC3015_1	4
			JC3015_2	5
			MK33041		6
			Q242		7
		sub_protocol==CG023
			CG023		0
			YD829		1
			H8_3D		2
		sub_protocol==MT99XX
			MT99		0
			H7			1
			YZ			2
			LS			3
		sub_protocol==MJXQ
			WLH08		0
			X600		1
			X800		2
			H26D		3
			E010		4
		sub_protocol==FRSKYX
			CH_16		0
			CH_8		1
		sub_protocol==HONTAI
			FORMAT_HONTAI	0
			FORMAT_JJRCX1	1
			FORMAT_X5C1		2
   Power value => 0x80	0=High/1=Low
  Stream[3]   = option_protocol;
   option_protocol value is -127..127
  Stream[4] to [25] = Channels
   16 Channels on 11 bits (0..2047)
	0		-125%
    204		-100%
	1024	   0%
	1843	+100%
	2047	+125%
   Channels bits are concatenated to fit in 22 bytes like in SBUS protocol
*/
