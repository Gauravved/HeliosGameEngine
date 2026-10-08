#include<glm/ext/matrix_transform.hpp>
#include<Helios/Renderer/SceneRenderer/SceneRenderer.h>
#include<Helios/Renderer/RenderCommand.h>

namespace Helios {
	SceneRenderer::SceneRenderer(uint32 width, uint32 height)
		: m_FrameBuffer(FrameBuffer::Create(width, height))
	{
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
        uint32 indices[] = {
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
        uint32 cubeBorderIndices[] = {
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
        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        // Crewate Index Buffer
        m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32));

        // Create VertexArray (empty)
        m_VertexArray = VertexArray::Create();

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Color"}
        };

        m_VertexBuffer->SetLayout(layout);

        //Add VertexBuffer to VertexArray
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        //Attach Index Buffer
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        //Create Shader for vertex and fragment
        m_Shader = Shader::Create(
            "Assets/Shaders/Basic.vert",
            "Assets/Shaders/Basic.frag"
        );

        m_BorderVertexArray = VertexArray::Create();
        m_BorderVertexBuffer = VertexBuffer::Create(cubeBorderVertices, sizeof(cubeBorderVertices));
        m_BorderIndexBuffer = IndexBuffer::Create(cubeBorderIndices, sizeof(cubeBorderIndices) / sizeof(uint32));
        m_BorderVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Color"}
            });

        m_BorderVertexArray->SetIndexBuffer(m_BorderIndexBuffer);
        m_BorderVertexArray->AddVertexBuffer(m_BorderVertexBuffer);


        // GRID lines
        std::vector<float> gridVertices;
        std::vector<uint32> gridIndices;

        const int gridSize = 50;
        const float gridSpacing = 1.0f;

        uint32 vertexIndex = 0;
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

        m_GridVertexArray = VertexArray::Create();

        m_GridVertexBuffer = VertexBuffer::Create(
            gridVertices.data(),
            static_cast<uint32>(gridVertices.size() * sizeof(float))
        );

        m_GridVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Color" }
            });

        m_GridVertexArray->AddVertexBuffer(m_GridVertexBuffer);

        m_GridIndexBuffer = IndexBuffer::Create(
            gridIndices.data(),
            static_cast<uint32>(gridIndices.size())
        );

        m_GridVertexArray->SetIndexBuffer(m_GridIndexBuffer);

        m_GridShader = Shader::Create(
            "Assets/Shaders/Grid.vert",
            "Assets/Shaders/Grid.frag"
        );
	}
	
	void SceneRenderer::Render(const glm::mat4& viewProjection) {
		// Bind the scene framebuffer so all rendering commands target
		// the off-screen framebuffer instead of the application window.
		m_FrameBuffer->Bind();

		// Clear the framebuffer before rendering the scene.
		// This clears both the color and depth attachments.
		RenderCommand::Clear();

		//Will move scene here next
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
        RenderCommand::DrawLines(m_GridVertexArray);

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
            RenderCommand::DrawIndexed(m_VertexArray);
        }

        // =========================================
        // Border Cubes
        // =========================================
        m_GridShader->Bind();
        m_GridShader->SetMat4("u_ViewProjection", viewProjection);
        for (const auto position : m_CubePositions) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
            m_GridShader->SetMat4("u_Model", model);
            RenderCommand::DrawLines(m_BorderVertexArray);
        }

		// Restore the default window framebuffer after the scene has finished
		// rendering into the off-screen framebuffer.
		m_FrameBuffer->Unbind();
	}

	void SceneRenderer::Resize(uint32 width, uint32 height) {
		m_FrameBuffer->Resize(width, height);
	}
}