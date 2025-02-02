#include "classes/vector2.h"

py::dict Vector2::ToDict()
{
    py::dict dict;
    dict["x"] = x;
    dict["y"] = y;
    return dict;
}

py::list Vector2::ToList()
{
    py::list list;
    list.append(x);
    list.append(y);
    return list;
}

void RegisterVector2Class(const pybind11::module_ &m)
{
    auto pyClass = py::class_<Vector2>(m, "Vector2");
    pyClass.def(py::init([](float _x, float _y) { return Vector2(_x, _y); }));
    pyClass.def_readwrite("x", &Vector2::x);
    pyClass.def_readwrite("y", &Vector2::y);
    pyClass.def("__str__", &Vector2::ToString);

    pyClass.def("toDict", &Vector2::ToDict);
    pyClass.def("toList", &Vector2::ToList);
    pyClass.def("length", &Vector2::Length);
    pyClass.def("distance", &Vector2::Distance);

    pyClass.def("toDegrees", &Vector2::ToDegrees);
    pyClass.def("toRadians", &Vector2::ToRadians);
    pyClass.def("isInRange", &Vector2::IsInRange);

    pyClass.def("add", py::overload_cast<const double>(&Vector2::Add));
    pyClass.def("add", py::overload_cast<const py::list &>(&Vector2::Add));
    pyClass.def("add", py::overload_cast<const double, const double>(&Vector2::Add));
    pyClass.def("add", py::overload_cast<const Vector2 &>(&Vector2::Add));

    pyClass.def("div", py::overload_cast<const double>(&Vector2::Div));
    pyClass.def("div", py::overload_cast<const py::list &>(&Vector2::Div));
    pyClass.def("div", py::overload_cast<const double, const double>(&Vector2::Div));
    pyClass.def("div", py::overload_cast<const Vector2 &>(&Vector2::Div));

    pyClass.def("dot", py::overload_cast<const double>(&Vector2::Dot));
    pyClass.def("dot", py::overload_cast<const py::list &>(&Vector2::Dot));
    pyClass.def("dot", py::overload_cast<const double, const double>(&Vector2::Dot));
    pyClass.def("dot", py::overload_cast<const Vector2 &>(&Vector2::Dot));

    pyClass.def("sub", py::overload_cast<const double>(&Vector2::Sub));
    pyClass.def("sub", py::overload_cast<const py::list &>(&Vector2::Sub));
    pyClass.def("sub", py::overload_cast<const double, const double>(&Vector2::Sub));
    pyClass.def("sub", py::overload_cast<const Vector2 &>(&Vector2::Sub));

    pyClass.def("mul", py::overload_cast<const double>(&Vector2::Mul));
    pyClass.def("mul", py::overload_cast<const py::list &>(&Vector2::Mul));
    pyClass.def("mul", py::overload_cast<const double, const double>(&Vector2::Mul));
    pyClass.def("mul", py::overload_cast<const Vector2 &>(&Vector2::Mul));

    pyClass.def_property_readonly("zero", &Vector2::zero);
    pyClass.def_property_readonly("one", &Vector2::one);
    pyClass.def_property_readonly("up", &Vector2::up);
    pyClass.def_property_readonly("down", &Vector2::down);
    pyClass.def_property_readonly("left", &Vector2::left);
    pyClass.def_property_readonly("right", &Vector2::right);

    pyClass.def_property_readonly("postiveInfinity", &Vector2::positiveInfinity);
    pyClass.def_property_readonly("negativeInfinity", &Vector2::negativeInfinty);

    pyClass.def("negative", &Vector2::Negative);
    pyClass.def("normalize", &Vector2::Normalize);
    pyClass.def("angleTo", &Vector2::AngleTo);
    pyClass.def("angleToDegrees", &Vector2::AngleToDegrees);
}
