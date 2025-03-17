#pragma once
#include "Icon.h"
class OkButton :
    public Icon
{
public:
	OkButton(GameObject* parent);
	~OkButton();
	void Update() override;
	void Draw() override;
	void updateCSVRow(const string& filename, int targetRow, const string& newData);
private:
};

