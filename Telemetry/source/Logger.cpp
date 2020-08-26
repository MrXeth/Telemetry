#include "../header/pch.h"
#include "../header/Logger.h"

Logger::Logger(scs_log_t gameLog)
{
	if (!gameLog) throw "GameLog is null!";
	this->gameLog = gameLog;
}

void Logger::log(const scs_log_type_t type, const char* const text, ...)
{
	char formatted[1024];
	va_list args;
	va_start(args, text);
	vsnprintf_s(formatted, sizeof(formatted) - 1, _TRUNCATE, text, args);
	va_end(args);
	gameLog(type, formatted);
}