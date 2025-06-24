#include "adapterlist.h"
#include "log.h"

namespace BlueC
{

AdapterList::AdapterList()
{
	
}

AdapterList::~AdapterList()
{
	// Ensure we wait until all parallel operations are done
	std::lock_guard lg(listLock);
}

void AdapterList::insertOrUpdate(const std::string& dev, const std::string& addr, const std::string& path, const std::string& alias)
{
	std::lock_guard lg(listLock);
}

} // namespace BlueC