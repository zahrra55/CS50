#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //TODO: Open memory card
    FILE *f = fopen("file.jpeg", "r");
    //TODO: Look for a begining for JPEG
    //TODO: Open a new JPEG file
    //TODO: Write 512 bytes until a new JPEG is found
    //TODO: Stop at end of file
    /*
    the first three bytes of JPEGs are
    0xff 0xd8 0xff
    from first byte to third byte, left to right. The fourth byte, meanwhile,
    is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec,
    0xed, 0xee, or 0xef. Put another way, the fourth byte’s first four bits are 1110.
    */
}
