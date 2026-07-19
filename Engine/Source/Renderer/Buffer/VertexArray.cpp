#include<Helios/Renderer/Buffer/VertexArray.h>
#include<Helios/Renderer/Buffer/OpenGLVertexArray.h>

namespace Helios {
	std::shared_ptr<VertexArray> VertexArray::Create() {
		return std::make_shared<OpenGLVexterArray>();
	}
}