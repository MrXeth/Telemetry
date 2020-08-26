#pragma once
#include "pch.h"
#include "Logger.h"
#include "TelemetryState.h"

/// <summary>
/// class for handling event callbacks.
/// </summary>
class Events
{
public:

	/// <summary>
	/// pointer to the current logger
	/// </summary>
	static Logger* logger;
	/// <summary>
	/// pointer to the current TelemetryState object
	/// </summary>
	static TelemetryState* telemetryState;

	/// <summary>
	/// Callback for the "SCS_TELEMETRY_EVENT_started" event.
	/// </summary>
	/// <param name="event">identifier of the invoked event</param>
	static SCSAPI_VOID telemetryStarted(const scs_event_t event, const void* const, const scs_context_t);
	/// <summary>
	/// Callack for the "SCS_TELEMETRY_EVENT_paused" event.
	/// </summary>
	/// <param name="event">identifier of the invoked event</param>
	static SCSAPI_VOID telemetryPaused(const scs_event_t event, const void* const, const scs_context_t);

	/// <summary>
	/// Callback for the "SCS_TELEMETRY_EVENT_configuration" event.
	/// </summary>
	/// <param name="event">identifier of the invoked event</param>
	/// <param name="eventInfo">passed data by the event</param>
	static SCSAPI_VOID telemetryConfiguration(const scs_event_t event, const void* eventInfo, const scs_context_t);

	/// <summary>
	/// Callback for the "SCS_TELEMETRY_EVENT_gameplay" event.
	/// </summary>
	/// <param name="event">identifier of the invoked event</param>
	/// <param name="eventInfo">passed data by the event</param>
	static SCSAPI_VOID telemetryGameplay(const scs_event_t event, const void* const eventInfo, const scs_context_t);
};