#include "baseobj.h"

#pragma code_seg("PAGE")


_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new(size_t Size, POOL_TYPE PoolType)
{
    PAGED_CODE();

    Size = (Size != 0) ? Size : 1;
    
#pragma warning (push)
#pragma warning (disable:4996)
    void* pObject = ExAllocatePoolWithTag(PoolType, Size, VIOGPUTAG);
#pragma warning (pop)

    if (pObject != NULL)
    {
#if DBG
        RtlFillMemory(pObject, Size, 0xCD);
#else
        RtlZeroMemory(pObject, Size);
#endif // DBG
    }
    return pObject;
}

_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType)
{
    PAGED_CODE();

    Size = (Size != 0) ? Size : 1;
    
#pragma warning (push)
#pragma warning (disable:4996)
    void* pObject = ExAllocatePoolWithTag(PoolType, Size, VIOGPUTAG);
#pragma warning (pop)

    if (pObject != NULL)
    {
#if DBG
        RtlFillMemory(pObject, Size, 0xCD);
#else
        RtlZeroMemory(pObject, Size);
#endif // DBG
    }
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

void __cdecl operator delete(void *pObject, size_t Size)
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(Size);

    if (pObject != NULL) {
        ExFreePool(pObject);
    }
}
