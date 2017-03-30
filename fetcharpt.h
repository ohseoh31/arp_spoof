
#define FETCH_ARP_TABLE_ERROR		0x0000		// could not access localhost ARP table
#define FETCH_ARP_TABLE_SUCCESS		0x0001		// find ARP entry
#define FETCH_ARP_TABLE_UNKNOW		0x0002		// ARP entry unknow or empty

int fetch_arpT(int flag, char * TargetIP, char * target_MAC);
