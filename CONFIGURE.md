# Configuration for JSON files

## Introduction
This file covers the configuration of the `platforms.json` and the `computationHosts.json`. Given you installed **HICS** following to the [INSTALL](INSTALL.md) manual, those to files should be located in the `/etc/hics/` directory. This guide will assume all files are located accordingly to the [INSTALL](INSTALL.md) manual, so if you changed flags or paths during installation please check where those files are.

In the following, performance data (power consumption, time consumption, flops) is used. For this application to work, the performance of different hosts and platforms only needs to be in relative relation to each other because it is used by the placing algorithms. However, using the real performance data is advised if it can be obtained. In the details window of a classification, the estimated consumed power is displayed. This value is calculated according to the power consumption of the computation hosts specified in the `computationHosts.json` (See example below). So in order to have a real estimation of power consumption you need to put in the correct power consumption values in the JSON file.

## Use Case 1: Only local computations
If you only want your local system to run classifications, you need to specify one host. Open or create the `computationHosts.json` (by default there is only an example file which can be used as reference). The `name` of the host needs to be `"local"` to be recognized by the application. `power` needs to set to the power a host needs in milliwatts. `time` is set to the time a host needs to classify an image in milliseconds. 
### Example:
```json
{
  "computationHosts": [
    {
      "name" : "local",
      "power" : 24952,
      "time" : 150
    }
  ]
}
```

The platforms specified in the `platforms.json` depend on your system. There are four supported platform types: `CPU, GPU, CL_CPU, FPGA`. GPU and CL_CPU platforms are implemented via OpenCL. To check availability run the `clinfo` command. The FPGA obviously needs to run on an FPGA board. But except for the type the configuration of a platform is the same. 

### Attributes:
 - type: 				as described above
 - description: 		textual representation of the platform, used to display platform in GUI
 - uuid: 				unique identifier
 - power_consumption: 	power consumption of the platform in milliwatts
 - flops:				measurement for computational power of a platform

 The flops and power only need to be in relative relation to each other in order for the placement algorithms to work correctly.

### Example for CPU, CL_CPU and GPU:
```json
 {
  "platforms": [
    {
      "type" : "CPU",
      "description" : "Intel(R) Core(TM) i5-4590 CPU",
      "uuid" : "b2028294-081f-11e8-aea8-b7fc73961889",
      "power_consumption" : 1500.5,
      "flops" : 500
    },
    {
      "type" : "CL_CPU",
      "description" : "OpenCL CPU",
      "uuid" : "bf11cc38-081f-11e8-bba2-abd6db15b367",
      "power_consumption" : 500,
      "flops" : 1400
    },
    {
      "type" : "GPU",
      "description" : "OpenCL GPU",
      "uuid" : "bfec1397-34ea-0913-bc3f-194fab7c630b",
      "power_consumption" : 700,
      "flops" : 2000
    }
  ]
}
```

### Example for FPGA:
```json
 {
  "platforms": [
    {
      "type" : "FPGA",
      "description" : "Altera DE1-SOC",
      "uuid" : "af357ba0-7fab-1948-edf7-058fbc4ed516",
      "power_consumption" : 100,
      "flops" : 250
    }
  ]
}
```

## Use Case 2: Using the HICS-Server

Install **HICS** according to the [INSTALL](INSTALL.md) manual. The structure should be the same on the remote and local system. Set up the `platforms.json` as described in [Use Case 1](#use-case-1-only-local-computations), but remember to set up both server and local platforms. **It is necessary for all platforms of local and remote hosts to have unique uuids!** You should also make sure that their description is not the same to distinguish the platforms in the GUI.

Now you need to change the settings in the `computationHosts.json` of the local system where you want to execute the **HICS** application (the equivalent file does not need to set up on the server system).
The local computation host does not need changes. Next you need to specify a new host. The `name` of this host must be `"fpga"` to be recognized as a server. This derives from the communication interface being build for the FPGA board. `power` and `time` need to be set up relative to the local host. The last and new attribute you need is `host`, where the location of the server is specified. 

### Example for two computation hosts:
```json
{
  "computationHosts": [
    {
      "name" : "local",
      "power" : 24952,
      "time" : 150
    },
    {
      "name" : "fpga",
      "power" : 615,
      "time" : 10974,
      "host" : "XXX.XXX.XXX.XXX:PORT"
    }
  ]
}
```

Thats it, you should be good to go. If the server doesn't show up in the GUI, double check that the server is running and the host location specified in the JSON file matches the location of the server. If you still have trouble, you can run the application from the console, the logger tells you if an error occurs while reading the JSON file or while communicating with the remote system.

If you want to use more than one remote host, you need to change a few lines of code in the software. These steps are not covered in this guide.