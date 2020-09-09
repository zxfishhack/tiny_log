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
* Origin
```
Memory region         Used Size  Region Size  %age Used
             RAM:       11336 B        20 KB     55.35%
           FLASH:       23660 B        64 KB     36.10%
```
* Using tiny_log (without float enable) [RAM: + 0B, Flash: + 608B]
```
Memory region         Used Size  Region Size  %age Used
             RAM:       11336 B        20 KB     55.35%
           FLASH:       24268 B        64 KB     37.03%
```
* Using tiny_log (with float enable) [RAM: + 0B, Flash: + 3,132B]
```
Memory region         Used Size  Region Size  %age Used
             RAM:       11336 B        20 KB     55.35%
           FLASH:       27400 B        64 KB     41.81%
```
* Using printf [RAM: + 1,456B, Flash: + 24,984B]
```
Memory region         Used Size  Region Size  %age Used
             RAM:       12792 B        20 KB     62.46%
           FLASH:       48644 B        64 KB     74.22%
```         