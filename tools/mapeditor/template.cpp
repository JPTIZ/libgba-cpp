#include "{{ name }}.h"
#include "{{ tileset }}.h"

namespace {{ namespace }}::maps {

{% for layer in layers %}

const std::array<uint16_t, {{ tilemap|length }}> raw_layer{{ loop.index0 }}_tilemap = {
{% for row in tilemap|chunks(10) %}
    {% for elm in row -%}
        {{ '0x{0:02x}'.format(elm) }},
    {%- endfor %}

{% endfor %}
};
const auto layer{{ loop.index0 }}_tilemap = gba::graphics::Tilemap{raw_layer{{ loop.index0 }}_tilemap};

{% endfor %}

const gba::graphics::Map {{ name }}{
    {{ tileset }},
{% for layer in layers %}
    layer{{ loop.index0 }}_tilemap,
{% endfor %}
    {{ map_size }}
};

}
