#include <pybind11/pybind11.h>

#include "meshArrange.hpp"

namespace py = pybind11;

PYBIND11_MODULE(meshArrange, m) {
  m.doc() = "Self-intersection removal for triangle meshes";
  build_meshArrange(m);
}