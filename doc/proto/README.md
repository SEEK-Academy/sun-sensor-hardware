# PROTOBUF

This directory contains Protocol Buffers (`.proto`) definitions used to serialize data exchanged between the onboard CubeSat firmware and the data visualization system. The main contract defines the structure and semantics of telemetry sent from the SunSensor module.

> [Documentation](https://protobuf.dev/)

> [Installation](https://protobuf.dev/installation/)

## Code Generation

To generate source code from the `.proto` file for your target language:

### C++
```bash
protoc -I=$version --cpp_out=$version/generated_models $version/sun_sensor_data.proto
```

### C#
```bash
protoc -I=$version --csharp_out=$version/generated_models $version/sun_sensor_data.proto
```
