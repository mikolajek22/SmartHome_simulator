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

TEST(StackTest, PushMethod)
{
    Stack<int, 5> s;
    int data = 10;
    EXPECT_EQ(s.push(data), STACK_OK);
}

TEST(StackTest, Full)
{
    Stack<int, 10> s;
    for (int i = 0; i < 10; i++)
    {
        s.push(100+i);
    }
    EXPECT_EQ(s.isFull(), STACK_FULL);
}

TEST(StackTest, Push)
{
    Stack<int, 2> s;
    s.push(1);
    int data = 0;
    s.pop(data);
    EXPECT_EQ(data, 1);
}

TEST(StackTest, Empty)
{
    Stack<int, 10> s;
    int data;
    for (int i = 0; i < 10; i++)
    {
        s.push(100+i);
    }
    for (int i = 0; i < 10; i++)
    {
        s.pop(data);
        EXPECT_EQ(data, 109 - i);
    }
    EXPECT_EQ(s.isEmpty(), STACK_EMPTY);
}