# Proteus simulation: step-by-step

## Start

1. Open `simulation/CarParking.pdsprj` in Proteus 8.
2. Double-click **U1: PIC18F45K22**. Point **Program File** to the `firmware/CarParking.hex` in this repository. Save the setting.
3. Click the lower-left **Play** button and verify the simulation shows **ANIMATING**.

## Parking sequence

1. **FSR** — activate the arrival sensor input (RB0). The status display can change to **P**, indicating the password stage.
2. **Password** — use switches on **RB4–RB7** to represent hexadecimal `0x01`, or `0001` when read **RB7 → RB4**. The circuit uses grounded switches and PIC port pull-ups, so switch positions must match the resulting logic levels, not merely the drawn switch orientation.
3. **ENTER PASSWORD** — momentarily activate RB3. Correct password moves to entry-authorization behavior; an incorrect password is rejected. The source checks `PORTB >> 4` against `0x01`.
4. **BSR** — momentarily activate RB1 when the car enters; the program starts its timer behavior.
5. **Wait** — let the Proteus simulation run while the parking timer increments.
6. **LS** — activate RB2 at exit; the program calculates the parking charge and updates the LCD.
7. **Reset/stop** — stop and restart the simulation to try another scenario.

## Expected fee rule from the source

- Recorded count `<= 3`: no charge; LCD thanks the user.
- Recorded count `> 3`: amount is **count / 2** (integer or half-unit amount).
- Example shown in the supplied screenshot: **`PARKING FEE: 4.5 $ Thank you!`**.

## Troubleshooting

- **`Unable to open HEX file`**: open U1 properties and select the actual repository-local `firmware/CarParking.hex`.
- **`PIC18.DLL` / `LCDALPHA.DLL` failed to authorize**: the installed Proteus license does not authorize the required VSM models; use an appropriately licensed version.
- **`Real Time Simulation failed to start`**: resolve any red errors in Proteus Simulation Errors, especially missing HEX or missing model authorization.
- **Relay pins not modeled**: this is a model warning, distinct from fatal HEX and licensing errors.

The project was demonstrated running by its developer. If your simulator differs, the source and circuit may need compatible tool versions.
