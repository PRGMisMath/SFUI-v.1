#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "GComponent.hpp"

class Container {
public:
	Container();
	explicit Container(std::vector<Component*> components);
	void addComponent(Component* component);
	void removeComponent(Component* component);
	void clear();
	const std::vector<Component*>& getComponents() const;
protected:
	std::vector<Component*> m_compounds;
};

#endif // !CONTAINER_HPP
