#pragma once

#include <bluec/bluec.h>

#include <memory>

namespace BlueC
{

class BlueCTX
{
public:
	BlueCTX();
	~BlueCTX();
};

std::shared_ptr<BlueCTX> getCTX();
void allocCTX();
void deallocCTX();

} // namespace BlueC
