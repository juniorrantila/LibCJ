#pragma once

typedef struct {
    void(*call)(void*);
    void* context;
} CJLambda;

static inline void CJLambda_call(CJLambda lambda)
{
    lambda.call(lambda.context);
}

static inline CJLambda CJLambda_make(void(*call)(void*), void* context)
{
    return (CJLambda) {
        .call = call,
        .context = context,
    };
}
