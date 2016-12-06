/* 
 * Battery Led Monitor
 * Copyright (C) 2011 Christophe Rubeck <christux@wanadoo.fr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
/*
	 Monitor your pc with keyboard leds on Linux !
	-----------------------------------------------
	
Keyboard Led Monitor is a free software which can monitor the utilization of resources with the leds of the keyboard (num lock, caps lock, scroll lock). The monitoring looks like the battery status bar of a mobile phone. Monitoring of CPU level, network traffic, memory  and swap usage, and battery level are supported. The software can be used with game modes also, like the program bl.
*/

// For simplicity defines, functions and variables moved to klm.h NA 08-01-07
#include "klm.h"
#define VERSION "1.2"
#define COPYRIGHT "Copyright (C) 2011 Christophe Rubeck"

int main(int argc, char *argv[])
{
	char background = 0 ,mode = 0 ;
	signed char choice ;
	extern char *optarg ;
	
	srand( (unsigned)time( 0 ) );
	
	// check args and print out message if necessary
	if(strcmp("-h",argv[argc - 1]) == 0 || strcmp("--help",argv[argc - 1]) == 0 || argc == 1 ) usage();

	// might have to show the warranty
	if(strcmp("-w",argv[argc - 1]) == 0) warranty();

	// get options
	while((choice = getopt(argc,argv,"DCN:m:MSAkRblrcdhw")) != -1)
		switch(choice) {
		    case 'D': background = 1 ; break;
 			case 'C': if(mode > 0) usage() ; mode = CPU ; break;
 			case 'N': if(mode > 0) usage() ; mode = NETWORK ; 
 				if(optarg != NULL && strcmp( optarg , argv[argc - 1] ) != 0 ) strcpy(network_device,optarg);
 				else
 				{
 					printf("You must specify the network interface!\n");
 					exit(-1);
 				}
 				break;
 			case 'M': if(mode > 0) usage() ; mode = MEMORY ; break;
 			case 'S': if(mode > 0) usage() ; mode = SWAP ; break;
 			case 'A': if(mode > 0) usage() ; mode = rand() % 6 + 5 ; break;
 			case 'k': if(mode > 0) usage() ; mode = K2000M ; break;
 			case 'R': if(mode > 0) usage() ; mode = RANDOM ; break;
 			case 'b': if(mode > 0) usage() ; mode = BOUNCE ; break;
 			case 'l': if(mode > 0) usage() ; mode = LEFTM ; break;
 			case 'r': if(mode > 0) usage() ; mode = RIGHTM ; break;
		    case 'c': if(mode > 0) usage() ; mode = CENTER ; break;
			// Added case NA 7/31/07
		    case 'm': if(mode > 0) usage() ; mode = MORSE ;
			  if(optarg != NULL && strcmp( optarg , argv[argc - 1] ) != 0 ) strcpy(morse_string,optarg);
			  else
			    {
			      printf("You must specify a string to convert to morse code!\n");
			      exit(-1);
			    }
			  break;
			case 'd': mode = DEMO ; break;
 			default : usage(); break ;
		}
	
	// if nothing selected
	if(mode == 0) usage();
	
	// get the device to use
	strcpy(device,argv[argc - 1]) ;

	// try to open tty device
	if((open(device,O_RDWR)) < 0)
	{
		printf("Failed to open \"%s\", type klm -h for help\n",device);
		exit(-1);
	}
	
	// signal handlers
	signal(SIGINT,end);
	signal(SIGQUIT,end);
	signal(SIGTERM,end);
	signal(SIGHUP,end);

	// daemonisation - Piotr Roszatycki <dexter@debian.org>
	if (background == 1) daemon(0,0);
	if (background == 1) daemon(0,0);
	
	// hello ! 
        // Version 1.1.1 has morse code additions NA 7/31/07
	printf("Keyboard Led Monitor %s\n",VERSION);
	switch(mode) {
		case CPU : printf("CPU monitoring\n"); break;
		case NETWORK : printf("Network monitoring\n"); break;
		case MEMORY : printf("Memory monitoring\n"); break;
		case SWAP : printf("Swap monitoring\n"); break;
		case K2000M : printf("K2000 mode\n"); break;
		case RANDOM : printf("Random mode\n"); break;
		case BOUNCE : printf("Bounce mode\n"); break;
		case LEFTM : printf("Left mode\n"); break;
		case RIGHTM : printf("Right mode\n"); break;
		case CENTER : printf("Center mode\n"); break;
		case MORSE : printf("Morse mode : %s\n",morse_string); break;
	}	
			
	// start monitoring
	while(1)
	{
		switch(mode) {
			case CPU : Cpu_Monitor() ; break;
			case NETWORK : Network_Monitor() ; break;
			case MEMORY : Memory_Monitor() ; break;
			case SWAP : Swap_Monitor(); break;
			case K2000M : K2000(); break;
			case RANDOM : Random(); break;
			case BOUNCE : Bounce(); break;
			case LEFTM : Left(); break;
			case RIGHTM : Right(); break;
			case CENTER : Center(); break;
			case MORSE : morse(LEFT, RIGHT, MIDDLE, TEMP, morse_string); return 1; break;
			case DEMO : Demo(); break;
		}
	}	
	return 0;
}

