#include "PythonResource.h"
#include "main.h"
#include "utils.h"

bool PythonResource::Start()
{
    alt::String mainFile = GetFullPath();

    std::string path = resource->GetPath().ToString();
    std::wstring escapedPath;
    escapedPath.assign(path.begin(), path.end());

    PySys_SetPath(escapedPath.c_str());

    FILE *fp = fopen(mainFile.CStr(), "r");
    bool crashed = PyRun_SimpleFile(fp, mainFile.CStr());
    return !crashed;
}
bool PythonResource::Stop()
{
    return true;
}

bool PythonResource::OnEvent(const alt::CEvent *ev)
{
    auto type = runtime->GetEventType(ev->GetType());
    if (runtime->GetEventArgs(type))
    {
        auto getter = GetEventList(ev, type);
        auto arguments = runtime->GetEventArgs(type)(ev);
        for (const auto &listener : getter)
        {
            try
            {
                listener(*arguments);
            }
            catch (py::error_already_set &e)
            {
                py::print(e.what());
            }
        }
    }
    else
    {
        for (const auto &listener : ServerEvents[type])
        {
            try
            {
                listener();
            }
            catch (py::error_already_set &e)
            {
                py::print(e.what());
            }
        }
    }
    return true;
}

void PythonResource::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{
    object->AddRef();
    objects.insert({object->GetType(), object});
}

void PythonResource::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{
    auto range = objects.equal_range(object->GetType());
    for (auto it = range.first; it != range.second; it++)
    {
        if (it->second == object)
        {
            objects.erase(it);
            break;
        }
    }
}

bool PythonResource::IsObjectValid(const alt::Ref<alt::IBaseObject> &object)
{
    auto range = objects.equal_range(object->GetType());
    for (auto it = range.first; it != range.second; it++)
        if (it->second == object)
            return true;
    for (const auto &player : Core->GetPlayers())
        if (player == object)
            return true;
    for (const auto &entity : Core->GetEntities())
        if (entity == object)
            return true;
    return false;
}

void PythonResource::AddEvent(const std::string &eventName, const py::function &eventFunc)
{
    ServerEvents[eventName].push_back(eventFunc);
}

void PythonResource::AddClientEvent(const std::string &eventName, const py::function &eventFunc)
{
    ClientEvents[eventName].push_back(eventFunc);
}

alt::String PythonResource::GetFullPath()
{
    alt::String path = resource->GetPath();
    alt::String fullPath = path + preferred_separator + resource->GetMain();
    return fullPath;
}

alt::MValue PythonResource::PythonFunction::Call(alt::MValueArgs args) const
{
    py::list funcArgs;
    for (const auto &arg : args)
    {
        funcArgs.append(Utils::MValueToValue(arg));
    }
    auto returnValue = func(*funcArgs);
    return Utils::ValueToMValue(returnValue);
}

bool PythonResource::MakeClient(alt::IResource::CreationInfo *info, alt::Array<alt::String> files)
{
    info->type = "js";
    return true;
}
