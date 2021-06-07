#pragma once

#include <main.h>
#include <PythonRuntime.h>

namespace Utils
{
    PythonResource* GetResourceFromFrame(PyFrameObject* frame);
    alt::MValue ValueToMValue(const py::object& arg);
    py::object MValueToValue(const alt::MValueConst& mValue);
    std::string GetTypeOfObject(const py::object& object);

    const std::vector<std::string> EventTypes{
            "NONE",

            "playerConnect",
            "playerDisconnect",

            "anyResourceStart",
            "anyResourceStop",
            "anyResourceError",

            "SERVER_SCRIPT_EVENT",
            "CLIENT_SCRIPT_EVENT",

            "metaChange",
            "syncedMetaChange",
            "streamSyncedMetaChange",
            "globalMetaChange",
            "globalSyncedMetaChange",

            "playerDamage",
            "playerDeath",
            "startFire",
            "explosion",
            "startProjectile",
            "weaponDamage",
            "vehicleDestroy",

            "checkpoint",
            "colshape",
            "playerEnterVehicle",
            "playerEnteringVehicle",
            "playerLeaveVehicle",
            "playerChangeVehicleSeat",
            "playerWeaponChange",

            "vehicleAttach",
            "vehicleDetach",
            "netOwnerChange",

            "removeEntity",
            "createBaseObject",
            "removeBaseObject",

            "dataNodeReceived",

            "consoleCommand",
    };
}


