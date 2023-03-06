#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Hunter Wells - haw2048@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 30.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	//init the mesh
	m_uMeshCount = 46;
	for (uint i = 0; i < m_uMeshCount; ++i)
	{
		MyMesh* pMesh = new MyMesh();
		m_pMeshList.push_back(pMesh);
		m_pMeshList[i]->GenerateCube(1.0f, C_BLACK);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Create a model matrix out of the arcball quaternion
	matrix4 m4Model = ToMatrix4(m_qArcBall);

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f, 2.0f, 2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 0.0f));
	value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += static_cast<float>(m_pSystem->GetDeltaTime(uClock)); //get the delta time for that timer

	uint i = 0;
	static float fHorizontal = -10.0f;
	static vector3 v3Position(fHorizontal, 0.0f, 0.0f);

	v3Position.x =  fTimer;
	v3Position.y = 0;
	matrix4 m4Position = glm::translate(vector3(-5.0f, 0.0f, -15.0f)) * glm::translate(v3Position);


	//first row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, 0.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 0.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 0.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f, 0.0f, 0.0f))); ++i;

	//second row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, 1.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 1.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, 1.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f, 1.0f, 0.0f))); ++i;

	//third row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, 2.0f, 0.0f))); ++i;
	for (uint count = 2; count < 9; ++count)
	{
		m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(count, 2.0f, 0.0f))); ++i;
	}
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f, 2.0f, 0.0f))); ++i;

	//fourth row
	for (uint count = 0; count < 11; ++count)
	{
		m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(count, 3.0f, 0.0f))); ++i;
	}

	//fifth row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, 4.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(9.0f, 4.0f, 0.0f))); ++i;

	//sixth row
	for (uint count = 2; count < 9; ++count)
	{
		m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(count, 5.0f, 0.0f))); ++i;
	}

	//seventh row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3, 6.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7, 6.0f, 0.0f))); ++i;

	//eight row
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2, 7.0f, 0.0f))); ++i;
	m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8, 7.0f, 0.0f))); ++i;

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	std::vector<MyMesh*> m_pMeshList;
	uint uSize = m_pMeshList.size();
	for (uint i = 0; i < uSize; ++i)
	{
		if (m_pMeshList[i] != nullptr)
		{
			delete m_pMeshList[i];
			m_pMeshList[i] = nullptr;
		}
	}
	//release GUI
	ShutdownGUI();
}