/*
*	�J�����N���X
*
*	2015/05/05		Y.Ozawa
*/

#include "include.h"

extern LPDIRECT3DDEVICE9 d3dDevice;

//�f�t�H���g�R���X�g���N�^
Camera::Camera()
{
	DebugLog("�J�����𐶐����܂���\n");

	Initialize();
}

//�f�X�g���N�^
Camera::~Camera()
{
	DebugLog("�J������������܂���\n");

	Release();
}

//������
void Camera::Initialize()
{
	position = D3DXVECTOR3(-3, 0, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);

	d3dDevice->GetViewport(&viewport);
	d3dDevice->SetViewport(&viewport);

	aspect = (float)viewport.Width / (float)viewport.Height;

	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(&m_projection);

	DebugLog("�J���������������܂���\n");
}

//�J�����̉��
void Camera::Release()
{

}

//�J��������B�e����
void Camera::View()
{
	//���W�v�Z
	TransForm();

	//�J�����̃r���[�s����v�Z
	D3DXMATRIX* m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(m_temp);
	D3DXMatrixInverse(m_temp, nullptr, &m_view);		//�J�����̋t�s��

	//�r���[�s���ݒ�
	d3dDevice->SetTransform(D3DTS_VIEW, m_temp);

	//�ˉe�s����쐬
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);

	//�ˉe�s����p�C�v���C���ɐݒ�
	d3dDevice->SetTransform(D3DTS_PROJECTION, &m_projection);

	delete m_temp;
}

//���W�ϊ�
void Camera::TransForm()
{
	D3DXMATRIX* m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(m_temp);

	//�s����g��k������
	D3DXMatrixScaling(m_temp, scale.x, scale.y, scale.z);
	m_view *= *m_temp;

	//�s�����]����
	D3DXMatrixRotationYawPitchRoll(m_temp, rotation.y, rotation.x, rotation.z);
	m_view *= *m_temp;

	//�s��𕽍s�ړ�������
	D3DXMatrixTranslation(m_temp, position.x, position.y, position.z);
	m_view *= *m_temp;

	delete m_temp;
}


