Kernel driver scpi-hwmon
========================

Supported chips:

 * Chips based on ARM System Control Processor Interface

   Addresses scanned: -

   Datasheet: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0922b/index.html

Author: Punit Agrawal <punit.agrawal@arm.com>

Description
-----------

This driver supports hardware monitoring for SoC's based on the ARM
System Control Processor (SCP) implementing the System Control
Processor Interface (SCPI). The following sensor types are supported
by the SCP:

  * temperature
  * voltage
  * current
  * power

The SCP interface provides an API to query the available sensors and
their values which are then exported to userspace by this driver.

Usage Notes
-----------

The driver relies on device tree node to indicate the presence of SCPI
support in the kernel. See
<<<<<<< HEAD
<<<<<<< HEAD
Documentation/devicetree/bindings/firmware/arm,scpi.yaml for details of the
=======
Documentation/devicetree/bindings/arm/arm,scpi.txt for details of the
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
Documentation/devicetree/bindings/firmware/arm,scpi.yaml for details of the
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
devicetree node.
