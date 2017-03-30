

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "fetcharpt.h"



static int MAC_SubFormatTransform(char * argv)
{
    char num1 =*(argv) ;
    char num2 =*(argv+1) ;
    int ret =0;

    if(num1 <='9') ret +=(num1-'0') *16 ;
    else if(num1 <='e') ret +=(num1-'a' +10) *16 ;
    else if(num1 <='E') ret +=(num1-'A' +10) *16 ;

    if(num2 <='9') ret +=(num2-'0') ;
    else if(num2 <='e') ret +=(num2-'a' +10) ;
    else if(num2 <='E') ret +=(num2-'A' +10) ;
	//printf("dec : %d hex : %02x\n", ret, ret);
    return ret ;
}

int fetch_arpT(int flag, char * TargetIP, char * target_MAC){
	
	// ARP table at /proc/net/arp
	int ret = FETCH_ARP_TABLE_UNKNOW;
	FILE *arp_f =fopen("/proc/net/arp" , "r");

    if(arp_f == NULL){
	    ret = FETCH_ARP_TABLE_ERROR;
	}
	else{
	    // pass title
	    char Title[100] ;		//file title pass that
	    fgets(Title ,100 ,arp_f);

	    char t_IP[15] ;
	    char t_HW_type[8] ;
	    char t_Flags[8] ;
	    char t_MAC[17] ;
	    char t_Mask[5] ;
	    char t_Device[16] ;
		
	    while(!feof(arp_f)){ //search arp table feof is find file end_point check
	    	
			fscanf(arp_f ,"%s %s %s %s %s %s",t_IP,t_HW_type,t_Flags,t_MAC,t_Mask,t_Device);
			if(strcmp(t_IP ,TargetIP)==0 && strcmp(t_Flags ,"0x2")==0){
			
		        //printf("%s|%s|%s|%s|%s|%s\n",t_IP,t_HW_type,t_Flags,t_MAC,t_Mask,t_Device) ;	// if you want to look data , unmark that
				ret = FETCH_ARP_TABLE_SUCCESS;
		    	// copy data to Target_MAC
				for(int i=0 ; i<6 ;i++){
					*(target_MAC+i) = MAC_SubFormatTransform(&t_MAC[i*3]);
				}
				printf("\n");

				break ;
				
			}
	    }
	    fclose(arp_f);
    }
	return ret ;
}
