// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

// SEALDll
#include "stdafx.h"
#include "secretkey.h"
#include "utilities.h"

// SEAL
#include "seal/secretkey.h"

using namespace std;
using namespace seal;
using namespace seal::dll;


SEALDLL HRESULT SEALCALL SecretKey_Create1(void** secret_key)
{
    IfNullRet(secret_key, E_POINTER);

    SecretKey* skey = new SecretKey();
    *secret_key = skey;
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_Create2(void* copy, void** secret_key)
{
    SecretKey* copyptr = FromVoid<SecretKey>(copy);
    IfNullRet(copyptr, E_POINTER);
    IfNullRet(secret_key, E_POINTER);

    SecretKey* skey = new SecretKey(*copyptr);
    *secret_key = skey;
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_Set(void* thisptr, void* assign)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);
    SecretKey* assignptr = FromVoid<SecretKey>(assign);
    IfNullRet(assignptr, E_POINTER);

    *skey = *assignptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_Data(void* thisptr, void** data)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);
    IfNullRet(data, E_POINTER);

    // This returns a pointer to an existing object, not a new object.
    // Make sure the managed side does not try to delete it.
    const Plaintext* plaintext = &skey->data();
    *data = const_cast<Plaintext*>(plaintext);
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_Destroy(void* thisptr)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);

    delete skey;
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_IsValidFor(void* thisptr, void* contextptr, bool* result)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);
    const auto& sharedctx = SharedContextFromVoid(contextptr);
    IfNullRet(sharedctx.get(), E_POINTER);
    IfNullRet(result, E_POINTER);

    *result = skey->is_valid_for(sharedctx);
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_ParmsId(void* thisptr, uint64_t* parms_id)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);
    IfNullRet(parms_id, E_POINTER);

    CopyParmsId(skey->parms_id(), parms_id);
    return S_OK;
}

SEALDLL HRESULT SEALCALL SecretKey_Pool(void* thisptr, void** pool)
{
    SecretKey* skey = FromVoid<SecretKey>(thisptr);
    IfNullRet(skey, E_POINTER);
    IfNullRet(pool, E_POINTER);

    MemoryPoolHandle* handleptr = new MemoryPoolHandle(skey->pool());
    *pool = handleptr;
    return S_OK;
}