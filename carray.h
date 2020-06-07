#if !defined(CARRAYS_C)

#define MAKE_ARRAY_START(data_name, _type) _type*  Start(data_name* arr) { return (arr->count > 0) ? &arr->data[0] : nullptr; }
#define MAKE_ARRAY_END(data_name, _type)   _type*  End(data_name* )   { return nullptr; }
#define MAKE_ARRAY_LAST(data_name, _type)   _type* Last(data_name* arr)   { return (arr->count > 0) ? &arr->data[arr->count-1] : nullptr; }
#define MAKE_ARRAY_NEXT(data_name, _type) _type*  Next(data_name* arr, _type* it) { \
        return (&arr->data[arr->count-1] == it) ? nullptr : (it + 1); }
#define MAKE_ARRAY_PREV(data_name, _type) _type*  Prev(data_name* arr, _type* it) { \
        return (&arr->data[0] == it) ? nullptr : (it - 1); }

#define MAKE_ARRAY(data_name, type) struct data_name {       \
        size_t size;                                          \
        size_t len;                                          \
        size_t count;                                         \
        type* data; };                                       \
    MAKE_ARRAY_START(data_name, type)                        \
    MAKE_ARRAY_END(data_name, type)                          \
    MAKE_ARRAY_NEXT(data_name, type)                         \
    MAKE_ARRAY_LAST(data_name, type)                         \
    MAKE_ARRAY_PREV(data_name, type)

#define ARRAY_INIT(_arr, _size) memset(&(_arr), 0, sizeof((_arr)));     \
    { size_t* _data = (size_t*)&(_arr).data;                              \
        *_data = (size_t)calloc(sizeof(*(_arr).data), (_size)); }        \
    if ((_arr).data) {                                                  \
        (_arr).count = 0;                                               \
        (_arr).len   = _size;                                           \
        (_arr).size  = _size * sizeof(*(_arr).data); }

#define ARRAY_PUSH(_arr, _item) if ((_arr).size != 0 && (_arr).count >= (_arr).len) { \
        size_t* _data = (size_t*)&(_arr).data;                            \
        *_data = (size_t)realloc((_arr).data, (_arr).size*2);            \
        memset((void*)((*_data) + (_arr).size), 0, (_arr).size);        \
        if ((_arr).data) {                                              \
            (_arr).size = (_arr).size*2;                                \
            (_arr).len  = (_arr).len*2;                                 \
        }                                                               \
    }                                                                   \
    if ((_arr).count < (_arr).len)                                      \
        (_arr).data[(_arr).count++] = (_item);                          \

#define ARRAY_POP(_arr) (_arr).count > 0 ? &(_arr).data[--(_arr).count] : nullptr;

#define CARRAYS_H
#endif
