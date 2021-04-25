#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace glass
{
    class shader
    {
    public:
        [[nodiscard]] std::string vertex() const;
        [[nodiscard]] std::string fragment() const;

        [[nodiscard]] std::uint64_t uniform_data_size() const;

        template<class type>
        shader& add_uniform(const type* p_variable)
        {
            m_uniform_variables.push_back({p_variable, sizeof(type)});
            m_uniform_data_size += sizeof(type);
            return *this;
        }

        using uniform_data = std::pair<const void*, std::uint64_t>;
        [[nodiscard]] const std::vector<uniform_data>& list_uniform_data() const;

    private:
        std::uint64_t m_uniform_data_size = 0ull;
        std::vector<uniform_data> m_uniform_variables;
    };
}  // namespace glass