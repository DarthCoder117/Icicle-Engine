#include "system/ThreadPool.h"

using namespace ice;
using namespace system;

Task::Task(sf::Thread task, LTaskPriority priority) : m_thread(task), m_priority(priority)
{
}
bool Task::operator()(Task& t1, Task& t2)
{
	return t1.m_priority < t2.m_priority;
}
