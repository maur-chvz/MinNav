
public actor MinNav { 
    let client: IPCClient
    
    public func currentLocation() async throws -> Coordinate {return Coordinate()}    
    // startLocationStream()
    
    public func test() -> String {
        do {
            try client.connect_socket()
            print("BEFORE PING TEST")
            client.ping_test()
            print("AFTER PING TEST")            
        } catch {
            print("Failed to connect to server")
        }
        
        return "Using and API..."
    }

    public init?() {
        guard let newClient = try? IPCClient() else {
            print("Failed to initialize...")       
            return nil
        }
        self.client = newClient        
    }

    func shutdown() {}
}
