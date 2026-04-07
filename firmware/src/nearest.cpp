#include "nearest.h"
#include "led_map.h"

#include <math.h>
#include <stddef.h>

static constexpr float DEG2RAD = 0.01745329252f;

// Max snap distance in degrees (lat-equivalent). ~50 m.
// 1 deg lat ≈ 111 km  ->  50 m ≈ 0.00045 deg  ->  squared ≈ 2.03e-7.
static constexpr float MAX_SNAP_D2 = 2.03e-7f;

size_t nearest_route_point(float lat, float lon) {
    const float coslat = cosf(lat * DEG2RAD);
    size_t best_i = 0;
    float  best_d2 = INFINITY;
    for (size_t i = 0; i < ROUTE_COUNT; ++i) {
        const float dlat = lat - ROUTE_LAT[i];
        const float dlon = (lon - ROUTE_LON[i]) * coslat;
        const float d2 = dlat * dlat + dlon * dlon;
        if (d2 < best_d2) {
            best_d2 = d2;
            best_i = i;
        }
    }
    if (best_d2 > MAX_SNAP_D2) return (size_t)-1;
    return best_i;
}
