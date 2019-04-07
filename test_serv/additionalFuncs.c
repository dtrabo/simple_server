//
//  additionalFuncs.c
//  testServ
//
//  Created by MacBook on 07/04/2019.
//  Copyright © 2019 MacBook. All rights reserved.
//

#include "additionalFuncs.h"

void dump(const unsigned char *data_buffer, const unsigned int lenght) {
    unsigned char byte;
    unsigned int i, j;
    for(i=0; i < lenght; i++){
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if (((i%16)==15) || (i==lenght-1)) {
            for (j=0; j < 15-(i%16); j++)
                printf(" ");
            printf("| ");
            for(j=(i-(i%16)); j <= i; j++) {
                byte = data_buffer[j];
                if ((byte > 31) && (byte < 127))
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
}
