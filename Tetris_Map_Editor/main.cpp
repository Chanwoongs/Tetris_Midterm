#include<iostream>
#include<fstream>
#include<string>
#include"Screen.h"
#include"Input.h"
#include"MapEditor.h"
using namespace std;

int main()
{
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto editor = new MapEditor;	

	while (!editor->isDone())
	{
		screen->clear();
		input->readInputs();

		editor->internalUpdate();
		editor->updatePos(false); // the location of the root game object won't be changed.
		editor->internalDraw();

		screen->render();

		Sleep(100);
	}	
}