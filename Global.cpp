#include "Global.h"

string HexDigitToBin(char h) {
     string temp;
     switch (h) {
     case '0': temp = "0000";
     case '1': temp = "0001";
     case '2': temp = "0010";
     case '3': temp = "0011";
     case '4': temp = "0100";
     case '5': temp = "0101";
     case '6': temp = "0110";
     case '7': temp = "0111";
     case '8': temp = "1000";
     case '9': temp = "1001";
     case 'A': temp = "1010";
     case 'B': temp = "1011";
     case 'C': temp = "1100";
     case 'D': temp = "1101";
     case 'E': temp = "1110";
     case 'F': temp = "1111";
	     break;
     }
     return temp;
}