#include "astar.h"

Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options)
{
    int dx, dy;
    double d2 = 1.41421356237;
    dx = abs(i2 - i1);
    dy = abs(j2 - j1);

    switch (options.metrictype)
    {
        case 0: //Диагональ
            return  (dx + dy) + (d2 - 2) * std::min(dx, dy);

        case 1: //Манхеттен
            return dx + dy;

        case 2://Евклидово расстояние
            return sqrt(dx * dx + dy * dy);

        case 3://Расстояние Чебышёва
            return (dx + dy) + (1 - 2) * std::min(dx, dy);

        default:
            return 0;

    }
}

