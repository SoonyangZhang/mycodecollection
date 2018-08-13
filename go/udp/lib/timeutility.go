package lib
import(
    "time"
)
func GetMilliSeconds() int64{
	now := time.Now()
	nanos := now.UnixNano()
	millis := nanos / 1000000
	return millis
}
