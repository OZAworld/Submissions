/*
*	�v���C���[�̃N���X
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

//���q�̃f�[�^�[
struct p_point
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	int deathCount;
	bool exist;
};

class Sprite
{
	//X�t�@�C��
	Object player;					//�v���C���[
	Object p_prop;					//�v���y��
	Object bullet;					//�e��
	Object enemy[ENEMY_MAX];		//�G

	p_point *explosion;

	//�}�g���b�N�X
	D3DXMATRIX mtrxPlayer;
	D3DXMATRIX mtrxProp;

	float cameraAngle;		//�J�����̊p�x
	float propAngle;		//�v���y���̊p�x
	float timeCount;
	bool shotFlag;			//�e�۔��˂̃t���O
	bool bulletDeath;		//�e�ۂ�����ł��邩�ǂ���
	bool hitFlag;
	D3DXVECTOR3 oldPlayerPos;
	D3DXVECTOR3 oldPlayerRot;
	D3DXVECTOR3 oldCameraRot;
	D3DXVECTOR3 oldBulletPos;

	//�Փ˔���p
	D3DXVECTOR3 bulletCollider;		//�e�ۂ̒��S���W
	D3DXVECTOR3 enemyCollider[ENEMY_MAX];		//�G�̒��S���W
	float bulletRadius;				//�e�ۂ̔��a
	float enemyRadius;				//�G�̔��a
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

	//�f�t�H���g�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
	~Sprite();

	//�L�[���͂ňړ�������
	void Move();

	//�B�e����
	void View();

	//�G�̕`��
	void EnemyView();

	//	������
	void initPlayer();
	void initBullet();
	void initEnemy();

	//	�v���C���[�̉��
	void Release();
};
