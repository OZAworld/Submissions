/*
*	カメラクラス
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
	//デフォルトコンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//カメラの初期化
	void Initialize();

	//カメラの解放
	void Release();

	//カメラから撮影する
	void View();

private:
	//座標変換
	void TransForm();
};