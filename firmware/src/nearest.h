#pragma once

#include <stddef.h>

// Returns the index of the route point closest to (lat, lon).
// May return an index >= LED_COUNT — the caller must skip those (off-map).
size_t nearest_route_point(float lat, float lon);
