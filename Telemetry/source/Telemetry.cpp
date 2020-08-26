#include "pch.h"
#include "Telemetry.h"
#include "Channels.h"
#include "Events.h"

#define REGISTER_CHANNEL(channel, name, type) \
versionParams->register_for_channel(SCS_TELEMETRY_##channel, SCS_U32_NIL, SCS_VALUE_TYPE_##type, SCS_TELEMETRY_CHANNEL_FLAG_none, \
channels::telemetryStore_##type, &channels.##name);

// definition of static attributes
Telemetry* Telemetry::telemetry;

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params)
{
	try 
	{
		Telemetry::telemetry = new Telemetry(version, params);
	}
	catch (scs_result_t result)
	{
		return result;
	}
	return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown()
{
	delete Telemetry::telemetry;
}

Telemetry::Telemetry(const scs_u32_t& version, const scs_telemetry_init_params_t* const params)
{
	if (version < SCS_TELEMETRY_VERSION_1_00) throw SCS_RESULT_unsupported;
	versionParams = static_cast<const scs_telemetry_init_params_v100_t*>(params);
	logger = new Logger(versionParams->common.log);
	logger->log(SCS_LOG_TYPE_message, "Game '%s' %u.%u", versionParams->common.game_id, SCS_GET_MAJOR_VERSION(versionParams->common.game_version), SCS_GET_MINOR_VERSION(versionParams->common.game_version));

	// ETS 2
	if (strcmp(versionParams->common.game_id, SCS_GAME_ID_EUT2) == 0)
	{
		if (versionParams->common.game_version < SCS_TELEMETRY_EUT2_GAME_VERSION_1_03)
			logger->log(SCS_LOG_TYPE_error, "The wheels.count attribute might behave incorrectly.");
		if (versionParams->common.game_version < SCS_TELEMETRY_EUT2_GAME_VERSION_1_07)
			logger->log(SCS_LOG_TYPE_warning, "This version of the game has less precise output of angular acceleration of the cabin");
		if (SCS_GET_MAJOR_VERSION(versionParams->common.game_version) > SCS_GET_MAJOR_VERSION(SCS_TELEMETRY_EUT2_GAME_VERSION_CURRENT))
			logger->log(SCS_LOG_TYPE_warning, "Too new major version of the game, some features might behave incorrectly");
	}
	// ATS
	else if (strcmp(versionParams->common.game_id, SCS_GAME_ID_ATS) == 0)
	{
		if (versionParams->common.game_version < SCS_TELEMETRY_ATS_GAME_VERSION_1_00)
			logger->log(SCS_LOG_TYPE_warning, "Too old version of the game, some features might behave incorrectly");
		if (SCS_GET_MAJOR_VERSION(versionParams->common.game_version) > SCS_GET_MAJOR_VERSION(SCS_TELEMETRY_ATS_GAME_VERSION_CURRENT))
			logger->log(SCS_LOG_TYPE_warning, "Too new major version of the game, some features might behave incorrectly");
	}
	else logger->log(SCS_LOG_TYPE_warning, "Unsupported game, some features or values might behave incorrectly");

	try
	{
		sharedMemory = new SharedMemory();
	}
	catch (const char*)
	{
		delete logger;
		throw SCS_RESULT_generic_error;
	}

	TelemetryState& state = sharedMemory->getState();
	
	Events::logger = logger;
	Events::telemetryState = &state;

	// register Events
	if (!registerEvents(versionParams))
	{
		logger->log(SCS_LOG_TYPE_error, "Unable to register event callbacks");
		delete logger;
		delete sharedMemory;
		throw SCS_RESULT_generic_error;
	}

	registerChannels(versionParams, state);

}

bool Telemetry::registerEvents(const scs_telemetry_init_params_v100_t* versionParams)
{
	return versionParams->register_for_event(SCS_TELEMETRY_EVENT_started, Events::telemetryStarted, nullptr) == SCS_RESULT_ok &&
		versionParams->register_for_event(SCS_TELEMETRY_EVENT_paused, Events::telemetryPaused, nullptr) == SCS_RESULT_ok &&
		versionParams->register_for_event(SCS_TELEMETRY_EVENT_configuration, Events::telemetryConfiguration, nullptr) == SCS_RESULT_ok &&
		versionParams->register_for_event(SCS_TELEMETRY_EVENT_gameplay, Events::telemetryGameplay, nullptr) == SCS_RESULT_ok;
}

void Telemetry::registerChannels(const scs_telemetry_init_params_v100_t* versionParams, TelemetryState& state)
{
	strcpy_s(state.game_id, versionParams->common.game_id);

	TelemetryState::Channels& channels = state.channels;

	REGISTER_CHANNEL(CHANNEL_game_time, game_time, u32);
	REGISTER_CHANNEL(CHANNEL_next_rest_stop, next_rest_stop, s32);

	REGISTER_CHANNEL(TRUCK_CHANNEL_speed, truck_speed, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_engine_rpm, truck_engine_rpm, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_cruise_control, truck_cruise_control, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_fuel, truck_fuel_amount, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_fuel_warning, truck_fuel_warning, bool);
	REGISTER_CHANNEL(TRUCK_CHANNEL_fuel_average_consumption, truck_fuel_consumption_average, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_adblue, truck_adblue, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_adblue_warning, truck_adblue_warning, bool);
	REGISTER_CHANNEL(TRUCK_CHANNEL_adblue_average_consumption, truck_adblue_consumption_average, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_wear_engine, truck_wear_engine, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_wear_transmission, truck_wear_transmission, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_wear_cabin, truck_wear_cabin, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_wear_chassis, truck_wear_chassis, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_wear_wheels, truck_wear_wheels, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_navigation_distance, truck_navigation_distance, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_navigation_time, truck_navigation_time, float);
	REGISTER_CHANNEL(TRUCK_CHANNEL_navigation_speed_limit, truck_navigation_speed_limit, float);

	REGISTER_CHANNEL(TRAILER_CHANNEL_connected, trailer_connected, bool);
	REGISTER_CHANNEL(TRAILER_CHANNEL_cargo_damage, trailer_cargo_damage, float);
	REGISTER_CHANNEL(TRAILER_CHANNEL_wear_chassis, trailer_wear_chassis, float);
	REGISTER_CHANNEL(TRAILER_CHANNEL_wear_wheels, trailer_wear_wheels, float);

	REGISTER_CHANNEL(JOB_CHANNEL_cargo_damage, job_cargo_damage, float);
}

Telemetry::~Telemetry()
{
	delete logger;
	delete sharedMemory;
}
