#pragma once

#include <template_lib/template_lib_module.h>
#include <template_lib/Types.h>
#include <memory>

namespace ddahlkvist
{
	class Library
	{
	public:
		TEMPLATE_PUBLIC static void createLibrary();
		TEMPLATE_PUBLIC static void destroyLibrary();
		TEMPLATE_PUBLIC static Library* instance();
		~Library() = default;

	private:
		Library();
		static std::unique_ptr<Library> _instance;
	};
}