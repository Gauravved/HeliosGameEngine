#include<SandboxLayer.h>


SandboxLayer::SandboxLayer(float aspectRatio,const std::shared_ptr<Helios::SceneRenderer>& sceneRenderer)
    : Helios::Layer("Sandbox"), 
      m_CameraController(
          45.0f,        // FOV
          aspectRatio,
          0.1f,         // Near Clip
          1000.0f       // Far Clip
      ),
      m_SceneRenderer(sceneRenderer)
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

    

}

SandboxLayer::~SandboxLayer() {
    HL_INFO("SandboxLayer Destroyed");
}

void SandboxLayer::OnUpdate(Helios::TimeStep timeStep) {
    
    //HL_INFO("Delta Time: {} ms", timeStep.GetMilliSeconds());
    m_CameraController.OnUpdate(timeStep);

    glm::mat4 viewProjection = m_CameraController.GetCamera().GetViewProjectionMatrix();

    m_SceneRenderer->Render(viewProjection);

 

}

void SandboxLayer::OnEvent(Helios::Event& event) {
    m_CameraController.OnEvent(event);
}