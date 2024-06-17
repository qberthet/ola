Native FPGA AXI DMX Plugin
==========================

Work in progress...

## Config file: `ola-axidmx.conf`

`enabled = true`
Enable this plugin (DISABLED by default).

`device = /dev/dmx0`
The device to use for DMX output (optional). Multiple devices are supported
if the hardware exists.

### Per Device Settings (using above device name)

`<device>-break = 100`
The DMX break time in microseconds for this device (optional).

`<device>-malf = 100`
The Mark After Last Frame time in microseconds for this device (optional).
