/*
 * This is so the C preprocessor does not try to include multiple copies
 * of the header file if someone uses multiple #include directives.
 */
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
 * Everyone uses NULL, or 0, as the null pointer,
 * but C never defines it so you have to define it yourself.  :(
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * This header file defines an interface to a generic chained hash table. 
 * It stores void * data and uses two functions, int (*) (void *)
 * and int (*) (void *, void *), to compute the hash and check
 * for equality.
 */
struct HashBucket {
  void *key;
  void *data;
  struct HashBucket *next;
};

typedef struct HashTable {
  // -- TODO --
  // HINT: Take a look at createHashTable.
} HashTable;

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
extern HashTable *createHashTable(int size,
                                  unsigned int (*hashFunction)(void *),
                                  int (*equalFunction)(void *, void *));

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
extern void insertData(HashTable *table, void *key, void *data);

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
extern void *findData(HashTable *table, void *key);

#endif
