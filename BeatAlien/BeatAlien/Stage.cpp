#include <time.h>
#include "include.h"
#include "Stage.h"


Stage::Stage()
{

	fire = new f_point[FIRE_MAX];
	for (int i = 0; i < FIRE_MAX; i++)
	{
		fire[i].deathCount = 0;
		fire[i].pos = D3DXVECTOR3(0, 0, 0);
		fire[i].exist = TRUE;
	}
	sand = new Texture("Texture/r_ball.bmp");
	stage = new Object();

	initStage();
}

Stage::~Stage()
{
	delete sand;
	delete stage;
}


void Stage::Move()
{
}

void Stage::initStage()
{
	MinRange = D3DXVECTOR3(-300, 0, -500);
	MaxRange = D3DXVECTOR3(300, 10, 500);

	D3DXVECTOR3 range = MaxRange - MinRange;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < FIRE_MAX; i++)
	{
		fire[i].pos.x = (float)((double)rand() / RAND_MAX * range.x) + MinRange.x;
		fire[i].pos.z = (float)((double)rand() / RAND_MAX * range.z) + MinRange.z;
	}
}

void Stage::View()
{
	Vertex3 *vertex = new Vertex3[FIRE_MAX];
	D3DXVECTOR3 range = MaxRange - MinRange;

	for (int i = 0; i < FIRE_MAX; i++)
	{
		if (fire[i].exist == TRUE)
		{
			fire[i].pos.y += rand() % 5 * 0.04f;
		}
		vertex[i].pos = fire[i].pos;
		vertex[i].size = 0.9f;
		vertex[i].color = 0xffffffff;

		if (fire[i].pos.y > 10)
		{
			fire[i].pos.x = (float)((double)rand() / RAND_MAX * range.x) + MinRange.x;
			fire[i].pos.z = (float)((double)rand() / RAND_MAX * range.z) + MinRange.z;

			fire[i].pos.y = 0;
		}

	}

	stage->DrawPointSprite(vertex, FIRE_MAX, *sand);
	delete[] vertex;


}