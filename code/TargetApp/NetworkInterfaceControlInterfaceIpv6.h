#ifndef NETWORKINTERFACECONTROLINTERFACEIPV6_H_
#define NETWORKINTERFACECONTROLINTERFACEIPV6_H_

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP6_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP6_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL, IP6 address multi-home index 0 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[2:0] = IP6 address multi-home index 0 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
		  3 If IP6 is configured on the network interface, unconfigure the IP6 default gateway using the IP6 address in
		    the IP6 default gateway configuration register.
		  4 If IP6 is configured on the network interface and a default gateway is not configured, configure a default
		    gateway to be IP6 address in the IP6 default gateway configuration register.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_MECHANISM_CONTROL, IP6 address allocation mechanism, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP6 address allocation mechanism. Valid values:
          1 Static
		  4 Stateless address autoconfiguration
	  A write to this register sets the IP6 address allocation mechanism and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. Stateless address autoconfiguration
	  cannot be enabled when there are multiple IP6 addresses statically configured on the interface. Static IPv6 addresses
	  with a multi-home index greater than zero must be unconfigured before stateless address autoconfiguration can be
	  configured. A read will read this register and it may not be the same as the configuration currently setup on the
	  network interface. The current configuration on the network interface can be read using the appropriate status register.
	  Enabling stateless address autoconfiguration will clear the IP6 address and subnet configuration registers.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_1, IP6 default gateway bytes 0..3, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 0 to 3.
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_2, IP6 default gateway bytes 4..7, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 4 to 7
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_3, IP6 default gateway bytes 8..11, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 8 to 11
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_4, IP6 default gateway bytes 12..15, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 12 to 15
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1, IP6 address multi-home index 0 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2, IP6 address multi-home index 0 bytes 4 ..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3, IP6 address multi-home index 0 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4, IP6 address multi-home index 0 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH, IP6 address multi-home index 0 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 0 prefix length
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_01, configuration control for IP6 address multi-home index 1, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = ip6 address multi-home index 1 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_01, IP6 address multi-home index 1 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_01, IP6 address multi-home index 1 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_01, IP6 address multi-home index 1 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_01, IP6 address multi-home index 1 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_01, IP6 address multi-home index 1 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 1 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_02, IP6 address multi-home index 2 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 2 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_02, IP6 address multi-home index 2 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_02, IP6 address multi-home index 2 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_02, IP6 address multi-home index 2 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_02, IP6 address multi-home index 2 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_02, IP6 address multi-home index 2 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 2 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_03, IP6 address multi-home index 3 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 multi-home index 3 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_03, IP6 address multi-home index 3 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_03, IP6 address multi-home index 3 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_03, IP6 address multi-home index 3 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_03, IP6 address multi-home index 3 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_03, IP6 address multi-home index 3 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 3 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_04, IP6 address multi-home index 4 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_04, IP6 address multi-home index 4 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_04, IP6 address multi-home index 4 bytes 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_04, IP6 address multi-home index 4 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_04, IP6 address multi-home index 4 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_04, IP6 address multi-home index 4 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 4 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_05, IP6 address multi-home index 5 prefix length, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 5 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_05, IP6 address multi-home index 5 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_05, IP6 address multi-home index 5 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_05, IP6 address multi-home index 5 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_05, IP6 address multi-home index 5 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_05, IP6 address multi-home 5 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 5 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_MECHANISM_CONTROL = 1,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_1 = 8,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_2 = 9,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_3 = 10,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_4 = 11,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1 = 16,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2 = 17,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3 = 18,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4 = 19,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH = 20,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_01 = 64,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_01 = 65,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_01 = 66,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_01 = 67,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_01 = 68,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_01 = 69,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_02 = 80,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_02 = 81,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_02 = 82,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_02 = 83,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_02 = 84,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_02 = 85,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_03 = 96,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_03 = 97,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_03 = 98,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_03 = 99,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_03 = 100,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_03 = 101,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_04 = 112,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_04 = 113,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_04 = 114,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_04 = 115,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_04 = 116,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_04 = 117,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_05 = 128,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_05 = 129,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_05 = 130,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_05 = 131,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_05 = 132,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_05 = 133,
	NETWORK_INTERFACE_PARAMS_IP6_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockIp6Config;

