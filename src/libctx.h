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
	Glib::RefPtr<Glib::MainContext> loopCtx;
	Glib::RefPtr<Glib::MainLoop> mainLoop;


	void initMainLoop();
	void initObjectManager();
	void updateAdapterList();

public:
	BlueCTX();
	~BlueCTX();
};

std::shared_ptr<BlueCTX> getCTX();
void allocCTX();
void deallocCTX();

} // namespace BlueC
