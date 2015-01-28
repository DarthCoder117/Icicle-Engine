#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <core/Uncopyable.h>
#include <vector>
#include <queue>
#include <SFML/System.hpp>

namespace ice
{
	namespace system
	{
		enum TaskPriority {
			LOWEST = 0, LOW = 1, NORMAL = 2, HIGH = 3, HIGHEST = 4
		};
		
		class Task 
		{
			Task(sf::Thread task, TaskPriority priority = NORMAL);		
			
			bool operator()(Task& t1, Task& t2);
		private:
			sf::Thread m_thread;
			TaskPriority m_priority;
		};
		
		class ThreadPool : core::Uncopyable
		{
		public:
			ThreadPool(uint16_t maxThreads);
			
			
		private:
			std::priority_queue m_taskQueue;
			std::vector<sf::Thread> m_threads;
		}
	}
}

#endif //THREADPOOL_H