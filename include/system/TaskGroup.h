#ifndef TASK_GROUP_H
#define TASK_GROUP_H
#include "core/ThreadEvent.h"

namespace ice
{
	namespace core
	{
		///@brief The TaskGroup is used to synchronize a group of thread pool tasks.
		class TaskGroup
		{
		public:

			///@brief Add a future to wait on.
			void add(SharedPtr<ThreadEvent> evt)
			{
				m_events.push(evt);
			}

			///@brief Wait until all tasks in the group have completed.
			void join()
			{
				while (!m_events.empty())
				{
					m_events.front()->wait();
					m_events.pop();
				}
			}

		private:

			Queue<SharedPtr<ThreadEvent> > m_events;
		};
	}
}

#endif