/*
 * The IPv6 virtual interfaces > 0 are the same as virtual interface 0 but only allow a single static IPv6 address.
 * Hence the parameters are the same as virtual interface 0 except many of them are reserved.
 */
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP6_CONFIG
/*
	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL, IP6 address multi-home index 0 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[2:0] = IP6 address multi-home index 0 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
		  3 If IP6 is configured on the network interface, unconfigure the IP6 default gateway using the IP6 address in
		    the IP6 default gateway configuration register.
		  4 If IP6 is configured on the network interface and a default gateway is not configured, configure a default
		    gateway to be IP6 address in the IP6 default gateway configuration register.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_MECHANISM_CONTROL, IP6 address allocation mechanism, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP6 address allocation mechanism. Valid values:
          1 Static
		  4 Stateless address autoconfiguration
	  A write to this register sets the IP6 address allocation mechanism and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. Stateless address autoconfiguration
	  cannot be enabled when there are multiple IP6 addresses statically configured on the interface. Static IPv6 addresses
	  with a multi-home index greater than zero must be unconfigured before stateless address autoconfiguration can be
	  configured. A read will read this register and it may not be the same as the configuration currently setup on the
	  network interface. The current configuration on the network interface can be read using the appropriate status register.
	  Enabling stateless address autoconfiguration will clear the IP6 address and subnet configuration registers.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_1, IP6 default gateway bytes 0..3, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 0 to 3.
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_2, IP6 default gateway bytes 4..7, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 4 to 7
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_3, IP6 default gateway bytes 8..11, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 8 to 11
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_4, IP6 default gateway bytes 12..15, rw, 0
	  Bits[31:0] = IP6 default gateway bytes 12 to 15
	  A write to this register sets the IP6 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP6 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1, IP6 address multi-home index 0 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2, IP6 address multi-home index 0 bytes 4 ..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3, IP6 address multi-home index 0 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4, IP6 address multi-home index 0 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH, IP6 address multi-home index 0 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 0 prefix length
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_01, configuration control for IP6 address multi-home index 1, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = ip6 address multi-home index 1 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_01, IP6 address multi-home index 1 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_01, IP6 address multi-home index 1 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_01, IP6 address multi-home index 1 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_01, IP6 address multi-home index 1 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_01, IP6 address multi-home index 1 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 1 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_02, IP6 address multi-home index 2 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 2 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_02, IP6 address multi-home index 2 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_02, IP6 address multi-home index 2 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_02, IP6 address multi-home index 2 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_02, IP6 address multi-home index 2 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_02, IP6 address multi-home index 2 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 2 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_03, IP6 address multi-home index 3 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 multi-home index 3 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_03, IP6 address multi-home index 3 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_03, IP6 address multi-home index 3 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_03, IP6 address multi-home index 3 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_03, IP6 address multi-home index 3 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_03, IP6 address multi-home index 3 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 3 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_04, IP6 address multi-home index 4 configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_04, IP6 address multi-home index 4 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_04, IP6 address multi-home index 4 bytes 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_04, IP6 address multi-home index 4 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_04, IP6 address multi-home index 4 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_04, IP6 address multi-home index 4 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 4 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_05, IP6 address multi-home index 5 prefix length, rw, 1
	  Bits[31:1] = Reserved
	  Bit[1:0] = IP6 address multi-home index 5 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip6 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the IP6 configuration on the network interface. This will not change the IP6 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the IP6 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an IP6 address
			and a valid prefix length. This operation is only permitted when the network interface does not already have an
			active IP6 configuration.
		  2 change IP6 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_05, IP6 address multi-home index 5 bytes 0..3, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 0 to 3
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_05, IP6 address multi-home index 5 byte 4..7, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 4 to 7
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_05, IP6 address multi-home index 5 bytes 8 to 11, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 8 to 11.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_05, IP6 address multi-home index 5 bytes 12 to 15, rw, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 12 to 15.
	  A write to this register sets the IP6 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_05, IP6 address multi-home 5 prefix length, rw, 0
	  Bits[31:0] = IP6 address multi-home index 5 prefix length.
	  A write to this register sets the IP6 prefix length configuration register and it will not be applied until the network
	  interface is configured by writing to the IP6 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
*/
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_MECHANISM_CONTROL = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_MECHANISM_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_1 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_1,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_2 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_2,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_3 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_3,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_4 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_DEFAULT_GATEWAY_4,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_01 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_02 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_03 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_04 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_CONTROL_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_CONTROL_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_1_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_1_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_2_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_2_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_3_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_3_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_4_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_4_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_05 = NETWORK_INTERFACE_PARAMS_IP6_CONFIG_ADDR_PREFIX_LENGTH_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceVirtualParamsSubBlockIp6Config;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP6_STATUS
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP6_STATUS
/*
	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL, IP6 address multi-home index 0 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 0 disabled
		  1 IP6 address multi-home index 0 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_MECHANISM_CONTROL, IP6 address allocation mechanism status, ro, 0
	  Bits[31:2] = Reserved
	  Bit[2:0] = IP6 address allocation mechanism status. Valid values:
          1 Static
		  4 Stateless address autoconfiguration

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_1, IP6 default gateway bytes 0..3 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_2, IP6 default gateway bytes 4..7 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 4 to 8 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_3, IP6 default gateway bytes 8..11 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 8 to 11 status

    + NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_4, IP6 default gateway bytes 12..15 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1, IP6 address multi-home index 0 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2, IP6 address multi-home index 0 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3, IP6 address multi-home index 0 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4, IP6 address multi-home index 0 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH, IP6 address multi-home index 0 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME, IP6 address multi-home index 0 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME, IP6 address multi-home index 0 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_01, IP6 address multi-home index 1 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 address multi-home index 1 control configuration status. Valid values:
		  0 IP6 address multi-home index 1 disabled
		  1 IP6 address multi-home index 1 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_01, IP6 address multi-home index 1 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_01, IP6 address multi-home index 1 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_01, IP6 address multi-home index 1 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_01, IP6 address multi-home index 1 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_01, IP6 address multi-home index 1 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 1 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_01, IP6 address multi-home index 1 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 1 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_01, IP6 address multi-home index 1 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 multi-home index 1 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_02, IP6 address multi-home index 2 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 2 disabled
		  1 IP6 address multi-home index 2 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_02, IP6 address multi-home index 2 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_02, IP6 address multi-home index 2 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_02, IP6 address multi-home index 2 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_02, IP6 address multi-home index 2 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_02, IP6 address multi-home index 2 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_02, IP6 address multi-home index 2 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_02, IP6 address multi-home index 2 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_03, IP6 address multi-home index 3 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 3 disabled
		  1 IP6 address multi-home index 3 enabled

	 + NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_03, IP6 address multi-home index 3 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_03, IP6 address multi-home index 3 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_03, IP6 address multi-home index 3 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_03, IP6 address multi-home index 3 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_03, IP6 address multi-home index 3 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_03, IP6 address multi-home index 3 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_03, IP6 address multi-home index 3 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_04, IP6 address multi-home index 4 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 4 disabled
		  1 IP6 address multi-home index 4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_04, IP6 address multi-home index 4 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 0 to 3 of address status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_04, IP6 address multi-home index 4 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 4 to 7 of address status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_04, IP6 address multi-home index 4 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 8 to 11 of address status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_04, IP6 address multi-home index 4 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 12 to 15 of address status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_04, IP6 address multi-home index 4 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4  prefix length of address status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_04, IP6 address multi-home index 4 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_04, IP6 address multi-home index 4 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_05, IP6 address multi-home index 5 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 5 disabled
		  1 IP6 address multi-home index 5 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_05, IP6 address multi-home index 5 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_05, IP6 address multi-home index 5 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_05, IP6 address multi-home index 5 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_05, IP6 address multi-home index 5 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_05, IP6 address multi-home index 5 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_05, IP6 address multi-home index 5 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_05, IP6 address multi-home index 5 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 preferred lifetime staus

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_06, IP6 address multi-home index 6 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 6 disabled
		  1 IP6 address multi-home index 6 enabled

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_06, IP6 address multi-home index 6 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 0 to 3 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_06, IP6 address multi-home index 6 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 4 to 7 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_06, IP6 address multi-home index 6 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 8 to 11 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_06, IP6 address multi-home index 6 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 12 to 15 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_06, IP6 address multi-home index 6 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_06, IP6 address multi-home index 6 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_06, IP6 address multi-home index 6 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 preferred lifetime status

    - NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_07, IP6 address multi-home index 7 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 7 disabled
		  1 IP6 address multi-home index 7 enabled

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_07, IP6 address multi-home index 7 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 0 to 3 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_07, IP6 address multi-home index 7 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 4 to 7 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_07, IP6 address multi-home index 7 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 8 to 11 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_07, IP6 address multi-home index 7 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 12 to 15 status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_07, IP6 address multi-home index 7 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 prefix length status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_07, IP6 addresss multi-home index 7 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 valid lifetime status

	- NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_07, IP6 address multi-home index 7 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_08, IP6 address multi-home index 8 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 8 disabled
		  1 IP6 address multi-home index 8 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_08, IP6 address multi-home index 8 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_08, IP6 address multi-home index 8 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_08, IP6 address multi-home index 8 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_08, IP6 address multi-home index 8 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_08, IP6 address multi-home index 8 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_08, IP6 address multi-home index 8 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_08, IP6 address multi-home index 8 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_09, IP6 address multi-home index 9 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 9 disabled
		  1 IP6 address multi-home index 9 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_09, IP6 address multi-home index 9 bytes 0..3 status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_09, IP6 address multi-home index 9 bytes 4..7 status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_09, IP6 address multi-home index 9 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 9 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_09, IP6 address multi-home index 9 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 9 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_09, IP6 address multi-home index 9 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_09, IP6 address multi-home index 9 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 multi-home index valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_09, IP6 address multi-home index 9 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 multihome index 9 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_10, IP6 address multi-home index 10 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 10 disabled
		  1 IP6 address multi-home index 10 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_10, IP6 address multi-home index 10 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_10, IP6 address multi-home index 10 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_10, IP6 address multi-home index 10 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_10, IP6 address multi-home index 10 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_10, IP6 address multi-home index 10 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_10, IP6 address multi-home index 10 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_10, IP6 address multi-home index 10 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_11, IP6 address multi-home index 11 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 11 disabled
		  1 IP6 address multi-home index 11 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_11, IP6 address multi-home index 11 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 11 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_11, IP6 address multi-home index 11 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 11 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_11, IP6 address multi-home index 11 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_11, IP6 address multi-home index 11 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_11, IP6 address multi-home index 11 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_11, IP6 address multi-home index 11 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_11, IP6 address multi-home index 11 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_12, IP6 address multi-home index 12 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 12 disabled
		  1 IP6 address multi-home index 12 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_12, IP6 address multi-home index 12 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_12, IP6 address multi-home index 12 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_12, IP6 address multi-home index 12 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index index 12 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_12, IP6 address multi-home index 12 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_12, IP6 address multi-home index 12 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_12, IP6 address multi-home index 12 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_12, IP6 address multi-home index 12 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_13, IP6 address multi-home index 13 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 13 disabled
		  1 IP6 address multi-home index 13 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_13, IP6 address multi-home index 13 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_13, IP6 address multi-home index 13 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_13, IP6 address multi-home index 13 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_13, IP6 address multi-home index 13 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_13, IP6 address multi-home index 13 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_13, IP6 address multi-home index 13 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_13, IP6 address multi-home index 13 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 preferred lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_14, IP6 address multi-home index 14 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 14 disabled
		  1 IP6 address multi-home index 14 enabled

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_14, IP6 address multi-home index 14 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 0 to 3 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_14, IP6 address multi-home index 14 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 4 to 7 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_14, IP6 address multi-home index 14 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 8 to 11 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_14, IP6 address multi-home index 14 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 12 to 15 status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_14, IP6 address multi-home index 14 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 prefix length status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_14, IP6 address multi-home index 14 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 valid lifetime status

	+ NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_14, IP6 address multi-home index 14 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 preferred lifetime status
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_MECHANISM_CONTROL = 1,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_1 = 8,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_2 = 9,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_3 = 10,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_4 = 11,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1 = 17,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2 = 18,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3 = 19,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4 = 20,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH = 21,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME = 22,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME = 23,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_01 = 64,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_01 = 65,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_01 = 66,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_01 = 67,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_01 = 68,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_01 = 69,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_01 = 70,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_01 = 71,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_02 = 80,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_02 = 81,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_02 = 82,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_02 = 83,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_02 = 84,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_02 = 85,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_02 = 86,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_02 = 87,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_03 = 96,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_03 = 97,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_03 = 98,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_03 = 99,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_03 = 100,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_03 = 101,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_03 = 102,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_03 = 103,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_04 = 112,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_04 = 113,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_04 =	 114,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_04 = 115,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_04 = 116,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_04 = 117,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_04 = 118,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_04 = 119,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_05 = 128,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_05 = 129,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_05 = 130,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_05 = 131,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_05 = 132,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_05 = 133,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_05 = 134,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_05 = 135,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_06 = 144,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_06 = 145,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_06 = 146,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_06 = 147,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_06 = 148,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_06 = 149,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_06 = 150,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_06 = 151,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_07 = 160,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_07 = 161,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_07 = 162,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_07 = 163,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_07 = 164,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_07 = 165,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_07 = 166,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_07 = 167,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_08 = 176,			/* Start of IPv6 dynamic addresses */
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_08 = 177,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_08 = 178,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_08 = 179,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_08 = 180,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_08 = 181,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_08 = 182,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_08 = 183,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_09 = 192,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_09 = 193,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_09 = 194,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_09 = 195,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_09 = 196,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_09 = 197,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_09 = 198,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_09 = 199,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_10 = 208,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_10 = 209,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_10 = 210,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_10 = 211,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_10 = 212,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_10 = 213,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_10 = 214,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_10 = 215,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_11 = 224,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_11 = 225,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_11 = 226,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_11 = 227,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_11 = 228,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_11 = 229,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_11 = 230,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_11 = 231,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_12 = 240,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_12 = 241,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_12 = 242,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_12 = 243,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_12 = 244,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_12 = 245,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_12 = 246,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_12 = 247,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_13 = 256,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_13 = 257,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_13 = 258,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_13 = 259,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_13 = 260,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_13 = 261,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_13 = 262,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_13 = 263,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_14 = 272,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_14 = 273,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_14 = 274,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_14 = 275,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_14 = 276,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_14 = 277,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_14 = 278,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_14 = 279,
	NETWORK_INTERFACE_PARAMS_IP6_STATUS_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockIP6Status;

