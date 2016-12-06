/*
 * morse.c
 * Copyright (C) 2007 Nick Aschenbach <dril1@hotmail.com>
 */

/* 

This part of the program translates a string from the command line. Inspired
by the book Cryptonomicon by Neal Stephenson where the main character uses
his keyboard LEDs instead of his laptop monitor for display purposes. 
The main character suspects that he is being eavesdropped on by his captors. 

For more information see van Eck phreaking:

http://en.wikipedia.org/wiki/Van_Eck_phreaking

The morse code lookup table was also found on Wikipedia:

http://en.wikipedia.org/wiki/Morse_code

*/

#include "morse.h"

void morse(int LEFT, int RIGHT, int MIDDLE, int TEMP, char *input_string) {
  

  // Break the string down into characters, discard non alpha numeric
  char *phrase = morse_decode(input_string);

  // Let the LEDs display the message
  display_morse(LEFT, RIGHT, MIDDLE, TEMP, phrase);

}

// Decode the letters and numbers to their dash / dot 
char *morse_decode(char *input_string) 
{
  char *decoded_phrase;
  // Predict how much memory we'll need for this variable
  decoded_phrase = (char *)calloc(strlen(input_string)*5 + 1, sizeof(char));

  char *decoded_letter;
  int i;
  for(i=0; i<strlen(input_string); i++) 
    {
      char inputChar = (char)tolower(input_string[i]);

      switch(inputChar)
	{
	case 'a' : decoded_letter = MORSE_A; break;
	case 'b' : decoded_letter = MORSE_B; break;
	case 'c' : decoded_letter = MORSE_C; break;
	case 'd' : decoded_letter = MORSE_D; break;
	case 'e' : decoded_letter = MORSE_E; break;
	case 'f' : decoded_letter = MORSE_F; break;
	case 'g' : decoded_letter = MORSE_G; break;
	case 'h' : decoded_letter = MORSE_H; break;
	case 'i' : decoded_letter = MORSE_I; break;
	case 'j' : decoded_letter = MORSE_J; break;
	case 'k' : decoded_letter = MORSE_K; break;
	case 'l' : decoded_letter = MORSE_L; break;
	case 'm' : decoded_letter = MORSE_M; break;
	case 'n' : decoded_letter = MORSE_N; break;
	case 'o' : decoded_letter = MORSE_O; break;
	case 'p' : decoded_letter = MORSE_P; break;
	case 'q' : decoded_letter = MORSE_Q; break;
	case 'r' : decoded_letter = MORSE_R; break;
	case 's' : decoded_letter = MORSE_S; break;
	case 't' : decoded_letter = MORSE_T; break;
	case 'u' : decoded_letter = MORSE_U; break;
	case 'v' : decoded_letter = MORSE_V; break;
	case 'w' : decoded_letter = MORSE_W; break;
	case 'x' : decoded_letter = MORSE_Y; break;
	case 'y' : decoded_letter = MORSE_X; break;
	case 'z' : decoded_letter = MORSE_Z; break;
	case '1' : decoded_letter = MORSE_1; break;
	case '2' : decoded_letter = MORSE_2; break;
	case '3' : decoded_letter = MORSE_3; break;
	case '4' : decoded_letter = MORSE_4; break;
	case '5' : decoded_letter = MORSE_5; break;
	case '6' : decoded_letter = MORSE_6; break;
	case '7' : decoded_letter = MORSE_7; break;
	case '8' : decoded_letter = MORSE_8; break;
	case '9' : decoded_letter = MORSE_9; break;
	case '0' : decoded_letter = MORSE_0; break;
	case ' ' : decoded_letter = MORSE_SPACE; break;
	}
      // Append the current letter (dit dah sequence)
      strcat(decoded_phrase, decoded_letter);

      if(decoded_letter != MORSE_SPACE) 
	strcat(decoded_phrase, MORSE_LETTER);
      else
	strcat(decoded_phrase, MORSE_WORD);
    }
  
  // Append a null character
  strcat(decoded_phrase, "\0");

  //printf(decoded_phrase);
  return decoded_phrase;
}

void display_morse(int LEFT, int RIGHT, int MIDDLE, int TEMP, char *decoded_phrase) {

  Led(0, TEMP);

  int phrase_length = strlen(decoded_phrase);
  char test;

  // display decoded message on keyboard using LEDS
  
  int i;
  for(i=0; i<phrase_length; i++) {
    test = (char)*decoded_phrase;
    
    switch(test) {
    case '.' : 
      Led(LEFT + MIDDLE + RIGHT, TEMP*2); 
      Led(0, TEMP*2);
      break;
    case '-' : 
      Led(LEFT + MIDDLE + RIGHT, TEMP*6); 
      Led(0, TEMP*2);
      break;
    case 'L' : Led(0, TEMP*3); break;
    case 'W' : Led(0, TEMP*5); break;
    default: break;
    }

    ++decoded_phrase;
    //printf("%c", test);
  }
}
