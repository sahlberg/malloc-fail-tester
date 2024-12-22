/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
#include <stdio.h>
#include <stdlib.h>

struct foo {
        int idx;
};

static void crasher(struct foo *foo)
{
        foo->idx = 1;
}

int main(int argc, char *argv[])
{
        struct foo *foo;
        char buf[16];
        
        foo = malloc(sizeof(*foo));
        printf("First MALLOC %p\n", foo);
        
        foo = malloc(sizeof(*foo));
        printf("Second MALLOC %p\n", foo);
        crasher(foo);

        return 0;
}
