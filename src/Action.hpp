#ifndef ACTION_HPP
#define ACTION_HPP

#include<vector>
#include<map>

class Action {
public:
	virtual void operator()() = 0;
};

class FoncAction : public Action {
public:
	FoncAction(void (*fonction)() = NULL);
	virtual void operator()();
private:
	void (*m_fonc)();
};

class ActionsManager {
public:
	ActionsManager();
	void addAction(Action* act, uint8_t type = 0);
	void removeAction(const Action* act, uint8_t type = 0);
protected:
	void execute(uint8_t type);
private:
	std::map<uint8_t, std::vector<Action*>> m_actions;
};

#endif // !ACTION_HPP
