#pragma once

#include <Arduino.h>
#include <vector>

struct BusPos {
    float lat;
    float lon;
    String line;
};

class BusradarClient {
public:
    // Fetches the current bus positions. Performs the secId cookie handshake
    // on first call (and re-handshakes if the cookie expires). Returns true on
    // success and fills `out` with all buses (unfiltered — caller decides which
    // lines to draw).
    bool fetch(std::vector<BusPos>& out);

private:
    String sec_id_;

    bool acquire_cookie();
    bool fetch_details(std::vector<BusPos>& out, bool& auth_failed);
};
