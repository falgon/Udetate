#ifndef INLCUDED_MENU
#define INLCUDED_MENU
#include<tuple>
#include<vector>
#include<array>
#include<string>
#include"Effect.hpp"
#include"menu_core.hpp"

class menu
	:public menu_core<std::tuple<unsigned int,unsigned int,std::string> >{
public:
	menu();
	menu(const std::tuple<int,int,const char*>&,
		const std::tuple<int,int,const char*>&);
	~menu();
	int Drow_menus();
	void Draw_bars();
	void effectiving();
	void load_max_v();
public:
	unsigned int max_v;
};
#endif