package lib
import(
    "net"
    "fmt"
    "encoding/binary"
    "strconv"
    "strings"
)
func InetNtoA(ip int64) string {
    return fmt.Sprintf("%d.%d.%d.%d",
        byte(ip>>24), byte(ip>>16), byte(ip>>8), byte(ip))
}

 func IP4toInt(IPv4Addr net.IP) int64 {
         bits := strings.Split(IPv4Addr.String(), ".")

         b0, _ := strconv.Atoi(bits[0])
         b1, _ := strconv.Atoi(bits[1])
         b2, _ := strconv.Atoi(bits[2])
         b3, _ := strconv.Atoi(bits[3])

         var sum int64

         // left shifting 24,16,8,0 and bitwise OR

         sum += int64(b0) << 24
         sum += int64(b1) << 16
         sum += int64(b2) << 8
         sum += int64(b3)
         return sum
 }
func IntToBytes(i int) []byte {
    var buf = make([]byte, 4)
    binary.BigEndian.PutUint32(buf, uint32(i))
    return buf
}