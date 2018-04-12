#pragma once
#include "header.h"
#include "templates.h"
#include "DisplayableObject.h"
class DemoBObject :
	public DisplayableObject
{
public:
	DemoBObject(BaseEngine* pEngine);
	~DemoBObject();
	void Draw();
	void DoUpdate(int);
};
