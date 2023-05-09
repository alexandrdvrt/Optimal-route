#include <iostream>
#include <stdlib.h>

using namespace std;

class Gas_Station
{
	float km;
public:
	Gas_Station() { km = 0; };
	Gas_Station(float _km) : km(_km) {};
	float get_km() { return km; };
};

class Highway
{
	float start;
	float end;
	int count;
	Gas_Station* map;
public:
	Highway() { start = 0; end = 0; count = 0; map = nullptr; };
	Highway(float _start, float _end) : start(_start), end(_end) { map = nullptr; count = 0; };
	Highway(float _start, int _count, char** interval);
	~Highway() { delete[] map; };
	int optimal_way(float range);
	int station_search(float km, float range);
};

int Highway::station_search(float km, float range)
{
	int left = 0;
	int right = count - 1;
	int middle;
	float dist = km + range;
	if (dist > map[count - 1].get_km())
		return count - 1;
	do
	{
		middle = (left + right) / 2;
		if (dist == map[middle].get_km())
			return middle;
		else
			if (dist > map[middle].get_km())
				left = middle + 1;
			else
				right = middle - 1;
	} while (dist >= map[left].get_km());
	return left-1;
}

int Highway::optimal_way(float range)
{
	cout << "Numbers of gas stations: ";
	int i, j = 0;
	float last = 0;
	i = this->station_search(0, range);
	while (i < count-1)
	{
		cout << i+1 << " ";
		if (map[i + 1].get_km() - map[i].get_km() > range)
		{
			cout << "\nTo pass the site is Impossible!";
			exit(-1);
		}
		last = map[i].get_km();
		i = this->station_search(last, range);
		j++;
	}
	if ((end - last > range))
	{
		j++;
		cout << i + 1;
	}
	cout << "\nCount of gas station: "; 
	return j;
}

Highway::Highway(float _start, int _count, char** interval)
{
	start = _start;
	count = _count-1;
	map = new Gas_Station [count];
	for (int i = 0; i < count; i++)
	{
		_start += atof(interval[i+1]);
		map[i] = Gas_Station(_start);
	}
	end = _start + atof(interval[_count]);
}

int main(int argv, char** argc)
{
	Highway R(0, argv-1, argc);
	float range;
	cout << "Enter the range of auto:\n";
	cin >> range;
	cout << R.optimal_way(range) << endl;
	return 0;
}
