# map

A hashmap implementation in C11 with djb2 hash function

The hashmap algorithm consist of a bucket with a pair of key and values and a hash value that will to index the address of the correct bucket

> Some implementations added a Linked List to solve the Hash Collision problem

<!--
    https://en.wikipedia.org/wiki/Hash_table#/media/File:Hash_table_3_1_1_0_1_0_0_SP.svg
-->
![Alt text](https://upload.wikimedia.org/wikipedia/commons/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg)

## How to build this project

Just type

```bash
mkdir build
cd build
cmake ..
```

## How to see the result

```bash
./map 2> /dev/null
```

> The default hash algorithm

```c
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
```

