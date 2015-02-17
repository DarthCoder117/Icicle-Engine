#ifndef GUIRENDERERBIND_H
#define GUIRENDERERBIND_H

#include <Rocket/Core/RenderInterface.h>


namespace ice 
{
	namespace gui
	{
		class GuiRendererBind : public Rocket::Core::RenderInterface
		{
		public:
			// Called by Rocket when it wants to enable or disable scissoring to clip content.
			virtual void EnableScissorRegion(bool enable);
			
			// Called by Rocket when it wants to change the scissor region.
			virtual void SetScissorRegion(int x, int y, int width, int height);
			
			// Called by Rocket when it wants to render geometry that the application does not wish to optimise.
			virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
			
			// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
			virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
			
			// Called by Rocket when it wants to render application-compiled geometry.
			virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
			
			// Called by Rocket when it wants to release application-compiled geometry.
			virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
		private:
			
		};
	}
}

#endif // GUIRENDERERBIND_H
