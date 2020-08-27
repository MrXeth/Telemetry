#pragma once
#include "pch.h"

/// <summary>
/// Struct representing the current game state.
/// </summary>
struct TelemetryState
{
	/// <summary>
	/// Represents wether the telemetry is running.
	/// </summary>
	bool running;

	/// <summary>
	/// Represents the current api version.
	/// </summary>
	scs_u32_t apiVersion;

	/// <summary>
	/// Represents the current game id.
	/// </summary>
	char game_id[8];

	/// <summary>
	/// Struct representing all channels.
	/// </summary>
	struct Channels
	{
		#pragma region Common

		/// <summary>
		/// Represents the current game time.
		/// SCS_TELEMETRY_CHANNEL_game_time
		/// </summary>
		scs_u32_t game_time; 

		/// <summary>
		/// Represents the time to the next rest stop.
		/// SCS_TELEMETRY_CHANNEL_next_rest_stop 
		/// </summary>
		scs_s32_t next_rest_stop;

		#pragma endregion

		#pragma region Truck
		
		/// <summary>
		/// Represents the current truck speed.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_speed
		/// </summary>
		scs_float_t truck_speed;

		/// <summary>
		/// Represents the current engine rpm.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm
		/// </summary>
		scs_float_t truck_engine_rpm;

		/// <summary>
		/// Represents the current speed of the cruise control.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control
		/// </summary>
		scs_float_t truck_cruise_control;

		/// <summary>
		/// Represents the current fuel amount.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_fuel
		/// </summary>
		scs_float_t truck_fuel_amount;

		/// <summary>
		/// Represents wether the fuel warning is activated.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning 
		/// </summary>
		bool truck_fuel_warning;

		/// <summary>
		/// Represents the current average fuel consumption.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption
		/// </summary>
		scs_float_t truck_fuel_consumption_average;

		/// <summary>
		/// Represents the current adblue amount.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_adblue 
		/// </summary>
		scs_float_t truck_adblue;

		/// <summary>
		/// Represents wether the adblue warning is activated.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning 
		/// </summary>
		bool truck_adblue_warning;

		/// <summary>
		/// Represents the current adblue average consumption.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_adblue_average_consumption
		/// </summary>
		scs_float_t truck_adblue_consumption_average;

		/// <summary>
		/// Represents the current engine wear.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine 
		/// </summary>
		scs_float_t truck_wear_engine;

		/// <summary>
		/// Represents the current transmission wear.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission
		/// </summary>
		scs_float_t truck_wear_transmission;

		/// <summary>
		/// Represents the current cabin wear.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin
		/// </summary>
		scs_float_t truck_wear_cabin;

		/// <summary>
		/// Represents the current chassis wear.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis
		/// </summary>
		scs_float_t truck_wear_chassis;

		/// <summary>
		/// Represents the current wheel wear.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels 
		/// </summary>
		scs_float_t truck_wear_wheels;

		/// <summary>
		/// Represents the current navigation distance until the destination.
		/// </summary>
		scs_float_t truck_navigation_distance; // SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance
		
		/// <summary>
		/// Represents the current navigation time until the destination.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time 
		/// </summary>
		scs_float_t truck_navigation_time;

		/// <summary>
		/// Represents the current speed limit displayed on the navigation device.
		/// SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit
		/// </summary>
		scs_float_t truck_navigation_speed_limit;

		#pragma endregion

		#pragma region Trailer

		/// <summary>
		/// Represents wether a trailer is connected to the vehicle.
		/// SCS_TELEMETRY_TRAILER_CHANNEL_connected
		/// </summary>
		bool trailer_connected;

		/// <summary>
		/// Represents the current trailer cargo damage.
		/// SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage
		/// </summary>
		scs_float_t trailer_cargo_damage;

		/// <summary>
		/// Represents the current trailer chassis wear.
		/// SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis
		/// </summary>
		scs_float_t trailer_wear_chassis;

		/// <summary>
		/// Represents the current trailer wheels wear.
		/// SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels
		/// </summary>
		scs_float_t trailer_wear_wheels;

		#pragma endregion

		#pragma region Job

		/// <summary>
		/// Represents the current job cargo damage.
		/// SCS_TELEMETRY_JOB_CHANNEL_cargo_damage
		/// </summary>
		scs_float_t job_cargo_damage; 

		#pragma endregion

	} channels;

	/// <summary>
	/// Struct representing all event data.
	/// </summary>
	struct Events {

		#pragma region Job

		/// <summary>
		/// Represents the timestamp for the last job event.
		/// </summary>
		scs_u32_t job_timestamp;

		/// <summary>
		/// Represent wether the current job was cancelled "<code>true</code>" or not "<code>false</code>"
		/// </summary>
		bool job_cancelled;

		/// <summary>
		/// Represents the job cancel penalty, if the job was cancelled.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_cancel_penalty
		/// </summary>
		scs_s64_t job_cancel_penalty;

		/// <summary>
		/// Represents the job revenue, if the job was delivered.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_revenue
		/// </summary>
		scs_s64_t job_revenue;

		/// <summary>
		/// Represents the earned xp for the job, if the job was delivered.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_earned_xp
		/// </summary>
		scs_s32_t job_earned_xp;

