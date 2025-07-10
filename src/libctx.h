#pragma once

#include <bluec/bluec.h>
#include "adapter.h"
#include "adapterlist.h"
#include "common.h"

#include <memory>

namespace BlueC
{

class BlueCTX
{
	AdapterList adapterList;
	Glib::RefPtr<GDBus::Proxy> bluezObjManager;
	Glib::RefPtr<Glib::MainLoop> mainLoop;


	void initMainLoop();
	void initObjectManager();
	void updateObjectList();

	void processAdapter(const std::string& path, const Glib::VariantContainerBase& ifaces);

	void onSignal(const Glib::ustring& sender, const Glib::ustring& signal, const Glib::VariantContainerBase& params);

public:
	BlueCTX(bool runMainLoop);
	~BlueCTX();
};

std::shared_ptr<BlueCTX> getCTX();
void allocCTX(bool runMainLoop);
void deallocCTX();

} // namespace BlueC
