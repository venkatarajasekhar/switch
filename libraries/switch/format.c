#include <string.h>

#include "format.h"


int _itoa(char* str, uint8_t format, int16_t value)
{
    unsigned char digit;
    uint8_t enable_digits = 0;
	char* ptr;

	ptr = str;

    // do sign
    if (value < 0){
        value = -value;
        *str++ = '-';
    } else {
		if(format <= format_OneDigit)	*str++ = ' ';
	}

    // do 10000's
   	digit = '0';
    while (value > 9999){
        value -= 10000;
        digit++;
    }
    if ((digit != '0') || (enable_digits != 0) || (format == format_kFiveDigits)) {
        *str++ = digit; 
        enable_digits = 1;
    }

    // do 1000's
    digit = '0';
    while(value > 999){
        value -= 1000;
        digit++;
    }
    if((digit != '0') || (enable_digits != 0) || (format == format_FourDigits)) {
        *str++ = digit;
        enable_digits = 1;
    }

    // do 100's
    digit = '0';
    while(value > 99){
        value -= 100;
        digit++;
    }
    if (format == format_Milli){
        if (enable_digits == 0) *str++ = '0';
        *str++ = '.';
        enable_digits = 1;
    }
    if((digit != '0') || (enable_digits != 0) || (format == format_ThreeDigits) ) {
        *str++ = digit;
        enable_digits = 1;
    }

    // do 10's
    digit = '0';
    while(value > 9){
        value -= 10;
        digit++;
    }
    if (format == format_Centi){
        if (enable_digits == 0) *str++ = '0';
        *str++ = '.';
        enable_digits = 1;
    }
    if((digit != '0') || (enable_digits != 0)  || (format == format_TwoDigits) ) {
        *str++ = digit;
        enable_digits = 1;
    }

    // do 1's
    digit = '0' + value;
    if (format == format_Deci){
        if (enable_digits == 0) *str++ = '0';
        *str++ = '.';
        enable_digits = 1;
    }
    if((digit != '0') || (enable_digits != 0) || (format == format_OneDigit)) {
        *str++ = digit;
        enable_digits = 1;
    }

	if(format == format_Hide) str = ptr;
	*str = 0;
	return str - ptr;
}


/// Convert integer to ascii decimal string and send to terminal
/// @param integer value
/// @param desired ascii decimal format
int format_toString(char* str, int16_t value, uint8_t format)
{
	int16_t hours = 0;

	if(format == format_Time){
		while (value >= 60) {++hours ; value -= 60;}
		str += _itoa(str, format_TwoDigits, hours);
		*str++ = '.'; 
		_itoa(str, format_TwoDigits, value);
		return 5; // number of characters in string
	} else if(format == format_Bool) {
		if(value) strcpy(str, "on"); else strcpy(str, "off");
		return strlen(str);
	} else {
		return _itoa(str, format, value);
	}
}



