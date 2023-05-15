#include"game.h"
#include"game.cpp"

Game *g = new Game;

int main(int argc,char **argv)
{
	g->Create();
	g->Set();
	while(!g->Stop())
	{
		if(g->RestartGame())
		{
			g->DrawRestartMenu();
			if(g->NewGame()) g->Set();
		}
		if((g->StartGame() && !g->RestartGame()) || (g->NewGame()))
		{
			g->Update();
			g->Run();
			g->PlaySound();
			SDL_Delay(16);
		}
		else
		{
			if(!g->RestartGame()) g->DrawStartMenu();
		}
	}
	g->Clear();
	delete g;
	return 0;
}
