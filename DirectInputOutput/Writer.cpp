#include <ostream>
#include "Writer.h"

namespace experis
{

// ~~~~~ Derived OstreamWriter ~~~~~
OstreamWriter::OstreamWriter(std::ostream& a_out)
: m_out{a_out}
{
}

void OstreamWriter::Write(const std::string& a_text)
{
	this->m_out << a_text;
}

// ~~~~~ Derived TelnetWriter ~~~~~
TelnetWriter::TelnetWriter(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_out)
: m_out{a_out}
{
}

void TelnetWriter::Write(const std::string& a_text)
{
	(*m_out.get()).Write(a_text);
}

} // namespace experis