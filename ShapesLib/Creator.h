#pragma once

#include <vector>
#include <string>

namespace experis
{
class Group;

class Creator
{

public:
	Creator() = default;
	Creator(const Creator& a_other) = delete;
	Creator& operator=(const Creator& a_other) = delete;
	virtual ~Creator() = default;

	virtual void CreateShape(experis::Group& a_group, const std::vector<std::string>& a_values) const = 0;
	inline void AddShape(){} //Todo ask what usage? + change inline after correct implementation! ______ ????????????????????????????????
};

} // experis namespace