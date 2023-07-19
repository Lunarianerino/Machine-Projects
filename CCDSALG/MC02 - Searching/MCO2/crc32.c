/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	crc32.c: This file is uses the crc32 algorithm to hash objects in a hashtable.
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Non Cryptographic Hash Functions - https://www.youtube.com/watch?v=siV5pr44FAI&t
*/

#include "crc32.h"

/**
 * @brief Hashes a value using the crc32 algorithm
 * 
 * @param data is the data to be used for hashing
 * @param len is the length of the hash table
 * @return uint32_t the index of the object to be placed in the hash table
 */
uint32_t crc32(char* data, size_t len)
{
    uint32_t crc = 0xffffffff;
    const char* ptr;

    for (ptr = data; ptr < (data + len); ptr++)
    {
        crc = (crc >> 8) ^ crc32_table[(crc ^ (*ptr)) & 0xff];
    }

    return crc;
}
