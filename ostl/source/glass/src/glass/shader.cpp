#include "glass/shader.hpp"

namespace glass
{

    std::string shader::vertex() const
    {
        return R"(
            #version 450

            void main()
            {
                vec2 circumscribed_triangle = 4. * vec2(gl_VertexIndex & 1, (gl_VertexIndex >> 1) & 1) - 1.;
                gl_Position = vec4(circumscribed_triangle, 0.0, 1.0);
            }
        )";
    }

    std::string shader::fragment() const
    {
        return R"(
            #version 450

            layout(location = 0) out vec4 frag_color;

			layout(binding = 0) uniform uniform_variables
			{
				ivec2 res;
                float time;
			};

            void main()
            {
                vec2 position = .5 + .5 * (-res + 2. * gl_FragCoord.xy) / min(res.x, res.y);
                vec2 blue_center = .5 + .5 * sin(vec2(1.4142135623730951 * time, 0.6931471805599453 * time));
                frag_color = .05 * vec4(position, 0, 1.) + vec4(0., 0., pow(1.01 - .5*length(position - blue_center), 16), 0);
            }
        )";
    }

    std::uint64_t shader::uniform_data_size() const
    {
        return m_uniform_data_size > 0ull ? m_uniform_data_size : 256ull;
    }

    const std::vector<shader::uniform_data>& shader::list_uniform_data() const { return m_uniform_variables; }
}  // namespace glass