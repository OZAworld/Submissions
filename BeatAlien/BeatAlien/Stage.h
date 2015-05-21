#pragma once

#define FIRE_MAX 5000

class Object;
class Model;
class Texture;

//���q�̃f�[�^�[
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

	//�f�t�H���g�R���X�g���N�^
	Stage();

	//�f�X�g���N�^
	~Stage();

	void Move();

	//�B�e����
	void View();

	//	������
	void initStage();

};