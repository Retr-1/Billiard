#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "vec.h"
#include "physics.h"
const olc::Pixel Ball::type_colors[4] = { olc::WHITE, olc::BLACK, olc::RED, olc::BLUE };

int randint(int a, int b) {
	// returns from [a,b)
	if (a > b)
		std::swap(a, b);

	return std::rand() % (b - a + 1) + a;
}

// Override base class with your custom functionality

class Window : public OlcPhysicsWindow
{
public:
	Window()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		OlcPhysicsWindow::OnUserCreate();
		Ball b;
		b.r = 50;
		//Ball b2;
		//b2.r = 100;

		engine.balls.emplace_back(b);
		engine.gravity = true;
		//engine.balls.emplace_back(b2);

		//Ball* pb = &engine.balls[0];
		//Ball* pb2 = &engine.balls[1];

		//engine.balls.erase(engine.balls.begin()+1);

		//std::cout << pb2->r << ' ' << pb->r << '\n';
		//std::cout << pb2 << ' ' << pb << '\n';

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		OlcPhysicsWindow::OnUserUpdate(fElapsedTime);
		return true;
	}
};


int main() {
	Window win;
	if (win.Construct(800, 800, 1, 1))
		win.Start();

	return 0;
}