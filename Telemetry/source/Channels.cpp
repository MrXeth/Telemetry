#include "pch.h"
#include "Channels.h"
#include <cassert>

SCSAPI_VOID channels::telemetryStore_u32(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context)
{
    assert(context);
    scs_u32_t& storage = *static_cast<scs_u32_t*>(context);
    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_u32);
        storage = value->value_u32.value;
    }
    else storage = 0;
}

SCSAPI_VOID channels::telemetryStore_s32(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context)
{
    assert(context);
    scs_s32_t& storage = *static_cast<scs_s32_t*>(context);
    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_s32);
        storage = value->value_s32.value;
    }
    else storage = 0;
}

SCSAPI_VOID channels::telemetryStore_s64(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context)
{
    assert(context);
    scs_s64_t& storage = *static_cast<scs_s64_t*>(context);
    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_s64);
        storage = value->value_s64.value;
    }
    else storage = 0;
}

SCSAPI_VOID channels::telemetryStore_float(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context)
{
    assert(context);
    scs_float_t& storage = *static_cast<scs_float_t*>(context);
    if (value)
    {
        assert(value->type = SCS_VALUE_TYPE_float);
        storage = value->value_float.value;
    }
    else storage = 0;
}

SCSAPI_VOID channels::telemetryStore_bool(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context)
{
    assert(context);
    bool& storage = *static_cast<bool*>(context);
    if (value)
    {
        assert(value->type = SCS_VALUE_TYPE_bool);
        storage = value->value_bool.value;
    }
    else storage = false;
}
