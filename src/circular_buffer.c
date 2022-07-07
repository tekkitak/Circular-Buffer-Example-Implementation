#include "circular_buffer.h"


void circ_buf_init(circ_buf* cb, int size) {
    cb->buf       = (char*) malloc(size);
    cb->buf_size  = size;
    cb->read_pos  = 0;
    cb->write_pos = 0;
}
void circ_buf_free(circ_buf* cb) {
    free(cb->buf);
    cb->buf = NULL;
}

void _circ_buf_push(circ_buf* cb, char c) {
    cb->buf[cb->write_pos++] = c;
    cb->write_pos %= cb->buf_size+1;
}

int circ_buf_push(circ_buf* cb, char c) {
    if( (cb->write_pos+1)%cb->buf_size == cb->read_pos ) {
        return 1;
    }
    _circ_buf_push(cb, c);
    return 0;
}

void _circ_buf_get(circ_buf* cb, char* c) {
    *c = cb->buf[cb->read_pos++];
    cb->read_pos %= cb->buf_size+1;
}

void circ_buf_get(circ_buf* cb, char* c) {
    if(cb->read_pos == cb->write_pos) {
        *c = '\0';
        return;
    }
    _circ_buf_get(cb, c);
}

int circ_buf_write(circ_buf* cb, char* str) {
    if(strlen(str) >= cb->buf_size) {
        return -1;
    }
    for(int i = 0; str[i] != '\0'; i++) {
        if(circ_buf_push(cb, str[i]))
            return 1;
    }
    circ_buf_push(cb, '\0');
    return 0;
}

char* circ_buf_read(circ_buf* cb) {
    int i;
    char c, *tmp_str = (char*) malloc(sizeof(char)*cb->buf_size);

    for(i = 0; i < cb->buf_size; i++) {
        circ_buf_get(cb, &c);
        if(c == '\0') {
            tmp_str[i] = '\0';
            break;
        }
        tmp_str[i] = c;
    }

    char* str = malloc(sizeof(char)*(i+1));
    strcpy(str, tmp_str);
    free(tmp_str);
    return str;
}

void circ_buf_to_string(circ_buf* cb, char* str, int size) {
    int i;
    for(i = 0; i < cb->buf_size && i < size-1; i++) {
        str[i] = (cb->buf[i]=='\0')?'$':cb->buf[i];
    }
    str[i+1] = '\0';
}

