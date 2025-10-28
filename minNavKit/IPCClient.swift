import Foundation

enum SocketError: Error {
    case failedToCreateSocket
    case failedToConnectToServer
}

public class IPCClient: UDSocket{
    func ping_test() {
        for _ in 1...10 {
            let msg = "PING"
            
            var bytes = write_so(msg)
            if bytes > 0 {
                print("Sent \(bytes) bytes to Server")
            }
            else {
                print("Failed to send data to server...")
            }
            
            var response: String = ""
            bytes = read_so(&response)
            if bytes > 0 {            
                print("Received \(bytes) bytes from Server...")
                print(response)
            }
            else {
                print("Failed to receive data from server...")
            }
        }
    }
}

public class UDSocket {
    let path = "/tmp/minnav.sock"
    let sockfd: Int32
    var addr: sockaddr_un
    
    func write_so(_ msg: String) -> Int {
        return Int(msg.withCString { write(sockfd, $0, strlen($0)) })            
    }
    
    func read_so(_ result: inout String) -> Int {
        var buff = [UInt8](repeating: 0, count: 1024)
        let bytes = read(sockfd, &buff, 1024)
        result = String(bytes: buff[0..<bytes], encoding: .utf8) ?? ""
        return bytes
    }


    func connect_socket() throws(SocketError) -> Void {
        let ret: Int32 = connect(sockfd,
                         withUnsafePointer(to: &addr) { $0.withMemoryRebound(to: sockaddr.self, capacity: 1) { $0 } },
                         socklen_t(MemoryLayout<sockaddr_un>.size))

        guard ret == 0 else {
            throw .failedToConnectToServer
        }
    }    

    init() throws(SocketError) {
        sockfd = socket(AF_UNIX, Int32(SOCK_STREAM.rawValue), 0)
        guard sockfd >= 0 else { throw .failedToCreateSocket  }

        addr = sockaddr_un()
        addr.sun_family = sa_family_t(AF_UNIX)
        strcpy(&addr.sun_path, path)                 
    }

    deinit {
        close(sockfd)
    }
}
