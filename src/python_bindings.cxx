#pragma once

#include <pybind11/pybind11.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"

namespace py = pybind11;
PYBIND11_MODULE(example, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);
}