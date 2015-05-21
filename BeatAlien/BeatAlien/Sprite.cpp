/*
*	プレイヤーの処理
*
*	2015/05/05		Y.Ozawa
*/

#include <time.h>
#include "include.h"
#include "Sprite.h"

extern LPDIRECT3DDEVICE9 d3dDevice;
extern LPDIRECTINPUTDEVICE8 dinputDevice;

//デフォルトコンストラクタ
Sprite::Sprite()
{
	camera = new Camera();

	model = new Model("Model/Heli.x");
	texture = new Texture("Texture/lapis_block.png");
	propModel = new Model("Model/Prop.x");
	propTexture = new Texture("Texture/Prop.bmp");

	b_model = new Model();
	b_texture = new Texture();

	e_model = new Model();
	e_texture = new Texture();

	explosion = new p_point[PARTICLE_MAX];
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		explosion[i].deathCount = 0;
		explosion[i].exist = FALSE;
	}
	exp_tex = new Texture("Texture/ball.bmp");

	hitFlag = FALSE;

	initPlayer();
	initBullet();
	initEnemy();
	camera->position = D3DXVECTOR3(0, 109, -10);
	camera->rotation = D3DXVECTOR3(D3DXToRadian(60), 0, 0);
}

//デストラクタ
Sprite::~Sprite()
{
	delete camera;
	delete model;
	delete b_model;
	delete e_model;
	delete texture;
	delete b_texture;
	delete e_texture;
	delete propModel;
	delete propTexture;
	delete exp_tex;
	delete explosion;
	Release();
}

