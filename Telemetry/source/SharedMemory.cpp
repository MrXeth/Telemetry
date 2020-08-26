#include "pch.h"
#include "SharedMemory.h"

SharedMemory::SharedMemory()
{
	state = nullptr;
	const DWORD size = sizeof(TelemetryState);
	handler = CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, size, "SCS_TELEMETRY");
	if (!handler) return;
	state = static_cast<TelemetryState*>(MapViewOfFile(handler, FILE_MAP_ALL_ACCESS, 0, 0, 0));
	if (!state) return;
	memset(state, 0, size);
	state->running = false;
}

SharedMemory::~SharedMemory()
{
	if (state) UnmapViewOfFile(state);
	if (handler) CloseHandle(handler);
}

HANDLE& SharedMemory::getHandler()
{
	return handler;
}

TelemetryState& SharedMemory::getState()
{
	return *state;
}
