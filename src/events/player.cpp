#include "events.hpp"

EventHandler playerConnect(alt::CEvent::Type::PLAYER_CONNECT, "player_connect", [](const alt::CEvent* ev) {
    py::list args;
    auto event = dynamic_cast<const alt::CPlayerConnectEvent*>(ev);
    args.append(event->GetTarget().Get());
    return args;
});