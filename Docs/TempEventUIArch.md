                    Event
                      │
          ┌───────────┴───────────┐
          ↓                       ↓
 Application handlers       LayerStack
          │                 (reverse order)
          │                       │
 WindowClose / Resize             ↓
          │                   ImGuiLayer
          │                       ↓
          │                  SandboxLayer
          │
          └────── Engine-level handling