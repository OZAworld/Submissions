/*
*	カメラクラス
*
*	2015/05/05		Y.Ozawa
*/

#include "include.h"

extern LPDIRECT3DDEVICE9 d3dDevice;

//デフォルトコンストラクタ
Camera::Camera()
{
	DebugLog("カメラを生成しました\n");

	Initialize();
}

//デストラクタ
Camera::~Camera()
{
	DebugLog("カメラを解放しました\n");

	Release();
}

//初期化
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

	DebugLog("カメラを初期化しました\n");
}

//カメラの解放
void Camera::Release()
{

}

//カメラから撮影する
void Camera::View()
{
	//座標計算
	TransForm();

	//カメラのビュー行列を計算
	D3DXMATRIX* m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(m_temp);
	D3DXMatrixInverse(m_temp, nullptr, &m_view);		//カメラの逆行列

	//ビュー行列を設定
	d3dDevice->SetTransform(D3DTS_VIEW, m_temp);

	//射影行列を作成
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 100000.0f);

	//射影行列をパイプラインに設定
	d3dDevice->SetTransform(D3DTS_PROJECTION, &m_projection);

	delete m_temp;
}

//座標変換
void Camera::TransForm()
{
	D3DXMATRIX* m_temp = new D3DXMATRIX;
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(m_temp);

	//行列を拡大縮小する
	D3DXMatrixScaling(m_temp, scale.x, scale.y, scale.z);
	m_view *= *m_temp;

	//行列を回転する
	D3DXMatrixRotationYawPitchRoll(m_temp, rotation.y, rotation.x, rotation.z);
	m_view *= *m_temp;

	//行列を平行移動させる
	D3DXMatrixTranslation(m_temp, position.x, position.y, position.z);
	m_view *= *m_temp;

	delete m_temp;
}


