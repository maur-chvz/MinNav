import MinNavKit

if let newHandler = MinNav() {
    let handler = newHandler
    print(await handler.test())
    print("Client side!")
} else {
    print("Failed to create handler!")    
}

