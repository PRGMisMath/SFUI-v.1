#include "Action.hpp"
#include<algorithm>

FoncAction::FoncAction(void(*fonction)()) :
	m_fonc(fonction)
{
}

void FoncAction::operator()()
{
	if (this->m_fonc != NULL)
		this->m_fonc();
}

ActionsManager::ActionsManager() :
	m_actions()
{
}

void ActionsManager::addAction(Action* act, uint8_t type)
{
	this->m_actions[type].push_back(act);
}

void ActionsManager::removeAction(const Action* act, uint8_t type)
{
	this->m_actions[type].erase(std::find(this->m_actions[type].begin(), this->m_actions[type].end(), act));
}

void ActionsManager::execute(uint8_t type)
{
	for (Action* act : this->m_actions[type])
		(*act)();
}
