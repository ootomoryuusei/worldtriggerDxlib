#include "rader.h"

rader::rader(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//rader.png");
	/*position = { 1000, 20, 0 };*/
	canVisible_ = true;
}

rader::~rader()
{
}

void rader::Update()
{
}
