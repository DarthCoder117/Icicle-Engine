#ifndef UPDATE_EVENT_LISTENER_H
#define UPDATE_EVENT_LISTENER_H

namespace ice
{
	namespace core
	{
		///@brief Game logic/simulation update.
		class UpdateEventListener
		{
		public:

			virtual void update(){}

			virtual void finalize(){}
		};
	}
}

#endif