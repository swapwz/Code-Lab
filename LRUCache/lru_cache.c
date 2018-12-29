#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_VALUE (~0)

typedef struct kvdata{
    int key;
    int value;
    struct kvdata *next;
    struct kvdata *prev;
} KVData;

typedef struct hash{
    int key;
    KVData *ref; /* used to access data entry directly */
    struct hash *first; /* collision list */
} Hash;

typedef struct {
    int capacity;
    int used;
    int hash_cap;
    Hash **hash; /* store the hash index corresponds to key */
    KVData *rear; /* position to insert */ 
    KVData *front; /* position to delete */
} LRUCache;

/* show internal of data */
void show(KVData *front)
{
    printf("*******************************\r\n");
    for (front=front->next; front != NULL; front = front->next)
    {
        printf("(%d, %d)\r\n", front->key, front->value);
    }
    printf("*******************************\r\n");
}


/* get next available key hash */
static Hash* getAvailiableHash(LRUCache *obj, int key)
{
    int entry;
    Hash *possiable_hash;
    Hash **hash;
    Hash *new_hash;
    
    new_hash = (Hash *) malloc(sizeof(Hash));
    if (NULL == new_hash)
    {
        return NULL;
    }
    
    /* initial new hash node */
    new_hash->key = key;
    new_hash->ref = NULL;
    
    entry = key % (obj->hash_cap); 
    hash = obj->hash;
    possiable_hash = hash[entry];
    if (possiable_hash != NULL)
    {
        new_hash->first = possiable_hash->first;
        possiable_hash->first = new_hash;
    }
    else
    {
        hash[entry] = new_hash;
        new_hash->first = NULL;
    }
    
    return new_hash;
}

static Hash* getKeyHash(LRUCache *obj, int key)
{
    int entry;
    Hash *possiable_hash;
    
    /* key hash is not at possiable position */
    entry = key % (obj->hash_cap); 
    possiable_hash = obj->hash[entry];
    for (; (possiable_hash != NULL) && (possiable_hash->key != key); possiable_hash = possiable_hash->first)
    {
        ;
    }
    
    return possiable_hash;
}

static void delKeyHash(LRUCache *obj, int key)
{
    int entry;
    Hash **cur;
    Hash *hash_first;
    
    entry = key % (obj->hash_cap); 
    hash_first = obj->hash[entry];
    
    /* key hash is not at possiable position */
    for (cur = &hash_first; *cur != NULL; )
    {
        Hash *hash = *cur;
        if (hash->key == key)
        {
            *cur = hash->first;
            free(hash);
        }
        else
	    {
            cur = &hash->first;
	    }
    }
    obj->hash[entry] = hash_first;
}

static KVData * getDataRef(LRUCache *obj, int key)
{
    Hash *hash;
    KVData *data;

    hash = getKeyHash(obj, key);   
    if (hash != NULL)
    {
        data = hash->ref;
    }
    else
    {
        data = NULL;
    }

    return data;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *cache;
    int hash_cap;
    Hash **hash;
    KVData *dummy_node;
    
    cache = (LRUCache *) malloc(sizeof(LRUCache));
    if (NULL == cache)
    {
        return NULL;
    }

    hash_cap = 3 * capacity + 1;
    hash = (Hash **) malloc(hash_cap * sizeof(Hash *));
    if (NULL == hash)
    {
        free(cache);
        return NULL;
    }

    dummy_node = (KVData *) malloc(sizeof(KVData));
    if (NULL == dummy_node)
    {
        free(cache);
        free(hash);
        return NULL;
    }

    memset(hash, 0, hash_cap * sizeof(Hash *));
    memset(dummy_node, 0, sizeof(KVData));
    dummy_node->next = NULL;
    dummy_node->prev = NULL;

    cache->capacity = capacity;
    cache->hash_cap = hash_cap;
    cache->used = 0;
    cache->hash = hash;
    cache->front = dummy_node;
    cache->rear = dummy_node;
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    KVData *entry;
    int value;
    
    entry = getDataRef(obj, key);
    if (entry != NULL)
    {
        /* step1: get data */
        value = entry->value;
                
        /* step2: move to the rear position */
        if (entry->next != NULL)
        {
            obj->rear->next = entry;
            entry->prev->next = entry->next;
            entry->next->prev = entry->prev;
            entry->next = NULL;
            entry->prev = obj->rear;
            obj->rear = entry;
        }
    }
    else 
    {
        value = INVALID_VALUE;
    }
    return value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int cap;
    int used;
    KVData *rear = obj->rear;
    KVData *front = obj->front;
    KVData *new_data;
    Hash *hash;

    /* if exists duplicate key */
    new_data = getDataRef(obj, key);
    if (new_data != NULL)
    {
        /* update data entry, move to the rear */
        new_data->value = value;
        if (new_data->next != NULL)
        {
            new_data->prev->next = new_data->next;
            new_data->next->prev = new_data->prev;
            rear->next = new_data;
            new_data->next = NULL;
            new_data->prev = rear;
            obj->rear = new_data;
        }

        show(obj->front);
        /* already the newest node, do nothing */
        return;
    }

    /* if reach capacity, evicts the oldest node */
    new_data = (KVData *) malloc(sizeof(KVData));
    if (NULL == new_data)
        return;
    
    new_data->key = key;
    new_data->value = value;

    cap = obj->capacity;
    used = obj->used;
    if (used == cap)
    {
        /* remove oldest node */
        KVData *next = NULL;
        KVData *del_node = front->next;
        
        if (del_node != NULL)
        {
            next = del_node->next;
            delKeyHash(obj, del_node->key);
            free(del_node);    
        }
        
        if (next != NULL)
        {
            next->prev = front;
        }
        else
        {
            obj->rear = front;
        }
        front->next = next;
        used--;
    }
    
    used++;
    obj->rear->next = new_data;
    new_data->prev = rear;
    new_data->next = NULL;
    obj->rear = new_data;
    obj->used = used;
    
    /* put new node */
    hash = getAvailiableHash(obj, key);
    if (hash != NULL)
    {
        hash->ref = new_data;
    }
    show(obj->front);
}

void lRUCacheFree(LRUCache* obj) {
    KVData *front = obj->front;
    KVData *next;

    for (front = front->next; front != NULL; front = next)
    {
        delKeyHash(obj, front->key);
        next = front->next;
        free(front);
    }

    free(obj->hash);
    free(obj->front);
    free(obj);
}

/**
 * Test here: 
 * LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int value = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */
int main(void)
{
    LRUCache *obj = lRUCacheCreate(2);

    printf("%d\r\n", lRUCacheGet(obj, 0));

    lRUCachePut(obj, 2, 1);
    lRUCachePut(obj, 2, 2);

    printf("get %d\n", lRUCacheGet(obj, 2));

    lRUCachePut(obj, 1, 1);
    lRUCachePut(obj, 4, 1);

    printf("get %d\n", lRUCacheGet(obj, 2));

    lRUCacheFree(obj);
 
    return 0;
}


