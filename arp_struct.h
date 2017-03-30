


//arp header info
typedef struct ARP_header
{
	unsigned short	Hardware ;
	unsigned short	Protocol ;
	unsigned char	HardwareAddressLen ;
	unsigned char	ProtocolAddressLeng ;
	unsigned short	Operation ;
	unsigned char	SoruceHardareAddr[6] ;
	unsigned char	SourceProtocolAddr[4] ;
	unsigned char	TargetHardareAddr[6] ;
	unsigned char	TargetProtocolAddr[4] ;
}ARP_HEADER;

//fake attack ip information
typedef struct attack_info
{
	unsigned char target_IP[4];	// Target IP
	unsigned char target_MAC[6];	// TargetMAC , this value will lookup ARP table
	unsigned char spoofing_IP[4];	// Spoofing IP
	unsigned char spoofing_MAC[6];	// spoofing MAC
}ATTACK_INFO;
