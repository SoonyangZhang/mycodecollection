package lib
import (
    //"io"
    "bytes"
    "net"
)
type PID byte

const (
    p_con PID = iota // value --> 0
    p_ping              // value --> 1
    p_pong            // value --> 2
    p_discon           // value --> 3
)
type base struct{
    pid []byte
    cid []byte
    size []byte
    payload []byte
}
//w io.Writer
func (b *base)WriteTo(conn net.Conn)(int64,error){
	var bf bytes.Buffer

	// Write the Packet data to the buffer.
	bf.Write(b.pid)
	bf.Write(b.size)
	bf.Write(b.cid)
    bf.Write(b.payload)
	// Write the buffered data to the writer.
	n, err := conn.Write(bf.Bytes())

	// Return the result.
	return int64(n), err    
}
func (b* base)Type() byte{
    return b.pid[0]
}