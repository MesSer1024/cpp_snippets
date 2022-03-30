#pragma once

namespace ddahlkvist
{

#define MSVC_COMPILER 1

#if defined(MSVC_COMPILER)
#define IMPORT_DLL __declspec(dllimport)
#define EXPORT_DLL __declspec(dllexport)
#else
#define IMPORT_DLL __attribute__ ((visibility("default")))
#define EXPORT_DLL __attribute__ ((visibility("default")))
#endif

#if defined(BUILD_COMPILE_DLL)
#if defined(BUILD_EXPORT_PREVIMPL_MODULE)
#define PREVIMPL_PUBLIC EXPORT_DLL
#else
#define PREVIMPL_PUBLIC IMPORT_DLL
#endif
#else
#define PREVIMPL_PUBLIC
#endif

#if defined(BUILD_INTERNAL_ACCESS_PREVIMPL_MODULE) || defined(BUILD_EXPORT_PREVIMPL_MODULE)
#define PREVIMPL_INTERNAL PREVIMPL_PUBLIC
#else
#define PREVIMPL_INTERNAL
#endif

	namespace previmpl
	{
		PREVIMPL_PUBLIC void executePrevimpl();
	}
}