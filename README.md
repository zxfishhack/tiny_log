## Tiny Log Module for STM32 or other MCU

mirgrate from nginx

log format:
`Tick`(hex string, length: 8) `LogLevel`(char, [D|V|I|W|E|F]): `msg`

### Usage (cmake base Project)
1. add follow line
```
set(TINY_LOG_LEVEL LOG_INFO) # log level, default is all off
set(TINY_LOG_ENABLE_FLOAT 1) # optional, if you want to log float. (need about 3 kilobyte)
include(<path_to_tiny_log>/tiny_log.cmake)
```

2. append `${TINY_LOG_INCLUDE}` to `include_directories`

3. append `${TINY_SOURCES}` to source file

4. implement `uint32_t GetTick()` and `int PutChar(char ch)`

5. implement `TinyLogEnterHook()` and `TinyLogLeaveHook()` if concurrency.

### Details
1. for float (`%[w].[fw]f`), there will not output frac part when fw is not exist or zero.
2. log_ series MACRO are recommended when size is critical. all call that log level is less than setting will not link to target.
3. g_logLevel can be modify runtime log level.

### Flash & RAM Cost
```
cmake profile: Release
cmake options:
set(TINY_LOG_SECTION "tiny_log") // tiny
set(TINY_LOG_ENABLE_FLOAT ON)
gcc version: 
-- The C compiler identification is GNU 13.2.1
-- The CXX compiler identification is GNU 13.2.1
```
* Origin
```
Memory region         Used Size  Region Size  %age Used
             RAM:       10320 B        20 KB     50.39%
           FLASH:       34988 B        62 KB     55.11%
        TINY_LOG:          0 GB         2 KB      0.00%
```
* Using tiny_log (without float enable) [ RAM: +80B, Flash: +1,964B ]
```
Memory region         Used Size  Region Size  %age Used
             RAM:       10400 B        20 KB     50.78%
           FLASH:       36952 B        62 KB     58.20%
        TINY_LOG:        1292 B         2 KB     63.09%
```
* Using tiny_log (with float enable) [ RAM: +80B, Flash: +4,440B ]
```
Memory region         Used Size  Region Size  %age Used
             RAM:       10400 B        20 KB     50.78%
           FLASH:       39428 B        62 KB     62.10%
        TINY_LOG:        1852 B         2 KB     90.43%      