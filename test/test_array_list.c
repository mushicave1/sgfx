#include <array_list.h>
#include "test.h"


SGFX_ARRAY_LIST_DECLARE_NATIVE(float, Float);


int testArrayList() 
{
    IntegerArrayList arr;
    IntegerArrayList_Init(&arr, 10);

    for ( size_t i = 0; i < 10; i++) { 
        IntegerArrayList_Push(&arr, 10);
        printf("item: %d", arr.data[i]);
    }

    ASSERT_EQ(arr.len == 10);

    IntegerArrayList_Deinit(&arr);

    return 0;
}