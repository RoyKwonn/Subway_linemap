//
//  DieWithError.c
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#include "TCP_Server.h"
#include <stdio.h>      // for perror()
#include <stdlib.h>     // for exit()

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
