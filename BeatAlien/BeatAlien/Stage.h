#pragma once

#define FIRE_MAX 5000

class Object;
class Model;
class Texture;

//粒子のデーター
struct f_point
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	int deathCount;
	bool exist;
};


class Stage
{
	D3DXVECTOR3 MinRange;
	D3DXVECTOR3 MaxRange;

private:
	Texture *sand;

	Object *stage;

	f_point *fire;
public:

	//デフォルトコンストラクタ
	Stage();

	//デストラクタ
	~Stage();

	void Move();

	//撮影する
	void View();

	//	初期化
	void initStage();

};