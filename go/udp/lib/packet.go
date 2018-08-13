package lib
import(
    "net"
)
// there is an interesting thing, if I put WriteTo in Packet interface,
// and the compiler would complain that the ping struct do not implement WriteTo fuction
// did not figure out why
type WriterAbstract interface {
    WriteTo(conn net.Conn) (n int64, err error)
}
type Packet interface{
	WriterAbstract
	Type() (byte)
}