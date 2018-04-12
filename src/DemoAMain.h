#pragma once
#include "header.h"
#include "templates.h"
#include "BaseEngine.h"
class DemoAMain :
	public BaseEngine
{
public:
	DemoAMain();
	~DemoAMain();
	void SetupBackgroundBuffer();
	void MouseDown(int, int, int);
	void KeyDown(int);
	int InitialiseObjects();
};
