#pragma once
#include"Character.h"
#include"BaseFactory.h"


class CharacterFactory : public BaseFactory<Character> {
public:
	static CharacterFactory& Instance() {
		static CharacterFactory instance;
		return instance;
	}
private:
};
