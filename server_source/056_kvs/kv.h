#ifndef __KV_H__
#define __KV_H__


struct _kvpair_t { 
  // struct for a key/value pair  
  char * key; // string for key
  char * value; // string for value
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t { 
  // struct for array of key value pairs (kvpair_t)
  kvpair_t ** kv_array;
  size_t array_size;
};
typedef struct _kvarray_t kvarray_t;

int getNumPairs(const char * fname);

kvpair_t * readAPair(FILE * f, kvarray_t * freeMem);

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
