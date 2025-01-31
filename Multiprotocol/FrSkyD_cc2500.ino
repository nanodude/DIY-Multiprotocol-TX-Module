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

#if defined(FRSKYD_CC2500_INO)

#include "iface_cc2500.h"

static void __attribute__((unused)) frsky2way_init(uint8_t bind)
{
	// Configure cc2500 for tx mode
	//
	for(uint8_t i=0;i<36;i++)
	{
		uint8_t reg=pgm_read_byte_near(&cc2500_conf[i][0]);
		uint8_t val=pgm_read_byte_near(&cc2500_conf[i][1]);
		
		if(reg==CC2500_0C_FSCTRL0)
			val=option;
		else
			if(reg==CC2500_1B_AGCCTRL2)
				val=bind ? 0x43 : 0x03;
		CC2500_WriteReg(reg,val);
	}
        prev_option = option ;

	CC2500_SetTxRxMode(TX_EN);
	CC2500_SetPower();
	
	CC2500_Strobe(CC2500_SIDLE);	

	CC2500_WriteReg(CC2500_09_ADDR, bind ? 0x03 : rx_tx_addr[3]);
	CC2500_WriteReg(CC2500_07_PKTCTRL1, 0x05);
	CC2500_Strobe(CC2500_SIDLE);	// Go to idle...
	//
	CC2500_WriteReg(CC2500_0A_CHANNR, 0x00);
	CC2500_WriteReg(CC2500_23_FSCAL3, 0x89);
	CC2500_Strobe(CC2500_SFRX);
	//#######END INIT########		
}
	
static uint8_t __attribute__((unused)) get_chan_num(uint16_t idx)
{
	uint8_t ret = (idx * 0x1e) % 0xeb;
	if(idx == 3 || idx == 23 || idx == 47)
		ret++;
	if(idx > 47)
		return 0;
	return ret;
}

static void __attribute__((unused)) frsky2way_build_bind_packet()
{
	//11 03 01 d7 2d 00 00 1e 3c 5b 78 00 00 00 00 00 00 01
	//11 03 01 19 3e 00 02 8e 2f bb 5c 00 00 00 00 00 00 01
	packet[0] = 0x11;                
	packet[1] = 0x03;                
	packet[2] = 0x01;                
	packet[3] = rx_tx_addr[3];
	packet[4] = rx_tx_addr[2];
	uint16_t idx = ((state -FRSKY_BIND) % 10) * 5;
	packet[5] = idx;
	packet[6] = get_chan_num(idx++);
	packet[7] = get_chan_num(idx++);
	packet[8] = get_chan_num(idx++);
	packet[9] = get_chan_num(idx++);
	packet[10] = get_chan_num(idx++);
	packet[11] = 0x00;
	packet[12] = 0x00;
	packet[13] = 0x00;
	packet[14] = 0x00;
	packet[15] = 0x00;
	packet[16] = 0x00;
	packet[17] = 0x01;
}

static void __attribute__((unused)) frsky2way_data_frame()
{//pachet[4] is telemetry user frame counter(hub)
	//11 d7 2d 22 00 01 c9 c9 ca ca 88 88 ca ca c9 ca 88 88
	//11 57 12 00 00 01 f2 f2 f2 f2 06 06 ca ca ca ca 18 18
	packet[0] = 0x11;             //Length
	packet[1] = rx_tx_addr[3];
	packet[2] = rx_tx_addr[2];
	packet[3] = counter;//	
	#if defined TELEMETRY
		packet[4] = telemetry_counter;
	#else
		packet[4] = 0x00;
	#endif

	packet[5] = 0x01;
	//
	packet[10] = 0;
	packet[11] = 0;
	packet[16] = 0;
	packet[17] = 0;
	for(uint8_t i = 0; i < 8; i++)
	{
		uint16_t value;
			value = convert_channel_frsky(i);
		if(i < 4)
		{
			packet[6+i] = value & 0xff;
			packet[10+(i>>1)] |= ((value >> 8) & 0x0f) << (4 *(i & 0x01));
		} 
		else
		{
			packet[8+i] = value & 0xff;
			packet[16+((i-4)>>1)] |= ((value >> 8) & 0x0f) << (4 * ((i-4) & 0x01));
		}
	}
} 

uint16_t initFrSky_2way()
{
	if(IS_AUTOBIND_FLAG_on)
	{	   
		frsky2way_init(1);
		state = FRSKY_BIND;
	}
	else
	{
		frsky2way_init(0);
		state = FRSKY_DATA2;
	}
	return 10000;
}	
		
uint16_t ReadFrSky_2way()
{ 
	if (state < FRSKY_BIND_DONE)
	{
		frsky2way_build_bind_packet();
		CC2500_Strobe(CC2500_SIDLE);
		CC2500_WriteReg(CC2500_0A_CHANNR, 0x00);
		CC2500_WriteReg(CC2500_23_FSCAL3, 0x89);		
		CC2500_Strobe(CC2500_SFRX);//0x3A
		CC2500_WriteData(packet, packet[0]+1);
		state++;
		return 9000;
	}
	if (state == FRSKY_BIND_DONE)
	{
		state = FRSKY_DATA2;
		frsky2way_init(0);
		counter = 0;
		BIND_DONE;
	}
	else
		if (state == FRSKY_DATA5)
		{
			CC2500_Strobe(CC2500_SRX);//0x34 RX enable
			state = FRSKY_DATA1;	
			return 9200;
		}
	counter = (counter + 1) % 188;	
	if (state == FRSKY_DATA4)
	{	//telemetry receive
		CC2500_SetTxRxMode(RX_EN);
		CC2500_Strobe(CC2500_SIDLE);
		CC2500_WriteReg(CC2500_0A_CHANNR, get_chan_num(counter % 47));
		CC2500_WriteReg(CC2500_23_FSCAL3, 0x89);
		state++;
		return 1300;
	}
	else
	{
		if (state == FRSKY_DATA1)
		{
			len = CC2500_ReadReg(CC2500_3B_RXBYTES | CC2500_READ_BURST) & 0x7F;
			if (len && len<=MAX_PKT)//27 bytes
			{
				CC2500_ReadData(pkt, len);	//received telemetry packets			
				#if defined(TELEMETRY)
				//parse telemetry packet here
				frsky_check_telemetry(pkt,len);	//check if valid telemetry packets and buffer them.
				#endif	
			}			
			CC2500_SetTxRxMode(TX_EN);
			CC2500_SetPower();	// Set tx_power
		}
		CC2500_Strobe(CC2500_SIDLE);
		CC2500_WriteReg(CC2500_0A_CHANNR, get_chan_num(counter % 47));
		if ( prev_option != option )
		{
		CC2500_WriteReg(CC2500_0C_FSCTRL0,option);	// Frequency offset hack 
		prev_option = option ;
		}
		CC2500_WriteReg(CC2500_23_FSCAL3, 0x89);
		CC2500_Strobe(CC2500_SFRX);        
		frsky2way_data_frame();
		CC2500_WriteData(packet, packet[0]+1);
		state++;
	}				
	return state == FRSKY_DATA4 ? 7500 : 9000;		
}
#endif
