package lib
import(
    "unsafe"
	"encoding/binary"
)
type Ping struct{
    base
}
func NewPing(cid uint32) Packet{
    p:=&Ping{}
    p.pid=append(p.pid,byte(p_ping))
    b := make([]byte, 4)
    binary.BigEndian.PutUint32(b, cid)
    p.cid=append(p.cid,b...)
    var now uint32 
    now=uint32(GetMilliSeconds())
    a:=make([]byte, 4)
    binary.BigEndian.PutUint32(a, uint32(now))
    p.payload=append(p.payload,a...)
    var total uint32
    total=uint32(unsafe.Sizeof(now))
    c:=make([]byte, 4)
    binary.BigEndian.PutUint32(c,total)
    p.size=append(p.size,c...)
    return p
}