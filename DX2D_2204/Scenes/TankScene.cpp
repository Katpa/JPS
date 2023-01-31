#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
	gameTileMap = new GameTileMap("TextData/Stage1.map");
	gameTileMap->Position() = { 50, 50 };
	gameTileMap->Update();

	tank = new Tank();
	tank->Position() = { 150, 150 };
	tank->Update();

	aStar = new AStar(gameTileMap);
	jps = new JPS(gameTileMap);
}

TankScene::~TankScene()
{
	delete gameTileMap;
	delete tank;
	delete aStar;
	delete jps;
}

void TankScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		POINT start = jps->FindCloseNode(tank->Position());
		POINT end = jps->FindCloseNode(mousePos);

		jps->GetPath(start, end, tank->GetPath());

		/*int start = aStar->FindCloseNode(tank->Position());
		int end = aStar->FindCloseNode(mousePos);
		
		aStar->GetPath(start, end, tank->GetPath());	

		tank->GetPath().insert(tank->GetPath().begin(), mousePos);*/
	}

	if (KEY_UP(VK_TAB))
		isShowNode = !isShowNode;

	gameTileMap->Update();
	tank->Update();	

	aStar->Update();
}

void TankScene::Render()
{
	gameTileMap->Render();
	tank->Render();

	if (isShowNode)
	{
		//aStar->Render();
		jps->Render();
	}
}
