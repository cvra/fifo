#include "CppUTest/TestHarness.h"
#include "../fifo.h"

TEST_GROUP(FIFO8TestGroup)
{
    char buffer[8];
    fifo8_t f;

    void setup(void)
    {
        fifo8_init(&f, buffer, sizeof(buffer));
    }
};

TEST(FIFO8TestGroup, FIFOIsEmptyAfterInit)
{
    CHECK_EQUAL(fifo8_isempty(&f), false);
}
