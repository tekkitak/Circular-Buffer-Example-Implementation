#include "../unity/unity.h"
#include "../src/circular_buffer.h"

void setUp(void)
{
}
void tearDown(void)
{
}


void test_circ_buf_init_free() {
    circ_buf cb;
    circ_buf_init(&cb, 10);
    TEST_ASSERT_EQUAL_INT(10, cb.buf_size);
    TEST_ASSERT_EQUAL_INT(0, cb.read_pos);
    TEST_ASSERT_EQUAL_INT(0, cb.write_pos);
    circ_buf_free(&cb);
    TEST_ASSERT_NULL(cb.buf);
}

void test_circ_buf_push_get() {
    circ_buf cb;
    char c;
    circ_buf_init(&cb, 10);

    circ_buf_get(&cb, &c);
    TEST_ASSERT_EQUAL_CHAR('\0', c);

    TEST_ASSERT_EQUAL(0, circ_buf_push(&cb, 'a'));
    TEST_ASSERT_EQUAL(0, circ_buf_push(&cb, 'b'));

    circ_buf_get(&cb, &c);
    TEST_ASSERT_EQUAL('a', c);
    circ_buf_get(&cb, &c);
    TEST_ASSERT_EQUAL('b', c);
}

void test_circ_buf_content() {
    circ_buf cb;
    circ_buf_init(&cb, 10);
    for(int i = 0; i < 9; i++) {
        TEST_ASSERT_EQUAL(0, circ_buf_push(&cb, 'a'));
    }
    TEST_ASSERT_EQUAL(1, circ_buf_push(&cb, 'c'));
    cb.read_pos++;
    TEST_ASSERT_EQUAL(0, circ_buf_push(&cb, 'b'));

    char* str = (char*) malloc(sizeof(char)*10);
    circ_buf_to_string(&cb, str, 10);
    TEST_ASSERT_EQUAL_STRING("aaaaaaaaa", str);
    free(str);
    
    circ_buf_free(&cb);
}

void test_circ_buf_write_read() {
    circ_buf cb;
    circ_buf_init(&cb, 25);
    char* str = "Hello World";
    TEST_ASSERT_EQUAL(0, circ_buf_write(&cb, str));
    char* str2 = "Test";
    TEST_ASSERT_EQUAL(0, circ_buf_write(&cb, str2));
    char* out_str = circ_buf_read(&cb);
    TEST_ASSERT_EQUAL_STRING(str, out_str);
    free(out_str);
    out_str = circ_buf_read(&cb);
    TEST_ASSERT_EQUAL_STRING(str2, out_str);
    free(out_str);

    TEST_ASSERT_EQUAL(0, circ_buf_write(&cb, "123456789ABCDEFGHIJKLMNO"));
    out_str = (char*) malloc(sizeof(char)*25);
    circ_buf_to_string(&cb, out_str, 25);
    printf("%s\n", out_str);


    circ_buf_free(&cb);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_circ_buf_init_free);
    RUN_TEST(test_circ_buf_push_get);
    RUN_TEST(test_circ_buf_content);
    RUN_TEST(test_circ_buf_write_read);
    return UNITY_END();
}
