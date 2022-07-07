#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct circ_buf {
    char* buf;
    int buf_size;
    int read_pos;
    int write_pos;    
} circ_buf;

/**
 * @brief Initialize a circular buffer.
 * 
 * @param cb circular buffer ptr to initialize
 * @param size buffer size
 */
void circ_buf_init(circ_buf* cb, int size);

/**
 * @brief Frees a circular buffer.
 * 
 * @param cb circular buffer free
 */
void circ_buf_free(circ_buf* cb);

void _circ_buf_push(circ_buf* cb, char c);
void _circ_buf_get(circ_buf* cb, char* c);


/**
 * @brief push char into buffer and return 0 if success, 1 if buffer is full
 * 
 * @param cb circular buffer
 * @param c char to be pushed into buffer 
 * 
 * @return 0 if successful, 1 if buffer is full
 */
int circ_buf_push(circ_buf* cb, char c);

/**
 * @brief store char from buffer, if empty stores '\0'
 * 
 * @param cb circular buffer
 * @param c adress to store char from buffer 
 */
void circ_buf_get(circ_buf* cb, char* c);

/**
 * @brief Write string into buffer
 * 
 * @param cb circular buffer
 * @param str string to be written into buffer
 * 
 * @return 0 if successful, 1 if buffer is full, -1 if string is too large for buffer 
 */
int circ_buf_write(circ_buf* cb, char* str);

/**
 * @brief Reads from cb until '\0' is found and returns a ptr to string with the data
 *
 * @param cb circular buffer
 * 
 * @return new string ptr
 */
char* circ_buf_read(circ_buf* cb);

/**
 * @brief Returns contents of the buffer as string.
 * 
 * @param cb circular buffer
 * @param str string to store buffer contents
 * @param size length of str
 */
void circ_buf_to_string(circ_buf* cb, char* str, int size);