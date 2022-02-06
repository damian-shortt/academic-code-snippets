#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Damian Shortt
 * Written for students in Stony Brook University, ESE 124,
 * as a demonstration of how one can create a dynamically-
 * resizing array.
 *
 * Rudimentary int vector implementation.
 */

struct vector {
    size_t size;
    size_t capacity;
    int *m_array;
};

#define vector_initial_capacity 10;

// Forward declarations of member functions.

struct vector *create_vector();
void destroy_vector(struct vector *vec);
void push_back(struct vector *vec, int value);
void expand(struct vector *vec);

struct vector *create_vector() {
    struct vector *vec_ = malloc(sizeof(* vec_));
    vec_->capacity = 0;
    vec_->size = 0;
    vec_->m_array = NULL;
    return vec_;
}

void destroy_vector(struct vector *vec) {
    free(vec->m_array);
    free(vec);
}

void push_back(struct vector *vec, int value) {
    if (vec->size >= vec->capacity) {
        expand(vec);
    }

    vec->m_array[vec->size++] = value;
}

void expand(struct vector *vec) {
    size_t new_capacity = vec->capacity * 2;
    if (new_capacity == 0)
        new_capacity = vector_initial_capacity;
    int *array_ = calloc(new_capacity, sizeof(int));
    memcpy(array_, vec->m_array, sizeof(* array_) * vec->capacity);
    free(vec->m_array);
    vec->m_array = array_;
    vec->capacity = new_capacity;
}

int main() {
    struct vector *vec_ = create_vector();
    push_back(vec_, 5);
    push_back(vec_, 2);
    push_back(vec_, 3);
    for (size_t i = 0; i < vec_->size; ++i) {
        printf("%d, ", vec_->m_array[i]);
    }
}
