#ifndef JSONTOQTINTERFACE_H
#define JSONTOQTINTERFACE_H
#include "LibraryManagers/Plugin/Plugin.h"

class JsonToQtInterface : public Plugin
{
public:
	virtual void call(const char*) = 0;
};
#endif