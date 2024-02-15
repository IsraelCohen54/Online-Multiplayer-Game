#include <istream>
#include "Reader.h"

namespace experis
{

/// ~~~~~~~~~ Ostream ~~~~~
IstreamReader::IstreamReader(std::istream& a_in)
: m_in{a_in}
{
}

void IstreamReader::ReadLine(std::string& a_untrust_input) const
{
	std::getline(this->m_in, a_untrust_input);
}

/// ~~~~~~~~~ Telnet ~~~~~

TelnetReader::TelnetReader(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_in)
: m_in{a_in}
{
}

void TelnetReader::ReadLine(std::string& a_untrust_input) const
{
    a_untrust_input = (*m_in.get()).ReadLine();
}

} // namespace experis