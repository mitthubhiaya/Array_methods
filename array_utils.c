#include <stdio.h>
#include "array_utils.h"
#include <stdlib.h>
#include <string.h>


ArrayUtil create(int typeSize, int length){
     ArrayUtil final_array;
     final_array.base = calloc(typeSize,length);
     final_array.typeSize = typeSize;
     final_array.length = length;
     return final_array;
};
int areEqual (ArrayUtil first_array,ArrayUtil second_array){
     if(first_array.length == second_array.length &&
         first_array.typeSize == second_array.typeSize){
         return 1;
     };
     return 0;
};

ArrayUtil resize (ArrayUtil array , int length){
    int size_required = (length *array.typeSize);
    array.base = realloc(array.base , size_required);
    array.length = length;
    return array;
};
void dispose (ArrayUtil array){
    free(array.base);
};

int findIndex(ArrayUtil array, void* element){
	void * value_of_array = (array.base);
	for (int count = 0; count < array.length; count++){
		if(memcmp(value_of_array,element,array.typeSize)==0)
			return count;
        };
	return -1;
};

void* findFirst(ArrayUtil array,MatchFunc* match, void* hint){
    int index;
    int *elements = array.base;
    for(index = 0; index < array.length ; index++){
        if(match(hint,&elements[index]))
            return &elements[index];
    }
    return NULL;
};

void* findLast(ArrayUtil array, MatchFunc* match, void* hint){
    int index;
    int *elements = array.base;
    for(index = array.length - 1; index >=0 ; index--){
        if(match(hint,&elements[index]))
            return &elements[index];
    }
    return NULL;
};

int count(ArrayUtil array, MatchFunc* match, void* hint){
    int elements = 0;
	int * numbers = array.base;
		for (int index = 0; index < array.length; index++)
			if(match(hint,&numbers[index]))
				elements++;
	return elements;
};

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint){
    void * elements_of_source = source.base;
    void * elements_of_destination = destination.base;
    for(int i = 0; i<source.length; i++){
        convert(hint,elements_of_source,elements_of_destination);
        elements_of_source += source.typeSize;
        elements_of_destination += destination.typeSize;
    };
};

void forEach(ArrayUtil array, OperationFunc* operation, void* hint){
	void * elements_of_array = array.base;
	for(int i =0; i<array.length; i++){
		operation(hint,elements_of_array);
		elements_of_array+=array.typeSize;
	};
};

int filter(ArrayUtil array, MatchFunc* match, void* hint, void** destination, int maxItems ){
    int count = 0,index;
    void * elements = array.base;
    for(index = 0; index  <array.length; index++){
        if(match(hint,elements)&& count < maxItems){
            destination[count] = elements;
            count ++;
        };
        elements += array.typeSize;
    };
    return count;
};

void* reduce(ArrayUtil array, ReducerFunc* reducer, void* hint, void* initialValue){
	void * elements_of_array = array.base;
	for(int i = 0; i <array.length; i++){
		initialValue = reducer (hint, initialValue, elements_of_array);
		elements_of_array += array.typeSize;
	};
	return initialValue;
};
