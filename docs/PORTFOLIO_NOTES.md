# Portfolio and reproducibility notes

- **Implementation:** Embedded C for Microchip PIC18F45K22, originally configured for the legacy C18 compiler.
- **Simulation:** Proteus schematic (`simulation/CarParking.pdsprj`) plus a prebuilt, unchanged firmware HEX (`firmware/CarParking.hex`).
- **Demonstration:** Recorded Proteus run in `media/parking-simulation-demo.mp4` and screenshots under `screenshots/`.
- **Credits:** Ahmad Mansour and Ziad Hamade (as identified in the original project overview). The original overview also contained student identification numbers, so those identifiers are intentionally excluded from this public portfolio copy.
- **Current validation:** The developer demonstrated a successful simulation run and fee calculation; source recompilation and operation on a clean second workstation are not independently verified.
- **Build notes:** Use an environment compatible with MPLAB X and the legacy C18 toolchain, or load the supplied HEX into Proteus without rebuilding.
- **Simulator license:** A licensed Proteus version with PIC18 and alphanumeric LCD VSM models is required. Proteus itself is not part of this repository.
