#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wrapper.h"
#include "x86emu_private.h"
#include "regs.h"

// the stack as the return address 1st thing, then the args...
#define stack(n) (R_ESP+4+n)
#define i32(n)  *(int32_t*)stack(n)
#define u32(n)  *(uint32_t*)stack(n)
#define p(n)    *(void**)stack(n)
// to check vvvv
#define i64(n)  *(int64_t*)stack(n)
#define u64(n)  *(uint64_t*)stack(n)
//          ^^^^
#define f32(n)  *(float*)stack(n)
#define d64(n)  *(double*)stack(n)
#define D80(n)  *(long double*)stack(n)

typedef void        (*vFv_t)();
typedef void        (*vFE_t)(x86emu_t*);
typedef int32_t     (*iFv_t)();
typedef uint32_t    (*uFE_t)(x86emu_t*);
typedef void        (*vFi_t)(int32_t);
typedef int32_t     (*iFi_t)(int32_t);
typedef int32_t     (*iFp_t)(void*);
typedef int32_t     (*iFpp_t)(void*, void*);
typedef int32_t     (*iFipp_t)(int, void*, void*);
typedef int32_t     (*iFppp_t)(void*, void*, void*);
typedef int32_t     (*iFEpippppp_t)(x86emu_t*, void*, int32_t, void*, void*, void*, void*, void*);

#define DEF(A) A f = (A)fnc

void    vFv(x86emu_t *emu, uintptr_t fnc)
{
    DEF(vFv_t);
    f();
}
void    vFE(x86emu_t *emu, uintptr_t fnc)
{
    DEF(vFE_t);
    f(emu);
}
void    iFv(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFv_t);
    *(int32_t*)&R_EAX = f();
}
void    uFE(x86emu_t *emu, uintptr_t fnc)
{
    DEF(uFE_t);
    R_EAX = f(emu);
}
void    vFi(x86emu_t *emu, uintptr_t fnc)
{
    DEF(vFi_t);
    f(i32(0));
}
void    iFi(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFi_t);
    *(int32_t*)&R_EAX = f(i32(0));
}
void    iFp(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFp_t);
    *(int32_t*)&R_EAX = f(p(0));
}
void    iFpp(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFpp_t);
    *(int32_t*)&R_EAX = f(p(0), p(4));
}
void    iFpV(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFpp_t);
    *(int32_t*)&R_EAX = f(p(0), (void*)stack(4));
}
void    iF1pV(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFipp_t);
    *(int32_t*)&R_EAX = f(1, p(0), (void*)stack(4));
}
void    iFopV(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFppp_t);
    *(int32_t*)&R_EAX = f((void*)stdout, p(0), (void*)stack(4));
}
void    iFvopV(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFppp_t);
    *(int32_t*)&R_EAX = f((void*)stdout, p(4), (void*)stack(8));
}
void    iFEpippppp(x86emu_t *emu, uintptr_t fnc)
{
    DEF(iFEpippppp_t);
    *(int32_t*)&R_EAX = f(emu, p(0), i32(4), p(8), p(12), p(16), p(20), p(24));
}