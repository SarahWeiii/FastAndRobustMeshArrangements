#pragma once
#include <array>
#include <vector>

namespace meshArrange
{

    class Mesh
    {
    public:
        std::vector<std::array<double, 3>> vertices;
        std::vector<std::array<int, 3>> indices;
        Mesh() {};
        Mesh(std::vector<std::array<double, 3>> _vertices, std::vector<std::array<int, 3>> _indices)
        {
            vertices = _vertices;
            indices = _indices;
        };
    };

    Mesh intersectionRemoval(Mesh const &input);

} // namespace meshArrange