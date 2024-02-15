#pragma once

#include <string>
#include "Action.h"

namespace experis
{

class Reader;

class TalkAction : public Action
{
public:
	explicit TalkAction() = delete;
	explicit TalkAction(Reader& a_reader);
	TalkAction(const TalkAction& a_other) = delete;
	TalkAction& operator=(const TalkAction& a_other) = delete;
	virtual ~TalkAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;

private:
	Reader& m_reader;
};

} // namespace experis

