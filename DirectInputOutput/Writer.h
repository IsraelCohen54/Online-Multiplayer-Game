#pragma once

#include <string>
#include <iosfwd>
#include "SimpleNetMT.h"

namespace experis
{

class Writer
{
public:
	explicit Writer() = default;
	Writer(const Writer& a_other) = delete;
	Writer& operator=(const Writer& a_other) = delete;
	virtual ~Writer() = default;

	virtual void Write(const std::string& a_text) = 0;
};

class OstreamWriter : public Writer
{
public:
	explicit OstreamWriter() = delete;
	explicit OstreamWriter(std::ostream& a_out);
	OstreamWriter(const OstreamWriter& a_other) = delete;
	OstreamWriter& operator=(const OstreamWriter& a_other) = delete;
	virtual ~OstreamWriter() = default;

	virtual void Write(const std::string& a_text) override;

private:
	std::ostream& m_out;
};

class TelnetWriter : public Writer
{
public:
	explicit TelnetWriter() = delete;
	explicit TelnetWriter(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_out);
	TelnetWriter(const TelnetWriter& a_other) = delete;
	TelnetWriter& operator=(const TelnetWriter& a_other) = delete;
	virtual ~TelnetWriter() = default;

	virtual void Write(const std::string& a_text) override;

private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_out;
};

} // experis