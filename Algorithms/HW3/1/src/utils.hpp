#pragma once
#pragma execution_character_set("utf-8")；

#include <vector>
#include <ctime>

class pt
{
public:
	pt(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	bool operator==(const pt& a) const {
		return (a.x == x) && (a.y == y);
	}

	double x = 0;
	double y = 0;
};

struct pt_pair
{
	pt_pair(const pt& _a = pt(), const pt& _b = pt(), double _dis = DBL_MAX) :a(_a), b(_b), dis(_dis) {}
	pt a;
	pt b;
	double dis;
};

bool cmp_xy(const pt& a, const pt& b)
{
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

bool cmp_y(const pt& a, const pt& b)
{
	return a.y < b.y;
}

inline double distance(const pt& a, const pt& b)
{
	if (a == b)
		return DBL_MAX;
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

inline double min(double a, double b)
{
	if (a < b)
		return a;
	else
		return b;
}

std::vector<pt> produce_pts(int n)
{
	srand(time(0));
	std::vector<pt> pts(n + 1);
	for (int i = 1; i <= n; i++)
	{
		pts[i].x = (double)rand() / RAND_MAX * 1000;
		pts[i].y = (double)rand() / RAND_MAX * 1000;
	}
	return pts;
}

int Partition(std::vector<pt>& A, int l, int h,bool (*cmp)(const pt&, const pt&))
{
	A[0] = A[l];
	//double pivotkey = A[l].x;
	while (l < h)
	{
		while (l < h && !cmp(A[h], A[0]))
			--h;
		A[l] = A[h];
		while (l < h && cmp(A[l], A[0]))
			++l;
		A[h] = A[l];
	}
	A[l] = A[0];
	return l;
}

void QSort(std::vector<pt>& A, int l, int h, bool (*cmp)(const pt&, const pt&))
{
	if (l < h)
	{
		int pivot = Partition(A, l, h, cmp);
		QSort(A, l, pivot - 1, cmp);
		QSort(A, pivot + 1, h, cmp);
	}
}

pt_pair brute_force(std::vector<pt>& pts)
{
	pt_pair result;
	int n = pts.size() - 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((i == j) || (pts[i] == pts[j]))
				continue;
			double d = distance(pts[i], pts[j]);
			if (d < result.dis)
			{
				result.dis = d;
				result.a = pts[i];
				result.b = pts[j];
			}
		}
	}

	return result;
}



pt_pair divide_and_conquer(std::vector<pt>& pts, int l, int r)
{
	pt_pair d;
	if (l == r)
		return d;
	if (r - l == 1)
	{
		d.a = pts[l];
		d.b = pts[r];
		d.dis = distance(pts[l], pts[r]);
		return d;
	}

	int m = (l + r) / 2;
	pt_pair&& d1 = divide_and_conquer(pts, l, m);
	pt_pair&& d2 = divide_and_conquer(pts, m + 1, r);

	if (d1.dis < d2.dis)
		d = d1;
	else
		d = d2;

	static std::vector<pt> temp;
	for (int i = l; i <= r; i++)
	{
		if (fabs(pts[m].x - pts[i].x) <= d.dis)
			temp.push_back(pts[i]);
	}

	QSort(temp, 0, temp.size() - 1, cmp_y);

	for (int i = 0; i < temp.size(); ++i)
	{
		for (int j = i + 1; j < temp.size() && temp[j].y - temp[i].y < d.dis; ++j)
		{
			double dc = distance(temp[i], temp[j]);
			if (dc < d.dis)
			{
				d.a = temp[i];
				d.b = temp[j];
				d.dis = dc;
			}
		}
	}

	temp.clear();
	return d;
}
