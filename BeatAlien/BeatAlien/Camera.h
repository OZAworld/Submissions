/*
*	�J�����N���X
*
*	2015/05/05		Y.Ozawa
*/

#pragma once

class Camera
{
public:
	D3DXVECTOR3 position;	
	D3DXVECTOR3 rotation;	
	D3DXVECTOR3 scale;		

private:
	D3DVIEWPORT9 viewport;

	float aspect;
	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;

public:
	//�f�t�H���g�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//�J�����̏�����
	void Initialize();

	//�J�����̉��
	void Release();

	//�J��������B�e����
	void View();

private:
	//���W�ϊ�
	void TransForm();
};