#include<SandboxLayer.h>
#include<Helios/Renderer/Shader.h>
#include<Helios/Renderer/Buffer/VertexArray.h>
#include<Helios/Renderer/Buffer/VertexBuffer.h>
#include<Helios/Renderer/Buffer/IndexBuffer.h>
#include<Helios/Renderer/Buffer/BufferLayout.h>
#include<Helios/Core/Base.h>
#include<Helios/Renderer/RenderCommand.h>

SandboxLayer::SandboxLayer() {

    /*This is not three points on your monitor.
     These are three points in Normalized Device Coordinates(NDC).

                 (0, 1)
                    ?
                    ?
         (-1, 0) ???????(1, 0)
                    ?
                    ?
                 (0, -1)

     OpenGL expects coordinates in the range :

            X: -1 ? 1
            Y : -1 ? 1
            Z : -1 ? 1
     So - 0.5f, -0.5f, 0.0f means Bottom Left
     Second vertex 0.5f, -0.5f, 0.0f means Bottom Right
     Third vertex 0.0f, 0.5f, 0.0f means Top Middle*/

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

    // Instead of duplicating vertex data, we reference existing vertices.
    Helios::uint32 indices[] = {
        0, 1, 2
    };

    // Create Vertex Buffer
    m_VertexBuffer = Helios::VertexBuffer::Create(vertices, sizeof(vertices));

    // Crewate Index Buffer
    m_IndexBuffer = Helios::IndexBuffer::Create(indices, sizeof(indices) / sizeof(Helios::uint32));

    // Create VertexArray (empty)
    m_VertexArray = Helios::VertexArray::Create();

    Helios::BufferLayout layout = {
        {Helios::ShaderDataType::Float3, "a_Position"}
    };
    
    m_VertexBuffer->SetLayout(layout);

    //Add VertexBuffer to VertexArray
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    //Attach Index Buffer
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    //Create Shader for vertex and fragment
    m_Shader = Helios::Shader::Create(
        "Assets/Shaders/Basic.vert",
        "Assets/Shaders/Basic.frag"
    );


}

SandboxLayer::~SandboxLayer() {

}

void SandboxLayer::OnUpdate() {
    m_Shader->Bind();

    Helios::RenderCommand::DrawIndexed(m_VertexArray);
}