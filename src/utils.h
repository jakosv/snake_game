#ifndef UTILS_H_SENTRY
#define UTILS_H_SENTRY

#define MAKE_SWAP_FUNCTION(TYPE) \
    static void swap_ ## TYPE(TYPE *a, TYPE *b) \
    { \
        TYPE tmp; \
        tmp = *a; \
        *a = *b; \
        *b = tmp; \
    }

#endif
