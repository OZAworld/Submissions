/*
*	3D���f��
*
*	2015/05/05		Y.Ozawa
*/

#include "include.h"

//Direct3D�f�o�C�X
extern LPDIRECT3DDEVICE9 d3dDevice;

//�f�t�H���g�R���X�g���N�^
Model::Model()
{
	mesh = nullptr;
	buffer = nullptr;
	numMaterial = 0;
}

//�R���X�g���N�^
Model::Model(const TCHAR *meshFileName)
{
	LoadMesh(meshFileName);
}

//�f�X�g���N�^
Model::~Model()
{
	SafeRelease(buffer);
	SafeRelease(mesh);
}

//���b�V����ǂݍ���
bool Model::LoadMesh(const TCHAR *meshFileName)
{
	if (FAILED(D3DXLoadMeshFromX(meshFileName, D3DXMESH_SYSTEMMEM, d3dDevice, nullptr, &buffer, nullptr, &numMaterial, &mesh)))
	{
		DebugAlert("%s��\n�ǂݍ��߂܂���ł����B\n�t�@�C������f�B���N�g�����ԈႦ�Ă��Ȃ������m�F���������B", meshFileName);
		return false;
	}

	return true;
}
