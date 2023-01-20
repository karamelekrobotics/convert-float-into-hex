/*
* Author: Berkan Onder Karamelek
* Date  : 18012023
* Rev   : 1
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <float.h>

// Set float number and it is going to be cınverted to hex automatically.
union{
    float f;
    unsigned int i;
} float_to_hex;


// Get/Store components of the floating point number
struct float_bits {
    unsigned int mantissa:23;
    unsigned int exponent:8;
    unsigned int sign:1;
} fb;


union{
    float f;
    unsigned int i;
}float_from_parts;

// Get/Parse each bytes for the given mantissa, exponent or sign
// Can be used for communication applications
union {
    unsigned int f;
    unsigned char bytes[sizeof(unsigned int)];
} parse;

int main(void)
{
    //set float value
    float_to_hex.f = 1050.478964;

    //set its components
    fb.mantissa = float_to_hex.i & 0x7FFFFF;
    fb.exponent = (float_to_hex.i >> 23) & 0xFF;
    fb.sign     = (float_to_hex.i >> 31) & 1;

    //convert back to float in binary form
    float_from_parts.i = (fb.sign < 31) | (fb.exponent << 23) | fb.mantissa;

    //get actual one
    printf("actual number: %f\t\t in hex = %X\n\n",float_from_parts.f,float_to_hex.i);

    //get bytes of each components
    parse.f = fb.mantissa;
    printf("\n\nPARSE MANSTISSA\n");
    for(int i = sizeof(unsigned int)-1; i >= 0 ; i--)
    {
        printf("%X",parse.bytes[i]);
    }

    printf("\n\nPARSE EXPONENT\n");
    parse.f = fb.exponent;
    for(int i = sizeof(unsigned int)-1; i >= 0 ; i--)
    {
        printf("%X",parse.bytes[i]);
    }

    printf("\n\nPARSE SIGN\n");
    parse.f = fb.sign;
    for(int i = sizeof(unsigned int)-1; i >= 0 ; i--)
    {
        printf("%X",parse.bytes[i]);
    }
    return 0;
}