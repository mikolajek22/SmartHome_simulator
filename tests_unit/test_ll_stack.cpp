#include <gtest/gtest.h>
#include "ll_stack.h"
#include "queue.h"
#include "binaryTree.h"

TEST(LL_StackTest, EmptyAtStart)
{
    LL_Stack<int> s;
    EXPECT_EQ(s.isEmpty(), LL_STACK_EMPTY);
}


TEST(LL_StackTest, Sequence)
{
    LL_Stack<int> s;
    int data = 0;
    int pushData = 0;
    for (int i = 0; i < 10; i++)
    {
        pushData = 100 + i;
        EXPECT_EQ(s.push(pushData), LL_STACK_OK);
        EXPECT_EQ(s.peek(data, 0), LL_STACK_OK);
        EXPECT_EQ(data, 100+i);
    }

    // EXPECT_EQ(s.push(123), LL_STACK_FULL);

    for (int i = 0; i < 10; i++)
    {
        s.pop(data);
        EXPECT_EQ(data, 109 - i);
    }
    EXPECT_EQ(s.isEmpty(), LL_STACK_EMPTY);
}

TEST(LL_StackTest, EdgeSize)
{
    LL_Stack<int> s;
    int data;
    for (int i = 0; i < 1024*1024; i++)
    {
        EXPECT_EQ(s.push(i), LL_STACK_OK);
    }
    for (int i = 0; i < 1024*1024; i++)
    {
        EXPECT_EQ(s.pop(data), LL_STACK_OK);
        EXPECT_EQ(data, 1024*1024 - 1 - i);
    }

}