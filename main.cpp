#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "vec.h"
#include "physics.h"

int randint(int a, int b) {
	// returns from [a,b)
	if (a > b)
		std::swap(a, b);

	return std::rand() % (b - a + 1) + a;
}


class BilliardBall {
public:
	enum Type {
		WHITE,
		BLACK,
		P1,
		P2
	};

	static const olc::Pixel type_colors[4];

	Ball* physics_ball;
	Type type;

	~BilliardBall() {
		std::cout << "called destructor!\n";
	}
};
const olc::Pixel BilliardBall::type_colors[4] = {olc::WHITE, olc::BLACK, olc::RED, olc::BLUE};

class BilliardPhysicsEngine {
	PhysicsEngine engine;

public:
	void add_ball() {

	}

	void remove_ball(int index) {

	}

	int get_ball_count() {

	}

	BilliardBall get_ball(int index) {

	}
};


// Override base class with your custom functionality

class Window : public OlcPhysicsWindow
{
private:
	std::vector<BilliardBall> b_balls;

	void add_billiard_ball(vec2d<float>& pos, float r, float mass, BilliardBall::Type type) {
		Ball b;
		b.pos = pos;
		b.r = r;
		b.mass = mass;

		BilliardBall bb;
		bb.type = type;

		engine.balls.emplace_back(b);
		bb.physics_ball = &engine.balls[engine.balls.size() - 1];
	}

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
		//Ball b;
		//b.r = 10;
		//Ball b2;
		//b2.r = 100;

		//engine.balls.emplace_back(b);
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