#pragma once
#include "TelemetryState.h"

/// <summary>
/// Class providing actions for a shared memory mapped file.
/// </summary>
class SharedMemory
{
private:

	/// <summary>
	/// shared memory handler
	/// </summary>
	HANDLE handler;

	/// <summary>
	/// reference to a shared memory TelemetryState object
	/// </summary>
	TelemetryState* state;

public:

	/// <summary>
	/// Constructor
	/// </summary>
	SharedMemory();
	
	/// <summary>
	/// Destructor
	/// </summary>
	~SharedMemory();

	/// <summary>
	/// Gets the shared memory handler.
	/// </summary>
	/// <returns>Shared Memory handler</returns>
	HANDLE& getHandler();

	/// <summary>
	/// Gets a pointer to a shared memory TelemetryState object.
	/// </summary>
	/// <returns>pointer to a shared memory TelemetryState object</returns>
	TelemetryState& getState();
};
