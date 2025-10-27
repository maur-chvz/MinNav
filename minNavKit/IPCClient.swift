import Foundation

public class IPCClient{}

public class UDSocket {
    let path = "/tmp/minnav.sock"
    let sockfd: Int32

    func test() {
        print("This is a test...")
    }
    
    func ping_test() {
        for _ in 1...10 {
            let msg = "PING"
            var bytes = Int(msg.withCString { write(sockfd, $0, strlen($0)) })
            if bytes > 0 {
                print("Sent \(bytes) bytes to Server")
            }
            else {
                print("Failed to send data to server...")
            }
            
            var buff = [UInt8](repeating: 0, count: 1024)
            bytes = read(sockfd, &buff, 1024)
            if bytes > 0 {
                let response = String(bytes: buff[0..<bytes], encoding: .utf8) ?? ""
                print("Received \(bytes) bytes from Server...")
                print(response)
            }
            else {
                print("Failed to receive data from server...")
            }
        }
    }
    
    init?() {
        sockfd = socket(AF_UNIX, Int32(SOCK_STREAM.rawValue), 0)
        guard sockfd >= 0 else { return nil }
        var addr = sockaddr_un()
        addr.sun_family = sa_family_t(AF_UNIX)
        strcpy(&addr.sun_path, path)
        
        let ret: Int32 = connect(sockfd, withUnsafePointer(to: &addr) { $0.withMemoryRebound(to: sockaddr.self, capacity: 1) { $0 } }, socklen_t(MemoryLayout<sockaddr_un>.size))
        guard ret == 0 else {
            close(sockfd)
            print("Failed to connect to Socket")
            return nil
        }     
    }

    deinit {
        close(sockfd)
    }
}
