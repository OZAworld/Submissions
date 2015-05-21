/*
*	3D���f��
*
*	2015/05/05		Y.Ozawa
*/


#pragma once

class Model
{
public:
	LPD3DXMESH mesh;
	LPD3DXBUFFER buffer;
	DWORD numMaterial;

public:
	//�f�t�H���g�R���X�g���N�^
	Model();

	//�R���X�g���N�^
	Model(const TCHAR *meshFileName);

	//�f�X�g���N�^
	~Model();

	//���b�V�������[�h����
	bool LoadMesh(const TCHAR *meshFileName);
};








