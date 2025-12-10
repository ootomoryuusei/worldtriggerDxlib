#pragma once
#include "Object2D.h"
class OkButton :
    public Object2D
{
public:
	OkButton(GameObject* parent);
	~OkButton();
	void Update() override;
	void Draw() override;

	void DeviceEvent(const DoubleClickEvent& event) override;
	void updateCSVRow(const string& filename, int targetRow, const string& newData);
private:
};

