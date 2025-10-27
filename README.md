Maps frameworks:

Background service (daemon) that handles location updates and routing
Swift API layer (framework) that client apps call into
Interprocess communication (IPC) between clients and daemon
Efficient, memory-aware design
Integration with performance logging and concurrency primitives


+----------------------+
| Client App (Swift)   |
|  - Calls MiniNav API |
+----------+-----------+
           |
           |   (IPC via UNIX domain sockets / protobuf)
           v
+----------------------+
| MiniNav Daemon (C)   |
|  - Handles routing   |
|  - Manages cache     |
|  - Sends updates     |
+----------------------+

--------------------

# Location Daemon (C)

-Runs as a background process.
-Maintains a “mock” GPS position that updates every N seconds (simulated movement).
-Handles IPC connections from clients (UNIX domain socket).
-Responds to requests like:
-"get_location" → returns latest coordinates
-"route_to:lat,lon" → runs a routing algorithm and sends ETA + path
-Add a small thread pool and queue system to practice concurrency control.

# Routing Engine (Swift)

Load a small static map graph (e.g., from OpenStreetMap export or hand-built JSON).

Implement Dijkstra or A* for shortest path routing.

Cache previous route results for reuse.
