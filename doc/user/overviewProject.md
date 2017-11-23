# Project overview

## Where

The aim of this project is to emulate two of the main components of NISP module of Euclid mission.
As said [before](../../README.md), Euclid is an ESA cosmic mission with the goal to understand the origin of universe acceleration studying dark energy and dark matter. To achieve this, a spacecraft is equipped with two telescopes (VIS and NISP) and will be sent to L2 Lagrangian zone in 2020. The NISP module is formed by three Near-IR photometer filters and a group of four grisms for the spectroscopic.
At the hardware level NISP is composed by:
- Payload module contains all mechanical instruments (including wheels to rotate above components) and all part of a *Detection System* (including sensors, heaters, calibration units, etc).
- Service modules including NI-ICU, the NISP Instrument Central Unit, defined mainly by DAS board and CDPU.

Data Acquisition System is used to manage filter wheel, grism wheel, and all data incoming from NI-DS; through SPI protocol receive commands about actuators, and send all information about these at the Central Data Processing Unit where is located CPU board with an IP core representative of the final LEON2 processor. RTERMS is chose as real time operating system.

## What

This is a parallel project out of Euclid mission that aims to emulate DAS, CDPU, sensors, and actuators behavior using SPI protocol as communication. 

## Why

Generally in astrophysics using narrow protocols during the entire missions' workflow, and all components are certified by authorities. If on the one hand this gives more security on the other hand can be required more funds, more time to develop some mission phases even if we have hardware technologically older. 
On Euclid mission works there are a lot of organizations located on entire occidental Europe. A part of the project is testing the application software on an NI-ICU emulator; this emulator doesn't have any spatial component, no radiates isolation, no physical sensors or actuators but just pre loaded values. Due to its cost there is only one of this element for entire european team.

So idea is: why not try to develop alternative and low cost hardware like NI-ICU emulator?

## How

Given that low cost technology grew up quickly in the last years, we want to develop a system entirely composed of an open-source hardware.
Original NI-ICU emulator has three FPGA: the first for CDPU, second for DAS board and last one to emulate sensor and actuators. Like real spacecraft hardware the first two FPGAs use SPI protocol for communication. 
Therefore, to recreate the system I want to use a Raspberry Pi to emulate CDPU, an Arduino for DAS board, stepper motors for wheels, LEDS, temperature and light components for sensors and actuators. Both main boards allow SPI protocol and RPI will be master and Arduino slave.

## References:
- [Ligori et al. Article](http://proceedings.spiedigitallibrary.org/proceeding.aspx?articleid=1894823)

Go back to [summary](../summary.md).

