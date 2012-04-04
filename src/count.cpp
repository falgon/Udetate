#include"count.hpp"

void count(unsigned int& counter)
{
	static bool INPUT_FIRST=false;
	if(CheckHitKey(KEY_INPUT_SPACE))
			INPUT_FIRST=true;
	if(!CheckHitKey(KEY_INPUT_SPACE)&&INPUT_FIRST){
		++counter;
		INPUT_FIRST=false;
	}
}