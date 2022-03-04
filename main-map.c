/*
 *  Source code written by Gabriel Correia
*/

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "map.h"

/* My simple hash algorithm */
static int map_hash (const char* key)
{
    int digest = 0;
    size_t key_len = strlen (key);

    for (size_t i = 0; i < key_len; i++) {
        digest += key[i];
    }

    return digest;
}

int main ()
{

    hashmap_t* map;

    map = hashmap_new ();

    /* A collection of keys and values used to exemplify the algorithm usage */
    const char* names[][2] = {
    /*  KEYS         VALUES */
        {"Gabriel", "Correia"},
        {"Pedro",   "Silva"},
        {"John",    "Kennedy"},
        {"Felipe",  "Farias"},
        {"Maria",   "Fernandes"},
        NULL
    };

    //hashmap_hash (map_hash, map);

#define NAMES_SIZE\
    (sizeof (names)/(sizeof (const char*)*2) - 1)
    fprintf (stderr, "Sizeof names: %ld\n", NAMES_SIZE);

    for (int i = 0; i < NAMES_SIZE; i++) {
        fprintf (stderr, "%d ", i);
        fflush (stdout);
        hashmap_push (names[i][0], names[i][1], map);
    }

    for (int i = 0; i < NAMES_SIZE; i++) {
        const char* key = names[i][0];
        printf ("%s - %s\n", key, hashmap_value (key, map));
    }

    hashmap_clear (map);

    hashmap_destroy (map);

    return 0;
}

