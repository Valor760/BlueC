#include "libctx.h"
#include "log.h"
#include "utils/utils.h"

#include <mutex>
#include <thread>
#include <map>

namespace BlueC
{

enum class ObjectType
{
	UNKNOWN,
	ADAPTER,
	DEVICE,
};

static const std::map<std::string, ObjectType> g_IfaceObjectMap = {
	{Bluez::Adapter::Interface, ObjectType::ADAPTER},
	{Bluez::Device::Interface, ObjectType::DEVICE},
};

static std::shared_ptr<BlueCTX> g_CTX = nullptr;
static std::mutex ctxLock;

std::shared_ptr<BlueCTX> getCTX()
{
	std::lock_guard lg(ctxLock);
	return g_CTX;
}

void allocCTX(bool runMainLoop)
{
	std::lock_guard lg(ctxLock);
	if(g_CTX)
	{
		LOG_ERROR("Library context is already initialized!");
		throw BLUEC_ERROR_ALREADY_INIT;
	}

	g_CTX = std::make_shared<BlueCTX>(runMainLoop);
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

static ObjectType getObjectType(const Glib::VariantContainerBase& interfaceArr)
{
	for(gsize i = 0; i < interfaceArr.get_n_children(); i++)
	{
		Glib::VariantContainerBase entry;
		interfaceArr.get_child(entry, i);

		Glib::Variant<std::string> iface;
		entry.get_child(iface, 0);

		const auto it = g_IfaceObjectMap.find(iface.get());
		if(it != std::end(g_IfaceObjectMap))
		{
			return it->second;
		}
	}

	return ObjectType::UNKNOWN;
}

BlueCTX::BlueCTX(bool runMainLoop)
{
	LOG_DEBUG("Init");
	Glib::init();

	if(runMainLoop)
	{
		initMainLoop();
	}

	initObjectManager();
	updateObjectList();
	
	bluezObjManager->signal_signal().connect(sigc::mem_fun(*this, &BlueCTX::onSignal));

	LOG_DEBUG("Init done");
}

BlueCTX::~BlueCTX()
{
	LOG_DEBUG("Deinit");

	if(mainLoop)
	{
		mainLoop->quit();
	}
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
	mainLoop = Glib::MainLoop::create();
	if(!mainLoop)
	{
		LOG_ERROR("Failed to create MainLoop");
		throw BLUEC_ERROR_INTERNAL; // TODO: Different error code
	}
	LOG_TRACE("MainLoop created: %p", mainLoop.get());

	std::thread th([this](){
		mainLoop->run();
	});
	th.detach();
}

void BlueCTX::updateObjectList()
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

		auto objType = getObjectType(ifaceDict);
		switch(objType)
		{
			case ObjectType::ADAPTER:
				break;

			case ObjectType::DEVICE:
				break;

			case ObjectType::UNKNOWN:
				[[fallthrough]];
			default:
				LOG_DEBUG("UNKNOWN object at %s path", path.get().c_str());
				break;
		}

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

void BlueCTX::onSignal(const Glib::ustring& sender, const Glib::ustring& signal, const Glib::VariantContainerBase& params)
{
	Glib::Variant<std::string> path;
	params.get_child(path, 0);

	LOG_DEBUG("ObjManager event: sender=%s signal=%s path=%s", sender.c_str(), signal.c_str(), path.get().c_str());
}

} // namespace BlueC