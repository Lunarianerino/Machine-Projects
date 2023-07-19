/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	murmurhash.c: This file is uses the murmur hash algorithm to hash objects in a hashtable.
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Non Cryptographic Hash Functions - https://www.youtube.com/watch?v=siV5pr44FAI&t
*/

#include <stdint.h>

/**
 * @brief Hashes a value using the murmurhash3 algorithm
 * 
 * @param data is the data to be used for hashing
 * @param len is the length of the hash table
 * @param seed is the seed used for the algorithm
 * @return uint32_t the index of the object to be placed in the hash table
 */
uint32_t murmurhash3_32 (const char* data, size_t len, uint32_t seed)
{
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t* blocks = (const uint32_t*) data;
    int i;
    for (i = 0; i < nblocks; i++)
    {
        uint32_t k = blocks[i];

        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t* tail = (const uint8_t*) (data + nblocks * 4);
    uint32_t k1 = 0;
    
    switch (len & 3)
    {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];

            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}