/*
 * The IPv6 virtual interfaces > 0 are the same as virtual interface 0 but only allow a single static IPv6 address.
 * Hence the parameters are the same as virtual interface 0 except many of them are reserved.
 */

//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP6_STATUS
/*
	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL, IP6 address multi-home index 0 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 0 disabled
		  1 IP6 address multi-home index 0 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_MECHANISM_CONTROL, IP6 address allocation mechanism status, ro, 0
	  Bits[31:2] = Reserved
	  Bit[2:0] = IP6 address allocation mechanism status. Valid values:
          1 Static
		  4 Stateless address autoconfiguration

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_1, IP6 default gateway bytes 0..3 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_2, IP6 default gateway bytes 4..7 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 4 to 8 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_3, IP6 default gateway bytes 8..11 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 8 to 11 status

    + NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_4, IP6 default gateway bytes 12..15 status, ro, 0
	  Bits[31:0] = IP6 default gateway bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1, IP6 address multi-home index 0 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2, IP6 address multi-home index 0 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3, IP6 address multi-home index 0 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4, IP6 address multi-home index 0 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 0 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH, IP6 address multi-home index 0 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME, IP6 address multi-home index 0 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME, IP6 address multi-home index 0 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 0 preferred lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_01, IP6 address multi-home index 1 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 address multi-home index 1 control configuration status. Valid values:
		  0 IP6 address multi-home index 1 disabled
		  1 IP6 address multi-home index 1 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_01, IP6 address multi-home index 1 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_01, IP6 address multi-home index 1 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_01, IP6 address multi-home index 1 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_01, IP6 address multi-home index 1 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 1 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_01, IP6 address multi-home index 1 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 1 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_01, IP6 address multi-home index 1 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 1 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_01, IP6 address multi-home index 1 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 multi-home index 1 preferred lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_02, IP6 address multi-home index 2 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 2 disabled
		  1 IP6 address multi-home index 2 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_02, IP6 address multi-home index 2 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_02, IP6 address multi-home index 2 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_02, IP6 address multi-home index 2 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_02, IP6 address multi-home index 2 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 2 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_02, IP6 address multi-home index 2 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_02, IP6 address multi-home index 2 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_02, IP6 address multi-home index 2 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 2 preferred lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_03, IP6 address multi-home index 3 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 3 disabled
		  1 IP6 address multi-home index 3 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_03, IP6 address multi-home index 3 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_03, IP6 address multi-home index 3 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_03, IP6 address multi-home index 3 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_03, IP6 address multi-home index 3 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 3 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_03, IP6 address multi-home index 3 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_03, IP6 address multi-home index 3 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_03, IP6 address multi-home index 3 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 3 preferred lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_04, IP6 address multi-home index 4 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 4 disabled
		  1 IP6 address multi-home index 4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_04, IP6 address multi-home index 4 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 0 to 3 of address status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_04, IP6 address multi-home index 4 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 4 to 7 of address status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_04, IP6 address multi-home index 4 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 8 to 11 of address status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_04, IP6 address multi-home index 4 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 4 bytes 12 to 15 of address status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_04, IP6 address multi-home index 4 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4  prefix length of address status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_04, IP6 address multi-home index 4 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_04, IP6 address multi-home index 4 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 4 preferred lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_05, IP6 address multi-home index 5 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 5 disabled
		  1 IP6 address multi-home index 5 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_05, IP6 address multi-home index 5 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_05, IP6 address multi-home index 5 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_05, IP6 address multi-home index 5 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_05, IP6 address multi-home index 5 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 5 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_05, IP6 address multi-home index 5 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_05, IP6 address multi-home index 5 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_05, IP6 address multi-home index 5 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 5 preferred lifetime staus

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_06, IP6 address multi-home index 6 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 6 disabled
		  1 IP6 address multi-home index 6 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_06, IP6 address multi-home index 6 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_06, IP6 address multi-home index 6 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_06, IP6 address multi-home index 6 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_06, IP6 address multi-home index 6 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 6 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_06, IP6 address multi-home index 6 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_06, IP6 address multi-home index 6 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_06, IP6 address multi-home index 6 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 6 preferred lifetime status

    - NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_07, IP6 address multi-home index 7 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 7 disabled
		  1 IP6 address multi-home index 7 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_07, IP6 address multi-home index 7 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 0 to 3 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_07, IP6 address multi-home index 7 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 4 to 7 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_07, IP6 address multi-home index 7 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 8 to 11 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_07, IP6 address multi-home index 7 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 7 bytes 12 to 15 status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_07, IP6 address multi-home index 7 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 prefix length status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_07, IP6 addresss multi-home index 7 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 valid lifetime status

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_07, IP6 address multi-home index 7 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 7 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_08, IP6 address multi-home index 8 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 8 disabled
		  1 IP6 address multi-home index 8 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_08, IP6 address multi-home index 8 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_08, IP6 address multi-home index 8 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_08, IP6 address multi-home index 8 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_08, IP6 address multi-home index 8 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 8 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_08, IP6 address multi-home index 8 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_08, IP6 address multi-home index 8 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_08, IP6 address multi-home index 8 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 8 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_09, IP6 address multi-home index 9 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 9 disabled
		  1 IP6 address multi-home index 9 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_09, IP6 address multi-home index 9 bytes 0..3 status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_09, IP6 address multi-home index 9 bytes 4..7 status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_09, IP6 address multi-home index 9 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 9 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_09, IP6 address multi-home index 9 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 9 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_09, IP6 address multi-home index 9 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 9 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_09, IP6 address multi-home index 9 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 multi-home index valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_09, IP6 address multi-home index 9 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 multihome index 9 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_10, IP6 address multi-home index 10 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 10 disabled
		  1 IP6 address multi-home index 10 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_10, IP6 address multi-home index 10 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_10, IP6 address multi-home index 10 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_10, IP6 address multi-home index 10 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_10, IP6 address multi-home index 10 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 10 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_10, IP6 address multi-home index 10 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_10, IP6 address multi-home index 10 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_10, IP6 address multi-home index 10 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 10 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_11, IP6 address multi-home index 11 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 11 disabled
		  1 IP6 address multi-home index 11 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_11, IP6 address multi-home index 11 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 11 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_11, IP6 address multi-home index 11 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 11 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_11, IP6 address multi-home index 11 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_11, IP6 address multi-home index 11 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_11, IP6 address multi-home index 11 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_11, IP6 address multi-home index 11 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_11, IP6 address multi-home index 11 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 11 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_12, IP6 address multi-home index 12 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 12 disabled
		  1 IP6 address multi-home index 12 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_12, IP6 address multi-home index 12 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_12, IP6 address multi-home index 12 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_12, IP6 address multi-home index 12 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index index 12 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_12, IP6 address multi-home index 12 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 12 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_12, IP6 address multi-home index 12 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_12, IP6 address multi-home index 12 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_12, IP6 address multi-home index 12 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 12 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_13, IP6 address multi-home index 13 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 13 disabled
		  1 IP6 address multi-home index 13 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_13, IP6 address multi-home index 13 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_13, IP6 address multi-home index 13 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_13, IP6 address multi-home index 13 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_13, IP6 address multi-home index 13 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 13 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_13, IP6 address multi-home index 13 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_13, IP6 address multi-home index 13 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_13, IP6 address multi-home index 13 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 13 preferred lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_14, IP6 address multi-home index 14 control status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP6 enabled status. Valid values:
		  0 IP6 address multi-home index 14 disabled
		  1 IP6 address multi-home index 14 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_14, IP6 address multi-home index 14 bytes 0..3 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 0 to 3 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_14, IP6 address multi-home index 14 bytes 4..7 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 4 to 7 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_14, IP6 address multi-home index 14 bytes 8 to 11 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 8 to 11 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_14, IP6 address multi-home index 14 bytes 12 to 15 status, ro, 0
	  Bits[31:0]  = IP6 address multi-home index 14 bytes 12 to 15 status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_14, IP6 address multi-home index 14 prefix length status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 prefix length status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_14, IP6 address multi-home index 14 valid lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 valid lifetime status

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_14, IP6 address multi-home index 14 preferred lifetime status, ro, 0
	  Bits[31:0] = IP6 address multi-home index 14 preferred lifetime status
*/
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_MECHANISM_CONTROL = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_MECHANISM_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_1 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_1,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_2 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_2,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_3 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_3,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_4 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_DEFAULT_GATEWAY_4,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_01 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_02 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_03 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_04 =	NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_04 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_05 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_06 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_06,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_07 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_07,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_08,	/* Start of IPv6 dynamic addresses */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_08 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_08,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_09 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_09,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_10 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_10,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_11 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_11,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_12 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_12,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_13 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_13,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_CONTROL_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_CONTROL_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_1_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_1_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_2_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_2_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_3_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_3_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_4_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_4_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFIX_LENGTH_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_VALID_LIFETIME_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_14 = NETWORK_INTERFACE_PARAMS_IP6_STATUS_ADDR_PREFERRED_LIFETIME_14,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP6_STATUS_SUBBLOCK_END
} mmApiNetworkInterfaceVirtualParamsSubBlockIP6Status;


ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp6ConfigSet(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp6ConfigGet(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp6StatusSet(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp6StatusGet(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress, uint16 endAddress, uint32 *data);

#endif /* NETWORKINTERFACECONTROLINTERFACEIPV6_H_ */
