#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "vec.h"
#include "physics.h"
#include <random>
#include <algorithm>
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
	int sx = (1200-(table_width+table_border*2))/2; int sy = (800-(table_height+table_border*2))/2;
	int tx = sx + table_border; int ty = sy + table_border;
	int etx = tx + table_width; int ety = ty + table_height;
	int ball_r = table_border / 3;
	float ball_mass = 20;
	vec2d<float> default_white_pos = vec2d<float>(tx + table_width / 3, ty + table_height / 2);
	Ball* white_ball = nullptr;
	Ball::Type player_turn = Ball::P1;
	Ball::Type winner = Ball::WHITE;
	bool own_ball_fallen = false;
	bool white_fallen = false;
	bool black_fallen = false;
	bool white_on_the_move = false;
	bool game_over = false;
	int n_player_balls[4] = {1,1,7,7 };


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

	void create_balls() {
		Ball b;
		b.type = Ball::WHITE;
		b.r = ball_r;
		b.pos = default_white_pos;
		b.mass = ball_mass;
		engine.balls.push_back(b);
		white_ball = &engine.balls[0];

		Ball::Type type_pool[15];
		for (int i = 0; i < 14; i += 2) {
			type_pool[i] = Ball::P1;
			type_pool[i + 1] = Ball::P2;
		}
		type_pool[14] = Ball::BLACK;
		
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(type_pool, type_pool + 15, g);

		int bx = tx + table_width*2/3;
		int by = ty + table_height / 2;
		int c = 0;
		for (int i = 0; i < 5; i++) {
			int tmpy = by;
			for (int j = 0; j <= i; j++) {
				Ball b;
				b.r = ball_r;
				b.pos = vec2d<float>(bx, tmpy);
				b.mass = ball_mass;
				b.type = type_pool[c];
				engine.balls.emplace_back(b);

				tmpy += ball_r*2;
				c++;
			}
			by -= ball_r;
			bx += ball_r*2;
		}
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
		OlcPhysicsWindow::draw(engine);
	}

	void draw(Ball& ball) override {
		FillCircle(olc::vi2d(ball.pos.x, ball.pos.y), ball.r, Ball::type_colors[ball.type]);
	}

	void end_turn() {
		player_turn = player_turn == Ball::P1 ? Ball::P2 : Ball::P1;
		white_fallen = false;
		own_ball_fallen = false;
	}

	void process_user_interaction() {
		for (Ball& ball : engine.balls) {
			if (ball.type != Ball::WHITE)
				continue;

			if (white_on_the_move) {
				white_on_the_move = false;
				if (black_fallen) {
					game_over = true;
					if (n_player_balls[player_turn] == 0) {
						winner = player_turn;
					}
					else {
						end_turn();
						winner = player_turn;
					}
					return;
				}
				else if (white_fallen || !own_ball_fallen) {
					end_turn();
				}
				else {
					own_ball_fallen = false;
				}
			}

			if ((GetMouse(olc::Mouse::LEFT).bPressed) && ball.is_inside(GetMouseX(), GetMouseY())) {
				white_ball = &ball;
			}
		}

		if (GetMouse(olc::Mouse::LEFT).bHeld && white_ball) {
			DrawLine(GetMousePos(), olc::vi2d(white_ball->pos.x, white_ball->pos.y), Ball::type_colors[player_turn]);
		}

		if (GetMouse(olc::Mouse::LEFT).bReleased && white_ball) {
			white_ball->v = (white_ball->pos - vec2d<float>(GetMouseX(), GetMouseY())) * 2;
			white_on_the_move = true;
			white_ball = nullptr;
		}
	}

	bool OnUserCreate() override
	{
		OlcPhysicsWindow::OnUserCreate();
		create_table();
		create_balls();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		engine.update(fElapsedTime);

		//check off grid
		for (int i = engine.balls.size() - 1; i >= 0; i--) {
			Ball& b = engine.balls[i];
			/*if (b.pos.x - b.r > etx || b.pos.x + b.r < tx || b.pos.y - b.r > ety || b.pos.y + b.r < ty) {
				engine.balls.erase(engine.balls.begin() + i);
			}*/
			if (b.pos.x > etx || b.pos.x  < tx || b.pos.y > ety || b.pos.y < ty) {
				if (b.type == Ball::WHITE) {
					b.pos = default_white_pos;
					b.v.x = 0;
					b.v.y = 0;
					white_fallen = true;
				}
				else {
					black_fallen |= b.type == Ball::BLACK;
					own_ball_fallen |= b.type == player_turn;
					n_player_balls[b.type]--;
					engine.balls.erase(engine.balls.begin() + i);
				}
			}
		}

		draw_table();

		bool all_still = true;
		for (Ball& b : engine.balls) {
			if (b.v.mag() > 1.0f) {
				all_still = false;
				break;
			}
		}

		if (all_still) {
			if (game_over) {
				DrawString({ tx,100 }, "Player " + (std::string)(winner == Ball::Type::P1 ? "RED" : "BLUE") + " WON!!!", Ball::type_colors[winner], 4U);
			}
			else {
				process_user_interaction();
				DrawString({ 10,10 }, "Player " + (std::string)(player_turn == Ball::Type::P1 ? "RED" : "BLUE") + "'s turn", Ball::type_colors[player_turn], 3U);
			}
		}

		

		return true;
	}
};


int main() {
	Window win;
	if (win.Construct(1200, 800, 1, 1))
		win.Start();

	return 0;
}