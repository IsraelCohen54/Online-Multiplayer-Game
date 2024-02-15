#pragma once

#include <string>
#include <iosfwd>
#include "SimpleNetMT.h"

namespace experis
{

class Reader
{
public:
	explicit Reader() = default;
	Reader(const Reader& a_other) = delete;
	Reader& operator=(const Reader& a_other) = delete;
	virtual ~Reader() = default;

	virtual void ReadLine(std::string& a_untrust_input) const = 0;
};

class IstreamReader : public Reader
{
public:
	explicit IstreamReader() = delete;
	explicit IstreamReader(std::istream& a_in);
	IstreamReader(const IstreamReader& a_other) = delete;
	IstreamReader operator=(const IstreamReader& a_other) = delete;
	virtual ~IstreamReader() override = default;

	virtual void ReadLine(std::string& a_untrust_input) const override;

private:
	std::istream& m_in;
};

class TelnetReader : public Reader
{
public:
	explicit TelnetReader() = delete;
	explicit TelnetReader(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_in);
	TelnetReader(const IstreamReader& a_other) = delete;
	TelnetReader operator=(const TelnetReader& a_other) = delete;
	virtual ~TelnetReader() override = default;

	virtual void ReadLine(std::string& a_untrust_input) const override;

private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_in;
};

} // namespace experis

