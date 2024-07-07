
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
 * This header file defines an interface to a generic hashtable.
 * It stores void* data, and uses two function, int (*) (void *) to
 * compute the hash and an int (*) (void *, void *) for equal true/false
 * which makes this a generic hashtable.
 */

struct HashBucket {
  void *key;
  void *data;
  struct HashBucket *next;
};

typedef struct HashTable {
  unsigned int (*hashFunction)(void *);
  int (*equalFunction)(void *, void *);
  struct HashBucket **data;
  int size;
} HashTable;

/*
 * this creates a new hashtable of the specified size and with
 * a hashfunction and a comparison function.
 */
extern HashTable *createHashTable(int size,
                                  unsigned int (*hashFunction)(void *),
                                  int (*equalFunction)(void *, void *));

/*
 * This inserts a bit of data and key into a hashtable.  To use this
 * to store strings, simply cast a char * to a void *.  EG, to store
 * the string refered to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string);
 * if you wanted to use the string both as data and as the key
 * (such as in the philspel project)
 */
extern void insertData(HashTable *table, void *key, void *data);

/*
 * This takes a key and returns the corresponding data to that key,
 * or NULL if the key was not found.
 */
extern void *findData(HashTable *table, void *key);

#endif
