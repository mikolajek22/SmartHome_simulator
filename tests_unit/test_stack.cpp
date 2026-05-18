#include <gtest/gtest.h>
#include "stack.h"
// #include "../stack/ll_stack.h"

TEST(StackTest, EmptyAtStart)
{
    Stack<int, 5> s;
    EXPECT_EQ(s.isEmpty(), STACK_EMPTY);
}

TEST(StackTest, TopAtStart)
{
    Stack<int, 5> s;
    EXPECT_EQ(s.count(), 0);
}

TEST(StackTest, Sequence)
{
    Stack<int, 10> s;
    int data = 0;
    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(s.push(100+i), STACK_OK);
        EXPECT_EQ(s.peek(data, 0), STACK_OK);
        EXPECT_EQ(data, 100+i);
    }

    EXPECT_EQ(s.push(123), STACK_FULL);

    for (int i = 0; i < 10; i++)
    {
        s.pop(data);
        EXPECT_EQ(data, 109 - i);
    }
    EXPECT_EQ(s.isEmpty(), STACK_EMPTY);
}

TEST(StackTest, EdgeSize)
{
    Stack<int, 1024 * 1024> s;
    int data;
    for (int i = 0; i < 1024*1024; i++)
    {
        EXPECT_EQ(s.push(i), STACK_OK);
    }
    for (int i = 0; i < 1024*1024; i++)
    {
        EXPECT_EQ(s.pop(data), STACK_OK);
        EXPECT_EQ(data, 1024*1024 - 1 - i);
    }

}