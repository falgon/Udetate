#include"DxLib.h"
#include"menu.hpp"
#include"count.hpp"
#include"start.hpp"
#include"rank.hpp"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	ChangeWindowMode(true),DxLib_Init(),SetDrawScreen(DX_SCREEN_BACK);

	menu man;

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		man.effectiving();
		man.Draw_bars();

		switch(man.Drow_menus()){
		case 0:
			Start();
			break;
		case 1:
			Rank(man);
			break;
		case 2:
			DxLib_End();
			return 0;
		case -1:
			;
		}

	}
	DxLib_End();

	return 0;
}