#include "Framework.h"

JPS::JPS(GameTileMap* map)
{
    map->GetNodes(nodes, mapSize);
    //SetEdge(map->GetWidth());

    openList = new JPSHeap();
}

JPS::~JPS()
{
    for (vector<JPSNode*>& vec : nodes)
    {
        for (JPSNode*& node : vec)
        {
            delete node;
        }

        vec.clear();
    }

    delete openList;
}

void JPS::Update()
{
}

void JPS::Render()
{
    for (vector<JPSNode*> vec : nodes)
        for (JPSNode* node : vec)
            node->Render();
}

//-------------------------------------------------------------
// Code: int FindCloseNode(Vector2 pos)
// Desc: ���� ��ǥ�� ���� ���� ����� ����� �ε����� ��ȯ�ϴ� �Լ�
//-------------------------------------------------------------
POINT JPS::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX;

    POINT index;

    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes[i].size(); j++)
        {
            if (nodes[i][j]->state == JPSNode::OBSTACLE) continue;

            float distance = Vector2::Distance(pos, nodes[i][j]->pos);

            if (minDist > distance)
            {
                minDist = distance;
                index.x = i;
                index.y = j;
            }
        }
    }

    return index;
}

//-------------------------------------------------------------
// Code: void GetPath(int start, int end, vector<Vector2>& path)
// Desc: �������� �������� ������ ��� ������ path ���Ϳ� �����ϴ� �Լ�
//-------------------------------------------------------------
void JPS::GetPath(IN POINT start, IN POINT end, OUT vector<Vector2>& path)
{
    Reset();
    path.clear();
    openList->Clear();

    float G = 0;
    float H = GetDistance(start, end);

    nodes[start.x][start.y]->g = G;
    nodes[start.x][start.y]->h = H;
    nodes[start.x][start.y]->f = G + H;

    target = nodes[end.x][end.y];

    // 1. ���� ��带 ���� ����Ʈ�� �ְ� 8���� �ʱ� Ž���� �ǽ��Ѵ�.
    openList->Insert(nodes[start.x][start.y]);
    DefaultSearch();

    // ��� ���� ������ 2~5�� �ݺ�
    // ���� ����Ʈ�� ����ִٸ� �� �̻� ��ΰ� ������ �ǹ���
    while (!openList->Empty())
    {
        // 2. ���� ����Ʈ���� F���� ���� ���� ��带 ���� ���� �����ϰ� ���� ����Ʈ���� ���� �� Ŭ���� ���·� �����
        JPSNode* curNode = openList->GetMinCostNode();
        POINT curIndex = curNode->index;

        // 3. ����Ž���� �缱Ž�� �� �� �ϳ��� �����ϱ�
        if(curNode->dir.x + curNode->dir.y == 1 || curNode->dir.x + curNode->dir.y == -1)
            StraightSearch(curNode);
        else
            DiagonalSearch(curNode);

        // 4. ������ ����
        if (target->parent)
        {
            break;
        }

        curNode->state = JPSNode::CLOSE;
    }

    JPSNode* tmpNode = target;
    vector<JPSNode*> tmpVec;

    while (tmpNode)
    {
        tmpNode->state = JPSNode::PATH;
        tmpVec.push_back(tmpNode);
        tmpNode = tmpNode->parent;

        if (tmpNode == nullptr || tmpNode == tmpNode->parent)
            break;
    }

    for (int i = 0; i < tmpVec.size(); i++)
        path.push_back(tmpVec[i]->pos);
}

//-------------------------------------------------------------
// Code: void Reset()
// Desc: Ž�� �ʱ⿡ �� ������ ���¸� �ʱ�ȭ�ϴ� �Լ�
//-------------------------------------------------------------
void JPS::Reset()
{
    for (vector<JPSNode*> vec : nodes)
    {
        for (JPSNode* node : vec)
        {
            if (node->state != JPSNode::OBSTACLE)
                node->SetInit();
        }
    }
}

float JPS::GetDistance(POINT start, POINT end)
{
    Vector2 startPos = nodes[start.x][start.y]->pos;
    Vector2 endPos = nodes[end.x][end.y]->pos;

    Vector2 tmp = endPos - startPos;

    return tmp.Length();
}

//
// ���� ���� : ���� ����
//
void JPS::DefaultSearch()
{
    JPSNode* node =  openList->GetMinCostNode();
    
    for (Vector2 dir : allDir)
    {
        node->SetNode(nullptr, dir);

        if (node->dir.x + node->dir.y == 1 || node->dir.x + node->dir.y == -1)
            StraightSearch(node);
        else
            DiagonalSearch(node);
    }

    node->state = JPSNode::CLOSE;
}

