#include "Framework.h"

#include "Scenes/TankScene.h"
#include "Scenes/DijkstraScene.h"

GameManager::GameManager()
{
	Create();

	scene = new TankScene();
	//scene = new DijkstraScene();
}

GameManager::~GameManager()
{
	delete scene;

	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();
	FX->Update();
	Audio::Get()->Update();

	scene->Update();

	CAM->Update();
}

void GameManager::Render()
{
	scene->PreRender();

	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	Device::Get()->SetRenderTarget();
	Environment::Get()->SetViewPort();
	Environment::Get()->SetOrtographic();

	scene->Render();
	FX->Render();

	CAM->RenderUI();
	Environment::Get()->SetUIView();
	scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Device::Get();
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	EffectManager::Get();
	Audio::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
	Device::Delete();
	Keyboard::Delete();
	Timer::Delete();
	Environment::Delete();
	EffectManager::Delete();
	Audio::Delete();

	Texture::Delete();
	Shader::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