//プレイヤーをキーで移動させる
void Sprite::Move()
{

	//プロペラを回転させる
	propAngle += 0.5f;
	if (propAngle > D3DX_PI)
		propAngle -= 2 * D3DX_PI;

	p_prop.rotation.y = propAngle;


	Vertex3 *vertex = new Vertex3[PARTICLE_MAX];
	bool exp_flag = FALSE;

	

	//弾丸発射
	if (shotFlag == FALSE && GetAsyncKeyState(VK_LBUTTON))
	{
		srand((unsigned int)time(NULL));

		bullet.position.x = oldPlayerPos.x;
		bullet.position.z = oldPlayerPos.z;
		bullet.rotation.y = oldPlayerRot.y;
		bullet.rotation.x = oldCameraRot.x;

		bullet.position.y = 101.5f;
		timeCount = 0;
		shotFlag = TRUE;
	}

	if (shotFlag == TRUE)
	{
		timeCount += 0.05f;
		bullet.position.y -= 1.0f + timeCount * sin(bullet.rotation.x);
		bullet.position.x += sin(bullet.rotation.y) * 2.0f * cos(bullet.rotation.x);
		bullet.position.z += cos(bullet.rotation.y) * 2.0f * cos(bullet.rotation.x);

		bullet.Draw(b_model, b_texture);	//弾丸の描画

		//衝突判定
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			enemyCollider[i] = enemy[i].position;
			enemyRadius = 5.0f;
			bulletCollider = bullet.position;
			bulletRadius = 3.0f;

			if (((enemyCollider[i].x - bulletCollider.x) * (enemyCollider[i].x - bulletCollider.x)) +
				((enemyCollider[i].y - bulletCollider.y) * (enemyCollider[i].y - bulletCollider.y)) +
				((enemyCollider[i].z - bulletCollider.z) * (enemyCollider[i].z - bulletCollider.z)) <=
				((bulletRadius + enemyRadius)*(bulletRadius + enemyRadius)))
			{
				hitFlag = TRUE;
				if (hitFlag == TRUE)
				{
					enemy[i].position.y = 1000.0f;
					if (enemy[i].position.y >= 1000.0f)
					{
						enemyCount += 1;
					}
					hitFlag = FALSE;
				}
			}
		}
		

		bulletDeath = FALSE;
	}

	if (enemyCount >= ENEMY_MAX)
	{
		bullet.DrawString({0, 0, 400, 300}, "CLEAR");
		
	}

	if (bullet.position.y < 0 || hitFlag == TRUE)
	{
		oldBulletPos = bullet.position;
		
		bulletDeath = TRUE;
	}
	if (bulletDeath == TRUE && shotFlag == TRUE)
	{
		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (explosion[i].exist == FALSE)
			{
				explosion[i].exist = TRUE;
				explosion[i].pos = oldBulletPos;
				explosion[i].deathCount = 0;
			}
		}
		shotFlag = FALSE;
		hitFlag = FALSE;
		bullet.position = oldBulletPos;
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (explosion[i].exist == TRUE)
		{
			exp_flag = TRUE;
			explosion[i].deathCount++;
			D3DXVec3Normalize(&explosion[i].accel, &D3DXVECTOR3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 40));

			explosion[i].pos.x += explosion[i].accel.x * 1.2;//rand() % 2 - rand() % 1 - 0.5;
			explosion[i].pos.y += explosion[i].accel.y * 1.2;//rand() % 2 - rand() % 1 - 0.5;
			explosion[i].pos.z += explosion[i].accel.z * 1.2;//rand() % 2 - rand() % 1 - 0.5;
		}
		vertex[i].pos = explosion[i].pos;
		vertex[i].size = 3.5f;
		vertex[i].color = 0xffffffff;
		if (explosion[i].deathCount > 20 && exp_flag == TRUE)
		{
			explosion[i].exist = FALSE;
			exp_flag = FALSE;
			explosion[i].pos.y = 10000.0f;
		}
	}
	
	player.DrawPointSprite(vertex, PARTICLE_MAX, *exp_tex);

	delete[] vertex;

	

	//移動する	キーボードで操作
	if (GetAsyncKeyState(0x57))
	{
		player.position.x += sin(player.rotation.y) * 2.0f;
		player.position.z += cos(player.rotation.y) * 2.0f;
	}
	if (GetAsyncKeyState(0x53))
	{
		player.position.x -= sin(player.rotation.y) * 2.0f;
		player.position.z -= cos(player.rotation.y) * 2.0f;
	}
	if (GetAsyncKeyState(0x41))
	{
		player.position.x += sin(player.rotation.y - D3DXToRadian(90)) * 2.0f;
		player.position.z += cos(player.rotation.y - D3DXToRadian(90)) * 2.0f;
	}
	if (GetAsyncKeyState(0x44))
	{
		player.position.x += sin(player.rotation.y + D3DXToRadian(90)) * 2.0f;
		player.position.z += cos(player.rotation.y + D3DXToRadian(90)) * 2.0f;
	}
	oldPlayerPos.x = player.position.x;
	oldPlayerPos.z = player.position.z;

	//カメラ移動		マウスの動きに合わせる
	DIMOUSESTATE2 dims;

	if (SUCCEEDED(dinputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &dims)))
	{
		cameraAngle += dims.lX * 0.005f;
		if (cameraAngle > D3DX_PI)
		{
			cameraAngle -= 2 * D3DX_PI;
		}
		
		camera->rotation.x += dims.lY * 0.005f;
		if (camera->rotation.x < D3DXToRadian(30))
		{
			camera->rotation.x = D3DXToRadian(30);
		}
		if (camera->rotation.x > D3DXToRadian(60))
		{
			camera->rotation.x = D3DXToRadian(60);
		}

	}

	//プレイヤーをカメラの中心にとらえる
	camera->position.x = player.position.x - 4 * sinf(cameraAngle);
	camera->position.z = player.position.z - 4 * cosf(cameraAngle);

	camera->rotation.y += dims.lX * 0.005f;
	player.rotation.y = camera->rotation.y;
	p_prop.position = player.position;
	oldPlayerRot.y = player.rotation.y;
	oldCameraRot.x = camera->rotation.x;


}


void Sprite::initPlayer()
{
	player.scale = D3DXVECTOR3(0.01, 0.01, 0.01);
	p_prop.scale = D3DXVECTOR3(0.01, 0.01, 0.01);

	player.position = D3DXVECTOR3(0, 102, 0);
	p_prop.position = D3DXVECTOR3(0, 102, 0);

}

void Sprite::initBullet()
{
	b_model = new Model("Model/tako.x");
	b_texture = new Texture("Texture/RedSkin.png");

	shotFlag = FALSE;
	bulletDeath = TRUE;
	bullet.position.y = 101.5f;

}

void Sprite::initEnemy()
{
	e_model = new Model("Model/alien.x");
	e_texture = new Texture("Texture/GreenSkin.png");
	enemyCount = 0;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].position.y = 0;
	}
}

//	プレイヤーの破棄
void Sprite::Release()
{

}

void Sprite::View()
{
	camera->View();

	EnemyView();

	player.Draw(model, texture);		//プレイヤーの描画

	p_prop.Draw(propModel, propTexture);
}

void Sprite::EnemyView()
{
	for (int z = 0; z < 10; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			enemy[x + z * 5].position.x = x * 10 - 20;
			enemy[x + z * 5].position.z = z * 10 + 100;
			enemy[x + z * 5].scale = D3DXVECTOR3(4, 4, 4);
			enemy[x + z * 5].Draw(e_model, e_texture);
		}
	}

}