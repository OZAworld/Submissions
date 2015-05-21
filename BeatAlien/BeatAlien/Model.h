/*
*	3Dモデル
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
	//デフォルトコンストラクタ
	Model();

	//コンストラクタ
	Model(const TCHAR *meshFileName);

	//デストラクタ
	~Model();

	//メッシュをロードする
	bool LoadMesh(const TCHAR *meshFileName);
};








