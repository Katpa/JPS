#pragma once

class TankScene : public Scene
{
public:
	TankScene();
	~TankScene();
		
	virtual void Update() override;
	virtual void Render() override;

private:
	GameTileMap* gameTileMap;
	Tank* tank;
	AStar* aStar;
	JPS* jps;

	bool isShowNode = false;
};