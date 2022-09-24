#include "GContainer.hpp"

Container::Container() :
	m_compounds()
{
}

Container::Container(std::vector<Component*> components) :
	m_compounds(components)
{
}

void Container::addComponent(Component* component)
{
	this->m_compounds.push_back(component);
}

void Container::removeComponent(Component* component)
{
	this->m_compounds.erase(std::find(std::begin(this->m_compounds), std::end(this->m_compounds), component));
}

void Container::clear()
{
	this->m_compounds.clear();
}

const std::vector<Component*>& Container::getComponents() const
{
	return this->m_compounds;
}
