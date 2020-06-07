#include "assert.h"
#include "vector.h"
#include "stdlib.h"

/**
 * Creates a vector
 * @return a pointer on the created empty vector
 */
vector *create_vector() {
    vector *v = malloc(sizeof(vector));
    v->size = 0;
    v->vector_add = vector_add;
    v->vector_get = vector_get;
    v->vector_size = vector_size;
    v->vector_remove = vector_remove;
    v->vector_contains = vector_contains;
    v->vector_free = vector_free;
    v->vector_clear = vector_clear;
    v->vector_add_all = add_all;
    return v;
}

/**
 * Adds an element inside the vector, expending its size
 * @param v the vector
 * @param e the element
 * @return true (for the moment it always returns true)
 */
bool vector_add(vector *v, void *e) {
    v->size += 1;
    v->vector_array = realloc(v->vector_array, sizeof(&e) * v->size);
    v->vector_array[v->size - 1] = e;
    return true;
}

/**
 * Gets an element from the vector
 * @param v the vector
 * @param i the element's index
 * @return
 */
void *vector_get(vector *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->vector_array[i];
}

/**
 * Clears a vector from all its elems
 * @param v the vector
 */
void vector_clear(vector *v) {
    for(int i = 0; i < v->size; i++) {
        free(v->vector_array[i]);
    }
    free(v->vector_array);
    v->size = 0;
}

/**
 * Frees a vector after freeing all its elems
 * @param v
 */
void vector_free(vector *v) {
    vector_clear(v);
    free(v);
}

/**
 * Check whether or not a vector contains a certain element at least once
 * @param v the vector
 * @param e the element
 * @return
 */
bool vector_contains(vector *v, void *e) {
    bool found = false;
    int index = 0;
    while(!found && index < v->size) {
        if(vector_get(v, index) == e)
            found = true;
        index++;
    }
    return found;
}

/**
 * Removes an element from a vector
 * @param v the vector
 * @param i the element's index
 * @return the element removed
 */
void *vector_remove(vector *v, int i) {
    assert(i >= 0 && i < v->size);
    void *return_value = v->vector_array[i];
    for(int index = i; index < v->size-1; index++) {
        v->vector_array[index] = v->vector_array[index + 1];
    }
    v->size -= 1;
    v->vector_array = realloc(v->vector_array, sizeof(int) * v->size);
    return return_value;
}

/**
 * Returns the vector size (to get a bit of encapsulation)
 * @param v the vector
 * @return its size
 */
int vector_size(vector *v) {
    return v->size;
}

/**
 * Clones a vector by duplicating its array (the array contains the same refs but its not the same array)
 * @param v the vector
 * @return a clone of the vector
 */
vector *vector_clone(vector *v) {
    vector *return_value = create_vector();
    for(int i = 0; i < v->size; i++) {
        vector_add(return_value, vector_get(v, i));
    }
    return return_value;
}

/**
 * Adds every elem from source to vector v
 * @param v the vector
 * @param source the source
 */
void add_all(vector *v, vector *source) {
    for(int i = 0; i < source->vector_size(source); i++) {
        v->vector_add(v, source->vector_get(source, i));
    }
}

