/*
*	オブジェクトの設定
*
*	2015/05/05		Y.Ozawa
*/


#pragma once

class Model;
class Texture;

// 3D頂点
struct Vertex3
{
	D3DXVECTOR3 pos;	// 位置
	float size;			// サイズ
	DWORD color;		// 色
};


class Object
{
public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

private:
	D3DXMATRIX m_world;
	// ポイントスプライトの頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 pointBuffer;

	// フォント
	LPD3DXFONT font;
public:
	//デフォルトコンストラクタ
	Object();

	//デストラクタ
	~Object();

	//オブジェクトの初期化
	void Initialize();

	//オブジェクトの解放
	void Release();

	//オブジェクトを描画
	void Draw(Model* model, Texture* texture);

	// ポイントスプライトを描画する
	void DrawPointSprite(Vertex3 point[], int numPoint, Texture &texture);

	// 文字列の描画
	void DrawString(RECT rect, const TCHAR *str);
private:
	//座標変換
	void TransForm();
};