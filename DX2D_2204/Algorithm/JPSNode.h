#pragma once

#define DIR_N	Vector2( 0,  0)
#define DIR_U	Vector2( 0,  1)
#define DIR_D	Vector2( 0, -1)
#define DIR_L	Vector2(-1,  0)
#define DIR_R	Vector2( 1,  0)
#define DIR_UL	Vector2(-1,  1)
#define DIR_UR	Vector2( 1,  1)
#define DIR_DL	Vector2(-1, -1)
#define DIR_DR	Vector2( 1, -1)

class JPSNode
{
public:
	friend class JPS;

	enum State
	{
		NONE, OPEN, CLOSE, OBSTACLE, PATH
	};

public:
	JPSNode(Vector2 pos, POINT index, float radius = 10.0f);
	~JPSNode();

	void Render();

	void SetInit();

	void SetNode(JPSNode* parent, Vector2 dir);
	void SetCost();

	bool operator> (JPSNode* b) { return f > b->GetCost(); }
	bool operator< (JPSNode* b) { return f < b->GetCost(); }
	bool operator!= (JPSNode* b) { return !(pos == b->pos); }

	JPSNode*& Parent() { return parent; }
	void SetState(State state) { this->state = state; }
	State GetState() { return state; }
	void SetDirection(Vector2 dir) { this->dir = dir; }
	float GetCost() { return f; }
	Vector2 GetDirection() { return dir; }

private:
	Vector2 pos;

	//---------------------------------------------------
	// JPSNode node[index.x][index.y]
	//---------------------------------------------------
	POINT index = {0, 0};
	JPSNode* parent;

	//--------------------------------------
	// f = ���� �Ÿ�
	// g = ��������� ���� �������� �Ÿ�
	// h = ���� ������ ��ǥ�������� ���� �Ÿ�(����ź)
	//--------------------------------------
	float f = 0, g = 0, h = 0;

	State state;
	Vector2 dir;

	Collider* collider;
};