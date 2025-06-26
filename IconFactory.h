#pragma once
#pragma once
#include"Icon.h"
#include"BaseFactory.h"

class IconFactory : public BaseFactory<Icon> {
public:
	static IconFactory& Instance() {
		static IconFactory instance;
		return instance;
	}
private:
};