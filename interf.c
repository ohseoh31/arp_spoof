
#include <string.h>
#include <sys/stat.h>
#include "interf.h"


//read my interface information 
int interf_init(int flag, char *inface_name){
    struct stat buf;
    int iLen =strlen(inface_name);
    if(iLen<16){	    
			   
        char ifPath[256]="/sys/class/net/";  //interface path
	    strcat(ifPath ,inface_name);
	    strcat(ifPath ,"/address");
	    
        if(stat(ifPath,&buf) == 0){
            return 1;
        }
        else 
            return 0;
    }
    else
        return 0;
}
