#pragma once

#include <vector>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../../public/meshArrange.h"

namespace py = pybind11;

void build_meshArrange(py::module &m)
{
    auto PyMesh = py::class_<meshArrange::Mesh>(m, "Mesh");
    PyMesh.def(py::init<>())
          .def(py::init([](std::vector<std::array<double, 3>> vertices, std::vector<std::array<int, 3>> indices){
            return std::unique_ptr<meshArrange::Mesh>(new meshArrange::Mesh(vertices, indices));
          }))
          .def_readwrite("vertices", &meshArrange::Mesh::vertices)
          .def_readwrite("indices", &meshArrange::Mesh::indices);

    m.def("intersectRemoval", &meshArrange::intersectionRemoval, py::arg("mesh"));
}