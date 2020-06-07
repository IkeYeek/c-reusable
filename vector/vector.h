#ifndef CSTREAM_VECTOR_H
#define CSTREAM_VECTOR_H

#include <stdbool.h>

typedef struct vector_s {
    int size;
    void **vector_array;
    bool (*vector_add)(struct vector_s *v, void *e);
    void (*vector_clear)(struct vector_s *v);
    void (*vector_free)(struct vector_s *v);
    bool (*vector_contains)(struct vector_s *v, void *e);
    void *(*vector_get)(struct vector_s *v, int i);
    void *(*vector_remove)(struct vector_s *v, int i);
    int (*vector_size)(struct vector_s *v);
    void (*vector_add_all)(struct vector_s *v, struct vector_s *source);
} vector;

vector *create_vector();
vector *vector_clone(vector *v);

bool vector_add(vector *v, void *e);
void add_all(vector *v, vector *source);
void vector_clear(vector *v);
void vector_free(vector *v);
bool vector_contains(vector *v, void *e);
void *vector_get(vector *v, int i);
void *vector_remove(vector *v, int i);
int vector_size(vector *v);



#endif //CSTREAM_VECTOR_H
