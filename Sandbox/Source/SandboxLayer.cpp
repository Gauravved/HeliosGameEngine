#include<SandboxLayer.h>


SandboxLayer::SandboxLayer()
    : Helios::Layer("Sandbox")
{

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
            // Position             // Colors
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // Red
		0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, // Green
		0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f  // Blue
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
        {Helios::ShaderDataType::Float3, "a_Position"},
        {Helios::ShaderDataType::Float3, "a_Color"}
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

void SandboxLayer::OnUpdate(Helios::TimeStep timeStep) {
    m_Shader->Bind();

    Helios::RenderCommand::DrawIndexed(m_VertexArray);
}