#pragma once

#include <windows.h>
#include <dbghelp.h>

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo);