		/// <summary>
		/// Represents the total cargo damage for the job, if it was delivered.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_cargo_damage
		/// </summary>
		scs_float_t job_cargo_damage;

		/// <summary>
		/// Represents the real driven distance for the job, if it was delivered.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_distance_km
		/// </summary>
		scs_float_t job_distance_km;

		/// <summary>
		/// Represents the real delivery time for the job, if it was delivered.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_delivery_time
		/// </summary>
		scs_u32_t job_delivery_time;

		#pragma endregion

		#pragma region Fine

		/// <summary>
		/// Represents the timestamp for the last fine event.
		/// </summary>
		scs_u32_t fine_timestamp;

		/// <summary>
		/// Represents the current fine offence.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_fine_offence
		/// </summary>
		char fine_offence[24];

		/// <summary>
		/// Represents the current fine amount.
		/// SCS_TELEMETRY_GAMEPLAY_EVENT_ATTRIBUTE_fine_amount
		/// </summary>
		scs_s64_t fine_amount;

		#pragma endregion

	} events;

	/// <summary>
	/// Struct representing all configuration data.
	/// </summary>
	struct Configs {

		#pragma region Truck

		/// <summary>
		/// Representing the current truck's brand id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_brand_id
		/// </summary>
		char truck_brand_id[32];

		/// <summary>
		/// Representing the current truck's brand id in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_brand 
		/// </summary>
		char truck_brand[32];

		/// <summary>
		/// Representing the current truck's id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_id 
		/// </summary>
		char truck_id[32];

		/// <summary>
		/// Representing the current truck's name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_name
		/// </summary>
		char truck_name[32];

		/// <summary>
		/// Representing the current truck's fuel capacity.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_fuel_capacity
		/// </summary>
		scs_float_t truck_fuel_capacity;

		/// <summary>
		/// Representing the current truck's adblue capacity.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_adblue_capacity
		/// </summary>
		scs_float_t truck_adblue_capacity;

		#pragma endregion

		#pragma region Trailer

		/// <summary>
		/// Representing the current trailer's id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_id 
		/// </summary>
		char trailer_id[32];

		/// <summary>
		/// Representing the current trailer's brand id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_brand_id
		/// </summary>
		char trailer_brand_id[32];

		/// <summary>
		/// Representing the current trailer's brand in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_brand
		/// </summary>
		char trailer_brand[32];

		/// <summary>
		/// Representing the current trailer's name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_name
		/// </summary>
		char trailer_name[32];

		#pragma endregion

		#pragma region Job

		/// <summary>
		/// Represents the current job's cargo id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_cargo_id
		/// </summary>
		char job_cargo_id[32];

		/// <summary>
		/// Represents the current job's cargo name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_cargo
		/// </summary>
		char job_cargo[32];

		/// <summary>
		/// Represents the current job's cargo mass.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_cargo_mass
		/// </summary>
		scs_float_t job_cargo_mass;

		/// <summary>
		/// Represents the current job's cargo unit mass.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_cargo_unit_mass
		/// </summary>
		scs_float_t job_cargo_unit_mass;

		/// <summary>
		/// Represents the current job's cargo unit count.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_cargo_unit_count
		/// </summary>
		scs_u32_t job_cargo_unit_count;

		/// <summary>
		/// Represents the current job's destination city id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_destination_city_id
		/// </summary>
		char job_destination_city_id[32];

		/// <summary>
		/// Represents the current job's destination city name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_destination_city
		/// </summary>
		char job_destination_city[32];

		/// <summary>
		/// Represents the current job's destination company id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_destination_company_id
		/// </summary>
		char job_destination_company_id[32];

		/// <summary>
		/// Represents the current job's destination company name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_destination_company
		/// </summary>
		char job_destination_company[32];

		/// <summary>
		/// Represents the current job's source city id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_source_city_id
		/// </summary>
		char job_source_city_id[32];

		/// <summary>
		/// Represents the current job's source city name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_source_city
		/// </summary>
		char job_source_city[32];

		/// <summary>
		/// Represents the current job's source company id.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_source_company_id
		/// </summary>
		char job_source_company_id[32];

		/// <summary>
		/// Represents the current job's source company name in ingame language.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_source_company
		/// </summary>
		char job_source_company[32];

		/// <summary>
		/// Represents the current job's planned income.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_income
		/// </summary>
		scs_u64_t job_income;

		/// <summary>
		/// Represents the current job's planned delivery time.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_delivery_time
		/// </summary>
		scs_u32_t job_delivery_time;

		/// <summary>
		/// Represents the current job's planned distance.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_planned_distance_km
		/// </summary>
		scs_u32_t job_planned_distance_km;

		/// <summary>
		/// Represent if the job cargo is loaded on the trailer.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_is_cargo_loaded
		/// </summary>
		bool job_cargo_loaded;

		/// <summary>
		/// Represents the current job market.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_job_market
		/// </summary>
		char job_market[24];

		/// <summary>
		/// Represents wether the current job is a special job.
		/// SCS_TELEMETRY_CONFIG_ATTRIBUTE_special_job
		/// </summary>
		bool job_is_special_job;

	#pragma endregion

	} configs;
};