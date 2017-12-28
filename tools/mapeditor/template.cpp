#include "{{ name }}.h"
#include "{{ tileset }}.h"

namespace {{ namespace }}::maps {

{% for layer in layers %}

const std::array<uint16_t, {{ tilemap|length }}> {{ name }}_raw_layer{{ loop.index0 }} = {
{% for row in tilemap|chunks(10) %}
    {% for elm in row -%}
        {{ '0x{0:02x}'.format(elm) }},
    {%- endfor %}

{% endfor %}
};
const auto {{ name }}_layer{{ loop.index0 }} = gba::graphics::Tilemap{{ '{' }}
    {{ name }}_raw_layer{{ loop.index0 }}
{{ '}' }};

{% endfor %}

const gba::graphics::Map {{ name }}{
    {{ tileset }},
{% for layer in layers %}
    {{ name }}_layer{{ loop.index0 }},
{% endfor %}
    {{ map_size }}
};

}
