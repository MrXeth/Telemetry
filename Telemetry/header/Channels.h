#pragma once
#include "pch.h"

/// <summary>
/// Store providing serveral store callbacks for different data type.
/// </summary>
namespace channels
{
	/// <summary>
	/// Callback function for a  "SCS_VALUE_TYPE_u32"- value.
	/// </summary>
	/// <param name="value">current value of the raised event</param>
	/// <param name="context">specific data type to store the value</param>
	SCSAPI_VOID telemetryStore_u32(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context);
	
	/// <summary>
	/// Callback function for a "SCS_VALUE_TYPE_s32"- value
	/// </summary>
	/// <param name="value">current value of the raised event</param>
	/// <param name="context">specific data type to store the value</param>
	 SCSAPI_VOID telemetryStore_s32(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context);
	
	/// <summary>
	/// Callback function for a "SCS_VALUE_TYPE_s64"- value
	/// </summary>
	/// <param name="value">current value of the raised event</param>
	/// <param name="context">specific data type to store the value</param>
	SCSAPI_VOID telemetryStore_s64(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context);
	
	/// <summary>
	/// Callback for a "SCS_VALUE_TYPE_float"- value
	/// </summary>
	/// <param name="value">current value of the raised event</param>
	/// <param name="context">specific data type to store the value</param>
	SCSAPI_VOID telemetryStore_float(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context);

	/// <summary>
	/// Callback for a "SCS_VALUE_TYPE_bool"- value
	/// </summary>
	/// <param name="value">current value for the raised event</param>
	/// <param name="context">specific data type to store the value</param>
	SCSAPI_VOID telemetryStore_bool(const scs_string_t, const scs_u32_t, const scs_value_t* const value, const scs_context_t context);
	
	
}

