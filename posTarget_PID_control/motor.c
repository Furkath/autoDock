#include<stdio.h>
#include<math.h>


int ninja(double vx, double vy, double k, double t, double n)
{
	if (n == 1000) return 0;
	else
	{
		double ox = vx - k * vx*sqrt(vx*vx + vy * vy)*t;
		double oy = vy - (10.0 + k * vy*sqrt(vx*vx + vy * vy))*t;
		printf("%f\n", ox);
		ninja(ox, oy, k, t, n + 1);
		return 0;
	}
}

int ninja1(double vx, double vy, double k, double t, double n)
{
	if (n == 1000) return 0;
	else
	{
		double ox = vx - k * vx*sqrt(vx*vx + vy * vy)*t;
		double oy = vy - (10.0 + k * vy*sqrt(vx*vx + vy * vy))*t;
		printf("%f\n", oy);
		ninja1(ox, oy, k, t, n + 1);
		return 0;
	}
}

int ninja2(double vx, double vy, double k, double t, double n, double x)
{
	if (n == 1000) return 0;
	else
	{
		double ox = vx - k * vx*sqrt(vx*vx + vy * vy)*t;
		double oy = vy - (10.0 + k * vy*sqrt(vx*vx + vy * vy))*t;
		double sm = x + (vx + ox)*t / 2;
		printf("%f\n", sm);
		ninja2(ox, oy, k, t, n + 1, sm);
		return 0;
	}
}

int ninja3(double vx, double vy, double k, double t, double n, double x)
{
	if (n == 1000) return 0;
	else
	{
		double ox = vx - k * vx*sqrt(vx*vx + vy * vy)*t;
		double oy = vy - (10.0 + k * vy*sqrt(vx*vx + vy * vy))*t;
		double sm = x + (vy + oy)*t / 2;
		printf("%f\n", sm);
		ninja3(ox, oy, k, t, n + 1, sm);
		return 0;
	}
}

int gg(double a, double k, double t)
{
	//printf("一系列x方向速度\n");
	//ninja(90 * a, 90 * sqrt(1 - a * a), k, t, 0);
	//printf("一系列y方向速度\n");
	//ninja1(90 * a, 90 * sqrt(1 - a * a), k, t, 0);
	//printf("一系列x方向位移\n");
	//ninja2(90 * a, 90 * sqrt(1 - a * a), k, t, 0, 0);
	//printf("一系列y方向位移\n");
	ninja3(90 * a, 90 * sqrt(1 - a * a), k, t, 0, 0);
	//printf("\n");
	return 0;
}

int main(void)
{
	gg(0.6, 0.036, 0.01);
	return 0;
}
