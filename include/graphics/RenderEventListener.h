#ifndef RENDER_EVENT_LISTENER_H
#define RENDER_EVENT_LISTENER_H

namespace ice
{
	namespace graphics
	{
		enum RENDERING_STAGE
		{
			RS_SHADOW_PASS,
			RS_OBJECT_RENDER,
			RS_POST_PROCESS,
			RS_OVERLAY
		};

		class RenderEventListener
		{
		public:

			virtual void render(RENDERING_STAGE stage) = 0;
		};
	}
}

#endif