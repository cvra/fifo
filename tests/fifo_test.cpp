#include "CppUTest/TestHarness.h"
#include "../fifo.h"

TEST_GROUP(FIFO8TestGroup)
{
    char buffer[3];
    fifo8_t f;

    void setup(void)
    {
        fifo8_init(&f, buffer, 3);
    }
};

TEST(FIFO8TestGroup, IsEmptyAfterInit)
{
    CHECK_EQUAL(fifo8_isempty(&f), true);
}

TEST(FIFO8TestGroup, CanBeFilled)
{
    CHECK(fifo8_put(&f, 'x'));
    CHECK(fifo8_put(&f, 'x'));
    CHECK(fifo8_put(&f, 'x'));
}

TEST(FIFO8TestGroup, IsFull)
{
    // fill buffer
    fifo8_put(&f, 'x');
    fifo8_put(&f, 'x');
    fifo8_put(&f, 'x');
    // should be full now
    CHECK(fifo8_isfull(&f));
    CHECK(fifo8_put(&f, 'x') == false);
}

TEST(FIFO8TestGroup, GetEmpty)
{
    char c;
    CHECK(fifo8_get(&f, &c) == false);
}

TEST(FIFO8TestGroup, GetItem)
{
    char c;
    fifo8_put(&f, '*');
    CHECK(fifo8_get(&f, &c));
    CHECK_EQUAL(c, '*');
}

TEST(FIFO8TestGroup, EmptyAfterItem)
{
    char c;
    fifo8_put(&f, '*');
    fifo8_get(&f, &c);
    CHECK(fifo8_get(&f, &c) == false);
}

TEST(FIFO8TestGroup, NotFullAfterRead)
{
    char c;
    // fill buffer
    fifo8_put(&f, 'x');
    fifo8_put(&f, 'x');
    fifo8_put(&f, 'x');
    // read one item
    fifo8_get(&f, &c);
    // should no longer be full now
    CHECK(fifo8_isfull(&f) == false);
    CHECK(fifo8_put(&f, 'x') == true);
}

TEST(FIFO8TestGroup, FiFoOrder)
{
    char c;
    fifo8_put(&f, '1');
    fifo8_put(&f, '2');
    fifo8_put(&f, '3');

    fifo8_get(&f, &c);
    CHECK_EQUAL(c, '1');
    fifo8_get(&f, &c);
    CHECK_EQUAL(c, '2');
    fifo8_get(&f, &c);
    CHECK_EQUAL(c, '3');
}



TEST_GROUP(FIFO8MemoryTestGroup)
{
    char buffer[1+3+1];
    fifo8_t f;

    bool check_buffer_overflow(void)
    {
        return buffer[0] == -1 && buffer[4] == -1;
    }

    void setup(void)
    {
        buffer[0] = -1;
        fifo8_init(&f, &buffer[1], 3);
        buffer[4] = -1;
    }
};

TEST(FIFO8MemoryTestGroup, WritePWrapAround)
{
    char c;
    fifo8_put(&f, 'a');
    fifo8_put(&f, 'b');
    fifo8_put(&f, 'c');
    // buffer is full now, free one item
    fifo8_get(&f, &c);
    // write pointer should wrap to start of buffer
    fifo8_put(&f, '*');
    CHECK(check_buffer_overflow());
    CHECK_EQUAL('*', buffer[1]);
}

TEST(FIFO8MemoryTestGroup, ReadPWrapAround)
{
    char c;
    fifo8_put(&f, 'a');
    fifo8_put(&f, 'b');
    fifo8_put(&f, 'c');
    fifo8_get(&f, &c); // a
    fifo8_get(&f, &c); // b
    fifo8_put(&f, 'd');
    fifo8_get(&f, &c); // c
    fifo8_get(&f, &c); // d
    CHECK_EQUAL(c, 'd'); // the read pointer has correctly wrapped around the end of the buffer
    CHECK(check_buffer_overflow());
}

