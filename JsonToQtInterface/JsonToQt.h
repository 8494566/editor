#ifndef JSONTOQT_H
#define JSONTOQT_H
#include "Interface/JsonToQtInterface.h"

class JsonToQt : public JsonToQtInterface
{
public:
	JsonToQt();
	~JsonToQt();

	void call(const char* var) override;
};
#endif