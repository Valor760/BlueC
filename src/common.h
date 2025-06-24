#pragma once

#include <glibmm/refptr.h>
#include <giomm/dbusproxy.h>
#include <glibmm/variant.h>
#include <glibmm/init.h>
#include <glibmm/main.h>

#include <string>

#define const_str static inline const std::string

namespace GDBus = Gio::DBus;

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

		} // namespace BlueC::Bluez::ObjectManager::Methods

	} // namespace BlueC::Bluez::ObjectManager

} // namespace BlueC::Bluez

#undef const_str
