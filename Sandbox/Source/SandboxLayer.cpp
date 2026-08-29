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

    // CUBE: LOCAL space 
    float vertices[] = {
        // Position                  // Color

        // Front face
        -0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,        0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 0.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        0.5f, 0.5f, 0.5f
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

    // CUBE: borders local space
    float cubeBorderVertices[] = {
        // Position                 // Color

        // Front face corners
        -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,

        // Back face corners
        -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f
    };

    // INDICES for borders
    Helios::uint32 cubeBorderIndices[] = {
        // Front face
        0, 1,
        1, 2,
        2, 3,
        3, 0,

        // Back face
        4, 5,
        5, 6,
        6, 7,
        7, 4,

        // Connect front and back
        0, 4,
        1, 5,
        2, 6,
        3, 7
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

    m_BorderVertexArray = Helios::VertexArray::Create();
    m_BorderVertexBuffer = Helios::VertexBuffer::Create(cubeBorderVertices, sizeof(cubeBorderVertices));
    m_BorderIndexBuffer = Helios::IndexBuffer::Create(cubeBorderIndices, sizeof(cubeBorderIndices) / sizeof(Helios::uint32));
    m_BorderVertexBuffer->SetLayout({
        {Helios::ShaderDataType::Float3, "a_Position"},
        {Helios::ShaderDataType::Float3, "a_Color"}
        });
    
    m_BorderVertexArray->SetIndexBuffer(m_BorderIndexBuffer);
    m_BorderVertexArray->AddVertexBuffer(m_BorderVertexBuffer);


    // GRID lines
    std::vector<float> gridVertices;
    std::vector<Helios::uint32> gridIndices;

    const int gridSize = 50;
    const float gridSpacing = 1.0f;

    Helios::uint32 vertexIndex = 0;
    const glm::vec3 gridColor(0.35f, 0.35f, 0.35f);

    // Lines parallel to Z
    for (int i = -gridSize; i <= gridSize; ++i) {
        float x = i * gridSpacing;

        // Starting Point
        gridVertices.push_back(x);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(-gridSize * gridSpacing);

        gridVertices.push_back(gridColor.r);
        gridVertices.push_back(gridColor.g);
        gridVertices.push_back(gridColor.b);

        // Ending point
        gridVertices.push_back(x);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(gridSize * gridSpacing);

        gridVertices.push_back(gridColor.r);
        gridVertices.push_back(gridColor.g);
        gridVertices.push_back(gridColor.b);

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // X axis
        gridVertices.insert(gridVertices.end(), {
            -50.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             50.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // Y axis
        gridVertices.insert(gridVertices.end(), {
            0.0f, -50.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f,  50.0f, 0.0f,   0.0f, 1.0f, 0.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // Z axis
        gridVertices.insert(gridVertices.end(), {
            0.0f, 0.0f, -50.0f,   0.0f, 0.0f, 1.0f,
            0.0f, 0.0f,  50.0f,   0.0f, 0.0f, 1.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

    }

    // Lines parallel to X
    for (int i = -gridSize; i <= gridSize; ++i) {
        float z = i * gridSpacing;

        // Starting Point
        gridVertices.push_back(-gridSize * gridSpacing);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(z);

        gridVertices.push_back(gridColor.r);
        gridVertices.push_back(gridColor.g);
        gridVertices.push_back(gridColor.b);

        // Ending point
        gridVertices.push_back(gridSize * gridSpacing);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(z);

        gridVertices.push_back(gridColor.r);
        gridVertices.push_back(gridColor.g);
        gridVertices.push_back(gridColor.b);

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // X axis
        gridVertices.insert(gridVertices.end(), {
            -50.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             50.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // Y axis
        gridVertices.insert(gridVertices.end(), {
            0.0f, -50.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f,  50.0f, 0.0f,   0.0f, 1.0f, 0.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

        // Z axis
        gridVertices.insert(gridVertices.end(), {
            0.0f, 0.0f, -50.0f,   0.0f, 0.0f, 1.0f,
            0.0f, 0.0f,  50.0f,   0.0f, 0.0f, 1.0f
            });

        gridIndices.push_back(vertexIndex++);
        gridIndices.push_back(vertexIndex++);

    }

    m_GridVertexArray = Helios::VertexArray::Create();

    m_GridVertexBuffer = Helios::VertexBuffer::Create(
        gridVertices.data(),
        static_cast<Helios::uint32>(gridVertices.size() * sizeof(float))
    );

    m_GridVertexBuffer->SetLayout({
        { Helios::ShaderDataType::Float3, "a_Position" },
        { Helios::ShaderDataType::Float3, "a_Color" }
    });

    m_GridVertexArray->AddVertexBuffer(m_GridVertexBuffer);

    m_GridIndexBuffer = Helios::IndexBuffer::Create(
        gridIndices.data(),
        static_cast<Helios::uint32>(gridIndices.size())
    );

    m_GridVertexArray->SetIndexBuffer(m_GridIndexBuffer);

    m_GridShader = Helios::Shader::Create(
        "Assets/Shaders/Grid.vert",
        "Assets/Shaders/Grid.frag"
    );

}

SandboxLayer::~SandboxLayer() {

}

void SandboxLayer::OnUpdate(Helios::TimeStep timeStep) {
    //HL_INFO("Delta Time: {} ms", timeStep.GetMilliSeconds());
    m_CameraController.OnUpdate(timeStep);

    glm::mat4 viewProjection = m_CameraController.GetCamera().GetViewProjectionMatrix();

    // ==========================================
    // Grid & World Axes
    // ==========================================
    // Render Grid
    m_GridShader->Bind();

    // Give the grid shader in current camera matrix
    m_GridShader->SetMat4(
        "u_ViewProjection",
        viewProjection
    );

    m_GridShader->SetMat4(
        "u_Model",
        glm::mat4(1.0f)
    );

    // Draw the indexed Grid
    Helios::RenderCommand::DrawLines(m_GridVertexArray);

    // ========================================
    // Cube
    // ========================================
    m_Shader->Bind();

    // SetCamera ViewProjection in Shader
    m_Shader->SetMat4("u_ViewProjection", viewProjection);

    // Identity model matrix = object stays at it's original position
    for (const auto position : m_CubePositions) {
        glm::mat4 model = glm::translate(
            glm::mat4(1.0f),
            position
        );

        m_Shader->SetMat4("u_Model", model);
        Helios::RenderCommand::DrawIndexed(m_VertexArray);
    }

    // =========================================
    // Border Cubes
    // =========================================
    m_GridShader->Bind();
    m_GridShader->SetMat4("u_ViewProjection", viewProjection);
    for (const auto position : m_CubePositions) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        m_GridShader->SetMat4("u_Model", model);
        Helios::RenderCommand::DrawLines(m_BorderVertexArray);
    }

}

void SandboxLayer::OnEvent(Helios::Event& event) {
    m_CameraController.OnEvent(event);
}