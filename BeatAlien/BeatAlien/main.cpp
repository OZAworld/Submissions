/*
*	アプリケーションのエントリーポイントとメインループ
*
*	2015/05/01		Y.Ozawa
*/



#include "include.h"
#include <memory>
#include "Sprite.h"
#include "Stage.h"

using namespace std;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int cmdShow)
{
	//デバッグビルド時にコンソールを開く
#if defined (DEBUG) | defined(_DEBUG)
	OpenConsole();
#endif
	

	//アプリケーション実行環境を構築
	unique_ptr<Application> app(new Application("BeatAlien", Rect(0, 0, 800, 600), false, hInst, cmdShow));
	unique_ptr<Sprite> sprite(new Sprite());			//プレイヤー
	unique_ptr<Light> light(new Light());				//ライト
	unique_ptr<Stage> stage(new Stage());
	unique_ptr<Object> font(new Object());

	RECT recDisplay;
	HWND hDeskWnd;
	hDeskWnd = GetDesktopWindow();

	GetWindowRect(hDeskWnd, &recDisplay);

	//メインループ
	while (app->Loop())
	{
		sprite->View();
		sprite->Move();

		stage->View();

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}

		ShowCursor(FALSE);
		SetCursorPos(recDisplay.right / 2, recDisplay.bottom / 2);
	}

	return 0;
}