void end(int signal) // turn off the led before leaving
{
	Reset_Led();
	exit(0);
}

void usage() // print help
{
	printf("Keyboard Led Monitor %s, %s\n",VERSION,COPYRIGHT);
	printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	printf("For details, type 'klm -w'.\n");
	printf("Usage: klm [-DCMSAkRblrchw] [-m message] [-N interface] <device>\n");
	printf("-D	run on the background (needed for daemon)\n");
	printf("-C	monitor the CPU level\n");
	printf("-N	monitor the network traffic\n");
	printf("-M	monitor the memory level\n");
	printf("-S	monitor the swap level\n");
	printf("-A	chose randomly a design mode at startup\n");
	printf("-k	K2000 design mode\n");
	printf("-R	random design mode\n");
	printf("-b	bounce design mode\n");
	printf("-l	left design mode\n");
	printf("-r	right design mode\n");
	printf("-c	center design mode\n");
	printf("-m	converts your message to morse code (e.g. klm -m \"Test monkey\" /dev/tty1)\n");
	printf("-d	demo mode\n");
	printf("-h	prints out this message\n");
	printf("-w	prints out warranty\n");
	printf("<device> is the virtual console you are logged in on or the virtual console\n that your X server is running on, in doubt try \"/dev/tty1\" or \"/dev/console\"\n");
	exit(0);
}

