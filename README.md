# CampusGuard

Emergency-response coordination platform for a university campus.
COS 214 Practical 5, 2026. Team: Musa, Ancheen, Katlego.

## Running with Docker (required for demonstration)

```bash
docker compose up --build
```

This builds the image and starts the application in one step, as required
by the practical brief. Do not demo a locally-built binary instead.

## Building locally (for development)

```bash
make        # builds ./build/campusguard
make run    # builds and runs
make clean  # removes build artifacts
```

Requires a C++11 compiler. Built and tested with g++.

## Pattern map

| Pattern | Where |
|---|---|
| Command | `include/commands/`, `src/commands/` |
| Mediator | `include/incident/IncidentCoordinator.h` |
| Adapter | `include/adapter/` |
| Facade | `include/facade/EmergencyOperationsFacade.h` |
| State | `include/incident/IncidentState.h` |
| Observer | `include/observer/`, `Incident` (subject) |

## Team split

- **Musa** — Incident core, State, Mediator, Docker/build
- **Ancheen** — Commands, response units, Observer wiring
- **Katlego** — Adapter, Facade, subsystems

Testing (Valgrind, GDB) is a shared responsibility across all three.

## Directory structure

```
include/    - headers, organised by pattern/subsystem
src/        - implementations, mirrors include/
tests/      - test scenarios
docs/uml/   - class + sequence diagrams
docker/     - any supporting docker assets
```
