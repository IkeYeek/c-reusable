#include "cstream.h"
#include <stdlib.h>

vector *extract(cstream *cs) {
    return cs->v;
}

bool all_match(cstream *cs, bool (*predicate)(void *e)) {
    vector *v = extract(cs);
    bool all_match = true;

    int index = 0;
    while(all_match && index < v->vector_size(v)) {
        if(!predicate(v->vector_get(v, index)))
            all_match = false;
        index += 1;
    }

    return all_match;
}
bool any_match(cstream *cs, bool (*predicate)(void *e)) {
    vector *v = extract(cs);
    bool any_match = false;

    int index = 0;
    while(!any_match && index < v->vector_size(v)) {
        if(predicate(v->vector_get(v, index)))
            any_match = true;
        index += 1;
    }

    return any_match;
}

cstream *filter(cstream *cs, bool (*predicate)(void*e)) {
    vector *v = extract(cs);
    vector *result = create_vector();
    for(int i = 0; i < v->vector_size(v); i++ ){
        void *elem = v->vector_get(v, i);
        if(predicate(elem)) {
            result->vector_add(result, elem);
        }
    }
    return stream(result);
}

int count(cstream *cs) {
    vector *v = extract(cs);
    return v->vector_size(v);
}

void for_each(cstream *cs, void (*consumer)(void *e)) {
        vector *v = extract(cs);
        for(int i = 0; i < v->vector_size(v); i++) {
            void *elem = v->vector_get(v, i);
            consumer(elem);
        }
}

void **to_array(cstream *cs) {
    vector *v = extract(cs);
    void **res = malloc(sizeof(v->vector_get(v, 0)) * v->vector_size(v));
    for(int i = 0; i < v->vector_size(v); i++) {
        res[i] = v->vector_get(v, i);
    }
    return res;
}

cstream *stream(vector *v) {
    cstream *cs = malloc(sizeof(cstream));
    cs->v = v;
    cs->for_each = for_each;
    cs->any_match = any_match;
    cs->all_match = all_match;
    cs->filter = filter;
    cs->to_array = to_array;
    return cs;
}