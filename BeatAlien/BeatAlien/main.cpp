/*
*	�A�v���P�[�V�����̃G���g���[�|�C���g�ƃ��C�����[�v
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
	//�f�o�b�O�r���h���ɃR���\�[�����J��
#if defined (DEBUG) | defined(_DEBUG)
	OpenConsole();
#endif
	

	//�A�v���P�[�V�������s�����\�z
	unique_ptr<Application> app(new Application("BeatAlien", Rect(0, 0, 800, 600), false, hInst, cmdShow));
	unique_ptr<Sprite> sprite(new Sprite());			//�v���C���[
	unique_ptr<Light> light(new Light());				//���C�g
	unique_ptr<Stage> stage(new Stage());
	unique_ptr<Object> font(new Object());

	RECT recDisplay;
	HWND hDeskWnd;
	hDeskWnd = GetDesktopWindow();

	GetWindowRect(hDeskWnd, &recDisplay);

	//���C�����[�v
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