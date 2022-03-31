#pragma once

namespace ddahlkvist
{

#define MSVC_COMPILER 1 // #TODO : offer support for a non-hardcoded MSVC-setting

#if defined(MSVC_COMPILER)
#define IMPORT_DLL __declspec(dllimport)
#define EXPORT_DLL __declspec(dllexport)
#else
#define IMPORT_DLL __attribute__ ((visibility("default")))
#define EXPORT_DLL __attribute__ ((visibility("default")))
#endif

#if defined(BUILD_COMPILE_DLL)
#if defined(BUILD_TEMPLATE_EXPORT)
#define TEMPLATE_PUBLIC EXPORT_DLL
#else
#define TEMPLATE_PUBLIC IMPORT_DLL
#endif
#else
#define TEMPLATE_PUBLIC
#endif

#if defined(BUILD_TEMPLATE_INTERNAL_ACCESS) || defined(BUILD_TEMPLATE_EXPORT)
#define TEMPLATE_INTERNAL TEMPLATE_PUBLIC
#else
#define TEMPLATE_INTERNAL
#endif

}