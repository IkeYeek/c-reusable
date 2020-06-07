#ifndef CSTREAM_CSTREAM_H
#define CSTREAM_CSTREAM_H

#include "../vector/vector.h"

typedef struct cstream_s {
    vector *v;
    void (*for_each)(struct cstream_s *stream, void (*consumer)(void *e));
    bool (*all_match)(struct cstream_s *stream, bool (*predicate)(void *e));
    bool (*any_match)(struct cstream_s *stream, bool (*predicate)(void *e));
    struct cstream_s *(*filter)(struct cstream_s *stream, bool (*predicate)(void*e));
    int (*count)(struct cstream_s *stream);
    void **(*to_array)(struct cstream_s *stream);
} cstream;

cstream *stream(vector *v);

bool all_match(cstream *cs, bool (*predicate)(void *e));
bool any_match(cstream *cs, bool (*predicate)(void *e));
cstream *filter(cstream *stream, bool (*predicate)(void*e));
int count(cstream *cs);
void **to_array(cstream *stream);

void for_each(cstream *cs, void (*consumer)(void *e));


#endif //CSTREAM_CSTREAM_H
