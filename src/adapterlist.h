#pragma once

#include "adapter.h"

#include <vector>
#include <memory>
#include <mutex>
#include <string>

namespace BlueC
{

class AdapterList
{
	std::mutex listLock;
	std::vector<std::shared_ptr<Adapter>> list;

public:
	AdapterList();
	~AdapterList();

	void insertOrUpdate(const std::string& dev, const std::string& addr, const std::string& path, const std::string& alias);
};

} // namespace BlueC