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


class Window : public OlcPhysicsWindow
{
private:
	int table_width = 600;
	int table_height = 350;
	int table_border = 40;
	int sx = 10; int sy = 10;
	int tx = sx + table_border; int ty = sy + table_border;
	int etx = tx + table_width; int ety = ty + table_height;

public:
	Window()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	void create_table() {
		const int r = 3;
		Capsule c1;
		c1.start = vec2d<float>(tx + table_border, ty);
		c1.end = vec2d<float>(tx + table_width / 2 - table_border, ty);
		c1.r = r;
		engine.capsules.emplace_back(c1);

		Capsule c2;
		c2.start = vec2d<float>(tx + table_border + table_width/2, ty);
		c2.end = vec2d<float>(tx + table_width - table_border, ty);
		c2.r = r;
		engine.capsules.emplace_back(c2);

		Capsule c3;
		c3.start = vec2d<float>(etx, ty+table_border);
		c3.end = vec2d<float>(etx, ty+table_height/2-table_border);
		c3.r = r;
		engine.capsules.emplace_back(c3);

		Capsule c4;
		c4.start = vec2d<float>(etx, ty+table_height / 2 + table_border);
		c4.end = vec2d<float>(etx, ety-table_border);
		c4.r = r;
		engine.capsules.emplace_back(c4);

		Capsule c5;
		c5.start = vec2d<float>(etx-table_border, ety);
		c5.end = vec2d<float>(etx-table_width/2+table_border, ety);
		c5.r = r;
		engine.capsules.emplace_back(c5);

		Capsule c6;
		c6.start = vec2d<float>(tx + table_border, ety);
		c6.end = vec2d<float>(tx + table_width / 2 - table_border, ety);
		c6.r = r;
		engine.capsules.emplace_back(c6);

		Capsule c7;
		c7.start = vec2d<float>(tx, ety-table_border);
		c7.end = vec2d<float>(tx, ty+table_height/2+table_border);
		c7.r = r;
		engine.capsules.emplace_back(c7);

		Capsule c8;
		c8.start = vec2d<float>(tx, ty+table_border);
		c8.end = vec2d<float>(tx, ty+table_height/2-table_border);
		c8.r = r;
		engine.capsules.emplace_back(c8);
	}

	void draw_table() {
		// outer border
		
		/*DrawLine(olc::vi2d(sx, sy), olc::vi2d(sx + table_width + table_border * 2, sy));
		DrawLine(olc::vi2d(sx, sy+table_border*2+table_height), olc::vi2d(sx + table_width + table_border * 2, sy+table_border*2+table_height));
		DrawLine(olc::vi2d(sx, sy), olc::vi2d(sx, sy+table_height+table_border*2));
		DrawLine(olc::vi2d(sx+table_width+table, sy), olc::vi2d(sx+table_width+table_border*2, sy + table_height + table_border * 2));*/
		FillRect(olc::vi2d(sx, sy), olc::vi2d(table_width + table_border * 2, table_height + table_border * 2), olc::DARK_GREEN);
		for (olc::vi2d pos : {
			olc::vi2d(sx + table_border,sy + table_border),
			olc::vi2d(sx + table_border + table_width / 2, sy + table_border),
			olc::vi2d(sx + table_border + table_width, sy + table_border),
			olc::vi2d(sx + table_border,sy + table_border + table_height),
			olc::vi2d(sx + table_border + table_width / 2, sy + table_border + table_height),
			olc::vi2d(sx + table_border + table_width, sy + table_border + table_height),
			olc::vi2d(sx + table_border, sy + table_border + table_height / 2),
			olc::vi2d(sx + table_border + table_width, sy + table_border + table_height / 2),
			})
		{
			FillCircle(pos, table_border, olc::GREY);
		}
		FillRect(olc::vi2d(sx + table_border, sy + table_border), olc::vi2d(table_width, table_height), olc::DARK_GREEN);
		draw(engine);
	}

	bool OnUserCreate() override
	{
		OlcPhysicsWindow::OnUserCreate();
		create_table();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		engine.update(fElapsedTime);
		draw_table();
		return true;
	}
};


int main() {
	Window win;
	if (win.Construct(800, 800, 1, 1))
		win.Start();

	return 0;
}