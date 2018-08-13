package main
import (
	"flag"
	"fmt"
	"net"
	"os"
)
func main() {
    addrF := flag.String("addr", "localhost:4244", "Address to bind")
	flag.Parse()
	addr, err := net.ResolveUDPAddr("udp", *addrF)
	if err != nil {
		fmt.Println("Can't resolve address: ", err)
		os.Exit(1)
	}
	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		fmt.Println("Error listening:", err)
		os.Exit(1)
	}
	defer conn.Close()
	for {
		handleClient(conn)
	}
}
func handleClient(conn *net.UDPConn) {
	data := make([]byte, 1024)
	_, remoteAddr, err := conn.ReadFromUDP(data)
    fmt.Printf("a new connection\n")
	if err != nil {
		fmt.Println("failed to read UDP msg because of ", err.Error())
		return
	}
	conn.WriteToUDP([]byte("hello ok"), remoteAddr)
}