void warranty()
{
	printf("Keyboard Led Monitor %s, %s\n\n",VERSION,COPYRIGHT);
    printf("\
    This program is free software; you can redistribute it and/or modify\n\
    it under the terms of the GNU General Public License as published by\n\
    the Free Software Foundation; either version 2 of the License, or\n\
    (at your option) any later version.\n\n\
    This program is distributed in the hope that it will be useful,\n\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
    GNU General Public License for more details.\n\n\
    You should have received a copy of the GNU General Public License\n\
    along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n");
	exit(0);
}

// keyboard leds control

void Led( char code, int delay) // delay in micro second
{
	char led;
	if ((led = open(device,O_NOCTTY)) == -1) {
	     perror("open");
	     exit(-1);
          }
	if (ioctl(led,KDSETLED,code) == -1) {
	     perror("ioctl");
	     close(led);
	     exit(-1);
          }
	close(led);
	usleep(delay);
}

// design modes

void Reset_Led()
{
	Led(NONE,0);
}

void K2000()
{
	int i ;
	for( i = 0 ; i < 4 ; i++ )
	{
		Led(LEFT,TEMP);
		Led(LEFT+MIDDLE,TEMP);
		Led(LEFT+MIDDLE+RIGHT,TEMP);
		Led(MIDDLE+RIGHT,TEMP);
		Led(RIGHT,TEMP);
		Led(NONE,2*TEMP);
		Led(RIGHT,TEMP);
		Led(MIDDLE+RIGHT,TEMP);
		Led(LEFT+MIDDLE+RIGHT,TEMP);
		Led(LEFT+MIDDLE,TEMP);
		Led(LEFT,TEMP);
		Led(NONE,2*TEMP);
	}
}

/*
Thanks to Greg Hankins <greg.hankins@cc.gatech.edu> and Ed Doolittle <dolittle@math.toronto.edu> for the blinkenlights software.
*/

void Left()
{
	int i ;
	for( i = 0 ; i < 15 ; i++ )
	{
		Led(LEFT,TEMP);
		Led(MIDDLE,TEMP);
		Led(RIGHT,TEMP);
		Led(NONE,TEMP);
	}
}

void Right()
{
	int i ;
	for( i = 0 ; i < 15 ; i++ )
	{
		Led(RIGHT,TEMP);
		Led(MIDDLE,TEMP);
		Led(LEFT,TEMP);
		Led(NONE,TEMP);
	}
}

void Bounce()
{
	int i ;
	for( i = 0 ; i < 9 ; i++ )
	{
		Led(LEFT,TEMP);
		Led(MIDDLE,TEMP);
		Led(RIGHT,2*TEMP);
		Led(MIDDLE,TEMP);
		Led(LEFT,TEMP);
	}
}

void Center()
{
	int i ;
	for( i = 0 ; i < 25 ; i++ )
	{
		Led(LEFT+RIGHT,2*TEMP);
		Led(MIDDLE,2*TEMP);
	}
}

void Random()
{
	int i ;	
	for( i = 0 ; i < 50 ; i++ ) Led(rand() % 8,TEMP);
}

// Displays morse code function
void Morse() 
{
  int i ;

  // S
  for( i = 0 ; i < 3 ; i++ ) 
    {
      Led(LEFT+RIGHT+MIDDLE,TEMP*2);
      Led(0,TEMP*2);
    }
  // O
  for( i = 0 ; i < 3 ; i++ )
    {
      Led(LEFT+RIGHT+MIDDLE,TEMP*6);
      Led(0,TEMP*2);
    }
  // S
  for( i = 0 ; i < 3 ; i++ )
    {
      Led(LEFT+RIGHT+MIDDLE,TEMP*2);
      Led(0,TEMP*2);
    }
  // Pause at the end
  Led(0,TEMP*10);

}

// demo mode

void Demo()
{
	printf("\nDemo mode\n\n");
	printf("Computer monitoring : \n") ;
	printf("CPU monitoring\n");
	Cpu_Monitor() ;
	printf("Memory monitoring\n");
	Memory_Monitor() ;
	
	if(strcmp(network_device,"") != 0)
	{
		printf("Network monitoring of %s\n", network_device);
		Network_Monitor() ;
	}
		
	printf("\nAnd now, have fun !\n");
	printf("K2000 mode\n");
	K2000();
	printf("Random mode\n");
	Random();
	printf("Bounce mode\n");
	Bounce();
	printf("Left mode\n");
	Left();
	printf("Right mode\n");
	Right();
	printf("Center mode\n");
	Center();
	printf("Morse mode : \"Hello\"\n");
	morse(LEFT, RIGHT, MIDDLE, TEMP, "Hello");
	printf("End of demo mode. Thanks.\n");
	exit(0);
}

// CPU monitoring

int Cpu_Read()
{
	int user_read, nice_read ;
	FILE *cpu ;
	cpu = fopen( "/proc/stat" , "r" ) ;
	if(!cpu)
	{
		printf("Error opening \"/proc/stat\"\n") ;
		exit(-1) ;
	}
	fscanf(cpu,"%*s %i %*i %i %*i",&user_read,&nice_read) ;
	fclose(cpu) ;
	return user_read + nice_read ;
}

int Cpu_Load()
{
	int load = Cpu_Read(), level ;
	usleep(250000);
	level = (Cpu_Read() - load) * 4 ;
	
	/*
	I comment this because there are troubles when frequencies change (cpufreq)
	
	if( level < 0 || level > 100)
	{
		printf("Error in calculating cpu level\n") ;
		exit(-1) ;
	}
	*/
	return level ;
}

void Cpu_Monitor()
{
	int i, cpu_load;
	char signal, signal_old ;
	
	for(i=0;i<20;i++)
	{
		cpu_load = Cpu_Load() ;
		if( cpu_load > 75 ) signal = LEFT+RIGHT+MIDDLE ;
		if( cpu_load <= 75 && cpu_load > 50 ) signal = LEFT+MIDDLE ;
		if( cpu_load <= 50 && cpu_load > 25 ) signal = LEFT ;
		if( cpu_load <= 25 ) signal = NONE ;
		// it is useless to send a signal to the keyboard if it is not a new one
		if(signal != signal_old) Led(signal,0);
		else usleep(250000) ;
	
		signal_old = signal ;
	}
}

// Memory monitoring

int Memory_Load()
{
	int memtotal, memfree, buffers, cached, level ;
	FILE *mem ;
	mem = fopen( "/proc/meminfo" , "r" );
	if(!mem)
	{
		printf("Error opening \"/proc/meminfo\"\n") ;
		exit(-1) ;
	}
	fscanf(mem,"%*s %i %*s\n%*s %i %*s\n%*s %i %*s\n%*s %i %*s\n", &memtotal, &memfree, &buffers, &cached) ;
	fclose(mem) ;
	level = ((memtotal-memfree-cached-buffers)*100)/memtotal ;
	if( level < 0 || level > 100)
	{
		printf("Error in calculating memory level\n") ;
		exit(-1) ;
	}
	return level ;
}

void Memory_Monitor()
{
	int memory_load = Memory_Load(), i ;
	if( memory_load > 85 ) Led(LEFT+RIGHT+MIDDLE, 40 * TEMP) ;
	if( memory_load <= 85 && memory_load > 70 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT+RIGHT+MIDDLE, 2 * TEMP) ;
			Led(LEFT+MIDDLE, 2 * TEMP) ;
		}
	}
	if( memory_load <= 70 && memory_load > 55 ) Led(LEFT+MIDDLE, 40 * TEMP) ;
	if( memory_load <= 55 && memory_load > 40 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT+MIDDLE, 2 * TEMP) ;
			Led(LEFT, 2 * TEMP) ;
		}
	}
	if( memory_load <= 40 && memory_load > 25 ) Led(LEFT, 40 * TEMP) ;
	if( memory_load <= 25 && memory_load > 10 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT, 2 * TEMP) ;
			Led(NONE, 2 * TEMP) ;
		}
	}
	if( memory_load <= 10 ) Led(NONE, 40 * TEMP) ;
}

