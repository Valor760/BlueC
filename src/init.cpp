#include <bluec/bluec.h>

#include <glibmm/refptr.h>
#include <giomm/dbusproxy.h>
#include <glibmm/variant.h>

// struct LibInit
// {
// 	GDBusConnection* conn = nullptr;
// 	GMainLoop* mainLoop = nullptr;
// 	bool initDone = false;
// 	std::thread mainLoopThread;
// };

// static LibInit g_Init;

// void bluez_list_controllers(GDBusConnection* con,
//     GAsyncResult* res,
//     gpointer data)
// {
//     GVariant* result = g_dbus_connection_call_finish(con, res, NULL);
//     if (result == NULL)
// 	{
//         printf("Unable to get result for GetManagedObjects\n");
// 		return;
// 	}

// 	result = g_variant_get_child_value(result, 0);
// 	GVariantIter i;
// 	g_variant_iter_init(&i, result);
// 	const gchar* object_path;
// 	GVariant* ifaces_and_properties;
// 	while (g_variant_iter_next(&i, "{&o@a{sa{sv}}}", &object_path, &ifaces_and_properties))
// 	{
// 		printf("Object path: %s\n", object_path);
// 	}
// 	printf("%s: exit\n", __func__);
// }

// static void mainLoopFunc()
// {
// 	g_main_loop_run(g_Init.mainLoop);
// }

int bluez_Init()
{
	// if(g_Init.initDone)
	// {
	// 	// TODO: Logging
	// 	printf("Init already done!\n");
	// 	return -1;
	// }

	// g_Init.mainLoop = g_main_loop_new(NULL, FALSE);
	// g_Init.mainLoopThread = std::thread(mainLoopFunc);

	// g_Init.conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

	// g_dbus_connection_call(g_Init.conn,
	// 	"org.bluez",
	// 	"/",
	// 	"org.freedesktop.DBus.ObjectManager",
	// 	"GetManagedObjects",
	// 	NULL,
	// 	G_VARIANT_TYPE("(a{oa{sa{sv}}})"),
	// 	G_DBUS_CALL_FLAGS_NONE,
	// 	-1,
	// 	NULL,
	// 	(GAsyncReadyCallback)bluez_list_controllers,
	// 	NULL);

	// sleep(5);

	// g_Init.initDone = true;
	// return 0;
}

void bluez_DeInit()
{
	// if(!g_Init.initDone)
	// {
	// 	printf("No init was done!\n");
	// 	return;
	// }

	// g_main_loop_quit(g_Init.mainLoop);
	// if(g_Init.mainLoopThread.joinable())
	// {
	// 	g_Init.mainLoopThread.join();
	// }
	// g_Init.mainLoop = nullptr;

	// g_Init.initDone = false;
}