#ifndef STATISTICSINITIALIZER_H
#define STATISTICSINITIALIZER_H

#include "core/City.h"
#include "core/Railway.h"
#include "core/Trip.h"
#include "core/Time.h"
#include "core/Statistics.h"

class StatisticsInitializer {
public:
    static void initialize(Statistics& stats);
};

#endif // STATISTICSINITIALIZER_H
