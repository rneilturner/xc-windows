/******************************Module*Header*******************************\
* Module Name: bdd.h
*
* Basic Display Driver memory allocation, deletion, and tracking 
*
*
* Copyright (c) 2010 Microsoft Corporation
\**************************************************************************/

/*
 *  Licensed under the Microsoft Limited Public License, Version 1.1.
 *  A copy of this license is included with this software.
 */

/* Copyright (c) 2011 Citrix Systems, Inc. */

#include "BDD.hxx"

#pragma code_seg("PAGE")

//
// New and delete operators
//
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new(size_t Size, POOL_TYPE PoolType)
{
    PAGED_CODE();

    Size = (Size != 0) ? Size : 1;
    
    void* pObject = ExAllocatePoolWithTag(PoolType, Size, BDDTAG);

#if DBG
    if (pObject != NULL)
    {
        RtlFillMemory(pObject, Size, 0xCD);
    }
#endif // DBG

    return pObject;
}

_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType)
{
    PAGED_CODE();

    Size = (Size != 0) ? Size : 1;
    
    void* pObject = ExAllocatePoolWithTag(PoolType, Size, BDDTAG);

#if DBG
    if (pObject != NULL)
    {
        RtlFillMemory(pObject, Size, 0xCD);
    }
#endif // DBG

    return pObject;
}

void __cdecl operator delete(void* pObject)
{
    PAGED_CODE();

    if (pObject != NULL)
    {
        ExFreePool(pObject);
    }
}

void __cdecl operator delete[](void* pObject)
{
    PAGED_CODE();

    if (pObject != NULL)
    {
        ExFreePool(pObject);
    }
}

