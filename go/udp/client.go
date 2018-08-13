package main
import(
    "net"
    "fmt"
    "flag"
    "strconv"
    "strings"
    "github.com/zsy/udp/lib"
    //"bufio"
)
func handlePing(cid uint32,conn net.Conn){
    p:=lib.NewPing(cid)
    //w:=bufio.NewWriter(conn)
    p.WriteTo(conn)
    //conn.Write([]byte("hello"))
}
func handleRead(conn net.Conn, done chan string){
	buf := make([]byte, 1024)
	reqLen, err :=conn.Read(buf)
	if err != nil {
		fmt.Println("Error to read message because of ", err)
		done <-"Read"		
	}
	fmt.Printf("read %s\n",string(buf[:reqLen]))
	done <-"Read"   
}
func main(){
    addrF := flag.String("addr", "localhost:4244", "Address to dial")
    clientAddr:=flag.String("ca", "localhost", "Address to bind in client")
    flag.Parse()
    localIP:=net.ParseIP(*clientAddr)
    //conn, err := net.ListenUDP("udp", &net.UDPAddr{IP:localIP, Port: 0})
    bits := strings.Split(*addrF, ":")
    servIPString:=bits[0]
    servPort,_:=strconv.Atoi(bits[1])
    sIP := net.ParseIP(servIPString)
    lAddr := &net.UDPAddr{IP: localIP, Port:0}
    dstAddr := &net.UDPAddr{IP: sIP, Port:servPort}
    conn,_:= net.DialUDP("udp", lAddr, dstAddr)
    defer conn.Close()
    done := make(chan string)
    go handlePing(1,conn)
    go handleRead(conn, done)
    Loop:
    for{
        select{
            case sigstr:=<-done:
            if strings.Compare(sigstr,"Read")==0{
			break Loop;
            }
        }
    }
}

