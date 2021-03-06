#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Damian Shortt
 * Written for students at Stony Brook University, ESE 124,
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

/**
 * Creates a new vector and returns a pointer to it.
 * When the vector is no longer in use, it should
 * be deallocated using destroy_vector.
 * @return a pointer to a heap-allocated vector.
 */
struct vector *create_vector();
/**
 * Destructs a vector by freeing the internal array
 * then the vector itself. Use this when your vector
 * is meant to go out of scope.
 * @param vec the vector to be destroyed.
 */
void destroy_vector(struct vector *vec);
/**
 * Attempts to push a value to the vector. If the
 * vector size has reached capacity, it will resize
 * via <code>expand(struct vector *)</code>.
 * @param vec the vector to push to.
 * @param value the value to append.
 */
void push_back(struct vector *vec, int value);
/**
 * Resizes a vector to twice the capacity. This should
 * only be used internally but you're at liberty to use
 * it as you see fit.
 * @param vec the vector whose internal array to expand.
 */
void expand(struct vector *vec);

struct vector *create_vector() {
    struct vector *vec_ = calloc(1, sizeof(* vec_));
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
    printf("%d %d\n", vec_->capacity, vec_->size);
    push_back(vec_, 5);
    push_back(vec_, 2);
    push_back(vec_, 3);
    for (size_t i = 0; i < vec_->capacity; ++i) {
        printf("%d, ", vec_->m_array[i]);
    }
    destroy_vector(vec_);

}
