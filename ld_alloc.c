/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
/*
Copyright (C) 2024 by Ronnie Sahlberg <ronniesahlberg@gmail.com>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <dlfcn.h>

int alloc_fail = -1;

void *(*real_malloc)(size_t size);
void *(*real_calloc)(size_t nelem, size_t size);

void *malloc(size_t size)
{
        static int call_idx = 0;

        if (call_idx++ == alloc_fail) {
                return NULL;
        }
        return real_malloc(size);
}

void *calloc(size_t nelem, size_t size)
{
        static int call_idx = 0;

        if (call_idx++ == alloc_fail) {
                return NULL;
        }
        return real_calloc(nelem, size);
}

static void __attribute__((constructor))
_init(void)
{
	if (getenv("ALLOC_FAIL") != NULL) {
		alloc_fail = atoi(getenv("ALLOC_FAIL"));
	}
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	real_calloc = dlsym(RTLD_NEXT, "calloc");
}
