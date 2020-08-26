#pragma once
#include "pch.h"
#include "Logger.h"
#include "SharedMemory.h"

/// <summary>
/// Main class for Telemetry actions.
/// </summary>
class Telemetry
{
private:

	/// <summary>
	/// version params pointer 
	/// </summary>
	const scs_telemetry_init_params_v100_t* versionParams;

	/// <summary>
	/// logger pointer
	/// </summary>
	Logger* logger;
	
	/// <summary>
	/// shared memory pointer
	/// </summary>
	SharedMemory* sharedMemory;
	
	/// <summary>
	/// Helper function for registering events.
	/// </summary>
	/// <param name="versionParams">version params</param>
	/// <returns>if all events have been initializes propertly</returns>
	bool registerEvents(const scs_telemetry_init_params_v100_t* versionParams);

	/// <summary>
	/// Helper function for registering channels.
	/// </summary>
	/// <param name="versionParams">version params</param>
	/// <param name="state">Reference to the TelemetryState object to present all telemetry information.</param>
	void registerChannels(const scs_telemetry_init_params_v100_t* versionParams, TelemetryState& state);

public:
	
	/// <summary>
	/// Static pointer to a telemetry object to share.
	/// </summary>
	static Telemetry* telemetry;
	
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="version">current api version</param>
	/// <param name="params">init params</param>
	Telemetry(const scs_u32_t& version, const scs_telemetry_init_params_t* const params);
	
	/// <summary>
	/// Destructor
	/// </summary>
	~Telemetry();
};
