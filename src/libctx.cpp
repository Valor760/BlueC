#include "libctx.h"
#include "log.h"
#include "utils/utils.h"

#include <mutex>
#include <thread>

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
	Glib::init();

	// initMainLoop();
	initObjectManager();
	updateAdapterList();

	LOG_DEBUG("Init done");
}

BlueCTX::~BlueCTX()
{
	LOG_DEBUG("Deinit");
}

void BlueCTX::initObjectManager()
{
	bluezObjManager = GDBus::Proxy::create_for_bus_sync(
		GDBus::BusType::SYSTEM,
		Bluez::BusName,
		"/",
		Bluez::ObjectManager::Interface
	);

	if(!bluezObjManager)
	{
		LOG_ERROR("Failed to create BlueZ Object Manager");
		throw BLUEC_ERROR_INTERNAL; // TODO: Different error code
	}

	LOG_TRACE("Object manager created: %p", bluezObjManager.get());
}

void BlueCTX::initMainLoop()
{
	loopCtx = Glib::MainContext::create(Glib::MainContextFlags::OWNERLESS_POLLING);
	if(!loopCtx)
	{
		LOG_ERROR("Failed to create MainLoop Context");
		throw BLUEC_ERROR_INTERNAL; // TODO: Different error code
	}
	LOG_TRACE("Loop Context created: %p", loopCtx.get());

	mainLoop = Glib::MainLoop::create(loopCtx, true);
	if(!mainLoop)
	{
		LOG_ERROR("Failed to create MainLoop");
		throw BLUEC_ERROR_INTERNAL; // TODO: Different error code
	}
	LOG_TRACE("MainLoop created: %p", mainLoop.get());
}

void BlueCTX::updateAdapterList()
{
	auto result = bluezObjManager->call_sync(Bluez::ObjectManager::Methods::GetObjects);

	Glib::VariantContainerBase objects;
	result.get_child(objects);

	for(size_t i = 0; i < objects.get_n_children(); i++)
	{
		Glib::VariantContainerBase obj;
		objects.get_child(obj, i);

		LOG_ERROR("i=%lu num children=%lu", i, obj.get_n_children());
		BLUEC_ASSERT(obj.get_n_children() == 2);

		Glib::Variant<std::string> path;
		obj.get_child(path, 0);
		LOG_ERROR("i=%lu path=%s", i, path.get().c_str());

		Glib::VariantContainerBase ifaceDict;
		obj.get_child(ifaceDict, 1);

		for(size_t j = 0; j < ifaceDict.get_n_children(); j++)
		{
			Glib::VariantContainerBase dictEntry;
			ifaceDict.get_child(dictEntry, j);

			Glib::Variant<std::string> iface;
			Glib::VariantContainerBase properties;
			dictEntry.get_child(iface, 0);
			dictEntry.get_child(properties, 1);

			LOG_ERROR("j=%lu children=%lu iface=%s", j, properties.get_n_children(), iface.get().c_str());
			if(true)//iface.get() == "org.bluez.Adapter1" || iface.get() == "org.bluez.NetworkServer1")
			{
				for(size_t k = 0; k < properties.get_n_children(); k++)
				{
					Glib::VariantContainerBase property;
        			properties.get_child(property, k);
					Glib::Variant<std::string> propertyName;
					Glib::VariantContainerBase propertyValue;
					property.get_child(propertyName, 0);
					property.get_child(propertyValue, 1);
					Glib::Variant<std::string> variant;
					propertyValue.get_child(variant);
					LOG_ERROR("k=%lu propname=%s value=%s", k, propertyName.get().c_str(), variant.get().c_str());
				}
			}
			// if (iface.get() != Device::Interface)
			// 	continue;

			// std::string device_address;
			// std::string device_path = path.get();
			// std::string device_alias;
			// get_property_value(properties, Bluez::Device::Properties::Address, device_address);
			// get_property_value(properties, Bluez::Device::Properties::Alias, device_alias);

			// _addressToDeviceMap.insert(std::pair<std::string, DeviceEntry>(device_address, {device_path, device_alias}));
			// _pathToAddressMap.insert(std::pair<std::string, std::string>(device_path, device_address));
		}
	}
}

} // namespace BlueC