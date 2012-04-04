#ifndef INCLUDED_MENU_CORE
#define INCLUDED_MENU_CORE
#include<vector>
#include<string>
#include"DxLib.h"
#include"Effect.hpp"

template<class _Tp>
class menu_core{
public:
	std::vector<_Tp> menus;
	
	unsigned int menu_string_color;
	unsigned int select_m;

	std::vector<unsigned int> font_Handle;
	std::vector<unsigned int> Picture_Handle;
public:
	menu_core()
		:menu_string_color(0),select_m(0),Picture_Handle(0)
	{}
	~menu_core()
	{}// Don't using new
	virtual int Drow_menus()=0;
	virtual void Draw_bars()=0;
	virtual void effectiving()=0;
protected:
	effect ef;
protected:
	void count()
	{
		static bool INPUT_FIRST_U=false;
		static bool INPUT_FIRST_D=false;
		
		if(CheckHitKey(KEY_INPUT_UP))
			INPUT_FIRST_U=true;
		if(!CheckHitKey(KEY_INPUT_UP)&&INPUT_FIRST_U){
			select_m=(select_m+menus.size()-1)%menus.size();
			INPUT_FIRST_U=false;
		}
		
		if(CheckHitKey(KEY_INPUT_DOWN))
			INPUT_FIRST_D=true;
		if(!CheckHitKey(KEY_INPUT_DOWN)&&INPUT_FIRST_D){
			select_m=(select_m+1)%menus.size();
			INPUT_FIRST_D=false;
		}
	}
};
#endif