// Swap monitoring

int Swap_Load()
{
	int swaptotal, swapfree, level ;
	FILE *swap ;
	swap = fopen( "/proc/meminfo" , "r" ) ;
	if(!swap)
	{
		printf("Error opening \"/proc/meminfo\"\n") ;
		exit(-1) ;
	}
	fscanf(swap,"%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %*i %*s\n%*s %i %*s\n%*s %i %*s\n", &swaptotal, &swapfree ) ;
	fclose(swap) ;
	level = ((swaptotal-swapfree)*100)/swaptotal ;
	if( level < 0 || level > 100)
	{
		printf("Error in calculating swap level\n") ;
		exit(-1) ;
	}
	return level ;
}

void Swap_Monitor()
{
	int swap_load = Swap_Load(), i ;
	if( swap_load > 85 ) Led(LEFT+RIGHT+MIDDLE, 40 * TEMP) ;
	if( swap_load <= 85 && swap_load > 70 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT+RIGHT+MIDDLE, 2 * TEMP) ;
			Led(LEFT+MIDDLE, 2 * TEMP) ;
		}
	}
	if( swap_load <= 70 && swap_load > 55 ) Led(LEFT+MIDDLE, 40 * TEMP) ;
	if( swap_load <= 55 && swap_load > 40 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT+MIDDLE, 2 * TEMP) ;
			Led(LEFT, 2 * TEMP) ;
		}
	}
	if( swap_load <= 40 && swap_load > 25 ) Led(LEFT, 40 * TEMP) ;
	if( swap_load <= 25 && swap_load > 10 )
	{
		for( i = 0 ; i < 10 ; i++)
		{
			Led(LEFT, 2 * TEMP) ;
			Led(NONE, 2 * TEMP) ;
		}
	}
	if( swap_load <= 10 ) Led(NONE, 40 * TEMP) ;
}

// Network monitoring

void Network_Packets()
{
	char char1[10], interface[10] ;
	int var1, var2, var3, var4 ;
	int i, j ;
	FILE *network ;
	network = fopen( "/proc/net/dev" , "r" ) ;
	if(!network)
	{
		printf( "Error opening \"%s\"\n", "/proc/net/dev" ) ;
		exit(-1) ;
	}
	// reading first ligne
	fscanf( network , "%*s %*s %*s %*s\n%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s\n" ) ;
	do
	{	
		strcpy( char1 , "" ) ;
		fscanf( network , "%s %i %i %*i %*i %*i %*i %*i %*i %i %i %*i %*i %*i %*i %*i" , &char1, &var1, &var2, &var3, &var4 ) ;
		if( char1[0] == '\0' )
		{
			printf( "Error, no \"%s\" network device found\n" , network_device ) ;
			exit(-1) ;
		}
		j = 0 ;
		while( char1[j] != ':' )
		{
			interface[j] = char1[j] ;
			j++;
		}
		interface[j] = '\0' ;
		j++ ;
	//  I am not sure I can comment this, but it works ;)
	//	if( !char1[j] ) fscanf( network,"\n" ) ;
	//	else fscanf( network, "%*i\n" ) ;
	} while ( strcmp( interface , network_device ) != 0 ) ;
	fclose( network ) ;
	if( char1[j] )
	{
		received_packets = var1 ;
		transmit_packets = var3 ;
	}
	else
	{
		received_packets = var2 ;
		transmit_packets = var4 ;
	}
}

void Network_Monitor()
{
	int i, transmit_packets_old, received_packets_old ;
	char signal = NONE, signal_old ;
	Network_Packets() ;
	transmit_packets_old = transmit_packets ;
	received_packets_old = received_packets ;
	for( i=0 ; i<100 ; i++ )
	{
		Network_Packets() ;
		if( received_packets != received_packets_old ) signal+= LEFT ;
		if( transmit_packets != transmit_packets_old ) signal+= RIGHT ;
		// it is useless to send a signal to the keyboard if it is not a new one
		if(signal != signal_old) Led( signal , 50000 ) ;
		else usleep( 50000 ) ;
		signal_old = signal ;
		signal = NONE ;
		received_packets_old = received_packets ;
		transmit_packets_old = transmit_packets ;
	}
}
