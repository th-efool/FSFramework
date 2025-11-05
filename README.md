# FSFramework (Unreal Engine 5)

A modular Unreal Engine 5 plugin framework that separates Core, Gameplay, Game Framework, UI, and cross-cutting brokers into clean, reusable modules. The goal is fast prototyping and scalable game architecture with clear seams between systems.

## Highlights
- **Modular Plugins**: `FSCore`, `FSGameplay`, `FSGameFramework`, `FSUI`, `FSPlugin`
- **Broker Pattern**: World/GameInstance subsystems that centralize cross-system coordination
- **Context-aware Layers**: Menu, Lobby, Match flows with their own GameModes, States, Controllers, HUD/UI
- **Blueprint-friendly**: UENUM/USTRUCT/UCLASS across systems for easy extension
- **Clean Separation**: Core data/logging vs gameplay vs UI vs orchestration

## Module Architecture

### Diagrams

#### Triangle Overview
High-level relationship between `FSGameFramework` (top), `FSGameplay` (bottom-left), and `FSUI` (bottom-right), with `FSCore` below.

![FSFramework Triangle](./Docs/module-architecture.svg?raw=1)

#### Detailed Interactions
More granular module/broker layout and flows.

![FSFramework Detailed](./Docs/module-architecture-detailed.svg?raw=1)

If the images do not render in your viewer, open the SVGs directly:
- [Docs/module-architecture.svg](./Docs/module-architecture.svg)
- [Docs/module-architecture-detailed.svg](./Docs/module-architecture-detailed.svg)

### FSCore
- Purpose: foundational types, error handling, and data assets
- Key items:
  - `Data/FSBrokerDataTypes.h`: shared enums/structs for inter-module messaging
  - `FSGameDataAsset`: data asset hook for game configuration
  - `Utility/FSErrorHandler.h`: centralized logging with categories `FS_Log_Debug/Info/Warn/Error/Fatal`

### FSGameFramework
- Purpose: the Unreal game-loop roles and scenario-specific orchestration
- Base classes: `FSGameModeBase`, `FSGameStateBase`, `FSPlayerControllerBase`, `FSPlayerStateBase`
- Scenarios:
  - `Menu/*`: menu mode/state/controller and broker
  - `Lobby/*`: lobby equivalents and `FSLobbyGameFrameworkBroker`
  - `Match/*` (+ `Match/Coop/*`): match mode/state/controller, plus broker for match-specific routing

### FSGameplay
- Purpose: world-facing gameplay systems, actors, and interfaces
- Systems:
  - `UFSGameplayBroker : UWorldSubsystem` — gameplay hub for world-level coordination
  - `UFSEventManager : UWorldSubsystem` — event routing within a world
  - `UFSGameDataSubsystem : UGameInstanceSubsystem` — game-wide data access
- Interfaces: `IFSPlayer`, `IFSInteract`, `IFSFlicker`
- Actors/Examples: `AFSCharacterBase`, `AFlickerLightActorBase`, `AInteractableActorBase`

### FSUI
- Purpose: HUD/widgets and UI brokers mapped to gameplay contexts
- Base: `AFSHUDBase`, `UFSHUDWidgetBase`, `UFSUserWidgetBase`, `UFSMenuWidgetBase`, `UFSComponentWidgetBase`, `UFSPlayerUIComponent`
- Brokers: `UFSUIBrokerBase : UWorldSubsystem`, specialized `UFS(Lobby|Match|Menu)UIBroker`
- Context UIs:
  - Menu: `AFSMenuHUD`, `UFSMainMenuWidget`, `UFSHostJoinWidget`
  - Lobby: `AFSLobbyHUD`, `UFSLobbyHUDWidget`, components (player list, etc.)
  - Match: `AFSMatchHUD`, `UFSMatchHUDWidget`, play/death/end screens and components

### FSPlugin (Cross-cutting Brokers)
- Purpose: high-level orchestration linking modules and lifecycle
- `UFSGameInstanceBroker : UGameInstanceSubsystem`
- `UFSWorldBroker : UWorldSubsystem`

## Repository Layout
- Project entry: `Source/FSFramework`
- Plugin: `Plugins/FSPlugin/Source`
  - `FSCore`, `FSGameplay`, `FSGameFramework`, `FSUI`, `FSPlugin`
