#include "System.hpp"

using namespace std::literals;

const void* System::get_focus()
{
    return this->m_focus;
}

void System::set_focus(void* focus)
{
    this->m_focus = focus;
}

bool System::has_focus(const void* focus)
{
    return this->m_focus == focus;
}

time_t System::time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
