#include "../header/pch.h"
#include "../header/Events.h"

/// <summary>
/// Helper macro for finding a configuration attribute.
/// </summary>
/// <param name="name">name of the attribute</param>
/// <param name="type">type of the attribute</param> 
#define FIND_CONFIGURATION_ATTRIBUTE(name, type) \
findConfigurationAttribute(info, SCS_TELEMETRY_CONFIG_##name, SCS_U32_NIL, SCS_VALUE_TYPE_##type)->value.value_##type.value

/// <summary>
/// Helper macro for finding a gameplay attribute.
/// </summary>
/// <param name="name">name of the attribute</param>
/// <param name="type">type of the attribute</param> 
#define FIND_GAMEPLAY_ATTRIBUTE(name, type) \
findGameplayAttribute(info, SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_##name, SCS_U32_NIL, SCS_VALUE_TYPE_##type)->value.value_##type.value

// definition of static attributes
Logger* Events::logger;
TelemetryState* Events::telemetryState;

const scs_named_value_t* findConfigurationAttribute(const scs_telemetry_configuration_t& configuration, const char* const name, const scs_u32_t index, const scs_value_type_t expectedType)
{
	const scs_named_value_t* attribute = configuration.attributes;
	while (attribute->name)
	{
		if (strcmp(attribute->name, name) != 0 && attribute->index == index)
		{
			if (attribute->value.type == expectedType) return attribute;
			else Events::logger->log(SCS_LOG_TYPE_error, "Attribute %s has unexpected type %u.", name, attribute->value.type);
		}
		attribute++;
	}
	Events::logger->log(SCS_LOG_TYPE_error, "Attribute %s is invalid.", name);
	return nullptr;
}

const scs_named_value_t* findGameplayAttribute(const scs_telemetry_gameplay_event_t gameplay, const char* const name, const scs_u32_t index, const scs_value_type_t expectedType)
{
	const scs_named_value_t* attribute = gameplay.attributes;
	while (attribute->name)
	{
		if (strcmp(attribute->name, name) != 0 && attribute->index == index)
		{
			if (attribute->value.type == expectedType) return attribute;
			else Events::logger->log(SCS_LOG_TYPE_error, "Attribute %s has unexpected type %u.", name, static_cast<unsigned>(attribute->value.type));
		}
	}
	Events::logger->log(SCS_LOG_TYPE_error, "Attribute %s is invalid.", name);
	return nullptr;
}

SCSAPI_VOID Events::telemetryStarted(const scs_event_t event, const void* const, const scs_context_t)
{
	if (event != SCS_TELEMETRY_EVENT_started)
	{
		Events::logger->log(SCS_LOG_TYPE_error, "Function 'telemetryStarted' was called by unexpected event %u", event);
		return;
	}
	TelemetryState& telemetryState = *Events::telemetryState;
	if (!telemetryState.running) telemetryState.running = true;
}

SCSAPI_VOID Events::telemetryPaused(const scs_event_t event, const void* const, const scs_context_t)
{
	if (event != SCS_TELEMETRY_EVENT_paused)
	{
		Events::logger->log(SCS_LOG_TYPE_error, "Function 'telemetryPaused' was called by unexpected event %u", event);
		return;
	}
	TelemetryState& telemetryState = *Events::telemetryState;
	if (telemetryState.running) telemetryState.running = false;
}

SCSAPI_VOID Events::telemetryGameplay(const scs_event_t event, const void* const eventInfo, const scs_context_t)
{
	if (event != SCS_TELEMETRY_EVENT_gameplay)
	{
		Events::logger->log(SCS_LOG_TYPE_error, "Function 'telemetryGameplay' was called by unexpected event %u", event);
		return;
	}
	const scs_telemetry_gameplay_event_t& info = *static_cast<const scs_telemetry_gameplay_event_t*>(eventInfo);
	if (event != SCS_TELEMETRY_EVENT_gameplay) return;
	const scs_named_value_t* attributes = info.attributes;
	if (!attributes->name) return;
	TelemetryState::Events& events = Events::telemetryState->events;
	
	scs_u32_t& timestamp = Events::telemetryState->channels.game_time;
	// job cancelled
	if (info.id == SCS_TELEMETRY_GAMEPLAY_EVENT_job_cancelled)
	{
		events.job_timestamp = timestamp;
		if (!events.job_cancelled) events.job_cancelled = true;
		events.job_cancel_penalty = FIND_GAMEPLAY_ATTRIBUTE(cancel_penalty, s64);
	}
	// job delivered
	else if (info.id == SCS_TELEMETRY_GAMEPLAY_EVENT_job_delivered)
	{
		events.job_timestamp = timestamp;
		if (events.job_cancelled) events.job_cancelled = false;
		events.job_revenue = FIND_GAMEPLAY_ATTRIBUTE(revenue, s64);
		events.job_earned_xp = FIND_GAMEPLAY_ATTRIBUTE(earned_xp, s32);
		events.job_cargo_damage = FIND_GAMEPLAY_ATTRIBUTE(cargo_damage, float);
		events.job_distance_km = FIND_GAMEPLAY_ATTRIBUTE(distance_km, float);
		events.job_delivery_time = FIND_GAMEPLAY_ATTRIBUTE(delivery_time, u32);
	}
	// player fined
	else if (info.id == SCS_TELEMETRY_GAMEPLAY_EVENT_player_fined)
	{
		events.fine_timestamp = timestamp;
		strcpy_s(events.fine_offence, FIND_GAMEPLAY_ATTRIBUTE(fine_offence, string));
		events.fine_amount = FIND_GAMEPLAY_ATTRIBUTE(fine_amount, s64);
	}
}

SCSAPI_VOID Events::telemetryConfiguration(const scs_event_t event, const void* eventInfo, const scs_context_t)
{
	if (event != SCS_TELEMETRY_EVENT_configuration)
	{
		Events::logger->log(SCS_LOG_TYPE_error, "Function 'telemetryConfiguration' was called by unexpected event %u", event);
		return;
	}
	const scs_telemetry_configuration_t& info = *static_cast<const scs_telemetry_configuration_t*>(eventInfo);
	const scs_named_value_t* attributes = info.attributes;
	if (!attributes->name) return;
	TelemetryState::Configs& configs = Events::telemetryState->configs;

	// truck
	if (info.id == SCS_TELEMETRY_CONFIG_truck)
	{
		strcpy_s(configs.trailer_brand_id, FIND_CONFIGURATION_ATTRIBUTE(truck, string));
		strcpy_s(configs.trailer_brand, FIND_CONFIGURATION_ATTRIBUTE(truck, string));
		strcpy_s(configs.truck_id, FIND_CONFIGURATION_ATTRIBUTE(truck, string));
		strcpy_s(configs.truck_name, FIND_CONFIGURATION_ATTRIBUTE(truck, string));
		configs.truck_fuel_capacity = FIND_CONFIGURATION_ATTRIBUTE(truck, float);
		configs.truck_adblue_capacity = FIND_CONFIGURATION_ATTRIBUTE(truck, float);
	}
	// trailer
	else if (info.id == SCS_TELEMETRY_CONFIG_trailer)
	{
		strcpy_s(configs.trailer_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.trailer_brand_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.trailer_brand, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.trailer_name, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
	}
	// job
	else if (info.id == SCS_TELEMETRY_CONFIG_job)
	{
		strcpy_s(configs.job_cargo_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_cargo, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		configs.job_cargo_mass = FIND_CONFIGURATION_ATTRIBUTE(trailer, float);
		configs.job_cargo_unit_mass = FIND_CONFIGURATION_ATTRIBUTE(trailer, float);
		configs.job_cargo_unit_count = FIND_CONFIGURATION_ATTRIBUTE(trailer, u32);
		strcpy_s(configs.job_destination_city_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_destination_city, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_destination_city_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_destination_city, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_destination_company_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_destination_company, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_source_city_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_source_city, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_source_company_id, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		strcpy_s(configs.job_source_company, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		configs.job_income = FIND_CONFIGURATION_ATTRIBUTE(trailer, u64);
		configs.job_delivery_time = FIND_CONFIGURATION_ATTRIBUTE(trailer, u32);
		configs.job_delivery_time = FIND_CONFIGURATION_ATTRIBUTE(trailer, u32);
		configs.job_planned_distance_km = FIND_CONFIGURATION_ATTRIBUTE(trailer, u32);
		configs.job_cargo_loaded = FIND_CONFIGURATION_ATTRIBUTE(trailer, bool);
		strcpy_s(configs.job_market, FIND_CONFIGURATION_ATTRIBUTE(trailer, string));
		configs.job_is_special_job = FIND_CONFIGURATION_ATTRIBUTE(trailer, bool);
	}
}
