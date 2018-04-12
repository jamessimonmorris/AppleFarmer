#pragma once
#include "header.h"
#include "templates.h"
#include "DisplayableObject.h"
class DemoBObject2 :
	public DisplayableObject
{
public:
	DemoBObject2(BaseEngine*);
	~DemoBObject2();
	void Draw();
	void DoUpdate(int);
};

