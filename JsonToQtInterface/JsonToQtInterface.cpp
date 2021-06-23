#include "JsonToQt.h"

extern "C"
{
	JsonToQtInterface* g_interface = nullptr;
	Plugin* CreateInterface()
	{
		if (g_interface == nullptr)
		{
			g_interface = new JsonToQt;
		}
		return g_interface;
	}
	void ReleaseInterface()
	{
		if (g_interface)
		{
			delete g_interface;
			g_interface = nullptr;
		}
	}
};
