#include <cstdint>
#include <iostream>

#include "api.hpp"

namespace Spray_Plugin {
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
};  // namespace Spray_Plugin

class SprayPlugin : public PluginAPI::Plugin {
private:
    PluginAPI::Position last_pos;

    void draw_line (PluginAPI::Canvas canvas, PluginAPI::Position pos, int thickness, Spray_Plugin::Color);
    void set_pixel (PluginAPI::Canvas canvas, PluginAPI::Position pos, int thickness, Spray_Plugin::Color);
public:
    bool init() override;
    bool deinit() override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
    void start_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;
};

