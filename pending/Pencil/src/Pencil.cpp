#include "../include/Spray/Spray.h"


bool SprayPlugin::init() {
    properties[PluginAPI::TYPE::PRIMARY_COLOR].display_type =
        PluginAPI::Property::DISPLAY_TYPE::COLOR_PICKER;
    return true;
}

bool SprayPlugin::deinit() { return true; }

void SprayPlugin::set_pixel (PluginAPI::Canvas canvas, PluginAPI::Position pos, int thickness, Spray_Plugin::Color color) {

    auto x = pos.x;
    auto y = pos.y;

    auto width = canvas.width;
    auto height = canvas.height;;

    Spray_Plugin::Color* current_pixel;
    for (int k = std::max (y - thickness, 0l); k <= std::min(y + thickness, static_cast<long>(height - 1)); k++)
        for (int l = std::max(x - thickness, 0l); l <= std::min(x + thickness, static_cast<long>(width - 1)); l++)
        {
            current_pixel = reinterpret_cast<Spray_Plugin::Color*> (canvas.pixels + 4 * (k * width + l));
            if (((k - y)*(k - y) + (l - x)*(l - x)) < thickness)
            {
                current_pixel->r = color.r;
                current_pixel->g = color.g;
                current_pixel->b = color.b;
                current_pixel->a = color.a;
            }
        }

}

void SprayPlugin::start_apply(PluginAPI::Canvas canvas,
                              PluginAPI::Position pos) {

    Spray_Plugin::Color* color =
        reinterpret_cast<Spray_Plugin::Color*>(
            &properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value);
    int thickness = properties[PluginAPI::TYPE::THICKNESS].int_value;

    set_pixel (canvas, pos, thickness, *color);

    last_pos = pos;
}

void SprayPlugin::draw_line (PluginAPI::Canvas canvas, PluginAPI::Position pos, int thickness, Spray_Plugin::Color color) {

    int begin_x = std::min (pos.x, last_pos.x);
    int begin_y = std::min (pos.y, last_pos.y);

    auto end_x = std::max (pos.x, last_pos.x);
    auto end_y = std::max (pos.y, last_pos.y);

    int width = end_x - begin_x;
    int height = end_y - begin_y;

    if (width > height)
    {
        for (auto i = 0; i <= width && width != 0; i++) {
            if ((pos.y >= last_pos.y && pos.x >= last_pos.x) ||
                (pos.y <= last_pos.y && pos.x <= last_pos.x))
            {
                set_pixel (canvas, {i + begin_x, i * height / width + begin_y}, thickness, color);
            } else {
                set_pixel (canvas, {i + begin_x,(width - i) * height / width + begin_y}, thickness, color);
            }
        }
    }
    else
    {
        for (auto i = 0; i <= height && height != 0; i++) {
            if ((pos.y >= last_pos.y && pos.x >= last_pos.x) ||
                (pos.y <= last_pos.y && pos.x <= last_pos.x))
            {
                set_pixel (canvas, {begin_x + width * i / height, i + begin_y}, thickness, color);
            } else {
                set_pixel (canvas, {begin_x + width - width * i / height, i + begin_y}, thickness, color);
            }
        }
    }
}

void SprayPlugin::stop_apply(PluginAPI::Canvas canvas,
                             PluginAPI::Position pos) {
    Spray_Plugin::Color* color =
            reinterpret_cast<Spray_Plugin::Color*>(
                    &properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value);
    int thickness = properties[PluginAPI::TYPE::THICKNESS].int_value;
    draw_line (canvas, pos, thickness, *color);
}

void SprayPlugin::apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) {
    Spray_Plugin::Color* color =
            reinterpret_cast<Spray_Plugin::Color*>(
                    &properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value);
    int thickness = properties[PluginAPI::TYPE::THICKNESS].int_value;
    draw_line (canvas, pos, thickness, *color);
    last_pos = pos;
}

extern "C" PluginAPI::Plugin* get_plugin() {
    return PluginAPI::get_instance<SprayPlugin>();
}
