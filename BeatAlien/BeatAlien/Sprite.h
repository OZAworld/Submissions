/*
*	プレイヤーのクラス
*
*	2015/05/05		Y.Ozawa
*/

#pragma once
#define ENEMY_MAX 50
#define PARTICLE_MAX 10000

class Camera;
class Model;
class Object;
class Texture;

//粒子のデーター
struct p_point
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	int deathCount;
	bool exist;
};

class Sprite
{
	//Xファイル
	Object player;					//プレイヤー
	Object p_prop;					//プロペラ
	Object bullet;					//弾丸
	Object enemy[ENEMY_MAX];		//敵

	p_point *explosion;

	//マトリックス
	D3DXMATRIX mtrxPlayer;
	D3DXMATRIX mtrxProp;

	float cameraAngle;		//カメラの角度
	float propAngle;		//プロペラの角度
	float timeCount;
	bool shotFlag;			//弾丸発射のフラグ
	bool bulletDeath;		//弾丸が死んでいるかどうか
	bool hitFlag;
	D3DXVECTOR3 oldPlayerPos;
	D3DXVECTOR3 oldPlayerRot;
	D3DXVECTOR3 oldCameraRot;
	D3DXVECTOR3 oldBulletPos;

	//衝突判定用
	D3DXVECTOR3 bulletCollider;		//弾丸の中心座標
	D3DXVECTOR3 enemyCollider[ENEMY_MAX];		//敵の中心座標
	float bulletRadius;				//弾丸の半径
	float enemyRadius;				//敵の半径
	int enemyCount;

private:

	Camera *camera;	

	Model *model;
	Model *propModel;
	Model *e_model;
	Model *b_model;

	Texture *texture;
	Texture *propTexture;
	Texture *e_texture;
	Texture *b_texture;
	Texture *exp_tex;
public:

	//デフォルトコンストラクタ
	Sprite();

	//デストラクタ
	~Sprite();

	//キー入力で移動させる
	void Move();

	//撮影する
	void View();

	//敵の描画
	void EnemyView();

	//	初期化
	void initPlayer();
	void initBullet();
	void initEnemy();

	//	プレイヤーの解放
	void Release();
};
