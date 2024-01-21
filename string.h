#ifndef JONATHAN_STRING_H_
#define JONATHAN_STRING_H_

#ifndef MALLOC
#include <stdlib.h>
#define MALLOC malloc
#endif

#ifndef REALLOC
#include <stdlib.h>
#define REALLOC realloc
#endif

#ifndef FREE
#include <stdlib.h>
#define FREE free
#endif


#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

#include <string.h>
#include <strings.h>


#define JSTRING_DEFAULT_CAPACITY 10


typedef struct jstring {
    int length;
    int capacity;
    char* string;
} jstring;


jstring jstringFrom(const char* from);
jstring jstringNew();

void jstringFree(jstring *str);

void jstringAppend(jstring* s, const char* str);


#ifdef JONATHAN_STRING_IMPLEMENTATION

jstring jstringFrom(const char* from)
{
    jstring s;
    s.capacity = strlen(from)+1;
    s.length = s.capacity-1;
    s.string = (char*)MALLOC(sizeof(char)*s.capacity);
    strcpy(s.string, from);

    return s;
}

jstring jstringNew()
{
    jstring s;
    s.capacity = JSTRING_DEFAULT_CAPACITY;
    s.length = 0;
    s.string = (char*)MALLOC(sizeof(char)*JSTRING_DEFAULT_CAPACITY);

    return s;
}

void jstringFree(jstring *str)
{
    FREE(str->string);
}


void jstringAppend(jstring* str, const char* add)
{
    int additional_size = strlen(add);

    if (additional_size + str->length + 1 > str->capacity)
    {
        int new_size = str->length + additional_size + 1;
        str->string = REALLOC(str->string, sizeof(char)*new_size);
        str->capacity = new_size;

        for (int i = str->length; i < new_size; i++)
        {
            str->string[i] = 0;
        }
    }

    strcpy(str->string+str->length, add);
    str->length += additional_size;
}

#endif // JONATHAN_STRING_IMPLEMENTATION
#endif // JONATHAN_STRING_H_
