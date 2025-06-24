#include "libctx.h"
#include "log.h"

#include <mutex>

namespace BlueC
{

static std::shared_ptr<BlueCTX> g_CTX = nullptr;
static std::mutex ctxLock;

std::shared_ptr<BlueCTX> getCTX()
{
	std::lock_guard lg(ctxLock);
	return g_CTX;
}

void allocCTX()
{
	std::lock_guard lg(ctxLock);
	if(g_CTX)
	{
		LOG_ERROR("Library context is already initialized!");
		throw BLUEC_ERROR_ALREADY_INIT;
	}

	g_CTX = std::make_shared<BlueCTX>();
}

void deallocCTX()
{
	std::lock_guard lg(ctxLock);
	if(!g_CTX)
	{
		LOG_DEBUG("Library context is not allocated - nothing to do");
		return;
	}

	// TODO: Check if this really might cause issues if we dereference here a ptr, but parallel thread is operating on it
	// Since a shared ptr is used - should be no issues, but main concern is when the init will be called right away
	// will the CTX allocated successfully again?
	if(g_CTX.use_count() > 1)
	{
		LOG_ERROR("Library context is used in parallel thread! Cannot dealloc");
		throw BLUEC_ERROR_INTERNAL;
	}

	g_CTX = nullptr;
}

BlueCTX::BlueCTX()
{
	LOG_DEBUG("Init");
}

BlueCTX::~BlueCTX()
{
	LOG_DEBUG("Deinit");
}

} // namespace BlueC