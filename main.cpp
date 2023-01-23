/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


//Pour voir comment fonctionne l'automate : Voir les fichiers automate.cpp et automate.h
#include "mbed.h"

#include "automate.h"

#define WAIT_TIME_MS 500ms

int main()
{

    while (true)
    {
        automate();
        ThisThread::sleep_for(WAIT_TIME_MS);
    }
}