//-------------------------------------------------------------
// Code: void StraightSearch(JPSNode* node)
// Desc: ���� ���� Ž���� �ϴ� �Լ�
//-------------------------------------------------------------
void JPS::StraightSearch(JPSNode* node)
{
    JPSNode* curNode = nullptr;
    POINT idx = node->index;
    Vector2 dir = node->dir;

    vector<JPSNode*> forcedNeighbors;

    // ���� Ž���� ���� Ž�� �� �ϳ��� ����
    // dir�� y�� ������ �Ǵ�
    if (dir.y)
    {
        // ���� Ž��
        while (true)
        {
            idx.x += dir.y;
            if (idx.x == mapSize.y || idx.x == -1) break;

            curNode = nodes[idx.x][idx.y];
            if (!IsPossible(curNode)) break;

            if (VerticalSearch(curNode, dir, forcedNeighbors))
            {
                curNode->SetNode(node, dir);
                curNode->SetCost();
                openList->Insert(curNode);

                for (JPSNode* neighbor : forcedNeighbors)
                    neighbor->SetCost();

                break;
            }

            curNode->state = JPSNode::CLOSE;
        }
    }
    else
    {
        // ���� Ž��
        while (true)
        {
            idx.y += dir.x;
            if (idx.y == mapSize.x || idx.y == -1) break;

            curNode = nodes[idx.x][idx.y];
            if (!IsPossible(curNode)) break;

            if (HorizentalSearch(curNode, dir, forcedNeighbors))
            {
                curNode->SetNode(node, dir);
                curNode->SetCost();
                openList->Insert(curNode);

                for (JPSNode* neighbor : forcedNeighbors)
                    neighbor->SetCost();

                break;
            }

            curNode->state = JPSNode::CLOSE;
        }
    }

    if (isEnd && !target->parent)
    {
        curNode->SetNode(node, dir);
        curNode->SetCost();
    }
}

//-------------------------------------------------------------
// Code: void DiagonalSearch(JPSNode* node)
// Desc: �缱 Ž���� �ϴ� �Լ�
//-------------------------------------------------------------
void JPS::DiagonalSearch(JPSNode* node)
{
    JPSNode* forcedNeighbor = nullptr;
    bool ableVertical = false;
    bool ableHorizental = false;

    JPSNode* curNode = node;
    POINT index = node->index;
    Vector2 dir = node->dir;

    while (true)
    {
        if (index.y + dir.x == mapSize.x || index.y + dir.x < 0) break;
        if (index.x + dir.y == mapSize.y || index.x + dir.y < 0) break;

        if (!IsPossible(curNode)) break;

        ableVertical = nodes[index.x][index.y - dir.x]->state == JPSNode::OBSTACLE;
        ableHorizental = nodes[index.x - dir.y][index.y]->state == JPSNode::OBSTACLE;

        if (curNode != node)
        {
            curNode->SetNode(node, dir);
        }


        if ((nodes[index.x][index.y + dir.x]->state == JPSNode::OBSTACLE) &&
             nodes[index.x + dir.y][index.y]->state == JPSNode::OBSTACLE)
        {
            break;
        }
        else if (ableVertical)
        {
            //������ �ִ� ���
            if (nodes[index.x + dir.y][index.y - dir.x]->state == JPSNode::NONE)
            {
                if (curNode != node)
                {
                    curNode->SetCost();
                    openList->Insert(curNode);
                }

                forcedNeighbor = nodes[index.x + dir.y][index.y - dir.x];
                forcedNeighbor->SetNode(curNode, { dir.x * -1.0f, dir.y });
                forcedNeighbor->SetCost();
                openList->Insert(forcedNeighbor);
            }
        }
        else if (ableHorizental)
        {
            //���� �ִ� ���
            if (nodes[index.x - dir.y][index.y + dir.x]->state == JPSNode::NONE)
            {
                if (curNode != node)
                {
                    curNode->SetCost();
                    openList->Insert(curNode);
                }

                forcedNeighbor = nodes[index.x - dir.y][index.y + dir.x];
                forcedNeighbor->SetNode(curNode, { dir.x, dir.y * -1.0f });
                forcedNeighbor->SetCost();
                openList->Insert(forcedNeighbor);
            }
        }

        //if (SubSearch(curNode)) break;
        if (!SubSearch(curNode) && !forcedNeighbor)
        {
            curNode->state = JPSNode::CLOSE;
        }

        index.x += dir.y;
        index.y += dir.x;

        curNode = nodes[index.x][index.y];
    }

    if (isEnd && !target->parent)
    {
        curNode->SetNode(node, dir);
        curNode->SetCost();
    }
}

