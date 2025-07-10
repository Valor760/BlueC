#pragma once

#include <glibmm/refptr.h>
#include <giomm/dbusproxy.h>
#include <glibmm/variant.h>
#include <glibmm/init.h>
#include <glibmm/main.h>

#include <string>

#define const_str static inline const std::string

namespace GDBus = Gio::DBus;

// TODO: Maybe move these strings to related classes
namespace BlueC::Bluez
{
	const_str BusName = "org.bluez";
	const_str PathPrefix = "/org/bluez";

	namespace ObjectManager
	{
		const_str Interface = "org.freedesktop.DBus.ObjectManager";
		namespace Methods
		{
			const_str GetObjects = "GetManagedObjects";
		}
	}

	namespace Adapter
	{
		const_str Interface = "org.bluez.Adapter1";
	}

	namespace Device
	{
		const_str Interface = "org.bluez.Device1";
	}

} // namespace BlueC::Bluez

#undef const_str
