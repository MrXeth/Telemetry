#pragma once
#include "pch.h"

/// <summary>
/// Class encapsulating logger logic.
/// </summary>
class Logger
{
private:

	/// <summary>
	/// Reference to game log function.
	/// </summary>
	scs_log_t gameLog;
public:

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="gameLog">game log function</param>
	Logger(scs_log_t gameLog);
	
	/// <summary>
	/// Logs messages into the game log.
	/// </summary>
	/// <param name="type">log type</param>
	/// <param name="text">message</param>
	/// <param name="">arguments</param>
	void log(const scs_log_type_t type, const char* const text, ...);
};

