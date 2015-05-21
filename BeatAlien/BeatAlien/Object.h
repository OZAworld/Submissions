/*
*	�I�u�W�F�N�g�̐ݒ�
*
*	2015/05/05		Y.Ozawa
*/


#pragma once

class Model;
class Texture;

// 3D���_
struct Vertex3
{
	D3DXVECTOR3 pos;	// �ʒu
	float size;			// �T�C�Y
	DWORD color;		// �F
};


class Object
{
public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

private:
	D3DXMATRIX m_world;
	// �|�C���g�X�v���C�g�̒��_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 pointBuffer;

	// �t�H���g
	LPD3DXFONT font;
public:
	//�f�t�H���g�R���X�g���N�^
	Object();

	//�f�X�g���N�^
	~Object();

	//�I�u�W�F�N�g�̏�����
	void Initialize();

	//�I�u�W�F�N�g�̉��
	void Release();

	//�I�u�W�F�N�g��`��
	void Draw(Model* model, Texture* texture);

	// �|�C���g�X�v���C�g��`�悷��
	void DrawPointSprite(Vertex3 point[], int numPoint, Texture &texture);

	// ������̕`��
	void DrawString(RECT rect, const TCHAR *str);
private:
	//���W�ϊ�
	void TransForm();
};