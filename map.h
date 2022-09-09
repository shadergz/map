/*
 *  Source code written by Gabriel Correia
*/

#pragma once

#define HASHTABLE_SIZE 256

/* Hash function pointer, the user can defined his own */
typedef int (*hashfunc_t) (const char* key);

typedef struct map_bucket {
    int available;
    const char* key;
    const char* value;
} bucket_t;

typedef struct hashmap {
    /* Memory needed to this array: 256 * 16 = 4096 bytes */
    bucket_t hashtable[HASHTABLE_SIZE];
    hashfunc_t genhash;

} hashmap_t;


/* Create a new hashmap into the heap */
extern hashmap_t* hashmap_new (void);

/* Destroy the hashmap and freedom the memory that was in use */
extern void hashmap_destroy (hashmap_t* map);

/* Add a new element into the hashmap */
extern void hashmap_push (const char* key, const char* value, hashmap_t* map);

/* Retrieve a value from the desired key */
extern const char* hashmap_value (const char* key, hashmap_t* map);

/* Clear all bucket array and make all positions available to be reused */
extern void hashmap_clear (hashmap_t* map);

/* Use the user hash function instead of the Dan (djb2) algorithm 
 * (If u think that your algorithm is better, go ahead)
*/
__attribute__((unused)) extern void hashmap_hash (hashfunc_t hash_func, hashmap_t* map);
