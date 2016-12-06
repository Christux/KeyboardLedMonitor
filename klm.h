// Put first part of klm.c into this header file NA 08-01-07
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>

// Added include file NA 8/1/07
#include "morse.h"

// arrange this for your keyboard
#define LEFT LED_NUM
#define MIDDLE LED_CAP
#define RIGHT LED_SCR

// ---
#define NONE 0
#define TEMP 125000

// modes
#define CPU 1
#define NETWORK 2
#define MEMORY 3
#define SWAP 4
// fun modes
#define K2000M 5
#define RANDOM 6
#define BOUNCE 7
#define LEFTM 8
#define RIGHTM 9
#define CENTER 10
// added mode NA 7/31/07
#define MORSE 11
// demo
#define DEMO 12


void end(int signal);
void usage();
void warranty();
void Led(char code, int delay);
void Reset_Led();
void K2000();
void Left();
void Right();
void Bounce();
void Center();
void Random();
// added function NA 7/31/07
// split into seperate file NA 8/1/07
// void Morse();
int Cpu_Read();
int Cpu_Load();
void Cpu_Monitor();
int Memory_Load();
void Memory_Monitor();
int Swap_Load();
void Swap_Monitor();
void Network_Packets();
void Network_Monitor();
void Demo() ;


char device[20];
char network_device[10];
char morse_string[512];
int transmit_packets, received_packets;
