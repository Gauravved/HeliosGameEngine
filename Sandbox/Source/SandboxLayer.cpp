#include<SandboxLayer.h>


SandboxLayer::SandboxLayer(float aspectRatio)
    : Helios::Layer("Sandbox"), 
      m_CameraController(
          45.0f,        // FOV
          aspectRatio,
          0.1f,         // Near Clip
          1000.0f       // Far Clip
      )
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

	//float vertices[] = {
 //           // Position             // Colors
	//	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // Red
	//	0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, // Green
	//	0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f  // Blue
	//};

    // These are the same values with with respect to worldf space and 16:9 aspect ratio insted of 1:1 aspect ratio
    //float vertices[] = {
    //    // Position                 // Colors
    //    -0.5f, -0.288675f, -5.0f,    1.0f, 0.0f, 0.0f, // Red
    //     0.5f, -0.288675f, -5.0f,    0.0f, 1.0f, 0.0f, // Green
    //     0.0f,  0.577350f, -5.0f,    0.0f, 0.0f, 1.0f  // Blue
    //};

    // CUBE:
    float vertices[] = {
        // Position                  // Color

        // Front face
        -0.5f, -0.5f, -4.5f,        1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -4.5f,        0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -4.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -4.5f,        1.0f, 1.0f, 0.0f,

        // Back face
        -0.5f, -0.5f, -5.5f,        1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -5.5f,        0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -5.5f,        1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -5.5f,        0.5f, 0.5f, 0.5f
    };

    // Instead of duplicating vertex data, we reference existing vertices.
    Helios::uint32 indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Right
        1, 5, 6,
        6, 2, 1,

        // Back
        7, 6, 5,
        5, 4, 7,

        // Left
        4, 0, 3,
        3, 7, 4,

        // Top
        3, 2, 6,
        6, 7, 3,

        // Bottom
        4, 5, 1,
        1, 0, 4
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

    //HL_INFO("Delta Time: {} ms", timeStep.GetMilliSeconds());
    m_CameraController.OnUpdate(timeStep);

    m_Shader->Bind();

    // SetCamera ViewProjection in Shader
    m_Shader->SetMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

    Helios::RenderCommand::DrawIndexed(m_VertexArray);
}

void SandboxLayer::OnEvent(Helios::Event& event) {
    m_CameraController.OnEvent(event);
}