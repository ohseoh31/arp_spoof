
#include "fakeip_set.h"

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

//remapping MAC address informaiton
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

    return ret ;
}

//setting the return ip return mac address
int resolution_ipinfo(char *argv,char * interface,char *Ret_MAC)
{
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  strcpy(s.ifr_name, interface);
  if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
    int i;
    for (i = 0; i < 6; ++i){
	  	*(Ret_MAC+i) = s.ifr_addr.sa_data[i];
      	//printf(" %02x", (unsigned char) s.ifr_addr.sa_data[i]);
	  	//printf(" %02x", Ret_MAC[i]);
    }
    return 0;
  }else return 1;
}