- Content: example maps and assets under `Plugins/FSPlugin/Content` and project `Content/`

## Getting Started

### Prerequisites
- Unreal Engine 5.x (tested with UE5)
- Windows 10/11 (current project files are for Win64)

### Open/Build
1. Double-click `FSFramework.uproject` to open in Unreal Editor.
2. If prompted, allow the Editor to build the modules.
3. Alternatively, generate project files and build via Visual Studio:
   - Right-click the `.uproject` → Generate Visual Studio project files
   - Build the solution `FSFramework.sln` (Debug/Development Editor, Win64)

### Enable the Plugin
The plugin is already embedded under `Plugins/FSPlugin`. If needed, toggle in Editor: Edit → Plugins → search for "FSPlugin".

## Usage Concepts

### Brokers (the hub pattern)
- GameInstance-level: `UFSGameInstanceBroker` handles app-wide state and services
- World-level: `UFSWorldBroker`, `UFSGameplayBroker`, and UI brokers coordinate per-world systems
- Benefits: decoupled systems call into a broker instead of hard-referencing each other

Typical flow:
- GameMode initializes context (Menu/Lobby/Match)
- Context Broker wires up: gameplay systems, HUD/UI broker, and event subscriptions
- UI widgets receive data via UI broker; gameplay actors publish events via `UFSEventManager`

### Contexts (Menu → Lobby → Match)
- Each context has its own GameMode/GameState/PlayerController/PlayerState and UI
- Swap contexts by loading the appropriate map (e.g., MenuMap, LobbyMap, MatchMap)
- Each context broker handles lifecycle glue for that context

### Extending Gameplay
1. Create a new interface or system under `FSGameplay/Public/Systems`
2. Register with `UFSGameplayBroker` or subscribe to `UFSEventManager`
3. Expose Blueprint types (UENUM/USTRUCT/UCLASS) where useful

### Extending UI
1. Add a widget deriving from `UFSHUDWidgetBase` or `UFSComponentWidgetBase`
2. Update the relevant context HUD (`AFS(Menu|Lobby|Match)HUD`) to compose it
3. Route data via the context `UFS(UI|Lobby|Match)UIBroker`

### Data & Logging
- Centralize shared enums/structs in `FSCore` under `Data/`
- Use `FSErrorHandler` categories (`FS_Log_*`) for consistent logging across modules

## Code Entry Points
- `IMPLEMENT_PRIMARY_GAME_MODULE(..., FSFramework, "FSFramework")` — project entry
- `IMPLEMENT_MODULE(..., FSCore|FSGameplay|FSGameFramework|FSUI|FSPlugin)` — plugin module entries

## Example Scenarios
- Add a new Match HUD panel:
  - Create widget in `FSUI/Public/Match/Components`
  - Add to `UFSMatchHUDWidget` composition
  - Expose data via `UFSMatchUIBroker`
- Add a world interaction:
  - Implement `IFSInteract` on an actor (e.g., `AInteractableActorBase`)
  - Fire events through `UFSEventManager` and respond in systems subscribed via `UFSGameplayBroker`

## Roadmap & Future Prospects
- Networking: expand Lobby/Match brokers for session management, party/teams, replication helpers
- Save/Load: integrate persistent profiles and progression via `UFSGameDataSubsystem`
- AI/Actors: richer AI modules under `FSGameplay/Character/AI`
- UI/UX: data-driven HUD composition, theme/skin system, accessibility options
- Tools: in-editor panels for brokers, debug overlays, and event inspection
- Cross-platform: formalize build targets and platform-specific tweaks
- Testing: unit tests for brokers/systems, automated map smoke tests
- Documentation: API references per module and developer cookbook examples

## Contributing
1. Fork the repo, create a topic branch
2. Prefer small, focused PRs per module
3. Follow Unreal coding conventions; keep interfaces thin and responsibilities clear
4. Add minimal but meaningful comments for non-obvious rationale; avoid needless noise

## License
TBD (add a license file if you plan to accept external contributions).

---

If you have specific features in mind, open an issue describing the context (Menu/Lobby/Match), the broker(s) involved, and the desired data flow. This helps keep extensions aligned with the framework’s architecture.