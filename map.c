/*
 *  Source code written by Gabriel Correia
*/

#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include "map.h"

/* The best string hash function, created by Dan Bernstein */
unsigned long djb2_hash (unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        /* HASH * 33 + C */
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int djb2_mod (const char* key)
{
    int digest = (unsigned)(djb2_hash ((unsigned char*)key)) % HASHTABLE_SIZE;
    fprintf (stderr, "Key digest: %d from %s\n", digest, key);
    return digest;
}

hashmap_t* hashmap_new (void)
{
    hashmap_t* map;
    bucket_t *bucket;

    map = calloc (1, sizeof (hashmap_t));
    assert (map);
    fprintf (stderr, "Hashmap size: %ld\n", sizeof (hashmap_t));

    map->genhash = djb2_mod;
    hashmap_clear (map);

    return map;
}

void hashmap_destroy (hashmap_t* map)
{
    assert (map);
    free (map);
}

static bucket_t* select_bucket (const char* key, bucket_t buckets[], hashmap_t* map)
{
    bucket_t* bucket;
    assert (buckets);
    bucket = &buckets[map->genhash (key)];
    assert (bucket);
    return bucket;
}

void hashmap_push (const char* key, const char* value, hashmap_t* map)
{
    assert (map);
    fprintf (stderr, "Key: %s\n", key);
    bucket_t* bucket = select_bucket (key, map->hashtable, map);
    if (bucket->available) {
        bucket->key = key;
        bucket->value = value;

        bucket->available = 0;
    } else {
        fprintf (stderr, "This bucket is already in use by the %s key\n", bucket->key);
    }
}

const char* hashmap_value (const char* key, hashmap_t* map)
{
    bucket_t* bucket;
    const char* value;

    assert (map);
    bucket = select_bucket (key, map->hashtable, map);
    fflush (stdout);
    if (!bucket->available) {
        if (strlen (key) == strlen (bucket->key) && (!(strcmp (key, bucket->key))))
            value = bucket->value;
        else
            value = "A collision has ocurred";
    } else {
        value = "Bucket isn't available";
    }

    return value;
}

void hashmap_clear (hashmap_t* map)
{
    bucket_t* bucket;
    bucket_t* table;
    assert (map);

    table = map->hashtable;

#define FOR_EACH_BUCKET(bucket,table)\
    for (size_t bucket_index = 0; bucket_index < HASHTABLE_SIZE && (bucket = &(table[bucket_index])); bucket_index++)

    FOR_EACH_BUCKET (bucket, table) {
        //fprintf (stderr, "Bucket address: %p\n", bucket);
        bucket->available = 1;
    }
}

void hashmap_hash (hashfunc_t hash_func, hashmap_t* map)
{
    assert (map);
    map->genhash = hash_func;
}