//-------------------------------------------------------------
// Code: void SubSearch(JPSNode* curNode)
// Desc: �缱 Ž�� �� �缱 ��θ� ���� ���� Ž���ϴ� �Լ�
//-------------------------------------------------------------
bool JPS::SubSearch(JPSNode* node)
{
    JPSNode* curNode;
    Vector2 dir = node->dir;
    POINT index = node->index;

    bool vertical = false;
    bool horizental = false;

    //����
    while (!vertical)
    {
        index.x += dir.y;
        if (index.x == mapSize.y || index.x == -1)
            break;

        curNode = nodes[index.x][index.y];
        curNode->SetNode(node, { 0, dir.y });
        if (!IsPossible(curNode)) break;
        
        vector<JPSNode*> forcedNeighbor;
                
        if (VerticalSearch(curNode, dir, forcedNeighbor))
        {
            vertical = true;

            curNode->SetCost();
            openList->Insert(curNode);

            for (JPSNode* node : forcedNeighbor)
                node->SetCost();

            break;
        }

        curNode->state = JPSNode::CLOSE;
    }

    index = node->index;

    //����
    while (!horizental)
    {
        index.y += dir.x;
        if (index.y == mapSize.x || index.y == -1)
            break;

        curNode = nodes[index.x][index.y];
        curNode->SetNode(node, { dir.x, 0 });
        if (!IsPossible(curNode)) break;

        vector<JPSNode*> forcedNeighbor;

        if (HorizentalSearch(curNode, dir, forcedNeighbor))
        {
            horizental = true;

            curNode->SetCost();
            openList->Insert(curNode);

            for (JPSNode* node : forcedNeighbor)
                node->SetCost();

            break;
        }

        curNode->state = JPSNode::CLOSE;

        
    }

    if (vertical || horizental)
        return true;

    return false;
}

//-------------------------------------------------------------
// Code: bool VerticalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors)
// Desc: ���� Ž���ϴ� �Լ�
//-------------------------------------------------------------
bool JPS::VerticalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors)
{
    bool isLeft = false;
    bool isRight = false;
    float dirY = dir.y;
    POINT index = curNode->index;

    // dirY�� -1�� 1�̳Ŀ� ���� ������ �޶�����
    if (dirY == -1 && index.x == 0) return false;
    if (dirY == 1 && index.x == mapSize.y) return false;

    // ���� �˻�
    if (index.y > 0)
    {
        JPSNode* forcedNeighbor = nodes[index.x + dirY][index.y - 1];
        isLeft = (forcedNeighbor->state == JPSNode::NONE && nodes[index.x][index.y - 1]->state == JPSNode::OBSTACLE);
        
        if (isLeft)
        {
            forcedNeighbor->SetNode(curNode, Vector2(-1, dirY));
            openList->Insert(forcedNeighbor);

            forcedNeighbors.push_back(forcedNeighbor);
        }
    }

    // ������ �˻�
    if (index.y < mapSize.x - 1)
    {
        JPSNode* forcedNeighbor = nodes[index.x + dirY][index.y + 1];
        isRight = (forcedNeighbor->state == JPSNode::NONE && nodes[index.x][index.y + 1]->state == JPSNode::OBSTACLE);

        if (isRight)
        {
            forcedNeighbor->SetNode(curNode, Vector2(1, dirY));
            openList->Insert(forcedNeighbor);

            forcedNeighbors.push_back(forcedNeighbor);
        }
    }

    if (isLeft || isRight)
        return true;

    return false;
}

//-------------------------------------------------------------
// Code: bool HorizentalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors)
// Desc: ���� Ž���ϴ� �Լ�
//-------------------------------------------------------------
bool JPS::HorizentalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors)
{
    bool isUp = false;
    bool isDown = false;
    float dirX = dir.x;
    POINT index = curNode->index;

    // dirX�� -1�� 1�̳Ŀ� ���� ������ �޶�����
    if (dirX == -1 && index.y == 0) return false;
    if (dirX == 1 && index.y == mapSize.y) return false;

    //if (nodes[index.x][index.y + dirX]->state = JPSNode::OBSTACLE) return false;

    // ���� Ž��
    if (index.x < mapSize.y - 1)
    {
        JPSNode* forcedNeighbor = nodes[index.x + 1][index.y + dirX];
        isUp = (forcedNeighbor->state == JPSNode::NONE && nodes[index.x + 1][index.y]->state == JPSNode::OBSTACLE);

        if (isUp)
        {
            forcedNeighbor->SetNode(curNode, Vector2(dirX, 1));
            openList->Insert(forcedNeighbor);

            forcedNeighbors.push_back(forcedNeighbor);
        }
    }

    // �Ʒ��� Ž��
    if (index.x > 0)
    {
        JPSNode* forcedNeighbor = nodes[index.x - 1][index.y + dirX];
        isUp = (forcedNeighbor->state == JPSNode::NONE && nodes[index.x - 1][index.y]->state == JPSNode::OBSTACLE);

        if (isUp)
        {
            forcedNeighbor->SetNode(curNode, Vector2(dirX, -1));
            openList->Insert(forcedNeighbor);

            forcedNeighbors.push_back(forcedNeighbor);
        }
    }

    if (isUp || isDown)
        return true;

    return false;
}

//-------------------------------------------------------------
// Code: bool IsPossible(JPSNode* node)
// Desc: ���� Ž�� ���⿡ Ž�� �ߴ� ���� �˻� �Լ�
//-------------------------------------------------------------
bool JPS::IsPossible(JPSNode* node)
{
    //�������� ���
    if (node == target)
    {
        isEnd = true;
        return false;
    }

    // ���ع��� ���
    if (node->state == JPSNode::CLOSE ||
        node->state == JPSNode::OBSTACLE)
        return false;

    // �� ���� ��쿣 Ž�� �����ϴ�
    return true;
}