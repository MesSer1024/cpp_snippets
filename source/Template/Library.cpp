#include <template_lib/Library.h>
#include <memory>

namespace ddahlkvist
{
std::unique_ptr<Library> Library::_instance;

Library::Library() {}

void Library::createLibrary() {
	DD_ASSERT(_instance.get() == nullptr);

	_instance.reset(new Library());
}

void Library::destroyLibrary() {
	DD_ASSERT(_instance.get() != nullptr);
	_instance.reset(nullptr);
}

Library* Library::instance() {
	return _instance.get();
}

}