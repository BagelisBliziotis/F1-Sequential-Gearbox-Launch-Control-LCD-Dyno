# F1 Sequential Gearbox + Launch Control + Physical Dyno Simulator

Desktop Formula 1 cockpit simulato built on Arduino Uno. Features a realistic sequential gearbox with paddle shifters, clutch interlock, launch control sequence, physical DC motor
16×2 LCD dashboard, RGB status LED, gear-indicator Leds (74HC595 register), and buzzer feedback.

#Features:
- *Sequential 8-speed gearbox(N-1-2-3-4-5-6-7) with servo gear indicator
- *Clutch-paddle interlock – must hold clutch to shift 
- *Rev-match protection – downshift denied above 8500 RPM
- *Missed-shift detection with buzzer and warning
- *Launch Control – hold both paddles + clutch → arm → release clutch → automatic RPM ramp + dyno spin-up
- *Physical DC motor d – speed-controlled "engine" that reacts to throttle + gear + launch
- *Real-time 16×2 LCD dashboard – Gear , RPM , Throttle % , Speed
- *RGB + 8-LED gear strip via shift register
- *Serial telemetry (9600 baud) for monitoring

#Components:
- Arduino Uno
- 16×2 LCD (4-bit mode)
- Servo (gear indicator)
- 74HC595 + 7 LEDs (gear strip)
- RGB LED (status)
- Passive buzzer
- 10kΩ Potentiometer (throttle)
- 3x push buttons (clutch + up + down paddles) with internal pull-ups
- DC motor + driver (dyno)
- Breadboard + jumper wires
- 
#What i learned:
This project taught me that millis() is essential for managing multiple systems at once. Running the sequential gearbox logic, launch control ramp, RPM simulation
and DC motor speed simultaneously. The state machine (clutch interlock, rev-match protection, launch sequence) depends on tracking elapsed time and making decisions
in the main loop every cycle. Cramming 14+ components on a single breadboard was the bigger challenge though  servo, LCD data lines, shift register pins
RGB LED, buttons, potentiometer, motor driver, and buzzer all competing for space. I had to wire methodically and test each subsystem before integration.
The DC motor control brought it all together speed ramping based on throttle, gear, and launch state made the dyno feel like a real engine responding to input.
By far the most satisfying and fullfilling project yet

