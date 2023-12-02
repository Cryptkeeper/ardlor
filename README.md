# ardlor

Example project for controlling Light-O-Rama hardware using an Arduino Mega 2560 (`metaatmega2560`). Other Arduino boards, such as `Arduino Uno Rev3` can be used by replacing the pre-selected `HardwareSerial` reference to `Serial` from `Serial1`.

## Hardware

1. RS485 to TTL board, I selected a [DSD TECH SH-U12](https://www.amazon.com/gp/product/B07B667STP?ie=UTF8&psc=1)
2. A way to connect the RS485 to a RJ45 connector for use with Light-O-Rama hardware ([I used this](https://www.amazon.com/gp/product/B085DSSZSR?ie=UTF8&psc=1))

## Usage

See `main.cpp` for the initialization and loop logic. The project already takes care of the heartbeat loop used by Light-O-Rama to test network connectivity. When connected to hardware, an Arduino running the pre-provided code should see its green status LED indicator go from flashing green to solid green.

Two example effect function calls, `LOR::WriteFade` & `LOR::WriteIntensity`, are provided for producing LOR fade effects and setting the intensity of a specific circuit.

## See Also

Related projects:

- [liblightorama](https://github.com/Cryptkeeper/liblightorama) - unofficial LOR networking library
- [fplayer](https://github.com/Cryptkeeper/fplayer) - fseq file player for LOR hardware
- [lightorama-protocol](https://github.com/Cryptkeeper/lightorama-protocol) - reverse engineered LOR effect protocols
- [libtinyfseq](https://github.com/Cryptkeeper/libtinyfseq) - C fseq file decoding API

## License

See [LICENSE](LICENSE).
