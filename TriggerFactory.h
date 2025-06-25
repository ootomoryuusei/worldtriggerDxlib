#pragma once
#include"Trigger.h"
#include"BaseFactory.h"

class TriggerFactory : public BaseFactory<Trigger> {
public:
	static TriggerFactory& Instance() {
		static TriggerFactory instance;
		return instance;
	}
private:
};